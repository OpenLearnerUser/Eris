#pragma once



namespace Eris{

    template<typename T>
    inline T absmin(T x,T y){
        return (x*x>y*y)?y:x;
    }

    template<typename T>
    inline T absmax(T x,T y){
        return (x*x>y*y)?x:y;
    }
}