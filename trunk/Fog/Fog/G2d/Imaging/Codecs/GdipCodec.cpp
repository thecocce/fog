// [Fog-G2d]
//
// [License]
// MIT, See COPYING file in package

// [Precompiled Headers]
#if defined(FOG_PRECOMP)
#include FOG_PRECOMP
#endif // FOG_PRECOMP

// [Guard]
#include <Fog/Core/C++/Base.h>
#if defined(FOG_OS_WINDOWS)

// [Dependencies]
#include <Fog/Core/Global/Init_p.h>
#include <Fog/Core/Math/Math.h>
#include <Fog/Core/OS/Library.h>
#include <Fog/Core/OS/WinCom.h>
#include <Fog/Core/Tools/ManagedString.h>
#include <Fog/Core/Tools/Stream.h>
#include <Fog/Core/Tools/String.h>
#include <Fog/G2d/Imaging/Codecs/GdipCodec_p.h>
#include <Fog/G2d/Imaging/Image.h>
#include <Fog/G2d/Imaging/ImageConverter.h>
#include <Fog/G2d/Imaging/ImageFormatDescription.h>
#include <Fog/G2d/OS/WinGdiPlus.h>

FOG_IMPLEMENT_OBJECT(Fog::GdipDecoder)
FOG_IMPLEMENT_OBJECT(Fog::GdipEncoder)

