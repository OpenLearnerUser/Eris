#pragma once

#include <cassert>

#if defined(DEBUG) || defined(_DEBUG)
#   define ERIS_DEBUG_MODE
#   define ERIS_ASSERT(x) assert(x)  // 防止宏展开问题
#else
#   define ERIS_ASSERT(x)
#endif