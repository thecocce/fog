// [Fog-Core]
//
// [License]
// MIT, See COPYING file in package

// [Guard]
#ifndef _FOG_CORE_GLOBAL_ENUMERROR_H
#define _FOG_CORE_GLOBAL_ENUMERROR_H

// [Dependencies]
#include <Fog/Core/C++/Base.h>

namespace Fog {

//! @addtogroup Fog_Core_Global
//! @{

//! @brief Error codes used by Fog-Framework.
enum ERR_CODE
{
  // --------------------------------------------------------------------------
  // [Global/Ok]
  // --------------------------------------------------------------------------

  //! @brief Function proceed without errors (success).
  ERR_OK = 0,

  // --------------------------------------------------------------------------
  // [Global/Range]
  // --------------------------------------------------------------------------

  //! @brief First error code that can be used by Fog-Framework.
  _ERR_RANGE_FIRST = 0x00010000,
  //! @brief Last error code that can be used by Fog-Framework.
  _ERR_RANGE_LAST  = 0x0001FFFF,

  // --------------------------------------------------------------------------
  // [Global/Unknown]
  // --------------------------------------------------------------------------

  //! @brief Unknown error retrieved by the operating system.
  ERR_UNKNOWN = _ERR_RANGE_FIRST,

  // --------------------------------------------------------------------------
  // [Global/Run-Time]
  // --------------------------------------------------------------------------

  //! @brief Failed to allocate memory.
  ERR_RT_OUT_OF_MEMORY,

  //! @brief Failed to create a process.
  ERR_RT_OUT_OF_PROCESSES,
  //! @brief Failed to create a thread (or to get thread from a @c Fog::ThreadPool).
  ERR_RT_OUT_OF_THREADS,
  //! @brief Failed to create a lock.
  ERR_RT_OUT_OF_LOCKS,
  //! @brief Failed to create a semaphore.
  ERR_RT_OUT_OF_SEMAPHORES,

  //! @brief Assertion failure when running in release-mode.
  //!
  //! Please use issue tracker if you get this error, because it can be caused
  //! by your code or Fog-Framework itself. Fog never return this error code
  //! when compiled in debug-mode, instead the assertion is raised.
  //!
  //! @note When running under Windows and Windows error to Fog error translator 
  //! is used, the ERR_RT_ASSERTION_FAILURE is translated from the following
  //! Windows error codes:
  //!   - ERROR_ASSERTION_FAILURE,
  //!   - ERROR_WOW_ASSERTION.
  ERR_RT_ASSERTION_FAILURE,

  //! @brief Some code you wanted to use is not implemented yet.
  //!
  //! Please use issue tracker if the feature you need is not implemented yet.
  ERR_RT_NOT_IMPLEMENTED,

  //! @brief Invalid argument passed to the Fog-Framework function.
  //!
  //! If you encounter such error then it's problem on the your side and you
  //! should fix your code.
  ERR_RT_INVALID_ARGUMENT,

  //! @brief Invalid handle or file descriptor (shouldn't happen).
  ERR_RT_INVALID_HANDLE,

  //! @brief Invalid state.
  //!
  //! This is generic error which is returned if some object is accessed 
  //! improperly. Fog contains objects that wraps others (for example @ref
  //! Pattern). If the method to retrieve the current state of the instance
  //! is used improperly (for example getting a color, but the object is a
  //! linear gradient) then the @c ERR_RT_INVALID_STATE is returned.
  ERR_RT_INVALID_STATE,

  //! @brief Operation not permitted.
  ERR_RT_NOT_PERMITTED,
  //! @brief Access denied.
  ERR_RT_ACCESS_DENIED,

  //! @brief Resource or device is busy.
  ERR_RT_BUSY,
  //! @brief Resource or synchronization deadlock.
  ERR_RT_DEADLOCK,

  ERR_RT_OBJECT_NOT_FOUND,
  ERR_RT_OBJECT_ALREADY_EXISTS,

  //! @brief Object value cannot be converted to a finite number (@ref Var).
  ERR_RT_NOT_A_NUMBER,
  //! @brief Objects (@ref Var) are not compatible.
  ERR_RT_NOT_COMPATIBLE,
  //! @brief Overflow in integer or floating point arithmetic.
  ERR_RT_OVERFLOW,

  // --------------------------------------------------------------------------
  // [Core/Kernel]
  // --------------------------------------------------------------------------

  //! @brief Object is not part of a hierarchy.
  //!
  //! Tried to remove object from a bad ascendant.
  //!
  //! @note This is very likely a runtime error and should be reported.
  ERR_OBJECT_NOT_FOUND,

