// [Fog-G2d]
//
// [License]
// MIT, See COPYING file in package

// [Precompiled Headers]
#if defined(FOG_PRECOMP)
#include FOG_PRECOMP
#endif // FOG_PRECOMP

// [Guard]
#include <Fog/Core/Config/Config.h>
#if defined(FOG_OPTIMIZE_SSE2)

// [Dependencies]
#include <Fog/Core/Face/Face_SSE.h>
#include <Fog/Core/Face/Face_SSE2.h>
#include <Fog/Core/Math/Math.h>
#include <Fog/G2d/Geometry/Box.h>
#include <Fog/G2d/Geometry/Internals_p.h>
#include <Fog/G2d/Geometry/Path.h>
#include <Fog/G2d/Geometry/PathClipper.h>
#include <Fog/G2d/Geometry/Rect.h>
#include <Fog/G2d/Geometry/Transform.h>

namespace Fog {

// ============================================================================
// [Fog::PathClipper - InitPath]
// ============================================================================

// TODO: Optimization

// ============================================================================
// [Init / Fini]
// ============================================================================

FOG_NO_EXPORT void PathClipper_initSSE2(void)
{
}

} // Fog namespace

// [Guard]
#endif // FOG_OPTIMIZE_SSE2