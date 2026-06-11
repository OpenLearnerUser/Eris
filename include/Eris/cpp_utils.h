#pragma once

#include <algorithm>
#include <functional>


namespace Eris{
    template <class ForwardIt, class T, class Compare = std::less<>>
    ForwardIt binaryFind(ForwardIt first, ForwardIt last, const T& value,
                         Compare comp={}) ;
        // Note: BOTH type T and the type after ForwardIt is dereferenced
        // must be implicitly convertible to BOTH Type1 and Type2, used in Compare.

}
#include "details/cpp_utils-inl.h"