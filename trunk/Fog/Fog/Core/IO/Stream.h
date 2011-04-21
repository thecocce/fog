// [Fog-Core]
//
// [License]
// MIT, See COPYING file in package

// [Guard]
#ifndef _FOG_CORE_IO_STREAM_H
#define _FOG_CORE_IO_STREAM_H

// [Dependencies]
#include <Fog/Core/Global/Constants.h>
#include <Fog/Core/Global/TypeInfo.h>
#include <Fog/Core/IO/FileSystem.h>
#include <Fog/Core/Tools/ByteArray.h>
#include <Fog/Core/Tools/String.h>

namespace Fog {

//! @addtogroup Fog_Core_IO
//! @{

// ============================================================================
// [Fog::StreamDevice]
// ============================================================================

//! @brief Stream device is interface used inside the Fog::Stream.
//!
//! It contains abstract virtual methods that can be reimplemented to make a
//! new stream device that can be used in all functions that needs Fog::Stream.
struct FOG_API StreamDevice
{
  // --------------------------------------------------------------------------
  // [Construction / Destruction]
  // --------------------------------------------------------------------------

  StreamDevice();
  virtual ~StreamDevice();

  // --------------------------------------------------------------------------
  // [Implicit Sharing]
  // --------------------------------------------------------------------------

  virtual StreamDevice* ref() const;
  virtual void deref();

  // --------------------------------------------------------------------------
  // [Abstract]
  // --------------------------------------------------------------------------

  virtual int64_t seek(int64_t offset, int whence) = 0;
  virtual int64_t tell() const = 0;

  virtual sysuint_t read(void* buffer, sysuint_t size) = 0;
  virtual sysuint_t write(const void* buffer, sysuint_t size) = 0;

  virtual err_t getSize(int64_t* size) = 0;
  virtual err_t setSize(int64_t size) = 0;
  virtual err_t truncate(int64_t offset) = 0;

  virtual void close() = 0;

  virtual ByteArray getBuffer() const;

  // --------------------------------------------------------------------------
  // [Members]
  // --------------------------------------------------------------------------

  mutable Atomic<sysuint_t> refCount;
  uint32_t flags;
};

// ============================================================================
// [Fog::Stream]
// ============================================================================

//! @brief Stream is IO stream implementation used in by Fog library.
struct FOG_API Stream
{
  // --------------------------------------------------------------------------
  // [Data]
  // --------------------------------------------------------------------------

  static StreamDevice* _dnull;

  // --------------------------------------------------------------------------
  // [Construction / Destruction]
  // --------------------------------------------------------------------------

  Stream();
  Stream(const Stream& stream);
  explicit Stream(StreamDevice* d);
  ~Stream();

  // --------------------------------------------------------------------------
  // [Implicit Sharing]
  // --------------------------------------------------------------------------

  FOG_INLINE sysuint_t getRefCount() const { return _d->refCount.get(); }

  // --------------------------------------------------------------------------
  // [Flags]
  // --------------------------------------------------------------------------

  FOG_INLINE uint32_t getFlags() const { return _d->flags; }

  FOG_INLINE bool isNull()     const { return _d == _dnull; }

  FOG_INLINE bool isOpen()     const { return (_d->flags & STREAM_IS_OPEN    ) != 0; }
  FOG_INLINE bool isSeekable() const { return (_d->flags & STREAM_IS_SEEKABLE) != 0; }
  FOG_INLINE bool isReadable() const { return (_d->flags & STREAM_IS_READABLE) != 0; }
  FOG_INLINE bool isWritable() const { return (_d->flags & STREAM_IS_WRITABLE) != 0; }
  FOG_INLINE bool isClosable() const { return (_d->flags & STREAM_IS_CLOSABLE) != 0; }

  FOG_INLINE bool isFile()     const { return (_d->flags & (STREAM_IS_FD | STREAM_IS_HFILE)) != 0; }
  FOG_INLINE bool isHFILE()    const { return (_d->flags & STREAM_IS_HFILE   ) != 0; }
  FOG_INLINE bool isFD()       const { return (_d->flags & STREAM_IS_FD      ) != 0; }
  FOG_INLINE bool isMemory()   const { return (_d->flags & STREAM_IS_MEMORY  ) != 0; }
  FOG_INLINE bool isGrowable() const { return (_d->flags & STREAM_IS_GROWABLE) != 0; }

  void setSeekable(bool seekable);

  // --------------------------------------------------------------------------
  // [Open]
  // --------------------------------------------------------------------------

  err_t openFile(const String& fileName, uint32_t openFlags);
  err_t openMMap(const String& fileName, bool loadOnFail = true);

#if defined(FOG_OS_WINDOWS)
  err_t openHandle(HANDLE hFile, uint32_t openFlags, bool canClose);
#endif // FOG_OS_WINDOWS

#if defined(FOG_OS_POSIX)
  err_t openFd(int fd, uint32_t openFlags, bool canClose);
#endif // FOG_OS_POSIX

  err_t openBuffer();
  err_t openBuffer(const ByteArray& buffer);
  err_t openBuffer(void* buffer, sysuint_t size, uint32_t openFlags);

  // --------------------------------------------------------------------------
  // [Seek / Tell]
  // --------------------------------------------------------------------------

  int64_t seek(int64_t offset, int whence);
  int64_t tell() const;

  // --------------------------------------------------------------------------
  // [Read / Write]
  // --------------------------------------------------------------------------

  sysuint_t read(void* buffer, sysuint_t size);
  sysuint_t read(ByteArray& dst, sysuint_t size);
  sysuint_t readAll(ByteArray& dst, sysuint_t maxBytes = 0);

  sysuint_t write(const void* buffer, sysuint_t size);
  sysuint_t write(const ByteArray& data);

  // --------------------------------------------------------------------------
  // [GetSize, SetSize, Truncate]
  // --------------------------------------------------------------------------

  err_t getSize(int64_t* size);
  err_t setSize(int64_t size);
  err_t truncate(int64_t offset);

  // --------------------------------------------------------------------------
  // [Close]
  // --------------------------------------------------------------------------

  void close();

  // --------------------------------------------------------------------------
  // [Stream Specific]
  // --------------------------------------------------------------------------

  //! @brief Get stream memory buffer. This method works only on memory streams.
  //!
  //! If stream was open by:
  //!   <core>openBuffer(void* buffer, sysuint_t size, uint32_t openFlags);</core>
  //! buffer will be created for it and data will be copied to this buffer.
  //!
  //! If stream was open by @c ByteArray instance, this method will return it.
  ByteArray getBuffer() const;

  // --------------------------------------------------------------------------
  // [Operator Overload]
  // --------------------------------------------------------------------------

  Stream& operator=(const Stream& other);

  // --------------------------------------------------------------------------
  // [Members]
  // --------------------------------------------------------------------------

  FOG_DECLARE_D(StreamDevice)
};

//! @}

} // Fog namespace

// ============================================================================
// [Fog::TypeInfo<>]
// ============================================================================

FOG_DECLARE_TYPEINFO(Fog::Stream, Fog::TYPEINFO_MOVABLE)

// [Guard]
#endif // _FOG_CORE_STREAM_H