  //! @brief Object has already part of a different hierarchy.
  //!
  //! Tried to add object to another, but the object was already added to
  //! another else. You must first remove it from its current parent.
  //!
  //! @note This is very likely a runtime error and should be reported.
  ERR_OBJECT_HAS_PARENT,

  //! @brief Invalid property name/syntax.
  ERR_PROPERTY_INVALID,
  //! @brief Property not found.
  ERR_PROPERTY_NOT_FOUND,
  //! @brief Property is read-only.
  ERR_PROPERTY_READ_ONLY,

  // --------------------------------------------------------------------------
  // [Core/OS - Environment]
  // --------------------------------------------------------------------------

  ERR_ENVIRONMENT_NOT_FOUND,

  // --------------------------------------------------------------------------
  // [Core/OS - IO]
  // --------------------------------------------------------------------------

  ERR_NOT_A_BLOCK_DEVICE,
  ERR_DEVICE_NOT_FOUND,
  ERR_DEVICE_NOT_READY,
  ERR_DEVICE_READ_ONLY,
  ERR_DEVICE_FULL,
  ERR_DEVICE_FAILURE,
  ERR_DEVICE_MISMATCH,
  ERR_DEVICE_LOCKED,
  ERR_DEVICE_NOT_ATOMIC,
  ERR_DEVICE_FRAGMENTED,

  ERR_NOT_A_DIRECTORY,
  ERR_DIRECTORY_IN_USE,
  ERR_DIRECTORY_NOT_ROOT,
  ERR_DIRECTORY_NOT_EMPTY,

  ERR_NOT_A_FILE,
  ERR_FILE_NOT_FOUND,
  ERR_FILE_IS_EMPTY,
  ERR_FILE_LOCKED,
  ERR_FILE_END,
  ERR_FILE_TOO_LARGE,

  ERR_PATH_EXISTS,
  ERR_PATH_NAME_INVALID,
  ERR_PATH_NOT_FOUND,
  ERR_PATH_BAD_SYNTAX,

  ERR_IO_CANT_CREATE,
  ERR_IO_CANT_OPEN,
  ERR_IO_CANT_READ,
  ERR_IO_CANT_WRITE,
  ERR_IO_CANT_SEEK,
  ERR_IO_CANT_RESIZE,
  ERR_IO_CANT_TRUNCATE,

  ERR_SEEK_OUT_OF_RANGE,
  ERR_NON_SEEKABLE,
  ERR_INVALID_IOCTL,

  ERR_TOO_MANY_FILES,
  ERR_TOO_MANY_LINKS,

  ERR_PIPE_BUSY,
  ERR_PIPE_EMPTY,
  ERR_PIPE_LOCAL,
  ERR_PIPE_DISCONNECTED,
  ERR_PIPE_END,
  ERR_PIPE_INVALID,

  ERR_NOT_AN_EXECUTABLE,

  // --------------------------------------------------------------------------
  // [Core/OS - Library]
  // --------------------------------------------------------------------------

  ERR_LIBRARY_LOAD_FAILED,
  ERR_LIBRARY_TOO_MANY,
  ERR_LIBRARY_NO_SYMBOL,

  // --------------------------------------------------------------------------
  // [Core/OS - Process]
  // --------------------------------------------------------------------------

  ERR_PROCESS_NOT_FOUND,
  ERR_PROCESS_ARGUMENTS_TOO_LONG,
  ERR_NO_CHILD_PROCESS,

  // --------------------------------------------------------------------------
  // [Core/OS - UserUtil]
  // --------------------------------------------------------------------------

  ERR_USER_NO_DIRECTORY,

  // --------------------------------------------------------------------------
  // [Core/Tools - Date]
  // --------------------------------------------------------------------------

  ERR_DATE_INVALID,

  // --------------------------------------------------------------------------
  // [Core/Tools - Locale]
  // --------------------------------------------------------------------------

  ERR_LOCALE_NOT_FOUND,

  // --------------------------------------------------------------------------
  // [Core/Tools - String]
  // --------------------------------------------------------------------------

  //! @brief Invalid text input (converting strings to numbers).
  ERR_STRING_INVALID_INPUT,

  //! @brief Invalid text codec (Null) used to encode / decode string.
  ERR_STRING_INVALID_CODEC,

  //! @brief Invalid UTF-8 sequence.
  ERR_STRING_INVALID_UTF8,

  //! @brief Invalid UTF-16 sequence (surrogate pair error).
  ERR_STRING_INVALID_UTF16,

  //! @brief Invalid UCS-2 sequence (surrogate pair in UCS-2).
  ERR_STRING_INVALID_UCS2,

  //! @brief Invalid Unicode character.
  ERR_STRING_INVALID_CHAR,

