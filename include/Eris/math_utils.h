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
    inline T absminn(const T *x, size_t n)
    {
        T m = x[0];
        for (size_t i = 1; i < n; i++)
        {
            m = absmin(m, x[i]);
        }
        return m;
    }

    template <typename T>
    inline T absmax(T x, T y)
    {
        return (x * x > y * y) ? x : y;
    }

    template <typename T>
    inline T absmaxn(const T *x, size_t n)
    {
        T m = x[0];
        for (size_t i = 1; i < n; i++)
        {
            m = absmax(m, x[i]);
        }
        return m;
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
