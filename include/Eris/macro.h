#pragma once


#if defined(DEBUG) || defined(_DEBUG)
#   define ERIS_DEBUG_MODE
#   include <cassert>
#   define ERIS_ASSERT(x) assert(x)
#else
#   define ERIS_ASSERT(x)
#endif