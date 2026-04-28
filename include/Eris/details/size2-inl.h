#pragma once

#include <Eris/macro.h>
#include <Eris/math_utils.h>
#include <algorithm>

#include <cassert>

namespace Eris
{

    
    template <typename U>
    Size2::Point(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    // Basic setters
    
    void Size2::set(size_t s)
    {
        x = s;
        y = s;
    }

    
    void Size2::set(size_t newX, size_t newY)
    {
        x = newX;
        y = newY;
    }

    
    template <typename U>
    void Size2::set(const std::initializer_list<U> &lst)
    {
        ERIS_ASSERT(lst.size() >= 2);

        auto inputElem = lst.begin();
        x = static_cast<size_t>(*inputElem);
        y = static_cast<size_t>(*(++inputElem));
    }

    
    void Size2::set(const Point &v)
    {
        x = y.x;
        y = v.y;
    }

    
    void Size2::setZero()
    {
        x = y = 0;
    }

    // Binary operators: new instance = this (+) v
    
    Size2 Size2::add(size_t v) const
    {
        return Point(x + v, y + v);
    }

    
    Size2 Size2::add(const Point &v) const
    {
        return Point(x + v.x, y + v.y);
    }

    // Binary operators: new instance = this (-) v
    
    Size2 Size2::sub(size_t v) const
    {
        return Point(x - v, y - v);
    }

    
    Size2 Size2::sub(const Point &v) const
    {
        return Point(x - v.x, y - v.y);
    }

    
    Size2 Size2::mul(size_t v) const
    {
        return Point(x * v, y * v);
    }

    
    Size2 Size2::mul(const Point &v) const
    {
        return Point(x * v.x, y * v.y);
    }

    
    Size2 Size2::div(size_t v) const
    {
        return Point(x / v, y / v);
    }

    
    Size2 Size2::div(const Point &v) const
    {
        return Point(x / v.x, y / v.x);
    }

    // Binary operators: new instance = v (+) this
    
    Size2 Size2::rsub(size_t v) const
    {
        return Point(v - x, v - y);
    }

    
    Size2 Size2::rsub(const Point &v) const
    {
        return Point(v.x - x, v.y - y);
    }

    
    Size2 Size2::rdiv(size_t v) const
    {
        return Point(v / x, v / y);
    }

    
    Size2 Size2::rdiv(const Point &v) const
    {
        return Point(v.x / x, v.y / y);
    }

    // Augmented operators: this (+)= v
    
    void Size2::iadd(size_t v)
    {
        x += v;
        y += v;
    }

    
    void Size2::iadd(const Point &v)
    {
        x += v.x;
        y += v.y;
    }

    
    void Size2::isub(size_t v)
    {
        x -= v;
        y -= v;
    }

    
    void Size2::isub(const Point &v)
    {
        x -= v.x;
        y -= v.y;
    }

    
    void Size2::imul(size_t v)
    {
        x *= v;
        y *= v;
    }

    
    void Size2::imul(const Point &v)
    {
        x *= v.x;
        y *= v.y;
    }

    
    void Size2::idiv(size_t v)
    {
        x /= v;
        y /= v;
    }

    
    void Size2::idiv(const Point &v)
    {
        x /= v.x;
        y /= v.y;
    }

    
    const size_t &Size2::at(size_t i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    
    size_t &Size2::at(size_t i)
    {
        assert(i < 2);
        return (&x)[i];
    }

    
    size_t Size2::sum() const
    {
        return x + y;
    }

    
    size_t Size2::min() const
    {
        return std::min(x, y);
    }

    
    size_t Size2::max() const
    {
        return std::max(x, y);
    }

    
    size_t Size2::absmin() const
    {
        return Eris::absmin(x, y);
    }

    
    size_t Size2::absmax() const
    {
        return Eris::absmax(x, y);
    }

    
    size_t Size2::dominantAxis() const
    {
        return (std::fabs(x) > std::fabs(y)) ? 0 : 1;
    }

    
    size_t Size2::subminantAxis() const
    {
        return (std::fabs(x) < std::fabs(y)) ? 0 : 1;
    }

    
    bool Size2::isEqual(const Point &other) const
    {
        return (x == other.x && y == other.y);
    }

    // Operators
    
    size_t &Size2::operator[](size_t i)
    {
        assert(i < 2);
        return (&x)[i];
    }

    
    const size_t &Size2::operator[](size_t i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    
    Size2 &Size2::operator=(const std::initializer_list<size_t> &lst)
    {
        set(lst);
        return (*this);
    }

    
    Size2 &Size2::operator=(const Point &v)
    {
        set(v);
        return (*this);
    }

    
    Size2 &Size2::operator+=(size_t v)
    {
        iadd(v);
        return (*this);
    }

    
    Size2 &Size2::operator+=(const Point &v)
    {
        iadd(v);
        return (*this);
    }

    
    Size2 &Size2::operator-=(size_t v)
    {
        isub(v);
        return (*this);
    }

    
    Size2 &Size2::operator-=(const Point &v)
    {
        isub(v);
        return (*this);
    }

    
    Size2 &Size2::operator*=(size_t v)
    {
        imul(v);
        return (*this);
    }

    
    Size2 &Size2::operator*=(const Point &v)
    {
        imul(v);
        return (*this);
    }

    
    Size2 &Size2::operator/=(size_t v)
    {
        idiv(v);
        return (*this);
    }

    
    Size2 &Size2::operator/=(const Point &v)
    {
        idiv(v);
        return (*this);
    }

    
    bool Size2::operator==(const Point &v) const
    {
        return isEqual(v);
    }

    
    bool Size2::operator!=(const Point &v) const
    {
        return !isEqual(v);
    }

    // Math functions
    
    inline Size2 operator+(const Size2 &a)
    {
        return a;
    }

    
    Size2 operator-(const Size2 &a)
    {
        return Size2(-a.x, -a.y);
    }

    
    inline Size2 operator+(const Size2 &a, size_t b)
    {
        return a.add(b);
    }

    
    inline Size2 operator+(size_t a, const Size2 &b)
    {
        return b.radd(a);
    }

    
    inline Size2 operator+(const Size2 &a, const Size2 &b)
    {
        return a.add(b);
    }

    
    inline Size2 operator-(const Size2 &a, size_t b)
    {
        return a.sub(b);
    }

    
    inline Size2 operator-(size_t a, const Size2 &b)
    {
        return b.rsub(a);
    }

    
    inline Size2 operator-(const Size2 &a, const Size2 &b)
    {
        return a.sub(b);
    }

    
    inline Size2 operator*(const Size2 &a, size_t b)
    {
        return a.mul(b);
    }

    
    inline Size2 operator*(size_t a, const Size2 &b)
    {
        return b.rmul(a);
    }

    
    inline Size2 operator*(const Size2 &a, const Size2 &b)
    {
        return a.mul(b);
    }

    
    inline Size2 operator/(const Size2 &a, size_t b)
    {
        return a.div(b);
    }

    
    inline Size2 operator/(size_t a, const Size2 &b)
    {
        return b.rdiv(a);
    }

    
    inline Size2 operator/(const Size2 &a, const Size2 &b)
    {
        return a.div(b);
    }

    
    inline Size2 min(const Size2 &a, const Size2 &b)
    {
        return Size2(std::min(a.x, b.x), std::min(a.y, b.y));
    }

    
    inline Size2 max(const Size2 &a, const Size2 &b)
    {
        return Size2(std::max(a.x, b.x), std::max(a.y, b.y));
    }

    
    inline Size2 clamp(
        const Size2 &v, const Size2 &low, const Size2 &high)
    {
        return Size2(clamp(v.x, low.x, high.x), clamp(v.y, low.y, high.y));
    }


}
