// [Fog/Graphics Library - C++ API]
//
// [Licence] 
// MIT, See COPYING file in package

// For some IDEs to enable code-assist.
#include <Fog/Build/Build.h>
#if defined(FOG_IDE)
#include <Fog/Graphics/Raster/Raster_C.h>
#endif // FOG_IDE

namespace Fog {
namespace Raster {

// ============================================================================
// [Fog::Raster_SSE2 - Defines]
// ============================================================================

#define READ_8(ptr)  (((const uint8_t *)(ptr))[0])
#define READ_16(ptr) (((const uint16_t*)(ptr))[0])
#define READ_32(ptr) (((const uint32_t*)(ptr))[0])

// These macros were designed to simplify blit functions. The idea is very simple.
// There are usually three loops that you can see in blitters. One is align loop.
// The align loop wants to align data into 16 bytes. When aligning is done, the
// main loop is run and it usually uses 16 byte increments (so 4 ARGB pixels).
// The reason for third loop (tail loop) is that it's needed to process remaining
// pixels that can't fit into main loop.
//
// There is idea to merge align and tail loop into one loop. This will save some
// library binary size (about 1/4 size of blitting functions) and simplify the
// development. So to not repeat dirty stuff in each function there are macros
// that will do everything for you.
//
// The two loops are named SMALL and LARGE.
//
// BLIT_[32/24/8]_SSE2_INIT(dst, w) - This macro will declare '_i' variable that
// contains initial value for small loop and '_j' variable that contains count
// of pixels to process in tail loop. It also modifies _w variable to contain
// only how many cycles will be processed by large loop (4 pixels at time), not
// whole width in pixels.
//
// 32-bit entities:
//   - 1 pixel at time:
//     - BLIT_SSE2_32x4_SMALL_BEGIN(dst) - Small loop begin.
//     - BLIT_SSE2_32x4_SMALL_END(dst) - Small loop end.
//
//   - 4 pixels at time:
//     - BLIT_SSE2_32x4_LARGE_BEGIN(dst) - Main loop begin.
//     - BLIT_SSE2_32x4_LARGE_END(dst) - Main loop end.
//
// 24-bit entities:
//   - TODO
//
// 8-bit entities:
//   - 1 pixel at time:
//     - BLIT_SSE2_8x16_SMALL_BEGIN(dst) - Small loop begin.
//     - BLIT_SSE2_8x16_SMALL_END(dst) - Small loop end.
//
//   - 16 pixels at time:
//     - BLIT_SSE2_8x16_LARGE_BEGIN(dst) - Main loop begin.
//     - BLIT_SSE2_8x16_LARGE_END(dst) - Main loop end.
//
// Because compilers can be quite missed from our machinery, it's needed
// to follow some rules to help them to optimize this code:
// - declare temporary variables (mainly sse2 registers) in local loop scope.
// - do not add anything between BLIT_SSE2_32x4_SMALL_END and BLIT_SSE2_32x4_LARGE_BEGIN.

// 32-bit entities:

#define BLIT_SSE2_32x4_INIT(_dst, _w) \
  sysuint_t _i = (sysuint_t)_w; \
  sysuint_t _j = 0; \
  \
  if (_i >= 4 && ((_i = ((-(sysuint_t)(_dst)) & 15)) & 3) == 0x0) \
  { \
    _i >>= 2; \
    _w -= (sysint_t)_i; \
    _j = _w & 3; \
    _w >>= 2; \
    if (_w == 0) _i += _j; \
  } \
  else \
  { \
    _i = _w; \
    _w = 0; \
  }

#define BLIT_SSE2_32x4_SMALL_BEGIN(group) \
  if (_i) \
  { \
group: \
    do {

#define BLIT_SSE2_32x4_SMALL_END(group) \
    } while (--_i); \
    if (!w) return; \
  } \

#define BLIT_SSE2_32x4_LARGE_BEGIN(group) \
  do {

#define BLIT_SSE2_32x4_LARGE_END(group) \
  } while (--w); \
  \
  if ((_i = _j)) goto group; \
  return;

// 8-bit entities:

#define BLIT_SSE2_8x4_INIT(_dst, _w) \
  sysuint_t _i = (sysuint_t)_w; \
  sysuint_t _j = 0; \
  \
  if (_i >= 4) \
  { \
    sysint_t align = ((sysint_t)4 - ((sysint_t)(_dst) & 3)) & 3; \
    \
    if (_w - align < 4) \
    { \
      _w = 0; \
    } \
    else \
    { \
      _i = align; \
      _w -= (sysint_t)_i; \
      _j = _w & 3; \
      _w >>= 2; \
    } \
  } \
  else \
  { \
    _w = 0; \
  }

#define BLIT_SSE2_8x4_SMALL_BEGIN(group) \
  if (_i) \
  { \
group: \
    do {

#define BLIT_SSE2_8x4_SMALL_END(group) \
    } while (--_i); \
    if (!w) return; \
  } \

#define BLIT_SSE2_8x4_LARGE_BEGIN(group) \
  do {

#define BLIT_SSE2_8x4_LARGE_END(group) \
  } while (--w); \
  \
  if ((_i = _j)) goto group; \
  return;

#define BLIT_SSE2_8x16_INIT(_dst, _w) \
  sysuint_t _i = (sysuint_t)_w; \
  sysuint_t _j = 0; \
  \
  if (_i >= 16) \
  { \
    sysint_t align = ((sysint_t)16 - ((sysint_t)(_dst) & 15)) & 15; \
    \
    if (_w - align < 16) \
    { \
      _w = 0; \
    } \
    else \
    { \
      _i = align; \
      _w -= (sysint_t)_i; \
      _j = _w & 15; \
      _w >>= 4; \
    } \
  } \
  else \
  { \
    _w = 0; \
  }

#define BLIT_SSE2_8x16_SMALL_BEGIN(group) \
  if (_i) \
  { \
group: \
    do {

#define BLIT_SSE2_8x16_SMALL_END(group) \
    } while (--_i); \
    if (!w) return; \
  } \

#define BLIT_SSE2_8x16_LARGE_BEGIN(group) \
  do {

#define BLIT_SSE2_8x16_LARGE_END(group) \
  } while (--w); \
  \
  if ((_i = _j)) goto group; \
  return;

// ============================================================================
// [Fog::Raster_SSE2 - Constants]
// ============================================================================

// W masks
static __m128i Mask_0080008000800080_0080008000800080;
static __m128i Mask_000000FF00FF00FF_000000FF00FF00FF;
static __m128i Mask_000000FF00FF00FF_00FF00FF00FF00FF;
static __m128i Mask_00FF00FF00FF00FF_000000FF00FF00FF;
static __m128i Mask_00FF00FF00FF00FF_00FF00FF00FF00FF;
static __m128i Mask_FF000000000000FF_FF000000000000FF;
static __m128i Mask_0101010101010101_0101010101010101;
static __m128i Mask_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF;
static __m128i Mask_00FF000000000000_00FF000000000000;
static __m128i Mask_0000000000000000_00FF000000000000;
static __m128i Mask_00FF000000000000_0000000000000000;
static __m128i Mask_FF000000FF000000_FF000000FF000000;
static __m128i Mask_00FFFFFF00FFFFFF_00FFFFFF00FFFFFF;
static __m128i Mask_0000000100000001_0000000100000001;

static __m128i Mask_00FF00FF00FF00FF_0000000000000000;
static __m128i Mask_0000000000000000_00FF00FF00FF00FF;

// D masks
static __m128i Mask_0001000000000000_0000000000000000;

// Float masks
static __m128  Mask_7FFFFFFF7FFFFFFF_7FFFFFFF7FFFFFFF;

// Double masks
static __m128d Mask_7FFFFFFFFFFFFFFF_7FFFFFFFFFFFFFFF;

// ============================================================================
// [Fog::Raster_SSE2 - Helpers]
// ============================================================================

static FOG_INLINE void sse2_mul_const_4D(__m128i& dst, const __m128i& a, const __m128i& b)
{
  __m128i tmp = _mm_shuffle_epi32(a, _MM_SHUFFLE(2, 3, 0, 1));

  dst = _mm_mul_epu32(a, b);
  tmp = _mm_mul_epu32(tmp, b);
  tmp = _mm_shuffle_epi32(tmp, _MM_SHUFFLE(2, 3, 0, 1));
  dst = _mm_or_si128(dst, tmp);
}

// Create Mask.

static FOG_INLINE __m128i pix_create_mask_8x2W(uint16_t m0, uint16_t m1, uint16_t m2, uint16_t m3)
{
  sse2_t t;

  t.uw[3] = m0;
  t.uw[2] = m1;
  t.uw[1] = m2;
  t.uw[0] = m3;
  t.uw[7] = m0;
  t.uw[6] = m1;
  t.uw[5] = m2;
  t.uw[4] = m3;

  return _mm_loadu_si128((__m128i*)&t);
}

static FOG_INLINE __m128i pix_create_mask_8x2W(uint16_t m0, uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4, uint16_t m5, uint16_t m6, uint16_t m7)
{
  sse2_t t;

  t.uw[7] = m0;
  t.uw[6] = m1;
  t.uw[5] = m2;
  t.uw[4] = m3;
  t.uw[3] = m4;
  t.uw[2] = m5;
  t.uw[1] = m6;
  t.uw[0] = m7;

  return _mm_loadu_si128((__m128i*)&t);
}

static FOG_INLINE __m128i pix_create_mask_4x1D(uint32_t m0, uint32_t m1, uint32_t m2, uint32_t m3)
{
  sse2_t t;

  t.ud[3] = m0;
  t.ud[2] = m1;
  t.ud[1] = m2;
  t.ud[0] = m3;

  return _mm_loadu_si128((__m128i*)&t);
}

// Load.

template<typename SrcT>
static FOG_INLINE void pix_load4(__m128i& dst0, const SrcT* srcp)
{
  dst0 = _mm_cvtsi32_si128(((int *)srcp)[0]);
}

template<typename SrcT>
static FOG_INLINE void pix_load8(__m128i& dst0, const SrcT* srcp)
{
  dst0 = _mm_loadl_epi64((__m128i*)(srcp));
}

template<typename SrcT>
static FOG_INLINE void pix_load16a(__m128i& dst0, const SrcT* srcp)
{
  dst0 = _mm_load_si128((__m128i *)(srcp));
}

template<typename SrcT>
static FOG_INLINE void pix_load16u(__m128i& dst0, const SrcT* srcp)
{
  dst0 = _mm_loadu_si128((__m128i *)(srcp));
}

// Store.

template<typename DstT>
static FOG_INLINE void pix_store4(DstT* dstp, const __m128i& src0)
{
  ((int *)dstp)[0] = _mm_cvtsi128_si32(src0);
}

template<typename DstT>
static FOG_INLINE void pix_store8(DstT* dstp, const __m128i& src0)
{
  _mm_storel_epi64((__m128i*)(dstp), src0);
}

template<typename DstT>
static FOG_INLINE void pix_store16a(DstT* dstp, const __m128i& src0)
{
  _mm_store_si128((__m128i *)(dstp), src0);
}

template<typename DstT>
static FOG_INLINE void pix_store16u(DstT* dstp, const __m128i& src0)
{
  _mm_storeu_si128((__m128i *)(dstp), src0);
}

// Unpack.

static FOG_INLINE void pix_unpack_1x1W(
  __m128i& dst0, __m128i data)
{
  __m128i xmmz = _mm_setzero_si128();
  dst0 = _mm_unpacklo_epi8(data, xmmz);
}

static FOG_INLINE void pix_unpack_1x2W(
  __m128i& dst0, __m128i data)
{
  __m128i xmmz = _mm_setzero_si128();
  dst0 = _mm_unpacklo_epi8(data, xmmz);
}

static FOG_INLINE void pix_unpack_1x1W(
  __m128i& dst0, uint32_t data)
{
  pix_unpack_1x1W(dst0, _mm_cvtsi32_si128(data));
}

static FOG_INLINE void pix_unpack_2x2W(
  __m128i& dst0,
  __m128i& dst1, __m128i data)
{
  __m128i xmmz = _mm_setzero_si128();
  dst1 = _mm_unpackhi_epi8(data, xmmz);
  dst0 = _mm_unpacklo_epi8(data, xmmz);
}

static FOG_INLINE void pix_unpack_1x1D(
  __m128i& dst0, const __m128i& src0)
{
  __m128i xmmz = _mm_setzero_si128();
  dst0 = _mm_unpacklo_epi8(src0, xmmz);
  dst0 = _mm_unpacklo_epi16(dst0, xmmz);
}

static FOG_INLINE void pix_unpack_1x1D(
  __m128i& dst0, uint32_t src0)
{
  pix_unpack_1x1D(dst0, _mm_cvtsi32_si128(src0));
}

static FOG_INLINE void pix_unpack_to_float(__m128& dst0, __m128i pix0)
{
  __m128i xmmz = _mm_setzero_si128();
  pix0 = _mm_unpacklo_epi8(pix0, xmmz);
  pix0 = _mm_unpacklo_epi16(pix0, xmmz);
  dst0 = _mm_cvtepi32_ps(pix0);
}

// Pack.

static FOG_INLINE void pix_pack_1x1W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_packus_epi16(src0, src0);
}

static FOG_INLINE void pix_pack_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& src1)
{
  dst0 = _mm_packus_epi16(src0, src1);
}