  //! @brief Truncated (incomplete) input buffer.
  //!
  //! This error can be returned if you passed UTF-16 string to some function
  //! and the string ends with UTF-16 lead surrogate character.
  ERR_STRING_TRUNCATED,

  //! @brief Some characters lost during conversion (replaced by '?' or a given replacer).
  //!
  //! This can only happen when converting unicode to non-unicode encoding.
  ERR_STRING_LOST,

  // --------------------------------------------------------------------------
  // [Core/Threading - ThreadLocal]
  // --------------------------------------------------------------------------

  //! @brien Invalid TLS index catched by @c ThreadLocal.
  ERR_THREAD_TLS_INVALID,
  //! @brief TLS indices exhausted.
  ERR_THREAD_TLS_EXHAUSTED,

  // --------------------------------------------------------------------------
  // [Core/Xml]
  // --------------------------------------------------------------------------

  ERR_XML_INTERNAL,

  // XmlDom Errors.
  ERR_XML_DOCUMENT_INVALID_CHILD,
  ERR_XML_MANUPULATION_NOT_ALLOWED,
  ERR_XML_TAG_CHANGE_NOT_ALLOWED,
  ERR_XML_ATTRIBUTES_NOT_ALLOWED,
  ERR_XML_NOT_A_TEXT_NODE,
  ERR_XML_ATTRIBUTE_NOT_EXISTS,
  ERR_XML_ATTRIBUTE_CANT_BE_REMOVED,
  ERR_XML_INVALID_ATTRIBUTE,
  ERR_XML_CYCLIC,
  ERR_XML_INVALID_CHILD,
  ERR_XML_INVALID_TAG_NAME,
  ERR_XML_DOCUMENT_HAS_ALREADY_ROOT,

  // XmlSaxReader Errors.
  ERR_XML_NO_DOCUMENT,
  ERR_XML_MISSING_ROOT_TAG,
  ERR_XML_MISSING_TAG,
  ERR_XML_MISSING_ATTRIBUTE,
  ERR_XML_UNMATCHED_CLOSING_TAG,
  ERR_XML_UNCLOSED_CDATA,
  ERR_XML_UNCLOSED_PI,
  ERR_XML_UNCLOSED_COMMENT,
  ERR_XML_UNCLOSED_DOCTYPE,
  ERR_XML_SYNTAX_ERROR,

  ERR_XML_INVALID_CLOSING_TAG,

  // --------------------------------------------------------------------------
  // [G2d/Imaging]
  // --------------------------------------------------------------------------

  //! @brief Image format is invalid.
  ERR_IMAGE_INVALID_FORMAT,
  //! @brief Image type is invalid.
  ERR_IMAGE_INVALID_TYPE,
  //! @brief Image size is invalid.
  ERR_IMAGE_INVALID_SIZE,

  ERR_IMAGEIO_INTERNAL_ERROR,
  ERR_IMAGEIO_UNSUPPORTED_FORMAT,

  ERR_IMAGE_NO_DECODER,
  ERR_IMAGE_NO_ENCODER,
  ERR_IMAGE_NO_FRAMES,

  ERR_IMAGE_TERMINATED,
  ERR_IMAGE_TRUNCATED,

  ERR_IMAGE_MIME_NOT_MATCH,

  ERR_IMAGE_MALFORMED_STRUCTURE,
  ERR_IMAGE_MALFORMED_RLE,

  ERR_IMAGE_LIBJPEG_NOT_LOADED,
  ERR_IMAGE_LIBJPEG_ERROR,

  ERR_IMAGE_LIBPNG_NOT_LOADED,
  ERR_IMAGE_LIBPNG_ERROR,

  //! @brief Failed to load Gdi+ library (Windows).
  ERR_IMAGE_GDIPLUS_NOT_LOADED,

  //! @brief Call to Gdi+ library failed and resulting error can't be
  //! translated to the Fog one. This is a generic error.
  ERR_IMAGE_GDIPLUS_ERROR,

  // --------------------------------------------------------------------------
  // [G2d/Geometry]
  // --------------------------------------------------------------------------

  //! @brief No shape to work with.
  //!
  //! This may happen when some method is requested on an empty path or shape
  //! that is @c SHAPE_TYPE_NONE. If this error is returned then the output
  //! of the functions shouldn't be considered as correct. For example the
  //! bounding-box of shape which is invalid will be [0, 0, 0, 0], but it
  //! shouldn't be used/merged or analyzed, because the shape doesn't exist.
  ERR_GEOMETRY_NONE,

