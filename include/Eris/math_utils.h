#pragma once

#include <algorithm>
#include <cmath>
#include <limits>

namespace Eris
{

    template <typename T>
    inline T absmin(T x, T y)
    {
        return (x * x > y * y) ? y : x;
    }

    template <typename T>
    inline T absmax(T x, T y)
    {
        return (x * x > y * y) ? x : y;
    }

    template <typename T>
    inline T sign(T x)
    {
        if (x > 0)
            return 1;
        if (x < 0)
            return -1;
        return 0;
    }

    template <typename T>
    inline T clamp(T v, T low, T high)
    {
        return std::max(low, std::min(v, high));
    }

    template <typename T>
    inline T square(T v)
    {
        return v * v;
    }

    template <typename T>
    inline T cubic(T v)
    {
        return v * v * v;
    }

} // namespace Eris