static FOG_INLINE void pix_pack_alpha(__m128i& dst0, const __m128i& src0)
{
  __m128i mmz = _mm_setzero_si128();
  dst0 = src0;

  dst0 = _mm_srli_epi32(dst0, 24);
  dst0 = _mm_packus_epi16(dst0, mmz);
  dst0 = _mm_packus_epi16(dst0, mmz);
}

static FOG_INLINE uint32_t pix_pack_alpha_to_uint32(const __m128i& src)
{
  __m128i dst;
  pix_pack_alpha(dst, src);
  return _mm_cvtsi128_si32(dst);
}

static FOG_INLINE void pix_pack_1x1D(
  __m128i& dst0, __m128i& src0)
{
  dst0 = _mm_packs_epi32(src0, src0);
  dst0 = _mm_packus_epi16(dst0, dst0);
}

static FOG_INLINE void pix_pack_from_float(__m128i& dst0, __m128 pix0)
{
  dst0 = _mm_cvtps_epi32(pix0);
  dst0 = _mm_packs_epi32(dst0, dst0);
  dst0 = _mm_packus_epi16(dst0, dst0);
}

// Combine / Split.

static FOG_INLINE void pix_combine_1x1B_1x1B(__m128i& hi, const __m128i& lo)
{
  hi = _mm_shuffle_epi32(hi, _MM_SHUFFLE(3, 2, 0, 3));
  hi = _mm_or_si128(hi, lo);
}

