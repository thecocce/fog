// [Fog-Graphics Library - Private API]
//
// [License]
// MIT, See COPYING file in package

// For some IDEs to enable code-assist.
#include <Fog/Core/Build.h>

#if defined(FOG_IDE)
#include <Fog/Graphics/RasterEngine/Defs_C_p.h>
#endif // FOG_IDE

namespace Fog {
namespace RasterEngine {

// ============================================================================
// [Fog::RasterEngine::C - Composite - Lighten]
// ============================================================================

//! @internal
struct FOG_HIDDEN CompositeLightenC : public CompositeBaseFuncsC32<CompositeLightenC>
{
  enum { CHARACTERISTICS = OPERATOR_CHAR_LIGHTEN };

  static FOG_INLINE void prgb32_op_prgb32_32b(
    ByteSIMD::b32_1x2& dst0, ByteSIMD::b32_1x2 a0, ByteSIMD::b32_1x2 b0,
    ByteSIMD::b32_1x2& dst1, ByteSIMD::b32_1x2 a1, ByteSIMD::b32_1x2 b1)
  {
    uint32_t aa = ByteSIMD::b32_1x2GetB1(a1);
    uint32_t ba = ByteSIMD::b32_1x2GetB1(b1);

    uint32_t at0, at1;
    uint32_t bt0, bt1;

    ByteSIMD::b32_2x2MulDiv255U(at0, a0, ba, at1, a1, ba);
    ByteSIMD::b32_2x2MulDiv255U(bt0, b0, aa, bt1, b1, aa);

    ByteSIMD::b32_2x2MaxB32_2x2(dst0, at0, bt0, dst1, at1, bt1);

    ByteSIMD::b32_2x2SubB32_2x2(at0, a0, at0, at1, a1, at1);
    ByteSIMD::b32_2x2SubB32_2x2(bt0, b0, bt0, bt1, b1, bt1);

    ByteSIMD::b32_2x2AddB32_2x2(dst0, dst0, at0, dst1, dst1, at1);
    ByteSIMD::b32_2x2AddB32_2x2(dst0, dst0, bt0, dst1, dst1, bt1);
  }

  static FOG_INLINE void prgb32_op_xrgb32_32b(
    ByteSIMD::b32_1x2& dst0, ByteSIMD::b32_1x2 a0, ByteSIMD::b32_1x2 b0,
    ByteSIMD::b32_1x2& dst1, ByteSIMD::b32_1x2 a1, ByteSIMD::b32_1x2 b1)
  {
    uint32_t aa = ByteSIMD::b32_1x2GetB1(a1);
    uint32_t bt0, bt1;

    ByteSIMD::b32_2x2MulDiv255U(bt0, b0, aa, bt1, b1, aa);

    ByteSIMD::b32_2x2MaxB32_2x2(dst0, a0, bt0, dst1, a1, bt1);
    ByteSIMD::b32_2x2SubB32_2x2(bt0, b0, bt0, bt1, b1, bt1);
    ByteSIMD::b32_2x2AddB32_2x2(dst0, dst0, bt0, dst1, dst1, bt1);

    ByteSIMD::b32_1x2FillB1(dst1, dst1);
  }

  static FOG_INLINE void xrgb32_op_prgb32_32b(
    ByteSIMD::b32_1x2& dst0, ByteSIMD::b32_1x2 a0, ByteSIMD::b32_1x2 b0,
    ByteSIMD::b32_1x2& dst1, ByteSIMD::b32_1x2 a1, ByteSIMD::b32_1x2 b1)
  {
    uint32_t ba = ByteSIMD::b32_1x2GetB1(b1);
    uint32_t at0, at1;

    ByteSIMD::b32_2x2MulDiv255U(at0, a0, ba, at1, a1, ba);

    ByteSIMD::b32_2x2MaxB32_2x2(dst0, at0, b0, dst1, at1, b1);
    ByteSIMD::b32_2x2SubB32_2x2(at0, a0, at0, at1, a1, at1);
    ByteSIMD::b32_2x2AddB32_2x2(dst0, dst0, at0, dst1, dst1, at1);

    ByteSIMD::b32_1x2FillB1(dst1, dst1);
  }

  static FOG_INLINE void xrgb32_op_xrgb32_32b(
    ByteSIMD::b32_1x2& dst0, ByteSIMD::b32_1x2 a0, ByteSIMD::b32_1x2 b0,
    ByteSIMD::b32_1x2& dst1, ByteSIMD::b32_1x2 a1, ByteSIMD::b32_1x2 b1)
  {
    ByteSIMD::b32_2x2MaxB32_2x2(dst0, a0, b0, dst1, a1, b1);
    ByteSIMD::b32_1x2FillB1(dst1, dst1);
  }
};

} // RasterEngine namespace
} // Fog namespace