#pragma once


#include <utility>
#include <algorithm>
#include <vector>


namespace Eris{

    template <typename T>
    Array<T, 1>::Array() {};

    template<typename T>
    Array<T,1>::Array(size_t size,const T& initVal){
        resize(size,initVal);
    };

    template <typename T>
    Array<T, 1>::Array(const std::initializer_list<T> &lst)
    {
        set(list)
    };

    template<typename T>
    Array<T,1>Array(const Array& others){
        set(others);

    };

    template<typename T>
    Array<T,1>::Array(Array&& others){
        (*this)=std::move(others);
    };

    template<typename T>
    void Array<T,1>::set(const T& value){
        for(auto& v:_data){
            v=value;
        }
    }

    template<typename T>
    void Array<T,1>::set(const Array& other){
        _data_resize(other._data.size());
        std::copy(other._data.begin(),other._data.end(),this->_data.begin());
    }
    template <typename T>
    void Array<T, 1>::set(const std::initializer_list<T> &lst)
    {
        size_t size = lst.size();
        resize(size);
        auto colIter = lst.begin();
        for (size_t i = 0; i < size; ++i)
        {
            (*this)[i] = *colIter;
            ++colIter;
        }
    }

    template <typename T>
    void Array<T, 1>::clear()
    {
        _data.clear();
    }

    template <typename T>
    void Array<T, 1>::resize(size_t size, const T &initVal)
    {
        _data.resize(size, initVal);
    }

    template <typename T>
    T &Array<T, 1>::at(size_t i)
    {
        assert(i < size());
        return _data[i];
    }

    template <typename T>
    const T &Array<T, 1>::at(size_t i) const
    {
        assert(i < size());
        return _data[i];
    }

    template <typename T>
    size_t Array<T, 1>::size() const
    {
        return _data.size();
    }

    template <typename T>
    T *Array<T, 1>::data()
    {
        return _data.data();
    }

    template <typename T>
    const T *const Array<T, 1>::data() const
    {
        return _data.data();
    }


    
}

