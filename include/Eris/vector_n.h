#pragma once
#include <Eris/ArrayAccessor1.h>
#include<Eris/Vector_expression.h>

#include <initializer_list>
#include <limits>
#include <vector>


namespace Eris{
    // MARK: VectorN

    //!
    //! \brief General purpose dynamically-sizedN-D vector class.
    //!
    //! This class defines N-D vector data where its size can be defined
    //! dynamically.
    //!
    //! \tparam T Type of the element.
    //!

    template <typename T>
    class VectorN final :public VectorExpression<T,VectorN<T> >{
    public:

        static_assert(std::is_floating_point<T>::value,
                      "VectorN only can be instantiated with floating point types");
        typedef std::vector<T> ContainerType;
 

        // !Constructs a vector with zeros.VectorN();
        //! Constructs vectorN instance with parameters.
       VectorN();

        //! Sets all elements to \p s.
        VectorN(size_t n ,const T &val=0);
        //! Constructs vector instance with initializer list.
        template <typename U>
        VectorN(const std::initializer_list<U> &lst);

        //! Constructs vector with expression template.
        template <typename E>
        VectorN(const VectorExpression<T, E> &others);

        //! Copy constructor.
        VectorN(const VectorN &others);

        //! Copy constructor.
        VectorN(VectorN &&others);

        // MARK: Basic setters
        //! Set vector instance with initializer list.

        void resize(size_t n,const T& val=0);

        void clear();

        void set(const T& s);

        template <typename U>
        void set(const std::initializer_list<U> &lst);

        //! Sets vector with expression template.
        template <typename E>
        void set(const VectorExpression<T, E> &other);

        //! Adds an element.
        void append(const T &val);

        //! Swaps the content of the vector with \p other vector.
        void swap(VectorN &other);

        //! Sets all elements to zero.
        void setZero();
        //! Normalizes this vector.
        void normalize();
        // MARK: Basic getters

        //! Returns the size of the vector.
        size_t size() const;

        //! Returns the raw pointer to the vector data.
        T *data();
        //! Returns the const raw pointer to the vector data.
        const T *data() const;
        //! Returns the begin iterator of the vector.
        //! Returns the begin iterator of the vector.
        typename ContainerType::iterator begin();

        //! Returns the begin const iterator of the vector.
        typename ContainerType::const_iterator begin() const;

        //! Returns the end iterator of the vector.
        typename ContainerType::iterator end();

        //! Returns the end const iterator of the vector.
        typename ContainerType::const_iterator end() const;

        //! Returns the array accessor.
        ArrayAccessor1<T> accessor();

        //! Returns the const array accessor.
        ConstArrayAccessor1<T> constAccessor() const;

        //! Returns const reference to the \p i -th element of the vector.
        T at(size_t i) const;

        //! Returns reference to the \p i -th element of the vector.
        T &at(size_t i);

        //! Returns the sum of all the elements.
        T sum() const;

        //! Returns the average of all the elements.
        T avg() const;

        //! Returns the minimum element.
        T min() const;

        //! Returns the maximum element.
        T max() const;

        //! Returns the absolute minimum element.
        T absmin() const;

        //! Returns the absolute maximum element.
        T absmax() const;

        //! Returns the index of the dominant axis.
        size_t dominantAxis() const;

        //! Returns the index of the subminant axis.
        size_t subminantAxis() const;

        VectorScalarDiv<T, VectorN<T>> normalized() const;

        //! Returns the length of the vector.
        T length() const;

        //! Returns the squared length of the vector.
        T lengthSquared() const;

        //! Returns the distance to the other vector.
        template <typename E>
        T distanceTo(const E &other) const;

        //! Returns the squared distance to the other vector.
        template <typename E>
        T distanceSquaredTo(const E &other) const;

        template <typename U>
        VectorTypeCast<U, VectorN<T>, T> castTo() const;

        //! Returns true if \p other is the same as this vector.
        template <typename E>
        bool isEqual(const E &other) const;
        //! Returns true if \p other is similar to this vector.
        template <typename E>
        bool isSimilar(const E &other, T epsilon = std::numeric_limits<T>::epsilon()) const;

        // MARK: Binary operations: new instance = this (+) v

        //! Computes this + v.
        template <typename E>
        VectorAdd<T, VectorN<T>, E> add(const E &v) const;
        //! Computes this + (s, s, ... , s).
        VectorScalarAdd<T, VectorN<T>> add(const T &s) const;

        //! Computes this - v.
        template <typename E>
        VectorSub<T, VectorN<T>, E> sub(const E &v) const;
        //! Computes this - (s, s, ... , s).
        VectorScalarSub<T, VectorN<T>> sub(const T &s) const;