static FOG_INLINE void pix_split_1x1B_1x1B(__m128i& hi, const __m128i& lo)
{
  hi = _mm_shuffle_epi32(hi, _MM_SHUFFLE(3, 2, 3, 1));
  FOG_UNUSED(lo);
}

static FOG_INLINE void pix_combine_1x1W_1x1W(__m128i& hi, const __m128i& lo)
{
  hi = _mm_shuffle_epi32(hi, _MM_SHUFFLE(1, 0, 3, 2));
}

static FOG_INLINE void pix_split_1x1W_1x1W(__m128i& hi, const __m128i& lo)
{
  hi = _mm_shuffle_epi32(hi, _MM_SHUFFLE(1, 0, 3, 2));
  FOG_UNUSED(lo);
}

// Negate.

static FOG_INLINE void pix_negate_1x1W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_xor_si128(src0, Mask_00FF00FF00FF00FF_00FF00FF00FF00FF);
}

static FOG_INLINE void pix_negate_1x2W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_xor_si128(src0, Mask_00FF00FF00FF00FF_00FF00FF00FF00FF);
}

static FOG_INLINE void pix_negate_1x2W_lo(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_xor_si128(src0, Mask_0000000000000000_00FF00FF00FF00FF);
}

static FOG_INLINE void pix_negate_1x2W_hi(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_xor_si128(src0, Mask_00FF00FF00FF00FF_0000000000000000);
}

static FOG_INLINE void pix_negate_2x2W(
  __m128i& dst0, const __m128i& src0,
  __m128i& dst1, const __m128i& src1)
{
  dst0 = _mm_xor_si128(src0, Mask_00FF00FF00FF00FF_00FF00FF00FF00FF);
  dst1 = _mm_xor_si128(src1, Mask_00FF00FF00FF00FF_00FF00FF00FF00FF);
}

// Swap.

static FOG_INLINE void pix_swap_1x1W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(0, 1, 2, 3));
}

static FOG_INLINE void pix_swap_1x2W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(0, 1, 2, 3));
  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(0, 1, 2, 3));
}

static FOG_INLINE void pix_swap_2x2W(
  __m128i& dst0, const __m128i& src0,
  __m128i& dst1, const __m128i& src1)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(0, 1, 2, 3));
  dst1 = _mm_shufflelo_epi16(src1, _MM_SHUFFLE(0, 1, 2, 3));
  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(0, 1, 2, 3));
  dst1 = _mm_shufflehi_epi16(dst1, _MM_SHUFFLE(0, 1, 2, 3));
}

// Expand Pixel.

static FOG_INLINE void pix_expand_pixel_1x1W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shuffle_epi32(src0, _MM_SHUFFLE(1, 0, 1, 0));
}

static FOG_INLINE void pix_expand_pixel_1x2W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shuffle_epi32(src0, _MM_SHUFFLE(1, 0, 1, 0));
}

static FOG_INLINE void pix_expand_pixel_1x4B(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shuffle_epi32(src0, _MM_SHUFFLE(0, 0, 0, 0));
}

// Expand Alpha.

static FOG_INLINE void pix_expand_alpha_1x1W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(3, 3, 3, 3));
}

static FOG_INLINE void pix_expand_alpha_1x2W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(3, 3, 3, 3));
  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(3, 3, 3, 3));
}

static FOG_INLINE void pix_expand_alpha_2x2W(
  __m128i& dst0, const __m128i& src0,
  __m128i& dst1, const __m128i& src1)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(3, 3, 3, 3));
  dst1 = _mm_shufflelo_epi16(src1, _MM_SHUFFLE(3, 3, 3, 3));
  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(3, 3, 3, 3));
  dst1 = _mm_shufflehi_epi16(dst1, _MM_SHUFFLE(3, 3, 3, 3));
}

// Expand one alpha value and unpack in to 1x4D format.
static FOG_INLINE void pix_expand_a8_1x4D(__m128i& dst0, uint32_t src0)
{
  dst0 = _mm_cvtsi32_si128(src0);
  dst0 = _mm_shuffle_epi32(dst0, _MM_SHUFFLE(0, 0, 0, 0));
  dst0 = _mm_packs_epi32(dst0, dst0);
  dst0 = _mm_packus_epi16(dst0, dst0);
}

static FOG_INLINE void pix_expand_a8_1x2W(__m128i& dst0, uint32_t src0)
{
  dst0 = _mm_cvtsi32_si128(src0);
  dst0 = _mm_shuffle_epi32(dst0, _MM_SHUFFLE(0, 0, 0, 0));
  dst0 = _mm_packs_epi32(dst0, dst0);
}

// Expand Alpha Reversed.

static FOG_INLINE void pix_expand_alpha_rev_1x1W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(0, 0, 0, 0));
}

static FOG_INLINE void pix_expand_alpha_rev_1x1W(
  __m128i& dst0, uint32_t src0)
{
  pix_expand_alpha_rev_1x1W(dst0, _mm_cvtsi32_si128(src0));
}

static FOG_INLINE void pix_expand_alpha_rev_1x2W(
  __m128i& dst0, const __m128i& src0)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(0, 0, 0, 0));
  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(0, 0, 0, 0));
}

