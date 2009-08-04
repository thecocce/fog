// [Fog/Graphics Library - C++ API]
//
// [Licence] 
// MIT, See COPYING file in package

// [Guard]
#ifndef _FOG_GRAPHICS_PALETTE_H
#define _FOG_GRAPHICS_PALETTE_H

// [Dependencies]
#include <Fog/Core/Atomic.h>
#include <Fog/Core/Memory.h>
#include <Fog/Core/Static.h>
#include <Fog/Graphics/Rgba.h>

//! @addtogroup Fog_Graphics
//! @{

namespace Fog {

// ============================================================================
// [Fog::Palette]
// ============================================================================

//! @brief Palette is array of 256 32-bit ARGB colors that can be used to 
//! define colors in 8 bit indexed images.
//!
//! Palette also contains 256 32-bit premultiplied colors that can be used to 
//! speed-up image blitting and compositing. These pixels are stored at index
//! 256 up to 511.
struct FOG_API Palette
{
  // [Indexes]

  enum Index
  {
    IndexARGB32 = 0,
    IndexPRGB32 = 256
  };

  // [Data]

  struct FOG_API Data
  {
    // [Ref / Deref]

    Data* ref() const;
    void deref();

    FOG_INLINE Data* refAlways() const
    {
      refCount.inc();
      return const_cast<Data*>(this);
    }

    // [Create]

    static Data* create();
    static Data* copy(const Data* other);

    // [Members]

    mutable Atomic<sysuint_t> refCount;

    Rgba data[512];
  };

  static Static<Data> sharedNull;
  static Static<Data> sharedGrey;

  // [Construction / Destruction]

  Palette();
  Palette(const Palette& other);
  explicit Palette(Data* d);
  ~Palette();

  // [Implicit Sharing]

  //! @copydoc Doxygen::Implicit::refCount().
  FOG_INLINE sysuint_t refCount() const { return _d->refCount.get(); }
  //! @copydoc Doxygen::Implicit::isDetached().
  FOG_INLINE bool isDetached() const { return refCount() == 1; }
  //! @copydoc Doxygen::Implicit::detach().
  FOG_INLINE err_t detach() { return (!isDetached()) ? _detach() : Error::Ok; }
  //! @copydoc Doxygen::Implicit::_detach().
  err_t _detach();
  //! @copydoc Doxygen::Implicit::free().
  void free();

  // [Data]

  //! @brief Returns const pointer to palette data.
  FOG_INLINE const Rgba* cData() const
  {
    return _d->data;
  }

  //! @brief Returns mutable pointer to palette data.
  //!
  //! @note If you change some data, you must call update() method.
  FOG_INLINE Rgba* mData()
  {
    return (detach() == Error::Ok) ? _d->data : NULL;
  }

  //! @brief Returns mutable pointer to palette data and not calls detach().
  //!
  //! @note If you change some data, you must call update() method.
  FOG_INLINE Rgba* xData()
  {
    FOG_ASSERT_X(isDetached(), "Fog::Palette::xData() - Non detached data.");
    return _d->data;
  }

  FOG_INLINE Rgba at(sysuint_t index) const
  { 
    FOG_ASSERT_X(index < 256, "Fog::Palette::at() - Index out of range.");
    return _d->data[index];
  }

  // [Operations]

  void clear();

  err_t set(const Palette& other);
  err_t setDeep(const Palette& other);

  //! @brief Set palette entries starting at index @a index to @a pal.
  err_t setRgba32(sysuint_t index, const Rgba* pal, sysuint_t count);

  //! @brief Set palette entries starting at index @a index to @a pal.
  err_t setRgb32(sysuint_t index, const Rgba* pal, sysuint_t count);

  //! @brief Set palette entries starting at index @a index to @a pal.
  //!
  //! Data format in @a pal is same as @c Image::FormatRGB24 (this means
  //! in BGR order on little endian machines and RGB order on big endian
  //! machines).
  err_t setRgb24(sysuint_t index, const uint8_t *pal, sysuint_t count);

  //! @brief Set palette entries starting at index @a index to @a pal.
  //!
  //! Data format in @a pal is in reversed order as @c Image::FormatRGB24
  //! (this means in RGB order on little endian machines and BGR order on
  //! big endian machines).
  err_t setBgr24(sysuint_t index, const uint8_t *pal, sysuint_t count);

  uint8_t findColor(uint8_t r, uint8_t g, uint8_t b) const;

  // [Changed]

  void update();

  // [Static Constructors]

  static Palette greyscale();
  static Palette colorCube(int r, int g, int b);

  // [Overloaded Operators]

  FOG_INLINE const Palette& operator=(const Palette& other)
  {
    set(other);
    return *this;
  }

  // [Statics]

  static bool isGreyOnly(const Rgba* data, sysuint_t count);

  // [Members]

  FOG_DECLARE_D(Data);
};

} // Fog namespace

//! @}

// [Guard]
#endif // _FOG_GRAPHICS_PALETTE_H
