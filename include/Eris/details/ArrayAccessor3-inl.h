#pragma once

#include <Eris/macro.h>
#include <Eris/parallel.h>
#include <utility>

namespace Eris
{

template <typename T>
ArrayAccessor<T, 3>::ArrayAccessor() : _size(), _data(nullptr) {}

template <typename T>
ArrayAccessor<T, 3>::ArrayAccessor(const Size3 &size, T *const data) {
    reset(size, data);
}

template <typename T>
ArrayAccessor<T, 3>::ArrayAccessor(const ArrayAccessor &other) {
    set(other);
}

template <typename T>
void ArrayAccessor<T, 3>::set(const ArrayAccessor &other) {
    reset(other._size, other._data);
}

template <typename T>
void ArrayAccessor<T, 3>::reset(const Size3 &size, T *const data) {
    _size = size;
    _data = data;
}

template <typename T>
void ArrayAccessor<T, 3>::reset(size_t width, size_t height,size_t depth, T *const data) {
    reset(Size3(width, height,depth), data);
}

template <typename T>
T &ArrayAccessor<T, 3>::at(size_t i) {
    ERIS_ASSERT(i < _size.x * _size.y*_size.z);
    return _data[i];
}

template <typename T>
const T &ArrayAccessor<T, 3>::at(size_t i) const {
    ERIS_ASSERT(i < _size.x * _size.y*_size.z);
    return _data[i];
}

template <typename T>
T &ArrayAccessor<T, 3>::at(const Point3UI &pt) {
    return at(pt.x, pt.y,pt.z);
}

template <typename T>
const T &ArrayAccessor<T, 3>::at(const Point3UI &pt) const {
    return at(pt.x, pt.y,pt.z);
}

template <typename T>
T &ArrayAccessor<T, 3>::at(size_t i, size_t j,size_t k) {
    ERIS_ASSERT(i < _size.x && j < _size.y&&k<_size.z);
    return _data[i +  _size.x*(j+k* _size.y)];
}

template <typename T>
const T &ArrayAccessor<T, 3>::at(size_t i, size_t j,size_t k) const {
    ERIS_ASSERT(i < _size.x && j < _size.y&&k<_size.z);
    return _data[i +  _size.x*(j+k* _size.y)];
}

template <typename T>
T *const ArrayAccessor<T, 3>::begin() const {
    return _data;
}

template <typename T>
T *const ArrayAccessor<T, 3>::end() const {
    return _data + _size.x * _size.y * _size.z;
}

template <typename T>
T *ArrayAccessor<T, 3>::begin() {
    return _data;
}

template <typename T>
T *ArrayAccessor<T, 3>::end() {
    return _data + _size.x * _size.y * _size.z;
}

template <typename T>
Size3 ArrayAccessor<T, 3>::size() const {
    return _size;
}

template <typename T>
size_t ArrayAccessor<T, 3>::width() const {
    return _size.x;
}

template <typename T>
size_t ArrayAccessor<T, 3>::height() const {
    return _size.y;
}

template <typename T>
size_t ArrayAccessor<T, 3>::depth() const {
    return _size.z;
}

template <typename T>
T *const ArrayAccessor<T, 3>::data() const {
    return _data;
}

template <typename T>
void ArrayAccessor<T, 3>::swap(ArrayAccessor &other) {
    std::swap(other._data, _data);
    std::swap(other._size, _size);
}

template <typename T>
template <typename Callback>
void ArrayAccessor<T, 3>::forEach(Callback func) const {
    for(size_t k = 0; k < _size.z; ++k)
        for (size_t j = 0; j < _size.y; ++j) {
            for (size_t i = 0; i < _size.x; ++i) {
                func(at(i, j,k));
        }
    }
}

template <typename T>
template <typename Callback>
void ArrayAccessor<T, 3>::forEachIndex(Callback func) const {
     for(size_t k = 0; k < _size.z; ++k)
        for (size_t j = 0; j < _size.y; ++j) {
            for (size_t i = 0; i < _size.x; ++i) {
                func(at(i, j,k));
        }
    }
}

template <typename T>
template <typename Callback>
void ArrayAccessor<T, 3>::parallelForEach(Callback func) {
    parallelFor(
        kZeroSize, _size.x, kZeroSize, _size.y,
        [&](size_t i, size_t j,size_t k) { func(at(i, j,k)); });
}

template <typename T>
template <typename Callback>
void ArrayAccessor<T, 3>::parallelForEachIndex(Callback func) const {
    parallelFor(kZeroSize, _size.x, kZeroSize, _size.y,kZeroSize, _size.z, func);
}

template <typename T>
T &ArrayAccessor<T, 3>::operator[](size_t i) {
    return _data[i];
}

template <typename T>
const T &ArrayAccessor<T, 3>::operator[](size_t i) const {
    return _data[i];
}

template <typename T>
T &ArrayAccessor<T, 3>::operator()(const Point3UI &pt) {
    return at(pt.x, pt.y,pt.z);
}

template <typename T>
const T &ArrayAccessor<T, 3>::operator()(const Point3UI &pt) const {
    return at(pt.x, pt.y,pt.z);
}

template <typename T>
T &ArrayAccessor<T, 3>::operator()(size_t i, size_t j,size_t k) {
    return at(i, j,k);
}

template <typename T>
const T &ArrayAccessor<T, 3>::operator()(size_t i, size_t j,size_t k) const {
    return at(i, j,k);
}

template <typename T>
ArrayAccessor<T, 3> &
ArrayAccessor<T, 3>::operator=(const ArrayAccessor &other) {
    set(other);
    return *this;
}

template <typename T>
ArrayAccessor<T, 3>::operator ConstArrayAccessor<T, 3>() const {
    return ConstArrayAccessor<T, 3>(*this);
}

// ConstArrayAccessor<T, 3> implementations

template <typename T>
ConstArrayAccessor<T, 3>::ConstArrayAccessor() : _size(), _data(nullptr) {}

template <typename T>
ConstArrayAccessor<T, 3>::ConstArrayAccessor(const Size3 &size,
                                             const T *const data)
    : _size(size), _data(data) {}

template <typename T>
ConstArrayAccessor<T, 3>::ConstArrayAccessor(const ArrayAccessor<T, 3> &other)
    : _size(other.size()), _data(other.data()) {}

template <typename T>
ConstArrayAccessor<T, 3>::ConstArrayAccessor(const ConstArrayAccessor &other)
    : _size(other._size), _data(other._data) {}

template <typename T>
const T &ConstArrayAccessor<T, 3>::at(size_t i) const {
    ERIS_ASSERT(i < _size.x * _size.y*_size.z);
    return _data[i];
}

template <typename T>
const T &ConstArrayAccessor<T, 3>::at(const Point3UI &pt) const {
    return at(pt.x, pt.y,pt.z);
}

template <typename T>
const T &ConstArrayAccessor<T, 3>::at(size_t i, size_t j,size_t k) const {
    ERIS_ASSERT(i < _size.x && j < _size.y && k < _size.z);
    return _data[i +  _size.x*(j+k* _size.y)];
}

template <typename T>
const T *const ConstArrayAccessor<T, 3>::begin() const {
    return _data;
}

template <typename T>
const T *const ConstArrayAccessor<T, 3>::end() const {
    return _data + _size.x * _size.y * _size.z;
}

template <typename T>
Size3 ConstArrayAccessor<T, 3>::size() const {
    return _size;
}

template <typename T>
size_t ConstArrayAccessor<T, 3>::width() const {
    return _size.x;
}

template <typename T>
size_t ConstArrayAccessor<T, 3>::height() const {
    return _size.y;
}

template <typename T>
size_t ConstArrayAccessor<T, 3>::depth() const {
    return _size.z;
}

template <typename T>
const T *const ConstArrayAccessor<T, 3>::data() const {
    return _data;
}

template <typename T>
template <typename Callback>
void ConstArrayAccessor<T, 3>::forEach(Callback func) const {
    for (size_t k = 0; k < _size.z; ++k)
        for (size_t j = 0; j < _size.y; ++j) {
            for (size_t i = 0; i < _size.x; ++i) {
                func(at(i, j,k));
        }
    }
}

template <typename T>
template <typename Callback>
void ConstArrayAccessor<T, 3>::forEachIndex(Callback func) const {
    for (size_t k = 0; k < _size.z; ++k)
        for (size_t j = 0; j < _size.y; ++j) {
            for (size_t i = 0; i < _size.x; ++i) {
                func(at(i, j,k));
        }
    }
}

template <typename T>
template <typename Callback>
void ConstArrayAccessor<T, 3>::parallelForEachIndex(Callback func) const {
    parallelFor(kZeroSize, _size.x, kZeroSize, _size.y,  kZeroSize, _size.z,func);
}

template <typename T>
size_t ConstArrayAccessor<T, 3>::index(const Point3UI &pt) const {
    return index(pt.x, pt.y,pt.z);
}

template <typename T>
size_t ConstArrayAccessor<T, 3>::index(size_t i, size_t j,size_t k) const {
    return i + _size.x *(j  +k * _size.y);
}

template <typename T>
const T &ConstArrayAccessor<T, 3>::operator[](size_t i) const {
    return _data[i];
}

template <typename T>
const T &ConstArrayAccessor<T, 3>::operator()(const Point3UI &pt) const {
    return at(pt.x, pt.y,pt.z);
}

template <typename T>
const T &ConstArrayAccessor<T, 3>::operator()(size_t i, size_t j,size_t k) const {
    return at(i, j,k);
}

}  // namespace Eris