static FOG_INLINE void pix_expand_alpha_rev_2x2W(
  __m128i& dst0, const __m128i& src0,
  __m128i& dst1, const __m128i& src1)
{
  dst0 = _mm_shufflelo_epi16(src0, _MM_SHUFFLE(0, 0, 0, 0));
  dst1 = _mm_shufflelo_epi16(src1, _MM_SHUFFLE(0, 0, 0, 0));
  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(0, 0, 0, 0));
  dst1 = _mm_shufflehi_epi16(dst1, _MM_SHUFFLE(0, 0, 0, 0));
}

// Add.

static FOG_INLINE void pix_adds_1x1W(
  __m128i& dst0, const __m128i& a0, const __m128i& b0)
{
  dst0 = _mm_adds_epu8(a0, b0);
}

static FOG_INLINE void pix_adds_2x2W(
  __m128i& dst0, const __m128i& a0, const __m128i& b0,
  __m128i& dst1, const __m128i& a1, const __m128i& b1)
{
  dst0 = _mm_adds_epu8(a0, b0);
  dst1 = _mm_adds_epu8(a1, b1);
}

static FOG_INLINE void pix_adds_1x1B(
  __m128i& dst0, const __m128i& a0, const __m128i& b0)
{
  dst0 = _mm_adds_epu8(a0, b0);
}

static FOG_INLINE void pix_adds_1x4B(
  __m128i& dst0, const __m128i& a0, const __m128i& b0)
{
  dst0 = _mm_adds_epu8(a0, b0);
}

// Sub.

static FOG_INLINE void pix_subs_1x1W(
  __m128i& dst0, const __m128i& a0, const __m128i& b0)
{
  dst0 = _mm_subs_epu8(a0, b0);
}

static FOG_INLINE void pix_subs_2x2W(
  __m128i& dst0, const __m128i& a0, const __m128i& b0,
  __m128i& dst1, const __m128i& a1, const __m128i& b1)
{
  dst0 = _mm_subs_epu8(a0, b0);
  dst1 = _mm_subs_epu8(a1, b1);
}

static FOG_INLINE void pix_subs_1x1B(
  __m128i& dst0, const __m128i& a0, const __m128i& b0)
{
  dst0 = _mm_subs_epu8(a0, b0);
}

static FOG_INLINE void pix_subs_1x4B(
  __m128i& dst0, const __m128i& a0, const __m128i& b0)
{
  dst0 = _mm_subs_epu8(a0, b0);
}

// Expand Mask.

static FOG_INLINE void pix_expand_mask_1x1W(
  __m128i& dst0, uint32_t msk)
{
  pix_expand_alpha_rev_1x1W(dst0, _mm_cvtsi32_si128(msk));
}

static FOG_INLINE void pix_expand_mask_2x2W(
  __m128i& dst0, __m128i& dst1, uint32_t msk)
{
  dst0 = _mm_cvtsi32_si128(msk);
  pix_unpack_1x1W(dst0, dst0);
  dst0 = _mm_shuffle_epi32(dst0, _MM_SHUFFLE(1, 0, 1, 0));

  dst1 = _mm_shufflelo_epi16(dst0, _MM_SHUFFLE(2, 2, 2, 2));
  dst0 = _mm_shufflelo_epi16(dst0, _MM_SHUFFLE(0, 0, 0, 0));
  dst1 = _mm_shufflehi_epi16(dst1, _MM_SHUFFLE(3, 3, 3, 3));
  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(1, 1, 1, 1));
}

static FOG_INLINE void pix_expand_mask_1x1D(
  __m128i& dst0, uint32_t msk)
{
  dst0 = _mm_shuffle_epi32(_mm_cvtsi32_si128(msk), _MM_SHUFFLE(0, 0, 0, 0));
}

// Multiply.

static FOG_INLINE void pix_multiply_1x1W(
  __m128i& dst0, const __m128i& data0, const __m128i& alpha0)
{
  __m128i t0;

  t0 = _mm_mullo_epi16(data0, alpha0);
  t0 = _mm_adds_epu16(t0, Mask_0080008000800080_0080008000800080);
  dst0 = _mm_mulhi_epu16(t0, Mask_0101010101010101_0101010101010101);
}

static FOG_INLINE void pix_multiply_1x2W(
  __m128i& dst0, const __m128i& data0, const __m128i& alpha0)
{
  pix_multiply_1x1W(dst0, data0, alpha0);
}

static FOG_INLINE void pix_multiply_2x2W(
  __m128i& dst0, const __m128i& data0, const __m128i& alpha0,
  __m128i& dst1, const __m128i& data1, const __m128i& alpha1)
{
  __m128i t0, t1;

  t0 = _mm_mullo_epi16(data0, alpha0);
  t1 = _mm_mullo_epi16(data1, alpha1);
  t0 = _mm_adds_epu16(t0, Mask_0080008000800080_0080008000800080);
  t1 = _mm_adds_epu16(t1, Mask_0080008000800080_0080008000800080);
  dst0 = _mm_mulhi_epu16(t0, Mask_0101010101010101_0101010101010101);
  dst1 = _mm_mulhi_epu16(t1, Mask_0101010101010101_0101010101010101);
}

// Fill Alpha.

static FOG_INLINE void pix_fill_alpha_1x1B(
  __m128i& dst0)
{
  dst0 = _mm_or_si128(dst0, Mask_FF000000FF000000_FF000000FF000000);
}

static FOG_INLINE void pix_fill_alpha_1x4B(
  __m128i& dst0)
{
  dst0 = _mm_or_si128(dst0, Mask_FF000000FF000000_FF000000FF000000);
}

static FOG_INLINE void pix_fill_alpha_1x1W(
  __m128i& dst0)
{
  dst0 = _mm_or_si128(dst0, Mask_00FF000000000000_00FF000000000000);
}

static FOG_INLINE void pix_fill_alpha_1x2W(
  __m128i& dst0)
{
  dst0 = _mm_or_si128(dst0, Mask_00FF000000000000_00FF000000000000);
}

static FOG_INLINE void pix_fill_alpha_1x2W_lo(
  __m128i& dst0)
{
  dst0 = _mm_or_si128(dst0, Mask_0000000000000000_00FF000000000000);
}

static FOG_INLINE void pix_fill_alpha_1x2W_hi(
  __m128i& dst0)
{
  dst0 = _mm_or_si128(dst0, Mask_00FF000000000000_0000000000000000);
}

static FOG_INLINE void pix_fill_alpha_2x2W(
  __m128i& dst0,
  __m128i& dst1)
{
  dst0 = _mm_or_si128(dst0, Mask_00FF000000000000_00FF000000000000);
  dst1 = _mm_or_si128(dst1, Mask_00FF000000000000_00FF000000000000);
}

