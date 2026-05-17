#pragma once
#include <Eris/macro.h>
#include <Eris/math_utils.h>

namespace Eris
{

    template <typename T>
    template <typename U>
    Vector<T, 2>::Vector(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T>
    void Vector<T, 2>::set(T v)
    {
        x = y = v;
    }

    template <typename T>
    void Vector<T, 2>::set(T x_, T y_)
    {
        x = x_;
        y = y_;
    }

    template <typename T>
    template <typename U>
    void Vector<T, 2>::set(const std::initializer_list<U> &lst)
    {
        ERIS_ASSERT(lst.size() == 2);
        auto inputElem = lst.begin();
        x = static_cast<T>(*inputElem);
        y = static_cast<T>(*(++inputElem));
    }

    template <typename T>
    void Vector<T, 2>::set(const Vector &pt)
    {
        x = pt.x;
        y = pt.y;
    }

    template <typename T>
    void Vector<T, 2>::setZero()
    {
        x = y = 0;
    }

    template <typename T>
    void Vector<T, 2>::normalize()
    {
        T l = length();
        x = x / l;
        y = y / l;
    }

    // MARK : Binary operations : new instance = this(+) v

    template <typename T>
    Vector<T, 2> Vector<T, 2>::add(T v) const
    {
        return Vector(x + v, y + v);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::add(const Vector &v) const
    {
        return Vector(x + v.x, y + v.y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::sub(T v) const
    {
        return Vector(x - v, y - v);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::sub(const Vector &v) const
    {
        return Vector(x - v.x, y - v.y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::mul(T v) const
    {
        return Vector(x * v, y * v);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::mul(const Vector &v) const
    {
        return Vector(x * v.x, y * v.y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::div(T v) const
    {
        return Vector(x / v, y / v);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::div(const Vector &v) const
    {
        return Vector(x / v.x, y / v.y);
    }

    template <typename T>
    T Vector<T, 2>::dot(const Vector &v) const
    {
        return x * v.x + y * v.y;
    }

    template <typename T>
    T Vector<T, 2>::cross(const Vector &v) const
    {
        return x * v.y - v.x * y;
    }

    // MARK: Binary operations: new instance = v (+) this

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rsub(T v) const
    {
        return Vector(v - x, v - y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rsub(const Vector &v) const
    {
        return Vector(v.x - x, v.y - y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rdiv(T v) const
    {
        return Vector(v / x, v / y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rdiv(const Vector &v) const
    {
        return Vector(v.x / x, v.y / y);
    }

    template <typename T>
    T Vector<T, 2>::rcross(const Vector &v) const
    {
        return v.x * y - x * v.y;
    }

    // MARK: Augmented operations: this (+)= v

    template <typename T>
    void Vector<T, 2>::iadd(T v)
    {
        x += v;
        y += v;
    }

    template <typename T>
    void Vector<T, 2>::iadd(const Vector &v)
    {
        x += v.x;
        y += v.y;
    }

    template <typename T>
    void Vector<T, 2>::isub(T v)
    {
        x -= v;
        y -= v;
    }

    template <typename T>
    void Vector<T, 2>::isub(const Vector &v)
    {
        x -= v.x;
        y -= v.y;
    }

    template <typename T>
    void Vector<T, 2>::imul(T v)
    {
        x *= v;
        y *= v;
    }

    template <typename T>
    void Vector<T, 2>::imul(const Vector &v)
    {
        x *= v.x;
        y *= v.y;
    }

    template <typename T>
    void Vector<T, 2>::idiv(T v)
    {
        x /= v;
        y /= v;
    }

    template <typename T>
    void Vector<T, 2>::idiv(const Vector &v)
    {
        x /= v.x;
        y /= v.y;
    }

    // MARK: Basic getters

    template <typename T>
    const T &Vector<T, 2>::at(size_t i) const
    {
        ERIS_ASSERT(i < 2);
        return (&x)[i];
    }

    template <typename T>
    T &Vector<T, 2>::at(size_t i)
    {
        ERIS_ASSERT(i < 2);
        return (&x)[i];
    }

    template <typename T>
    T Vector<T, 2>::sum() const
    {
        return x + y;
    }

    template <typename T>
    T Vector<T, 2>::avg() const
    {
        return sum() / 2;
    }

    template <typename T>
    T Vector<T, 2>::min() const
    {
        return x < y ? x : y;
    }

    template <typename T>
    T Vector<T, 2>::max() const
    {
        return std::max(x, y);
    }

    template <typename T>
    T Vector<T, 2>::absmin() const
    {
        return Eris::absmin(x, y);
    }

    template <typename T>
    T Vector<T, 2>::absmax() const
    {
        return Eris::absmax(x, y);
    }

    template <typename T>
    size_t Vector<T, 2>::dominantAxis() const
    {
        return (std::fabs(x) > std::fabs(y)) ? 0 : 1;
    }

    template <typename T>
    size_t Vector<T, 2>::subminantAxis() const
    {
        return (std::fabs(x) < std::fabs(y)) ? 0 : 1;
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::normalized() const
    {
        T l = length();
        return Vector(x / l, y / l);
    }

    template <typename T>
    T Vector<T, 2>::length() const
    {
        return std::sqrt(x * x + y * y);
    }

    template <typename T>
    T Vector<T, 2>::lengthSquared() const
    {
        return x * x + y * y;
    }

    template <typename T>
    T Vector<T, 2>::distanceTo(const Vector &other) const
    {
        return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

    template <typename T>
    T Vector<T, 2>::distanceSquaredTo(const Vector &other) const
    {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::reflected(const Vector &normal) const
    {

        return sub(normal.mul(2 * dot(normal)));
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::projected(const Vector &normal) const
    {
        return sub(normal.mul(dot(normal)));
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::tangential() const
    {
        // Rotate 90 degrees
        return Vector<T, 2>(-y, x);
    }

    template <typename T>
    template <typename U>
    Vector<U, 2> Vector<T, 2>::castTo() const
    {
        return Vector<U, 2>(static_cast<U>(x), static_cast<U>(y));
    }

    template <typename T>
    bool Vector<T, 2>::isEqual(const Vector &other) const
    {
        return x == other.x && y == other.y;
    }

    template <typename T>
    bool Vector<T, 2>::isSimilar(const Vector &other,
                                 T epsilon) const
    {
        return (std::fabs(x - other.x) < epsilon) &&
               (std::fabs(y - other.y) < epsilon);
    }

    // MARK: Operators

    template <typename T>
    T &Vector<T, 2>::operator[](size_t i)
    {
        ERIS_ASSERT(i < 2);
        return (&x)[i];
    }

    template <typename T>
    const T &Vector<T, 2>::operator[](size_t i) const
    {
        ERIS_ASSERT(i < 2);
        return (&x)[i];
    }

    template <typename T>
    template <typename U>
    Vector<T, 2> &Vector<T, 2>::operator=(const std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator=(const Vector &v)
    {
        set(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator+=(T v)
    {
        iadd(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator+=(const Vector &v)
    {
        iadd(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator-=(T v)
    {
        isub(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator-=(const Vector &v)
    {
        isub(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator*=(T v)
    {
        imul(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator*=(const Vector &v)
    {
        imul(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator/=(T v)
    {
        idiv(v);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator/=(const Vector &v)
    {
        idiv(v);
        return *this;
    }

    template <typename T>
    bool Vector<T, 2>::operator==(const Vector &v) const
    {
        return isEqual(v);
    }

    template <typename T>
    bool Vector<T, 2>::operator!=(const Vector &v) const
    {
        return !isEqual(v);
    }

    //! Returns the same vector (unary plus).
    template <typename T>
    Vector2<T> operator+(const Vector2<T> &a)
    {
        return a;
    }

    //! Returns the negated vector (unary minus).
    template <typename T>
    Vector2<T> operator-(const Vector2<T> &a)
    {
        return Vector<T, 2>(-a.x, -a.y);
    }

    //! Computes scalar + vector.
    template <typename T>
    Vector2<T> operator+(T a, const Vector2<T> &b)
    {
        return b.add(a);
    }

    //! Computes scalar - vector.
    template <typename T>
    Vector2<T> operator-(T a, const Vector2<T> &b)
    {
        return b.rsub(a);
    }

    //! Computes vector + vector.
    template <typename T>
    Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b)
    {
        return a.add(b);
    }

    //! Computes vector - vector.
    template <typename T>
    Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b)
    {
        return a.sub(b);
    }

    //! Computes vector + scalar.
    template <typename T>
    Vector2<T> operator+(const Vector2<T> &a, T b)
    {
        return a.add(b);
    }

    //! Computes vector - scalar.
    template <typename T>
    Vector2<T> operator-(const Vector2<T> &a, T b)
    {
        return a.sub(b);
    }

    //! Computes vector * scalar.
    template <typename T>
    Vector2<T> operator*(const Vector2<T> &a, T b)
    {
        return a.mul(b);
    }

    //! Computes scalar * vector.
    template <typename T>
    Vector2<T> operator*(T a, const Vector2<T> &b)
    {
        return b.mul(a);
    }

    //! Computes element-wise vector * vector.
    template <typename T>
    Vector2<T> operator*(const Vector2<T> &a, const Vector2<T> &b)
    {
        return a.mul(b);
    }

    //! Computes vector / scalar.
    template <typename T>
    Vector2<T> operator/(const Vector2<T> &a, T b)
    {
        return a.div(b);
    }

    //! Computes scalar / vector.
    template <typename T>
    Vector2<T> operator/(T a, const Vector2<T> &b)
    {
        return b.rdiv(a);
    }

    //! Computes element-wise vector / vector.
    template <typename T>
    Vector2<T> operator/(const Vector2<T> &a, const Vector2<T> &b)
    {
        return a.div(b);
    }

    //! Returns element-wise min vector: (min(a.x, b.x), min(a.y, b.y)).
    template <typename T>
    Vector2<T> min(const Vector2<T> &a, const Vector2<T> &b)
    {
        return Vector<T, 2>(std::min(a.x, b.x), std::min(a.y, b.y));
    }

    //! Returns element-wise min vector: (max(a.x, b.x), max(a.y, b.y)).
    template <typename T>
    Vector2<T> max(const Vector2<T> &a, const Vector2<T> &b)
    {
        return Vector<T, 2>(std::max(a.x, b.x), std::max(a.y, b.y));
    }

    //! Returns element-wise clamped vector.
    template <typename T>
    Vector2<T> clamp(const Vector2<T> &v, const Vector2<T> &low,
                     const Vector2<T> &high)
    {
        return Vector<T, 2>(clamp(v.x, low.x, high.x), clamp(v.y, low.y, high.y));
    }

    //! Returns element-wise ceiled vector.
    template <typename T>
    Vector2<T> ceil(const Vector2<T> &a)
    {
        return Vector<T, 2>(std::ceil(a.x), std::ceil(a.y));
    }

    //! Returns element-wise floored vector.
    template <typename T>
    Vector2<T> floor(const Vector2<T> &a)
    {
        return Vector<T, 2>(std::floor(a.x), std::floor(a.y));
    }

    // Extensions
    template <typename T>
    Vector<T, 2> monotonicCatmullRom(const Vector<T, 2> &v0, const Vector<T, 2> &v1,
                                     const Vector<T, 2> &v2, const Vector<T, 2> &v3,
                                     T f)
    {
        static const T two = static_cast<T>(2);
        static const T three = static_cast<T>(3);

        Vector<T, 2> d1 = (v2 - v0) / two;
        Vector<T, 2> d2 = (v3 - v1) / two;
        Vector<T, 2> D1 = v2 - v1;

        if (std::fabs(D1.x) < std::numeric_limits<T>::epsilon() ||
            sign(D1.x) != sign(d1.x) || sign(D1.x) != sign(d2.x))
        {
            d1.x = d2.x = 0;
        }

        if (std::fabs(D1.y) < std::numeric_limits<T>::epsilon() ||
            sign(D1.y) != sign(d1.y) || sign(D1.y) != sign(d2.y))
        {
            d1.y = d2.y = 0;
        }

        Vector<T, 2> a3 = d1 + d2 - two * D1;
        Vector<T, 2> a2 = three * D1 - two * d1 - d2;
        Vector<T, 2> a1 = d1;
        Vector<T, 2> a0 = v1;

        return a3 * cubic(f) + a2 * square(f) + a1 * f + a0;
    }

}