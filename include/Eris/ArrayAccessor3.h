#pragma once
#include <Eris/ArrayAccessor.h>
#include <Eris/point3.h>
#include <Eris/size3.h>
#include <utility>

namespace Eris
{

    //!
    //! \brief 3-D array accessor class.
    //!
    //! This class represents 3-D array accessor. Array accessor provides array-like
    //! data read/write functions, but does not handle memory management. Thus, it
    //! is more like a random access iterator, but with multi-dimension support.
    //! Similar to Array<T, 3>, this class interprets a linear array as a 3-D array
    //! using i-major indexing.
    //!
    //! \see Array<T, 3>
    //!
    //! \tparam T - Array value type.
    //!
    template <typename T>
    class ArrayAccessor<T, 3> final
    {
    public:
        //! Constructs empty 3-D array accessor.
        ArrayAccessor();
        //! Constructs an array accessor that wraps given array.
        ArrayAccessor(const Size3& t, T *const data);
        //! Copy constructor.
        ArrayAccessor(const ArrayAccessor &other);

        //! Replaces the content with given \p other array accessor.
        void set(const ArrayAccessor &other);

        //! Resets the array.
        void reset(const Size3& size, T *const data);
        //! Resets the array.
        void reset(size_t width, size_t height, size_t depth, T *const data);
        //! Returns the reference to the i-th element.
        T &at(size_t t);
        //! Returns the const reference to the i-th element.
        const T &at(size_t i) const;

        //! Returns the reference to the element at (pt.x, pt.y, pt.z).
        T &at(const Point3UI &t);
        //! Returns the reference to the element at (pt.x, pt.y, pt.z).
        const T &at(const Point3UI &i) const;

        //! Returns the reference to the element at (i, j, k).
        T &at(size_t width, size_t height, size_t depth);
        //! Returns the reference to the element at (i, j, k).
        const T &at(size_t width, size_t height, size_t depth) const;

        //! Returns the begin iterator of the array.
        T *const begin() const;

        //! Returns the end iterator of the array.
        T *const end() const;

        //! Returns the begin iterator of the array.
        T *begin();

        //! Returns the end iterator of the array.
        T *end();

        //! Returns size of the array.
        Size3 size() const;

        //! Returns the width of the array.
        size_t width() const;

        //! Returns the height of the array.
        size_t height() const;

        //! Returns the depth of the array.
        size_t depth() const;

        //! Returns the raw pointer to the array data.
        T *const data() const;

        //! Swaps the content of with \p other array accessor.
        void swap(ArrayAccessor &other);

        //!
        //! \brief Iterates the array and invoke given \p func for each index.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes array's element as its
        //! input. The order of execution will be the same as the nested for-loop
        //! below:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! for (size_t k = 0; k < acc.depth(); ++k) {
        //!     for (size_t j = 0; j < acc.height(); ++j) {
        //!         for (size_t i = 0; i < acc.width(); ++i) {
        //!             func(acc(i, j, k));
        //!         }
        //!     }
        //! }
        //! \endcode
        //!
        //! Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! acc.forEach([](int elem) {
        //!     printf("%d\n", elem);
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void forEach(Callback func) const;

        //!
        //! \brief Iterates the array and invoke given \p func for each index.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes three parameters which are
        //! the (i, j, k) indices of the array. The order of execution will be the same
        //! as the nested for-loop below:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! for (size_t k = 0; k < acc.depth(); ++k) {
        //!     for (size_t j = 0; j < acc.height(); ++j) {
        //!         for (size_t i = 0; i < acc.width(); ++i) {
        //!             func(i, j, k);
        //!         }
        //!     }
        //! }
        //! \endcode
        //!
        //! Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! acc.forEachIndex([&](size_t i, size_t j, size_t k) {
        //!     acc(i, j, k) = 4.f * i + 7.f * j + 1.5f;
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void forEachIndex(Callback func) const;

        //!
        //! \brief Iterates the array and invoke given \p func for each index in
        //!     parallel.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes array's element as its
        //! input. The order of execution will be non-deterministic since it runs in
        //! parallel. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! acc.parallelForEach([](int& elem) {
        //!     elem *= 2;
        //! });
        //! \endcode
        //!
        //! The parameter type of the callback function doesn't have to be T&, but
        //! const T& or T can be used as well.
        //!
        template <typename Callback>
        void parallelForEach(Callback func);

        //!
        //! \brief Iterates the array and invoke given \p func for each index in
        //!     parallel using multi-threading.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func in parallel using multi-threading. The callback
        //! function takes three parameters which are the (i, j, k) indices of the
        //! array. The order of execution will be non-deterministic since it runs in
        //! parallel. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! acc.parallelForEachIndex([&](size_t i, size_t j, size_t k) {
        //!     acc(i, j, k) *= 2;
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void parallelForEachIndex(Callback func) const;

        //! Returns the reference to i-th element.
        T &operator[](size_t i);