// Zero Alpha.

static FOG_INLINE void pix_zero_alpha_1x1B(
  __m128i& dst0)
{
  dst0 = _mm_and_si128(dst0, Mask_00FFFFFF00FFFFFF_00FFFFFF00FFFFFF);
}

static FOG_INLINE void pix_zero_alpha_1x4B(
  __m128i& dst0)
{
  dst0 = _mm_and_si128(dst0, Mask_00FFFFFF00FFFFFF_00FFFFFF00FFFFFF);
}

static FOG_INLINE void pix_zero_alpha_1x1W(
  __m128i& dst0)
{
  dst0 = _mm_and_si128(dst0, Mask_000000FF00FF00FF_000000FF00FF00FF);
}

static FOG_INLINE void pix_zero_alpha_1x2W(
  __m128i& dst0)
{
  dst0 = _mm_and_si128(dst0, Mask_000000FF00FF00FF_000000FF00FF00FF);
}

static FOG_INLINE void pix_zero_alpha_1x2W_lo(
  __m128i& dst0)
{
  dst0 = _mm_and_si128(dst0, Mask_00FF00FF00FF00FF_000000FF00FF00FF);
}

static FOG_INLINE void pix_zero_alpha_1x2W_hi(
  __m128i& dst0)
{
  dst0 = _mm_and_si128(dst0, Mask_000000FF00FF00FF_00FF00FF00FF00FF);
}

static FOG_INLINE void pix_zero_alpha_2x2W(
  __m128i& dst0,
  __m128i& dst1)
{
  dst0 = _mm_and_si128(dst0, Mask_000000FF00FF00FF_000000FF00FF00FF);
  dst1 = _mm_and_si128(dst1, Mask_000000FF00FF00FF_000000FF00FF00FF);
}

// Premultiply.

static FOG_INLINE void pix_premultiply_1x1W(
  __m128i& dst0, const __m128i& src0)
{
  __m128i alpha0;

  pix_expand_alpha_1x1W(alpha0, src0);
  pix_fill_alpha_1x1W(alpha0);
  pix_multiply_1x1W(dst0, src0, alpha0);
}

static FOG_INLINE void pix_premultiply_2x2W(
  __m128i& dst0, const __m128i& src0,
  __m128i& dst1, const __m128i& src1)
{
  __m128i alpha0;
  __m128i alpha1;

  pix_expand_alpha_2x2W(
    alpha0, src0,
    alpha1, src1);
  pix_fill_alpha_2x2W(
    alpha0,
    alpha1);
  pix_multiply_2x2W(
    dst0, src0, alpha0,
    dst1, src1, alpha1);
}

// Demultiply.

static FOG_INLINE void pix_demultiply_1x1W(__m128i& dst0, const __m128i& src0)
{
  __m128i recip;
  uint32_t index;
  uint8_t buffer[8];

  pix_store8(buffer, src0);

  index = buffer[6];

  pix_load8(recip, (int8_t*)demultiply_reciprocal_table_w + index * 8);
  dst0 = _mm_slli_epi16(dst0, 8);
  dst0 = _mm_mulhi_epu16(dst0, recip);
}

static FOG_INLINE void pix_demultiply_2x2W(__m128i& dst0, const __m128i& src0, __m128i& dst1, const __m128i& src1)
{
  __m128i recip0, recip1;
  uint32_t index0;
  uint32_t index1;
  uint8_t buffer[16];

  pix_store16u(buffer, src0);

  index0 = buffer[6];
  index1 = buffer[14];

  pix_load8(recip0, (int8_t*)demultiply_reciprocal_table_w + index0 * 8);
  pix_load8(recip1, (int8_t*)demultiply_reciprocal_table_w + index1 * 8);

  pix_store16u(buffer, src1);

  dst0 = _mm_slli_epi16(src0, 8);
  dst1 = _mm_slli_epi16(src1, 8);

  recip1 = _mm_shuffle_epi32(recip1, _MM_SHUFFLE(1, 0, 3, 2));
  recip0 = _mm_or_si128(recip0, recip1);

  dst0 = _mm_mulhi_epu16(dst0, recip0);

  index0 = buffer[6];
  index1 = buffer[14];

  pix_load8(recip0, (int8_t*)demultiply_reciprocal_table_w + index0 * 8);
  pix_load8(recip1, (int8_t*)demultiply_reciprocal_table_w + index1 * 8);

  recip1 = _mm_shuffle_epi32(recip1, _MM_SHUFFLE(1, 0, 3, 2));
  recip0 = _mm_or_si128(recip0, recip1);

  dst1 = _mm_mulhi_epu16(dst1, recip0);
}

static FOG_INLINE void pix_demultiply_1x1W_srcbuf(__m128i& dst0, const __m128i& src0, const uint8_t* srcBuf)
{
  __m128i recip;
  uint32_t index;

  index = srcBuf[RGB32_AByte];

  pix_load8(recip, (int8_t*)demultiply_reciprocal_table_w + index * 8);
  dst0 = _mm_slli_epi16(dst0, 8);
  dst0 = _mm_mulhi_epu16(dst0, recip);
}

static FOG_INLINE void pix_demultiply_2x2W_srcbuf(__m128i& dst0, const __m128i& src0, __m128i& dst1, const __m128i& src1, const uint8_t* srcBuf)
{
  __m128i recip0, recip1;
  uint32_t index0;
  uint32_t index1;

  index0 = srcBuf[RGB32_AByte];
  index1 = srcBuf[RGB32_AByte+4];

  pix_load8(recip0, (int8_t*)demultiply_reciprocal_table_w + index0 * 8);
  pix_load8(recip1, (int8_t*)demultiply_reciprocal_table_w + index1 * 8);

  dst0 = _mm_slli_epi16(src0, 8);
  dst1 = _mm_slli_epi16(src1, 8);

  recip1 = _mm_shuffle_epi32(recip1, _MM_SHUFFLE(1, 0, 3, 2));
  recip0 = _mm_or_si128(recip0, recip1);

  dst0 = _mm_mulhi_epu16(dst0, recip0);

  index0 = srcBuf[RGB32_AByte+8];
  index1 = srcBuf[RGB32_AByte+12];

  pix_load8(recip0, (int8_t*)demultiply_reciprocal_table_w + index0 * 8);
  pix_load8(recip1, (int8_t*)demultiply_reciprocal_table_w + index1 * 8);

  recip1 = _mm_shuffle_epi32(recip1, _MM_SHUFFLE(1, 0, 3, 2));
  recip0 = _mm_or_si128(recip0, recip1);

  dst1 = _mm_mulhi_epu16(dst1, recip0);
}

// Lerp (Interpolation).

