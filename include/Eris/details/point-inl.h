#pragma once

#include <Eris/macro.h>
#include <cassert>
#include <type_traits>

namespace Eris
{
    template <typename T, size_t N>
    Point<T, N>::Point()
    {
        for (auto &e : _elements)
        {
            e = static_cast<T>(0);
        }
    }
    template <typename T, size_t N>
    template <typename... Param>
    Point<T, N>::Point(Param... param)
    {
        static_assert(sizeof...(param) == N, "Invalid number of parameters.");
        set(0, param...);
    }
    template <typename T, size_t N>
    template <typename U>
    Point<T, N>::Point(const std::initializer_list<U> &lst)
    {
        size_t i = 0;
        for (const auto &input : lst)
        {
            _elements[i] = static_cast<T>(input);
            i++;
        }
    }
    template <typename T, size_t N>
    Point<T, N>::Point(const Point &other) : _elements(other._elements)
    {
    }

    template <typename T, size_t N>
    template <typename U>
    void Point<T, N>::set(const std::initializer_list<U> &lst)
    {
        assert(lst.size() >= N);
        size_t i = 0;
        for (const auto &inputElem : lst)
        {
            _elements[i] = static_cast<T>(inputElem);
            ++i;
        }
    }

    template <typename T, size_t N>
    void Point<T, N>::set(const Point &other)
    {
        _elements = other._elements;
    }

    template <typename T, size_t N>
    template <typename U>
    Point<T, N> &Point<T, N>::operator=(const std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }
    template <typename T, size_t N>
    Point<T, N> &Point<T, N>::operator=(const Point &other)
    {
        set(other);
        return *this;
    }
    template <typename T, size_t N>
    const T& Point<T, N>::operator[](size_t i) const
    {
        return _elements[i];
    }

    template <typename T, size_t N>
    T &Point<T, N>::operator[](size_t i)
    {
        return _elements[i];
    }
    template <typename T, size_t N>
    template<typename... Param>
    void Point<T,N>::setAt(size_t i,T v,Param... param){
        _elements[i]=v;
        setAt(i+1,param...);
    }
    template <typename T, size_t N>
    void Point<T,N>::setAt(size_t i,T V){
        _elements[i]=V;
    }




}