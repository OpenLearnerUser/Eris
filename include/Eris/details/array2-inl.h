#pragma once
#include <Eris/macro.h>
#include <Eris/parallel.h>

#include <utility>
#include <algorithm>
#include <vector>

namespace Eris
{

    template <typename T>
    Array<T, 2>::Array() {};

    template <typename T>
    Array<T, 2>::Array(const Size2& size, const T &initVal)
    {
        resize(size, initVal);
    };
    template <typename T>
    Array<T, 2>::Array(size_t width, size_t height, const T &initVal)
    {
        resize(width, height, initVal);
    }

    template <typename T>
    Array<T, 2>::Array(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        set(lst);
    };

    template <typename T>
    Array<T, 2>::Array(const Array &others)
    {
        set(others);
    };

    template <typename T>
    Array<T, 2>::Array(Array &&others)
    {
        (*this) = std::move(others);
    };

    template <typename T>
    void Array<T, 2>::set(const T &value)
    {
        for (auto &v : _data)
        {
            v = value;
        }
    }

    template <typename T>
    void Array<T, 2>::set(const Array &other)
    {
        _data_resize(other._data.size());
        std::copy(other._data.begin(), other._data.end(), this->_data.begin());
    }
    template <typename T>
    void Array<T, 2>::set(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        size_t height = lst.size();
        size_t width = (height > 0) ? lst.begin() - lst.end() : 0;

        resize(Size2(height, width));
        auto rowIter = lst.begin();
        for (size_t j = 0; j < height; ++j)
        {
            ERIS_ASSERT(width == rowIter->size());
            auto colIter = rowIter->begin();
            for (size_t i = 0; j < width; j++)
            {
                (*this)(i, j) = *colIter;
                ++colIter;
            }
            rowIter++;
        }
    }

    template <typename T>
    void Array<T, 2>::clear()
    {
        _data.clear();
        _size = Size2(0, 0);
    }

    template <typename T>
    void Array<T, 2>::resize(const Size2 &size, const T &initVal)
    {

        if(size==_size)return;
        Array grid;
        grid._data.resize(size.x * size.y, initVal);
        grid._size = size;
        const size_t copyWidth = std::min(_size.x, size.x);
        const size_t copyHeight = std::min(_size.y, size.y);
        for (size_t y = 0; y < copyHeight; ++y)
        {
            const size_t oldRowStart = y * _size.x;
            const size_t newRowStart = y * size.x;

            // 批量复制一行
            std::copy(_data.begin() + oldRowStart,
                      _data.begin() + oldRowStart + copyWidth,
                      grid._data.begin() + newRowStart);
        }
        swap(grid);
    }

    template <typename T>
    void Array<T, 2>::resize(size_t width, size_t height, const T &initVal)
    {
        resize(Size2(width, height), initVal);
    }

    template <typename T>
    T &Array<T, 2>::at(size_t i)
    {
        ERIS_ASSERT(i < _size.x * _size.y);
        return _data[i];
    }

    template <typename T>
    const T &Array<T, 2>::at(size_t i) const
    {
        ERIS_ASSERT(i < _size.x * _size.y);
        return _data[i];
    }

    template <typename T>
    T &Array<T, 2>::at(const Point2UI &pt)
    {
        return at(pt.x, pt.y);
    }

    template <typename T>
    const T &Array<T, 2>::at(const Point2UI &pt) const
    {
        return at(pt.x, pt.y);
    }

    template <typename T>
    T &Array<T, 2>::at(size_t i, size_t j)
    {
        ERIS_ASSERT(i < _size.x && j < _size.y);
        return _data[i + _size.x * j];
    }

    template <typename T>
    Size2 Array<T, 2>::size() const
    {
        return _size;
    }
    template <typename T>
    size_t Array<T, 2>::width() const
    {
        return _size.x;
    }
    template <typename T>
    size_t Array<T, 2>::height() const
    {
        return _size.y;
    }

    template <typename T>
    T *Array<T, 2>::data()
    {
        return _data.data();
    }

    template <typename T>
    const T *const Array<T, 2>::data() const
    {
        return _data.data();
    }

    template <typename T>
    typename Array<T, 2>::ContainerType::iterator Array<T, 2>::begin()
    {
        return _data.begin();
    }
    template <typename T>
    typename Array<T, 2>::ContainerType::const_iterator Array<T, 2>::begin() const
    {
        return _data.cbegin();
    }
    template <typename T>
    typename Array<T, 2>::ContainerType::iterator Array<T, 2>::end()
    {
        return _data.end();
    }

    template <typename T>
    typename Array<T, 2>::ContainerType::const_iterator Array<T, 2>::end() const
    {
        return _data.cend();
    }
    template <typename T>
    ArrayAccessor2<T> Array<T, 2>::accessor()
    {
        return ArrayAccessor2<T>(size(), data());
    }

    template <typename T>
    ConstArrayAccessor2<T> Array<T, 2>::constAccessor() const
    {
        return ConstArrayAccessor2<T>(size(), data());
    }

    template <typename T>
    void Array<T, 2>::swap(Array &other)
    {
        std::swap(other._data, _data);
        std::swap(other._size, _size);
    }

    template <typename T>
    template <typename CallBack>
    void Array<T, 2>::forEach(CallBack fun) const
    {
        constAccessor().forEach(fun);
    }

    template <typename T>
    template <typename CallBack>
    void Array<T, 2>::forEachIndex(CallBack func) const
    {
        constAccessor().forEachIndex(func);
    };
    template <typename T>
    template <typename Callback>
    void Array<T, 2>::parallelForEach(Callback func)
    {
        accessor().parallelForEach(func);
    };

    template <typename T>
    template <typename Callback>
    void Array<T, 2>::parallelForEachIndex(Callback func) const
    {

        constAccessor().parallelForEachIndex(func);
    }

    template <typename T>
    T& Array<T, 2>::operator[](size_t i)
    {
        return _data[i];
    }

    template <typename T>
    const T& Array<T, 2>::operator[](size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    T& Array<T, 2>::operator()(size_t i, size_t j)
    {
        ERIS_ASSERT(i < _size.x && j < _size.y);
        return _data[i + _size.x * j];
    }

    template <typename T>
    const T& Array<T, 2>::operator()(size_t i, size_t j) const
    {
        ERIS_ASSERT(i < _size.x && j < _size.y);
        return _data[i + _size.x * j];
    }

    template <typename T>
    T& Array<T, 2>::operator()(const Point2UI &pt)
    {
        ERIS_ASSERT(pt.x < _size.x && pt.y < _size.y);
        return _data[pt.x + _size.x * pt.y];
    }

    template <typename T>
    const T &Array<T, 2>::operator()(const Point2UI &pt) const
    {
        ERIS_ASSERT(pt.x < _size.x && pt.y < _size.y);
        return _data[pt.x + _size.x * pt.y];
    }

    template <typename T>
    Array<T, 2> &Array<T, 2>::operator=(const T &value)
    {
        set(value);
        return *this;
    }

    template <typename T>
    Array<T, 2> &Array<T, 2>::operator=(const Array &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    Array<T, 2> &Array<T, 2>::operator=(Array &&other)
    {
        _data = std::move(other._data);
        _size = other._size;
        other._size = Size2();
        return *this;
    }

    template <typename T>
    Array<T, 2>::operator ArrayAccessor2<T>()
    {
        return accessor();
    }

    template <typename T>
    Array<T, 2>::operator ConstArrayAccessor2<T>() const
    {
        return constAccessor();
    }

    template <typename T>
    Array<T, 2> &Array<T, 2>::operator=(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        set(lst);
        return *this;
    };

}