namespace Fog {

// ===========================================================================
// [Fog::GdiPlusImage - Format - Helpers]
// ===========================================================================

static uint32_t _GdipCodec_cvtFogFormatFromGpFormat(GpPixelFormat fmt)
{
  switch (fmt)
  {
    case GpPixelFormat1bppIndexed   : return IMAGE_FORMAT_I8       ;
    case GpPixelFormat4bppIndexed   : return IMAGE_FORMAT_I8       ;
    case GpPixelFormat8bppIndexed   : return IMAGE_FORMAT_I8       ;
    case GpPixelFormat16bppGrayScale: return IMAGE_FORMAT_RGB48    ;
    case GpPixelFormat16bppRGB555   : return IMAGE_FORMAT_RGB24    ;
    case GpPixelFormat16bppRGB565   : return IMAGE_FORMAT_RGB24    ;
    case GpPixelFormat16bppARGB1555 : return IMAGE_FORMAT_PRGB32   ;
    case GpPixelFormat24bppRGB      : return IMAGE_FORMAT_RGB24    ;
    case GpPixelFormat32bppRGB      : return IMAGE_FORMAT_XRGB32   ;
    case GpPixelFormat32bppARGB     : return IMAGE_FORMAT_PRGB32   ;
    case GpPixelFormat32bppPARGB    : return IMAGE_FORMAT_PRGB32   ;
    case GpPixelFormat48bppRGB      : return IMAGE_FORMAT_RGB48    ;
    case GpPixelFormat64bppARGB     : return IMAGE_FORMAT_PRGB64   ;
    case GpPixelFormat64bppPARGB    : return IMAGE_FORMAT_PRGB64   ;
    default                         : return IMAGE_FORMAT_NULL     ;
  }
}

static GpPixelFormat _GdipCodec_cvtGpFormatFromFogFormat(uint32_t fmt)
{
  switch (fmt)
  {
    case IMAGE_FORMAT_PRGB32   : return GpPixelFormat32bppPARGB ;
    case IMAGE_FORMAT_XRGB32   : return GpPixelFormat32bppRGB   ;
    case IMAGE_FORMAT_RGB24    : return GpPixelFormat24bppRGB   ;
    case IMAGE_FORMAT_A8       : return GpPixelFormat32bppPARGB ;
    case IMAGE_FORMAT_I8       : return GpPixelFormat8bppIndexed;
    case IMAGE_FORMAT_PRGB64   : return GpPixelFormat64bppPARGB ;
    case IMAGE_FORMAT_RGB48    : return GpPixelFormat48bppRGB   ;
    case IMAGE_FORMAT_A16      : return GpPixelFormat64bppPARGB ;
    default                    : return GpPixelFormatUndefined  ;
  }
}

// ===========================================================================
// [Fog::GdiPlusImage - Params - GUID]
// ===========================================================================

FOG_COM_DEFINE_GUID(GpEncoderQuality, 0x1d5be4b5, 0xfa4a, 0x452d, 0x9c, 0xdd, 0x5d, 0xb3, 0x51, 0x05, 0xe7, 0xeb);

// ===========================================================================
// [Fog::GdiPlusImage - Params - Helpers]
// ===========================================================================

static void _GdipCodec_clearCommonParams(GdipCommonParams* params, uint32_t streamType)
{
  memset(params, 0, sizeof(GdipCommonParams));

  switch (streamType)
  {
    case IMAGE_STREAM_JPEG:
      params->jpeg.quality = 90;
      break;
    case IMAGE_STREAM_PNG:
      break;
    case IMAGE_STREAM_TIFF:
      break;
  }
}

static err_t _GdipCodec_getCommonParam(const GdipCommonParams* params, uint32_t streamType, const ManagedStringW& name, Var& dst)
{
  // This means to continue property processing calling superclass.
  err_t err = (err_t)0xFFFFFFFF;

  switch (streamType)
  {
    case IMAGE_STREAM_JPEG:
      if (name == FOG_STR_(IMAGE_CODEC_quality))
      {
        return dst.setInt(params->jpeg.quality);
      }
      break;
    case IMAGE_STREAM_PNG:
      break;
    case IMAGE_STREAM_TIFF:
      break;
  }

  return err;
}

static err_t _GdipCodec_setCommonParam(GdipCommonParams* params, uint32_t streamType, const ManagedStringW& name, const Var& src)
{
  // This means to continue property processing calling superclass.
  err_t err = (err_t)0xFFFFFFFF;

  switch (streamType)
  {
    case IMAGE_STREAM_JPEG:
      if (name == FOG_STR_(IMAGE_CODEC_quality))
        return src.getInt(params->jpeg.quality, 0, 100);
      break;
    case IMAGE_STREAM_PNG:
      break;
    case IMAGE_STREAM_TIFF:
      break;
  }

  return err;
}

// ===========================================================================
// [Fog::GdipCodecProvider]
// ===========================================================================

static err_t getGdipEncoderClsid(WinGdiPlus* _gdip, const WCHAR* mime, CLSID* clsid)
{
  GpStatus status;
  GpImageCodecInfo* codecs = NULL;

  UINT i;
  UINT codecsCount;
  UINT codecsDataSize;

  err_t err = ERR_OK;

  status = _gdip->_GdipGetImageEncodersSize(&codecsCount, &codecsDataSize);
  if (status != GpOk)
  {
    err = ERR_IMAGE_GDIPLUS_ERROR;
    goto _End;
  }

  codecs = reinterpret_cast<GpImageCodecInfo*>(MemMgr::alloc(codecsDataSize));
  if (codecs == NULL)
  {
    err = ERR_RT_OUT_OF_MEMORY;
    goto _End;
  }

  status = _gdip->_GdipGetImageEncoders(codecsCount, codecsDataSize, codecs);
  if (status != GpOk)
  {
    err = ERR_IMAGE_GDIPLUS_ERROR;
    goto _End;
  }

  for (i = 0; i < codecsCount; i++)
  {
    if (wcscmp(codecs[i].MimeType, mime) == 0)
    {
      *clsid = codecs[i].Clsid;
      goto _End;
    }
  }

  // Shouldn't happen.
  err = ERR_IMAGEIO_INTERNAL_ERROR;

_End:
  if (codecs) MemMgr::free(codecs);
  return err;
}

GdipCodecProvider::GdipCodecProvider(uint32_t streamType)
{
  const WCHAR* gdipMime = NULL;

  // Supported codecs.
  _codecType = IMAGE_CODEC_BOTH;

  // Supported streams.
  _streamType = streamType;

  // Name of ImageCodecProvider.
  switch (_streamType)
  {
    case IMAGE_STREAM_JPEG:
      _name = FOG_STR_(IMAGE_FILE_JPEG);
      _gdipMime = L"image/jpeg";
      break;
    case IMAGE_STREAM_PNG:
      _name = FOG_STR_(IMAGE_FILE_PNG);
      _gdipMime = L"image/png";
      break;
    case IMAGE_STREAM_TIFF:
      _name = FOG_STR_(IMAGE_FILE_TIFF);
      _gdipMime = L"image/tiff";
      break;
  }

  // All GDI+ providers starts with "[GDI+]" prefix.
  _name.append(Ascii8("[GDI+]"));

  // Supported extensions.
  switch (_streamType)
  {
    case IMAGE_STREAM_JPEG:
      _imageExtensions.reserve(4);
      _imageExtensions.append(FOG_STR_(IMAGE_EXT_jpg));
      _imageExtensions.append(FOG_STR_(IMAGE_EXT_jpeg));
      _imageExtensions.append(FOG_STR_(IMAGE_EXT_jfi));
      _imageExtensions.append(FOG_STR_(IMAGE_EXT_jfif));
      break;
    case IMAGE_STREAM_PNG:
      _imageExtensions.reserve(1);
      _imageExtensions.append(FOG_STR_(IMAGE_EXT_png));
      break;
    case IMAGE_STREAM_TIFF:
      _imageExtensions.reserve(2);
      _imageExtensions.append(FOG_STR_(IMAGE_EXT_tif));
      _imageExtensions.append(FOG_STR_(IMAGE_EXT_tiff));
      break;
    default:
      FOG_ASSERT_NOT_REACHED();
  }
}

GdipCodecProvider::~GdipCodecProvider()
{
}

uint32_t GdipCodecProvider::checkSignature(const void* mem, size_t length) const
{
  // Note: GdiPlus proxy provider uses 14 as a base score. This is by one less
  // than all other providers based on external libraries (libpng, libjpeg,
  // libtiff) and reason is that when these external libraries are available
  // then they are used instead.
  if (!mem || length == 0) return 0;

  uint32_t score = 0;
  size_t i;

  // Mime data.
  static const uint8_t mimeJPEG[2]    = { 0xFF, 0xD8 };
  static const uint8_t mimePNG[8]     = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
  static const uint8_t mimeTIFF_LE[4] = { 0x49, 0x49, 0x00, 0x42 };
  static const uint8_t mimeTIFF_BE[4] = { 0x4D, 0x4D, 0x42, 0x00 };

  // Mime check.
  switch (_streamType)
  {
    case IMAGE_STREAM_JPEG:
      i = Math::min<size_t>(length, 2);
      if (memcmp(mem, mimeJPEG, i) == 0)
        score = Math::max<uint32_t>(score, 14 + ((uint32_t)i * 40));
      break;

    case IMAGE_STREAM_PNG:
      i = Math::min<size_t>(length, 8);
      if (memcmp(mem, mimePNG, i) == 0)
        score = Math::max<uint32_t>(score, 14 + ((uint32_t)i * 10));
      break;

    case IMAGE_STREAM_TIFF:
      i = Math::min<size_t>(length, 4);
      if (memcmp(mem, mimeTIFF_LE, i) == 0 || memcmp(mem, mimeTIFF_BE, i) == 0)
        score = Math::max<uint32_t>(score, 14 + ((uint32_t)i * 20));
      break;

    default:
      FOG_ASSERT_NOT_REACHED();
  }

  return score;
}

err_t GdipCodecProvider::createCodec(uint32_t codecType, ImageCodec** codec) const
{
  FOG_ASSERT(codec != NULL);

  WinGdiPlus* gdip = WinGdiPlus::get();
  if (FOG_IS_NULL(gdip))
    return ERR_IMAGE_GDIPLUS_NOT_LOADED;

  ImageCodec* c = NULL;
  switch (codecType)
  {
    case IMAGE_CODEC_DECODER:
      c = fog_new GdipDecoder(const_cast<GdipCodecProvider*>(this));
      break;
    case IMAGE_CODEC_ENCODER:
      c = fog_new GdipEncoder(const_cast<GdipCodecProvider*>(this));
      break;
    default:
      return ERR_RT_INVALID_ARGUMENT;
  }

  if (FOG_IS_NULL(c))
    return ERR_RT_OUT_OF_MEMORY;

  *codec = c;
  return ERR_OK;
}

// ===========================================================================
// [Fog::GdipDecoder - Construction / Destruction]
// ===========================================================================

GdipDecoder::GdipDecoder(ImageCodecProvider* provider) :
  ImageDecoder(provider),
  _istream(NULL),
  _gdip(WinGdiPlus::get()),
  _gpImage(NULL)
{
  _GdipCodec_clearCommonParams(&_params, _streamType);
}

GdipDecoder::~GdipDecoder()
{
}

// ===========================================================================
// [Fog::GdipDecoder - AttachStream / DetachStream]
// ===========================================================================

void GdipDecoder::attachStream(Stream& stream)
{
  WinCOM::makeIStream(&_istream, stream);
  base::attachStream(stream);
}

void GdipDecoder::detachStream()
{
  if (_gpImage != NULL)
  {
    _gdip->_GdipDisposeImage(_gpImage);
    _gpImage = NULL;
  }

  if (_istream != NULL)
  {
    _istream->Release();
    _istream = NULL;
  }

  base::detachStream();
}

// ===========================================================================
// [Fog::GdipDecoder - Reset]
// ===========================================================================

void GdipDecoder::reset()
{
  _GdipCodec_clearCommonParams(&_params, _streamType);
  ImageDecoder::reset();
}

// ===========================================================================
// [Fog::GdipDecoder - ReadHeader]
// ===========================================================================

err_t GdipDecoder::readHeader()
{
  // Do not read header more than once.
  if (_headerResult) return _headerResult;

  if (_istream == NULL) return ERR_RT_INVALID_HANDLE;

  GpStatus status = _gdip->_GdipLoadImageFromStream(_istream, &_gpImage);
  if (status != GpOk) return (_headerResult = ERR_IMAGE_GDIPLUS_ERROR);

  FOG_ASSERT(sizeof(UINT) == sizeof(int));
  _gdip->_GdipGetImageWidth(_gpImage, (UINT*)&_size.w);
  _gdip->_GdipGetImageHeight(_gpImage, (UINT*)&_size.h);
  _planes = 1;

  GpPixelFormat pf;
  _gdip->_GdipGetImagePixelFormat(_gpImage, &pf);

  _format = _GdipCodec_cvtFogFormatFromGpFormat(pf);
  _depth = ImageFormatDescription::getByFormat(_format).getDepth();

  return ERR_OK;
}

// ===========================================================================
// [Fog::GdipDecoder - ReadImage]
// ===========================================================================

err_t GdipDecoder::readImage(Image& image)
{
  err_t err = ERR_OK;

  if (_istream == NULL) return ERR_RT_INVALID_HANDLE;

  GpBitmap* bm = NULL;
  GpGraphics* gr = NULL;
  GpStatus status;

  // Read image header.
  if (readHeader() != ERR_OK) return _headerResult;

  // Don't read image more than once.
  if (isReaderDone()) return (_readerResult = ERR_IMAGE_NO_FRAMES);

  // Create image.
  if ((err = image.create(_size, _format)) != ERR_OK) return err;

  // Create GpBitmap that will share raster data with our image.
  status = _gdip->_GdipCreateBitmapFromScan0(
    (INT)image.getWidth(),
    (INT)image.getHeight(),
    (INT)image.getStride(),
    _GdipCodec_cvtGpFormatFromFogFormat(image.getFormat()),
    (BYTE*)image.getDataX(),
    &bm);
  if (status != GpOk) { err = ERR_IMAGE_GDIPLUS_ERROR; goto _End; }

  // Create GpGraphics context.
  status = _gdip->_GdipGetImageGraphicsContext((GpImage*)bm, &gr);
  if (status != GpOk) { err = ERR_IMAGE_GDIPLUS_ERROR; goto _End; }

  // Set compositing to source copy (we want alpha bits).
  status = _gdip->_GdipSetCompositingMode(gr, GpCompositingModeSourceCopy);
  if (status != GpOk) { err = ERR_IMAGE_GDIPLUS_ERROR; goto _End; }

  // Draw streamed image to GpGraphics context.
  status = _gdip->_GdipDrawImageI(gr, _gpImage, 0, 0);
  if (status != GpOk) { err = ERR_IMAGE_GDIPLUS_ERROR; goto _End; }

  // flush (this step is probably not necessary).
  status = _gdip->_GdipFlush(gr, GpFlushIntentionSync);
  if (status != GpOk) { err = ERR_IMAGE_GDIPLUS_ERROR; goto _End; }

_End:
  // Delete created Gdi+ objects.
  if (gr) _gdip->_GdipDeleteGraphics(gr);
  if (bm) _gdip->_GdipDisposeImage((GpImage*)bm);

  if (err == ERR_OK) updateProgress(1.0f);
  return (_readerResult = err);
}

// ===========================================================================
// [Fog::GdipDecoder - Properties]
// ===========================================================================

err_t GdipDecoder::_getProperty(const ManagedStringW& name, Var& dst) const
{
  err_t err = _GdipCodec_getCommonParam(&_params, _streamType, name, dst);
  if (err != (err_t)0xFFFFFFFF) return err;

  return base::_getProperty(name, dst);
}

err_t GdipDecoder::_setProperty(const ManagedStringW& name, const Var& src)
{
  err_t err = _GdipCodec_setCommonParam(&_params, _streamType, name, src);
  if (err != (err_t)0xFFFFFFFF) return err;

  return base::_setProperty(name, src);
}

// ===========================================================================
// [Fog::GdipEncoder - Construction / Destruction]
// ===========================================================================

GdipEncoder::GdipEncoder(ImageCodecProvider* provider) :
  ImageEncoder(provider),
  _istream(NULL),
  _gdip(WinGdiPlus::get())
{
  _GdipCodec_clearCommonParams(&_params, _streamType);
}

GdipEncoder::~GdipEncoder()
{
}

// ===========================================================================
// [Fog::GdipEncoder - AttachStream / DetachStream]
// ===========================================================================

void GdipEncoder::attachStream(Stream& stream)
{
  WinCOM::makeIStream(&_istream, stream);
  base::attachStream(stream);
}

void GdipEncoder::detachStream()
{
  if (_istream != NULL)
  {
    _istream->Release();
    _istream = NULL;
  }

  base::detachStream();
}

// ===========================================================================
// [Fog::GdipEncoder - Reset]
// ===========================================================================

void GdipEncoder::reset()
{
  _GdipCodec_clearCommonParams(&_params, _streamType);
  ImageEncoder::reset();
}

// ===========================================================================
// [Fog::GdipEncoder - WriteImage]
// ===========================================================================

err_t GdipEncoder::writeImage(const Image& image)
{
  Image tmp;
  if (image.isEmpty()) return ERR_IMAGE_INVALID_SIZE;

  err_t err = ERR_OK;
  if (_istream == NULL) return ERR_RT_INVALID_HANDLE;

  GpBitmap* bm = NULL;
  GpGraphics* gr = NULL;
  GpStatus status;

  CLSID encoderClsid;

  uint32_t fogFormat = image.getFormat();
  GpPixelFormat gpFormat = _GdipCodec_cvtGpFormatFromFogFormat(fogFormat);

  // Get GDI+ encoder CLSID.
  err = getGdipEncoderClsid(_gdip, reinterpret_cast<GdipCodecProvider*>(getProvider())->_gdipMime, &encoderClsid);
  if (FOG_IS_ERROR(err)) goto _End;

  if (_GdipCodec_cvtFogFormatFromGpFormat(gpFormat) != fogFormat)
  {
    // Create GpBitmap that will share raster data with the temporary image.
    tmp = image;
    err = tmp.convert(_GdipCodec_cvtFogFormatFromGpFormat(gpFormat));
    if (FOG_IS_ERROR(err)) goto _End;

    status = _gdip->_GdipCreateBitmapFromScan0(
      (INT)tmp.getWidth(),
      (INT)tmp.getHeight(),
      (INT)tmp.getStride(),
      gpFormat,
      (BYTE*)tmp.getData(),
      &bm);
  }
  else
  {
    // Create GpBitmap that will share raster data with the image.
    status = _gdip->_GdipCreateBitmapFromScan0(
      (INT)image.getWidth(),
      (INT)image.getHeight(),
      (INT)image.getStride(),
      gpFormat,
      (BYTE*)image.getData(),
      &bm);
  }
  if (status != GpOk) { err = ERR_IMAGE_GDIPLUS_ERROR; goto _End; }

  // Encoder parameters.
  {
    uint8_t paramsData[sizeof(GpEncoderParameters)];
    GpEncoderParameters* params = reinterpret_cast<GpEncoderParameters*>(paramsData);

    params->Count = 0;

    switch (_streamType)
    {
       case IMAGE_STREAM_JPEG:
        params->Count = 1;
        params->Parameter[0].Guid = GpEncoderQuality;
        params->Parameter[0].Type = GpEncoderParameterValueTypeLong;
        params->Parameter[0].NumberOfValues = 1;
        params->Parameter[0].Value = &_params.jpeg.quality;
        break;
    }

    status = _gdip->_GdipSaveImageToStream(
      (GpImage*)bm, _istream, &encoderClsid,
      // If there are no parameters then NULL pointer must be used instead.
      // This information can be found on MSDN. Windows Vista and Win7 will
      // return an error if (params.Count == 0).
      params->Count > 0 ? params : NULL);
  }

_End:
  // Delete created Gdi+ objects.
  if (bm) _gdip->_GdipDisposeImage((GpImage*)bm);

  if (err == ERR_OK) updateProgress(1.0f);
  return err;
}

// ===========================================================================
// [Fog::GdipEncoder - Properties]
// ===========================================================================

err_t GdipEncoder::_getProperty(const ManagedStringW& name, Var& dst) const
{
  err_t err = _GdipCodec_getCommonParam(&_params, _streamType, name, dst);
  if (err != (err_t)0xFFFFFFFF) return err;

  return base::_getProperty(name, dst);
}

err_t GdipEncoder::_setProperty(const ManagedStringW& name, const Var& src)
{
  err_t err = _GdipCodec_setCommonParam(&_params, _streamType, name, src);
  if (err != (err_t)0xFFFFFFFF) return err;

  return base::_setProperty(name, src);
}

// ===========================================================================
// [Init / Fini]
// ===========================================================================

FOG_NO_EXPORT void ImageCodecProvider_initGdip(void)
{
  ImageCodecProvider* provider;

  provider = fog_new GdipCodecProvider(IMAGE_STREAM_PNG);
  ImageCodecProvider::addProvider(provider);
  provider->deref();

  provider = fog_new GdipCodecProvider(IMAGE_STREAM_JPEG);
  ImageCodecProvider::addProvider(provider);
  provider->deref();

  provider = fog_new GdipCodecProvider(IMAGE_STREAM_TIFF);
  ImageCodecProvider::addProvider(provider);
  provider->deref();
}

} // Fog namespace

#endif // FOG_OS_WINDOWS