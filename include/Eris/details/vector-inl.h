#pragma once
#include <Eris/macro.h>
#include <Eris/math_utils.h>
#include <Eris/vector.h>

namespace Eris{

    template <typename T,size_t N>
    Vector<T,N>::Vector(){
        for(auto& e:_elements){
            e=static_cast<T>(0);
        }
    }

    



}