  //! @brief Invalid shape.
  //!
  //! This may happen if @c PathF or @c PathD contains invalid data (although
  //! this might be considered as the run-time error) or if some basic shape
  //! is incorrectly given (for example if @c RectF or @c RectD with or height
  //! is negative).
  ERR_GEOMETRY_INVALID,

  //! @brief The transform to be used is degenerated.
  //!
  //! The degenerated transform can't be used in geometry, because the result
  //! is simply nothing - for example rectange might degenerate to rectangle
  //! with zero width or height and it won't be painted. To prevent errors
  //! caused by degenerate transform use @c TransformF::isDegenerate() and
  //! @c TransformD::isDegenerate().
  //!
  //! @note This error is always related to transform.
  ERR_GEOMETRY_DEGENERATE,

  //! @brief Can't stroke the path or shape.
  ERR_GEOMETRY_CANT_STROKE,

  //! @brief It is required that a previous path command is a vertex,
  //!
  //! To add @c PATH_CMD_LINE_TO, @c PATH_CMD_QUAD_TO, @c PATH_CMD_CUBIC_TO or
  //! @c PATH_CMD_CLOSE the previous command must be a vertex. The only command
  //! that do not require such condition is @c PATH_CMD_MOVE_TO.
  ERR_PATH_NO_VERTEX,

  //! @brief The relative command can't be added, because the previous command
  //! is not a vertex.
  ERR_PATH_NO_RELATIVE,

  // --------------------------------------------------------------------------
  // [G2d/Painting]
  // --------------------------------------------------------------------------

  //! @brief Image format is not supported by the paint engine.
  //!
  //! The error can be misleading, but it can be returned by @c Painter::begin()
  //! where the image argument points to image that is using @c IMAGE_FORMAT_I8.
  //!
  //! Painter can be used only to paint into supported pixel formats (all RGB,
  //! ARGB and ALPHA-only pixel formats are supported).
  ERR_PAINTER_UNSUPPORTED_FORMAT,

  //! @brief Error that can be returned by painter if it's illegal to change
  //! paint engine at this time.
  //!
  //! This can happen if multithreaded or hardware accelerated painter is used
  //! and you want to switch to a different paint engine.
  //!
  //! @sa @c Painter::setEngine().
  ERR_PAINTER_NOT_ALLOWED,

  //! @brief There is not state to restore, might be caused by
  //! @ref Painter::restore().
  ERR_PAINTER_NO_STATE,

  // --------------------------------------------------------------------------
  // [G2d/Text]
  // --------------------------------------------------------------------------

  ERR_FONT_NOT_MATCHED,
  ERR_FONT_INVALID_FACE,
  ERR_FONT_INVALID_DATA,
  ERR_FONT_CANT_LOAD_DEFAULT_FACE,
  ERR_FONT_CANT_GET_OUTLINE,

  ERR_FONT_FONTCONFIG_NOT_LOADED,
  ERR_FONT_FONTCONFIG_INIT_FAILED,

  ERR_FONT_FREETYPE_NOT_LOADED,
  ERR_FONT_FREETYPE_INIT_FAILED,

  ERR_FONT_INTERNAL,

  // --------------------------------------------------------------------------
  // [Svg]
  // --------------------------------------------------------------------------
  //! @brief Invalid style name.
  ERR_SVG_INVALID_STYLE_NAME,
  //! @brief Invalid style value.
  ERR_SVG_INVALID_STYLE_VALUE,
  //! @brief Error set if svg embedded data are not in base64 format.
  ERR_SVG_INVALID_DATA_ENCODING,

  // --------------------------------------------------------------------------
  // [UI]
  // --------------------------------------------------------------------------

  //! @brief There is no gui engine available.
  ERR_UI_NO_ENGINE,
  ERR_UI_INTERNAL_ERROR,

  ERR_UI_CANT_CREATE_GUIENGINE,
  ERR_UI_CANT_CREATE_GUIWINDOW,

  ERR_UI_LIBX11_NOT_LOADED,
  ERR_UI_LIBEXT_NOT_LOADED,
  ERR_UI_LIBXRENDER_NOT_LOADED,

  ERR_UI_CANT_OPEN_DISPLAY,
  ERR_UI_CANT_CREATE_PIPE,
  ERR_UI_CANT_CREATE_COLORMAP,
  ERR_UI_CANT_TRANSLATE_COORDINATES,

  ERR_UI_CANT_CREATE_WINDOW,

  //! @brief Can't load native theme (UxTheme.dll).
  ERR_THEME_NATIVE_NOT_AVAILABLE,
  //! @brief Error happened during call to native theme (UxTheme.dll).
  ERR_THEME_NATIVE_ERROR
};

//! @}

} // Fog namespace

// [Guard]
#endif // _FOG_CORE_GLOBAL_ENUMERROR_H
