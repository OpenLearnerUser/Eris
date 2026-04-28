#pragma once

#include <Eris/macro.h>
#include <Eris/constant.h>
#include <Eris/Size2.h>

namespace Eris
{
    class Size3
    {
    public:
        
        size_t x;
        size_t y;
        size_t z;
        //! Constructs default point (0, 0).
        constexpr Size3() : x(0), y(0), z(0) {}
        //! Constructs point with given parameters \p x_ and \p y_.
        constexpr Size3(size_t x_, size_t y_, size_t z_) : x(x_), y(y_), z(z_) {}
        //! Constructs point with initializer list.
        template <typename U>
        Size3(const std::initializer_list<U> &lst);

        //! Copy constructor.
        constexpr Size3(const Size3 &v) : x(v.x), y(v.y), z(v.z) {}
        //! Set both x and y components to \p s.
        void set(size_t x);
        //! Set x and y components with given parameters.
        void set(size_t x, size_t y, size_t z);

        //! Set x, y, and z components with given \p pt.x, \p pt.y, and \p z.
        void set(const Size2 &pt, size_t z);

        //! Set x and y components with given initializer list.
        template <typename U>
        void set(const std::initializer_list<U> &lst);
        //! Set x and y with other point \p pt.
        void set(const Size3 &pt);
        //! Set both x and y to zero.
        void setZero();

        //! Computes this + (v, v).
        Size3 add(size_t v) const;

        //! Computes this + (v.x, v.y).
        Size3 add(const Size3 &v) const;

        //! Computes this - (v, v).
        Size3 sub(size_t v) const;

        //! Computes this - (v.x, v.y).
        Size3 sub(const Size3 &v) const;

        //! Computes this * (v, v).
        Size3 mul(size_t v) const;

        //! Computes this * (v.x, v.y).
        Size3 mul(const Size3 &v) const;

        //! Computes this / (v, v).
        Size3 div(size_t v) const;

        //! Computes this / (v.x, v.y).
        Size3 div(const Size3 &v) const;

        // MARK: Binary operations: new instance = v (+) this

        //! Computes (v, v) - this.
        Size3 rsub(size_t v) const;

        //! Computes (v.x, v.y) - this.
        Size3 rsub(const Size3 &v) const;

        //! Computes (v, v) / this.
        Size3 rdiv(size_t v) const;

        //! Computes (v.x, v.y) / this.
        Size3 rdiv(const Size3 &v) const;

        // MARK: Augmented operations: this (+)= v

        //! Computes this += (v, v).
        void iadd(size_t v);

        //! Computes this += (v.x, v.y).
        void iadd(const Size3 &v);

        //! Computes this -= (v, v).
        void isub(size_t v);

        //! Computes this -= (v.x, v.y).
        void isub(const Size3 &v);

        //! Computes this *= (v, v).
        void imul(size_t v);

        //! Computes this *= (v.x, v.y).
        void imul(const Size3 &v);

        //! Computes this /= (v, v).
        void idiv(size_t v);

        //! Computes this /= (v.x, v.y).
        void idiv(const Size3 &v);

        // MARK: Basic getters

        //! Returns const reference to the \p i -th element of the point.
        const size_t &at(size_t i) const;

        //! Returns reference to the \p i -th element of the point.
        size_t &at(size_t i);

        //! Returns the sum of all the components (i.e. x + y).
        size_t sum() const;

        //! Returns the minimum value among x and y.
        size_t min() const;

        //! Returns the maximum value among x and y.
        size_t max() const;

        //! Returns the absolute minimum value among x and y.
        size_t absmin() const;

        //! Returns the absolute maximum value among x and y.
        size_t absmax() const;

        //! Returns the index of the dominant axis.
        size_t dominantAxis() const;

        //! Returns the index of the subminant axis.
        size_t subminantAxis() const;

        //! Returns a point with different value type.
        template <typename U>
        Size3<U, 3> castTo() const;

        //! Returns true if \p other is the same as this point.
        bool isEqual(const Size3 &other) const;

        // MARK: Operators

        //! Returns reference to the \p i -th element of the point.
        size_t &operator[](size_t i);

        //! Returns const reference to the \p i -th element of the point.
        const size_t &operator[](size_t i) const;

        //! Set x and y components with given initializer list.
        template <typename U>
        Size3 &operator=(const std::initializer_list<U> &lst);

        //! Set x and y with other point \p pt.
        Size3 &operator=(const Size3 &v);

        //! Computes this += (v, v)
        Size3 &operator+=(size_t v);

        //! Computes this += (v.x, v.y)
        Size3 &operator+=(const Size3 &v);

        //! Computes this -= (v, v)
        Size3 &operator-=(size_t v);

        //! Computes this -= (v.x, v.y)
        Size3 &operator-=(const Size3 &v);

        //! Computes this *= (v, v)
        Size3 &operator*=(size_t v);

        //! Computes this *= (v.x, v.y)
        Size3 &operator*=(const Size3 &v);

        //! Computes this /= (v, v)
        Size3 &operator/=(size_t v);

        //! Computes this /= (v.x, v.y)
        Size3 &operator/=(const Size3 &v);

        //! Returns true if \p other is the same as this point.
        bool operator==(const Size3 &v) const;

        //! Returns true if \p other is the not same as this point.
        bool operator!=(const Size3 &v) const;
    };

    //! Positive sign operator.
    
    Size3 operator+(const Size3 &a);

    
    Size3 operator-(const Size3 &a);
    //! Computes (a, a) + (b.x, b.y).
    
    Size3 operator+(T a, const Size3 &b);

    //! Computes (a.x, a.y) + (b.x, b.y).
    
    Size3 operator+(const Size3 &a, const Size3 &b);

    //! Computes (a, a) - (b.x, b.y).
    
    Size3 operator-(T a, const Size3 &b);

    //! Computes (a.x, a.y) - (b.x, b.y).
    
    Size3 operator-(const Size3 &a, const Size3 &b);

    //! Computes (a*b.x, a*b.y).
    
    Size3 operator*(T a, const Size3 &b);

    //! Computes (a.x*b.x, a.y*b.y).
    
    Size3 operator*(const Size3 &a, const Size3 &b);

    //! Computes (a.x, a.y) / (b, b).
    
    Size3 operator/(const Size3 &a, T b);

    //! Computes (a, a) / (b.x, b.y).
    
    Size3 operator/(T a, const Size3 &b);

    //! Computes (a.x, a.y) / (b.x, b.y).
    
    Size3 operator/(const Size3 &a, const Size3 &b);

    //! Returns element-wise min point: (min(a.x, b.x), min(a.y, b.y)).
    Size3 min(const Size3 &a, const Size3 &b);

    //! Returns element-wise max point: (max(a.x, b.x), max(a.y, b.y)).
    
    Size3 max(const Size3 &a, const Size3 &b);

    //! Returns element-wise clamped point.
    
    Size3 clamp(const Size3 &v, const Size3 &low,
                    const Size3 &high);

    
}

#include "Eris/details/point3-inl.h"