static FOG_INLINE void pix_lerp_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0)
{
  __m128i ialpha0;
  __m128i tmp0;

  pix_multiply_1x1W(tmp0, src0, alpha0);
  pix_negate_1x1W(ialpha0, alpha0);
  pix_multiply_1x1W(dst0, dst0, ialpha0);
  pix_adds_1x1W(dst0, dst0, tmp0);
}

static FOG_INLINE void pix_lerp_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0,
  __m128i& dst1, const __m128i& src1, const __m128i& alpha1)
{
  __m128i ialpha0, ialpha1;
  __m128i tmp0, tmp1;

  pix_multiply_2x2W(tmp0, src0, alpha0, tmp1, src1, alpha1);
  pix_negate_2x2W(ialpha0, alpha0, ialpha1, alpha1);
  pix_multiply_2x2W(dst0, dst0, ialpha0, dst1, dst1, ialpha1);
  pix_adds_2x2W(dst0, dst0, tmp0, dst1, dst1, tmp1);
}

static FOG_INLINE void pix_lerp_ialpha_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0, const __m128i& ialpha0)
{
  __m128i tmp0;

  pix_multiply_1x1W(tmp0, src0, alpha0);
  pix_multiply_1x1W(dst0, dst0, ialpha0);
  pix_adds_1x1W(dst0, dst0, tmp0);
}

static FOG_INLINE void pix_lerp_ialpha_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0, const __m128i& ialpha0,
  __m128i& dst1, const __m128i& src1, const __m128i& alpha1, const __m128i& ialpha1)
{
  __m128i tmp0, tmp1;

  pix_multiply_2x2W(tmp0, src0, alpha0, tmp1, src1, alpha1);
  pix_multiply_2x2W(dst0, dst0, ialpha0, dst1, dst1, ialpha1);
  pix_adds_2x2W(dst0, dst0, tmp0, dst1, dst1, tmp1);
}

// Over.

static FOG_INLINE void pix_over_ialpha_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& ialpha0)
{
  pix_multiply_1x1W(dst0, dst0, ialpha0);
  pix_adds_1x1W(dst0, dst0, src0);
}

static FOG_INLINE void pix_over_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0)
{
  __m128i ialpha0;

  pix_negate_1x1W(ialpha0, alpha0);
  pix_multiply_1x1W(dst0, dst0, ialpha0);
  pix_adds_1x1W(dst0, dst0, src0);
}

static FOG_INLINE void pix_over_ialpha_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& ialpha0,
  __m128i& dst1, const __m128i& src1, const __m128i& ialpha1)
{
  pix_multiply_2x2W(
    dst0, dst0, ialpha0,
    dst1, dst1, ialpha1);
  pix_adds_2x2W(dst0, dst0, src0, dst1, dst1, src1);
}

static FOG_INLINE void pix_over_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0,
  __m128i& dst1, const __m128i& src1, const __m128i& alpha1)
{
  __m128i ialpha0;
  __m128i ialpha1;

  pix_negate_2x2W(
    ialpha0, alpha0,
    ialpha1, alpha1);
  pix_multiply_2x2W(
    dst0, dst0, ialpha0,
    dst1, dst1, ialpha1);
  pix_adds_2x2W(dst0, dst0, src0, dst1, dst1, src1);
}

static FOG_INLINE void pix_over_1x1W(
  __m128i& dst0, __m128i& src0)
{
  __m128i src0ia;

  pix_expand_alpha_1x1W(src0ia, src0);
  pix_negate_1x1W(src0ia, src0ia);
  pix_over_ialpha_1x1W(dst0, src0, src0ia);
}

static FOG_INLINE void pix_over_2x2W(
  __m128i& dst0, __m128i& src0,
  __m128i& dst1, __m128i& src1)
{
  __m128i src0ia;
  __m128i src1ia;

  pix_expand_alpha_2x2W(src0ia, src0, src1ia, src1);
  pix_negate_2x2W(src0ia, src0ia, src1ia, src1ia);
  pix_over_ialpha_2x2W(dst0, src0, src0ia, dst1, src1, src1ia);
}

// OverRev.

static FOG_INLINE void pix_overrev_ialpha_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& ialpha0)
{
  __m128i t0;
  pix_multiply_1x1W(t0, src0, ialpha0);
  pix_adds_1x1W(dst0, dst0, t0);
}

static FOG_INLINE void pix_overrev_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0)
{
  __m128i t0;
  __m128i ialpha0;

  pix_negate_1x1W(ialpha0, alpha0);
  pix_multiply_1x1W(t0, src0, ialpha0);
  pix_adds_1x1W(dst0, dst0, t0);
}

static FOG_INLINE void pix_overrev_ialpha_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& ialpha0,
  __m128i& dst1, const __m128i& src1, const __m128i& ialpha1)
{
  __m128i t0;
  __m128i t1;

  pix_multiply_2x2W(
    t0, src0, ialpha0,
    t1, src1, ialpha1);
  pix_adds_2x2W(dst0, dst0, t0, dst1, dst1, t1);
}

static FOG_INLINE void pix_overrev_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& alpha0,
  __m128i& dst1, const __m128i& src1, const __m128i& alpha1)
{
  __m128i t0;
  __m128i t1;
  __m128i ialpha0;
  __m128i ialpha1;

  pix_negate_2x2W(
    ialpha0, alpha0,
    ialpha1, alpha1);
  pix_multiply_2x2W(
    t0, src0, ialpha0,
    t1, src1, ialpha1);
  pix_adds_2x2W(dst0, dst0, t0, dst1, dst1, t1);
}

static FOG_INLINE void pix_overrev_1x1W(
  __m128i& dst0, __m128i& src0)
{
  __m128i dst0ia;

  pix_expand_alpha_1x1W(dst0ia, dst0);
  pix_negate_1x1W(dst0ia, dst0ia);
  pix_overrev_ialpha_1x1W(dst0, src0, dst0ia);
}

static FOG_INLINE void pix_overrev_2x2W(
  __m128i& dst0, __m128i& src0,
  __m128i& dst1, __m128i& src1)
{
  __m128i dst0ia;
  __m128i dst1ia;

  pix_expand_alpha_2x2W(dst0ia, dst0, dst1ia, dst1);
  pix_negate_2x2W(dst0ia, dst0ia, dst1ia, dst1ia);
  pix_overrev_ialpha_2x2W(dst0, src0, dst0ia, dst1, src1, dst1ia);
}

// Atop.

static void FOG_INLINE pix_atop_ialpha_1x1W(
  __m128i& dst0, __m128i& src0, __m128i& src0ia)
{
  __m128i dst0a;

  pix_expand_alpha_1x1W(dst0a, dst0);
  pix_multiply_1x1W(dst0, dst0, src0ia);
  pix_multiply_1x1W(dst0a, dst0a, src0);
  pix_adds_1x1W(dst0, dst0, dst0a);
}