        //! Computes this * v.
        template <typename E>
        VectorMul<T, VectorN<T>, E> mul(const E &v) const;
        //! Computes this * (s, s, ... , s).
        VectorScalarMul<T, VectorN<T>> mul(const T &s) const;

        //! Computes this / v.
        template <typename E>
        VectorDiv<T, VectorN<T>, E> div(const E &v) const;
        //! Computes this / (s, s, ... , s).
        VectorScalarDiv<T, VectorN<T>> div(const T &s) const;

        //! Computes dot product.
        template <typename E>
        T dot(const E &v) const;

        // MARK: Binary operations: new instance = v (+) this

        //! Computes (s, s, ... , s) - this.
        VectorScalarRSub<T, VectorN<T>> rsub(const T &s);

        //! Computes v - this.
        template <typename E>
        VectorSub<T, VectorN<T>, E> rsub(const E &v) const;

        //! Computes (s, s, ... , s) / this.
        VectorScalarRDiv<T, VectorN<T>> rdiv(const T &s);

        //! Computes v / this.
        template <typename E>
        VectorDiv<T, VectorN<T>, E> rdiv(const E &v) const;

        // MARK: Augmented operations: this (+)= v

        //! Computes this += (s, s, ... , s).

        void iadd(const T &s);

        //! Computes this += v.
        template <typename E>
        void iadd(const E &v);

        //! Computes this -= (s, s, ... , s).
        void isub(const T &s);

        //! Computes this -= v.
        template <typename E>
        void isub(const E &v);

        //! Computes this *= (s, s, ... , s).
        void imul(const T &s);

        //! Computes this *= v.
        template <typename E>
        void imul(const E &v);

        //! Computes this /= (s, s, ... , s).
        void idiv(const T &s);

        //! Computes this /= v.
        template <typename E>
        void idiv(const E &v);

        // MARK: Operators

        //!
        //! \brief Iterates the vector and invoke given \p func for each element.
        //!
        //! This function iterates the vector elements and invoke the callback
        //! function \p func. The callback function takes array's element as its
        //! input. The order of execution will be 0 to N-1 where N is the size of
        //! the vector. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! VectorN<float, 2> vec(10, 4.f);
        //! vec.forEach([](float elem) {
        //!     printf("%d\n", elem);
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void forEach(Callback func) const;

        //!
        //! \brief Iterates the vector and invoke given \p func for each index.
        //!
        //! This function iterates the vector elements and invoke the callback
        //! function \p func. The callback function takes one parameter which is the
        //! index of the vector. The order of execution will be 0 to N-1 where N is
        //! the size of the array. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! VectorN<float, 2> vec(10, 4.f);
        //! vec.forEachIndex([&](size_t i) {
        //!     vec[i] = 4.f * i + 1.5f;
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void forEachIndex(Callback func) const;

        //! Returns the const reference to the \p i -th element.
        const T &operator[](size_t i) const;

        //! Returns the reference to the \p i -th element.
        T &operator[](size_t);

        //! Set vector instance with initializer list.
        template <typename U>
        VectorN &operator=(const std::initializer_list<U> &lst);

        //! Sets vector with expression template.
        template <typename E>
        VectorN &operator=(const VectorExpression<T, E> &other);

     
        VectorN &operator=(const VectorN &other);

    
        VectorN &operator=(VectorN &&other);

        //! Computes this += (s, s, ... , s)
        VectorN &operator+=(const T &s);

        //! Computes this += v
        template <typename E>
        VectorN &operator+=(const E &v);

        //! Computes this -= (s, s, ... , s)
        VectorN &operator-=(const T &s);

        //! Computes this -= v
        template <typename E>
        VectorN &operator-=(const E &v);

        //! Computes this *= (s, s, ... , s)
        VectorN &operator*=(const T &s);

        //! Computes this *= v
        template <typename E>
        VectorN &operator*=(const E &v);

        //! Computes this /= (s, s, ... , s)
        VectorN &operator/=(const T &s);

        //! Computes this /= v
        template <typename E>
        VectorN &operator/=(const E &v);

        //! Returns true if \p other is the same as this vector.
        template <typename E>
        bool operator==(const E &v) const;

        //! Returns true if \p other is the not same as this vector.
        template <typename E>
        bool operator!=(const E &v) const;

    private:
        ContainerType _elements;

    };

    // MARK: Type aliases
    using VectorND = VectorN<double>;
    using VectorNF = VectorN<float>;
}

#include "details/vector_n-inl.h"