        //! Returns the const reference to i-th element.
        const T &operator[](size_t i) const;

        //! Returns the reference to the element at (pt.x, pt.y, pt.z).
        T &operator()(const Point3UI &pt);

        //! Returns the const reference to the element at (pt.x, pt.y, pt.z).
        const T &operator()(const Point3UI &pt) const;

        //! Returns the reference to the element at (i, j, k).
        T &operator()(size_t i, size_t j, size_t k);

        //! Returns the const reference to the element at (i, j, k).
        const T &operator()(size_t i, size_t j, size_t k) const;

        ArrayAccessor &operator=(const ArrayAccessor &other);

        operator ConstArrayAccessor<T, 3>() const;

    private:
        Size3 _size;
        T *_data;
    };

    template <typename T>
    using ArrayAccessor3 = ArrayAccessor<T, 3>;

    //!
    //! \brief 3-D read-only array accessor class.
    //!
    //! This class represents 3-D read-only array accessor. Array accessor provides
    //! array-like data read/write functions, but does not handle memory management.
    //! Thus, it is more like a random access iterator, but with multi-dimension
    //! support. Similar to Array<T, 3>, this class interprets a linear array as a
    //! 3-D array using i-major indexing.
    //!
    //! \see Array<T, 3>
    //!
    template <typename T>
    class ConstArrayAccessor<T, 3>
    {

    public:
        ConstArrayAccessor();
        //! Constructs an read-only array accessor that wraps given array.
        ConstArrayAccessor(const Size3& t, const T *const data);

        explicit ConstArrayAccessor(const ArrayAccessor<T, 3> &other);

        ConstArrayAccessor(const ConstArrayAccessor &other);

        const T &at(size_t) const;
        //! Returns the const reference to the element at (pt.x, pt.y, pt.z).
        const T &at(const Point3UI &pt) const;
        //! Returns the const reference to the element at (i, j, k).
        const T &at(size_t i, size_t j, size_t k) const;

        const T *const begin() const;

        const T *const end() const;
        //! Returns size of the array.
        Size3 size() const;

        size_t width() const;

        size_t height() const;

        size_t depth() const;

        //! Returns the raw pointer to the array data.
        const T *const data() const;

        //!
        //! \brief Iterates the array and invoke given \p func for each index.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes array's element as its
        //! input. The order of execution will be the same as the nested for-loop
        //! below:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ConstArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! for (size_t k = 0; k < acc.depth(); ++k) {
        //!     for (size_t j = 0; j < acc.height(); ++j) {
        //!         for (size_t i = 0; i < acc.width(); ++i) {
        //!             func(acc(i, j, k));
        //!         }
        //!     }
        //! }
        //! \endcode
        //!
        //! Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ConstArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! acc.forEach([](int elem) {
        //!     printf("%d\n", elem);
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void forEach(Callback func) const;

        //!
        //! \brief Iterates the array and invoke given \p func for each index.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes three parameters which are
        //! the (i, j, k) indices of the array. The order of execution will be the same
        //! as the nested for-loop below:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ConstArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! for (size_t k = 0; k < acc.depth(); ++k) {
        //!     for (size_t j = 0; j < acc.height(); ++j) {
        //!         for (size_t i = 0; i < acc.width(); ++i) {
        //!             func(i, j, k);
        //!         }
        //!     }
        //! }
        //! \endcode
        //!
        //! Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ConstArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! acc.forEachIndex([&](size_t i, size_t j, size_t k) {
        //!     acc(i, j, k) = 4.f * i + 7.f * j + 1.5f;
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void forEachIndex(Callback func) const;

        //!
        //! \brief Iterates the array and invoke given \p func for each index in
        //!     parallel using multi-threading.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func in parallel using multi-threading. The callback
        //! function takes three parameters which are the (i, j, k) indices of the
        //! array. The order of execution will be non-deterministic since it runs in
        //! parallel. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        //! ConstArrayAccessor<int, 3> acc(2, 3, 2, data);
        //! acc.parallelForEachIndex([&](size_t i, size_t j, size_t k) {
        //!     acc(i, j, k) *= 2;
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void parallelForEachIndex(Callback func) const;

        //! Returns the linear index of the given 3-D coordinate (pt.x, pt.y, pt.z).
        size_t index(const Point3UI &pt) const;

        //! Returns the linear index of the given 3-D coordinate (i, j, k).
        size_t index(size_t i, size_t j, size_t k) const;

        const T &operator[](size_t i) const;

        //! Returns the const reference to the element at (pt.x, pt.y, pt.z).
        const T &operator()(const Point3UI &pt) const;

        //! Returns the const reference to the element at (i, j, k).
        const T &operator()(size_t i, size_t j, size_t k) const;

    private:
        Size3 _size;
        const T *_data;
    };

    //! Type alias for 3-D const array accessor.
    template <typename T>
    using ConstArrayAccessor3 = ConstArrayAccessor<T, 3>;

}
#include "details/ArrayAccessor3-inl.h"