static void FOG_INLINE pix_atop_ialpha_2x2W(
  __m128i& dst0, __m128i& src0, __m128i& src0ia,
  __m128i& dst1, __m128i& src1, __m128i& src1ia)
{
  __m128i dst0a;
  __m128i dst1a;

  pix_expand_alpha_2x2W(dst0a, dst0, dst1a, dst1);
  pix_multiply_2x2W(dst0, dst0, src0ia, dst1, dst1, src1ia);
  pix_multiply_2x2W(dst0a, dst0a, src0, dst1a, dst1a, src1);
  pix_adds_2x2W(dst0, dst0, dst0a, dst1, dst1, dst1a);
}

static void FOG_INLINE pix_atop_1x1W(
  __m128i& dst0, __m128i& src0, __m128i& src0a)
{
  __m128i src0ia;

  pix_negate_1x1W(src0ia, src0a);
  pix_atop_ialpha_1x1W(dst0, src0, src0ia);
}

static void FOG_INLINE pix_atop_2x2W(
  __m128i& dst0, __m128i& src0, __m128i& src0a,
  __m128i& dst1, __m128i& src1, __m128i& src1a)
{
  __m128i src0ia;
  __m128i src1ia;

  pix_negate_1x1W(src0ia, src0a);
  pix_negate_1x1W(src1ia, src1a);
  pix_atop_ialpha_2x2W(dst0, src0, src0ia, dst1, src1, src1ia);
}

static void FOG_INLINE pix_atop_1x1W(
  __m128i& dst0, __m128i& src0)
{
  __m128i src0ia;
  pix_expand_alpha_1x1W(src0ia, src0);
  pix_negate_1x1W(src0ia, src0ia);
  pix_atop_ialpha_1x1W(dst0, src0, src0ia);
}

static void FOG_INLINE pix_atop_2x2W(
  __m128i& dst0, __m128i& src0,
  __m128i& dst1, __m128i& src1)
{
  __m128i src0ia;
  __m128i src1ia;

  pix_expand_alpha_2x2W(src0ia, src0, src1ia, src1);
  pix_negate_2x2W(src0ia, src0ia, src1ia, src1ia);
  pix_atop_ialpha_2x2W(dst0, src0, src0ia, dst1, src1, src1ia);
}

// AtopRev.

static void FOG_INLINE pix_atoprev_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& srca0)
{
  __m128i dstia0;

  pix_expand_alpha_1x1W(dstia0, dst0);
  pix_negate_1x1W(dstia0, dstia0);

  pix_multiply_1x1W(dst0, dst0, srca0);
  pix_multiply_1x1W(dstia0, dstia0, src0);
  pix_adds_1x1W(dst0, dst0, dstia0);
}

static void FOG_INLINE pix_atoprev_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& srca0,
  __m128i& dst1, const __m128i& src1, const __m128i& srca1)
{
  __m128i dstia0;
  __m128i dstia1;

  pix_expand_alpha_2x2W(dstia0, dst0, dstia1, dst1);
  pix_negate_2x2W(dstia0, dstia0, dstia1, dstia1);
  pix_multiply_2x2W(dst0, dst0, srca0, dst1, dst1, srca1);
  pix_multiply_2x2W(dstia0, dstia0, src0, dstia1, dstia1, src1);
  pix_adds_2x2W(dst0, dst0, dstia0, dst1, dst1, dstia1);
}

// Xor.

static void FOG_INLINE pix_xor_ialpha_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& srcia0)
{
  __m128i dstia0;

  pix_expand_alpha_1x1W(dstia0, dst0);
  pix_negate_1x1W(dstia0, dstia0);
  pix_multiply_1x1W(dst0, dst0, srcia0);
  pix_multiply_1x1W(dstia0, dstia0, src0);
  pix_adds_1x1W(dst0, dst0, dstia0);
}

static void FOG_INLINE pix_xor_1x1W(
  __m128i& dst0, const __m128i& src0, const __m128i& srca0)
{
  __m128i srcia0;
  pix_negate_1x1W(srcia0, srca0);
  pix_xor_ialpha_1x1W(dst0, src0, srcia0);
}

static void FOG_INLINE pix_xor_ialpha_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& srcia0,
  __m128i& dst1, const __m128i& src1, const __m128i& srcia1)
{
  __m128i dstia0;
  __m128i dstia1;

  pix_expand_alpha_2x2W(dstia0, dst0, dstia1, dst1);
  pix_negate_2x2W(dstia0, dstia0, dstia1, dstia1);
  pix_multiply_2x2W(dst0, dst0, srcia0, dst1, dst1, srcia1);
  pix_multiply_2x2W(dstia0, dstia0, src0, dstia1, dstia1, src1);
  pix_adds_2x2W(dst0, dst0, dstia0, dst1, dst1, dstia1);
}

static void FOG_INLINE pix_xor_2x2W(
  __m128i& dst0, const __m128i& src0, const __m128i& srca0,
  __m128i& dst1, const __m128i& src1, const __m128i& srca1)
{
  __m128i srcia0;
  __m128i srcia1;

  pix_negate_2x2W(srcia0, srca0, srcia1, srca1);
  pix_xor_ialpha_2x2W(dst0, src0, srcia0, dst1, src1, srcia1);
}

// Fetch RGB24/BGR24.

static FOG_INLINE void pix_fetch_rgb24_1x1W(__m128i& dst0, const uint8_t* srcp)
{
  pix_unpack_1x1W(dst0, READ_32(srcp));
  pix_fill_alpha_1x1W(dst0);
}

static FOG_INLINE void pix_fetch_rgb24_2x2W(__m128i& dst0, __m128i& dst1, const uint8_t* srcp)
{
  __m128i xmmz = _mm_setzero_si128();

  pix_load8(dst0, srcp + 0);                                 // dst0 = [G2 B2 R1 G1 B1 R0 G0 B0]
  pix_load8(dst1, srcp + 4);                                 // dst1 = [R3 G3 B3 R2 G2 B2 R1 G1]

  dst0 = _mm_slli_epi64(dst0, 8);                            // dst0 = [B2 R1 G1 B1 R0 G0 B0   ]
  dst1 = _mm_srli_epi64(dst1, 8);                            // dst1 = [   R3 G3 B3 R2 G2 B2 R1]

  dst0 = _mm_or_si128(dst0, Mask_FF000000000000FF_FF000000000000FF);           // dst0 = [FF R1 G1 B1 R0 G0 B0 FF]
  dst1 = _mm_or_si128(dst1, Mask_FF000000000000FF_FF000000000000FF);           // dst1 = [FF R3 G3 B3 R2 G2 B2 FF]

  dst0 = _mm_unpacklo_epi8(dst0, xmmz);
  dst1 = _mm_unpacklo_epi8(dst1, xmmz);

  dst0 = _mm_shufflelo_epi16(dst0, _MM_SHUFFLE(0, 3, 2, 1)); // dst0 = [FF R1 G1 B1 FF R0 G0 B0]
  dst1 = _mm_shufflelo_epi16(dst1, _MM_SHUFFLE(0, 3, 2, 1)); // dst1 = [FF R3 G3 B3 FF R2 G2 B2]
}

