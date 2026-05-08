#pragma once 
#include <functional>

namespace Eris{

    ////! Type casting operator.
    template <typename T, typename U>
    struct TypeCast{
         constexpr U operator()(const T& a)const;
    };

    template<typename T>
    struct RMinus{

        constexpr T operator()(const T& a, const T& b)const;
    };


    template<typename T>
    struct  RDivides{
        constexpr T operator()(const T& a, const T& b)const;
    };

}


#include "details/functors-inl.h"