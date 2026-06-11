#pragma once
#include <cmath>
#include <limits>

namespace Eris
{

    //! Zero size_t.
    constexpr size_t kZeroSize = 0;

    //! Zero ssize_t.
    constexpr ssize_t kZeroSSize = 0;

    constexpr double kPiD = 3.14159265358979323846264338327950288;

    //! Max size_t.
    constexpr size_t kMaxSize = std::numeric_limits<size_t>::max();

    //! Max ssize_t.
    constexpr ssize_t kMaxSSize = std::numeric_limits<ssize_t>::max();

    //! Max float.
    constexpr float kMaxF = std::numeric_limits<float>::max();

    //! Max double.
    constexpr double kMaxD = std::numeric_limits<double>::max();

}