static FOG_INLINE void pix_fetch_bgr24_2x2W(__m128i& dst0, __m128i& dst1, const uint8_t* srcp)
{
  __m128i xmmz = _mm_setzero_si128();

  pix_load8(dst0, srcp + 0);                                 // dst0 = [G2 R2 B1 G1 R1 B0 G0 R0]
  pix_load8(dst1, srcp + 4);                                 // dst1 = [B3 G3 R3 B2 G2 R2 B1 G1]

  dst0 = _mm_slli_epi64(dst0, 8);                            // dst0 = [R2 B1 G1 R1 B0 G0 R0   ]
  dst1 = _mm_srli_epi64(dst1, 8);                            // dst1 = [   B3 G3 R3 B2 G2 R2 B1]

  dst0 = _mm_or_si128(dst0, Mask_FF000000000000FF_FF000000000000FF);           // dst0 = [FF B1 G1 R1 B0 G0 R0 FF]
  dst1 = _mm_or_si128(dst1, Mask_FF000000000000FF_FF000000000000FF);           // dst1 = [FF B3 G3 R3 B2 G2 R2 FF]

  dst0 = _mm_unpacklo_epi8(dst0, xmmz);
  dst1 = _mm_unpacklo_epi8(dst1, xmmz);

  dst0 = _mm_shufflelo_epi16(dst0, _MM_SHUFFLE(0, 1, 2, 3)); // dst0 = [FF B1 G1 R1 FF R0 G0 B0]
  dst1 = _mm_shufflelo_epi16(dst1, _MM_SHUFFLE(0, 1, 2, 3)); // dst1 = [FF B3 G3 R3 FF R2 G2 B2]

  dst0 = _mm_shufflehi_epi16(dst0, _MM_SHUFFLE(0, 1, 2, 3)); // dst0 = [FF R1 G1 B1 FF R0 G0 B0]
  dst1 = _mm_shufflehi_epi16(dst1, _MM_SHUFFLE(0, 1, 2, 3)); // dst1 = [FF R3 G3 B3 FF R2 G2 B2]
}

// Mask analyzer.

static FOG_INLINE void pix_analyze_mask_16B_zero(uint32_t& msk0isZero, const __m128i& msk0)
{
  __m128i t0;

  t0 = _mm_setzero_si128();
  t0 = _mm_cmpeq_epi8(t0, msk0);
  msk0isZero = _mm_movemask_epi8(t0);
}

static FOG_INLINE void pix_analyze_mask_16B_full(uint32_t& msk0isFull, const __m128i& msk0)
{
  __m128i t0;

  t0 = _mm_setzero_si128();
  t0 = _mm_cmpeq_epi8(t0, t0);
  t0 = _mm_cmpeq_epi8(t0, msk0);
  msk0isFull = _mm_movemask_epi8(t0);
}

static FOG_INLINE void pix_analyze_mask_16B(uint32_t& msk0IsZero, uint32_t& msk0IsFull, const __m128i& msk0)
{
  __m128i t0;
  __m128i t1;

  t1 = _mm_setzero_si128();
  t0 = _mm_setzero_si128();
  t1 = _mm_cmpeq_epi8(t1, t1);
  t0 = _mm_cmpeq_epi8(t0, msk0);
  t1 = _mm_cmpeq_epi8(t1, msk0);

  msk0IsZero = _mm_movemask_epi8(t0);
  msk0IsFull = _mm_movemask_epi8(t1);
}

// Misc / Unsorted.

static FOG_INLINE void pix_load_1xA8(__m128i& dst0, const uint8_t* p)
{
  dst0 = _mm_cvtsi32_si128(p[0]);
}

static FOG_INLINE void pix_load_4xA8(__m128i& dst0, const uint8_t* p)
{
  pix_load4(dst0, p);
  pix_unpack_1x1D(dst0, dst0);
  dst0 = _mm_slli_epi32(dst0, 24);
}

static FOG_INLINE void pix_load_1xI8(__m128i& dst0, const uint8_t* p, const Rgba* pal)
{
  const uint8_t* p0 = (uint8_t*)(&pal[p[0]]);
  pix_load4(dst0, p0);
}

static FOG_INLINE void pix_load_4xI8(__m128i& dst0, const uint8_t* p, const Rgba* pal)
{
  __m128i dst1;
  __m128i dst2;

  const uint8_t* p0;
  const uint8_t* p1;

  p0 = (uint8_t*)(&pal[p[0]]);
  p1 = (uint8_t*)(&pal[p[1]]);

  pix_load4(dst0, p0);
  pix_load4(dst1, p1);

  dst1 = _mm_shuffle_epi32(dst1, _MM_SHUFFLE(3, 3, 0, 3));

  p0 = (uint8_t*)(&pal[p[2]]);
  p1 = (uint8_t*)(&pal[p[3]]);

  dst0 = _mm_or_si128(dst0, dst1);

  pix_load4(dst1, p0);
  pix_load4(dst2, p1);

  dst1 = _mm_shuffle_epi32(dst1, _MM_SHUFFLE(3, 0, 3, 3));
  dst2 = _mm_shuffle_epi32(dst2, _MM_SHUFFLE(0, 3, 3, 3));

  dst1 = _mm_or_si128(dst1, dst2);
  dst0 = _mm_or_si128(dst0, dst1);
}

static FOG_INLINE void pix_load_and_unpack_axxx32_64B(__m128i& dst0, __m128i& dst1, const uint8_t* src)
{
  __m128i dst2;

  pix_load16u(dst0, src);
  pix_load16u(dst1, src + 16);
  dst0 = _mm_srli_epi32(dst0, 24);
  dst1 = _mm_srli_epi32(dst1, 24);
  dst0 = _mm_packs_epi32(dst0, dst1);

  pix_load16u(dst1, src + 32);
  pix_load16u(dst2, src + 48);
  dst1 = _mm_srli_epi32(dst1, 24);
  dst2 = _mm_srli_epi32(dst1, 24);
  dst1 = _mm_packs_epi32(dst1, dst2);
}

} // Raster namespace
} // Fog namespace
