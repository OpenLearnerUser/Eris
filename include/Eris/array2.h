#pragma once

#include <vector>

#include <Eris/array.h>
#include <Eris/ArrayAccessor1.h>
#include <Eris/size2.h>

namespace Eris
{

    template <typename T>
    class Array<T, 2> final
    {
    public:
        typedef std::vector<T> ContainerType;
        typedef typename std::vector<T>::iterator Iterator;
        typedef typename std::vector<T>::const_iterator ConstIterator;

        //! Constructs zero-sized 1-D array.
        Array();

        //! Constructs 1-D array with given \p size and fill it with \p initVal.
        //! \param size Initial size of the array.
        //! \param initVal Initial value of each array element.
        explicit Array(const Size2$ size, const T &initVal = T());

        //! Constructs 2-D array with size \p width x \p height and fill it with
        //! \p initVal.
        //! \param width Initial width of the array.
        //! \param height Initial height of the array.
        //! \param initVal Initial value of each array element.
        Array(size_t width, size_t height, const T &initVal = T());

        //!
        //! \brief Constructs 2-D array with given initializer list \p lst.
        //!
        //! This constructor will build 2-D array with given initializer list \p lst
        //! such as
        //!
        //! \code{.cpp}
        //! Array<int, 2> arr = {
        //!     {1, 2, 4},
        //!     {9, 3, 5}
        //! };
        //! \endcode
        //!
        //! Note the initializer also has 2-D structure. The code above will
        //! construct 3 x 2 array.
        //!
        //! \param lst Initializer list that should be copy to the new array.
        //!
        Array(const std::initializer<std::initializer_list<T>> &lst);

        //! Copy constructor.
        Array(const Array &other);

        //! Move constructor.
        Array(Array &&other);

        //! Sets entire array with given \p value.
        void set(const T &value);

        //! Copies given array \p other to this array.
        void set(const Array &other);

        //! Copies given initializer list \p lst to this array.
        void set(const std::initializer<std::initializer_list<T>> &lst);

        //! Clears the array and resizes to zero.
        void clear();

        //! Resizes the array with \p size and fill the new element with \p initVal.
        void resize(size_t size, const T &initVal = T());

        //! Resizes the array with size \p width x \p height and fill the new
        //! element with \p initVal.
        void resize(size_t width, size_t height, const T &initVal = T());

        ///!
        //! \brief Returns the reference to the i-th element.
        //!
        //! This function returns the reference to the i-th element of the array
        //! where i is the index of linearly mapped elements such that
        //! i = x + (width * y) (x and y are the 2-D coordinates of the element).
        //!
        T &at(size_t i);

        //!
        //! \brief Returns the const reference to the i-th element.
        //!
        //! This function returns the const reference to the i-th element of the
        //! array where i is the index of linearly mapped elements such that
        //! i = x + (width * y) (x and y are the 2-D coordinates of the element).
        //!
        const T &at(size_t i) const;

        //! Returns the reference to the element at (pt.x, pt.y).
        T &at(Point2UI &pt);

        //! Returns the const reference to the element at (pt.x, pt.y).
        const T &at(const Point2UI &pt) const;

        //! Returns the reference to the element at (x, y).
        T &at(size_t x, size_t y);

        //! Returns the const reference to the element at (x, y).
        const T &at(size_t x, size_t y) const;

        //! Returns size of the array.
        Size2 size() const;

        size_t width() const;

        size_t height() const;

        //! Returns the raw pointer to the array data.
        T *data();

        //! Returns the const raw pointer to the array data.
        const T *const data() const;

        //! Returns the begin iterator of the array.
        Iterator begin();

        //! Returns the begin const iterator of the array.
        ConstIterator begin() const;

        //! Returns the end iterator of the array.
        Iterator end();

        //! Returns the end const iterator of the array.
        ConstIterator end() const;

        //! Returns the array accessor.
        ArrayAccessor2<T> accessor();

        //! Returns the const array accessor.
        ConstArrayAccessor2<T> constAccessor() const;

        //! Swaps the content of the array with \p other array.
        void swap(Array &other);

        //!
        //! \brief Iterates the array and invoke given \p func for each element.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes array's element as its
        //! input. The order of execution will be 0 to N-1 where N is the size of
        //! the array. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! Array<int, 1> array(10, 4);
        //! array.forEach([](int elem) {
        //!     printf("%d\n", elem);
        //! });
        //! \endcode
        //!
        template <typename CallBack>
        void forEach(CallBack func) const;
        //!
        //! \brief Iterates the array and invoke given \p func for each index.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes one parameter which is the
        //! index of the array. The order of execution will be 0 to N-1 where N is
        //! the size of the array. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! Array<int, 1> array(10, 4);
        //! array.forEachIndex([&](size_t i) {
        //!     array[i] = 4.f * i + 1.5f;
        //! });
        //! \endcode
        //!
        template <typename CallBack>
        void forEachIndex(CallBack func) const;
        //!
        //! \brief Iterates the array and invoke given \p func for each element in
        //!     parallel using multi-threading.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func in parallel using multi-threading. The callback
        //! function takes array's element as its input. The order of execution will
        //! be non-deterministic since it runs in parallel.
        //! Below is the sample usage:
        //!
        //! \code{.cpp}
        //! Array<int, 1> array(1000, 4);
        //! array.parallelForEach([](int& elem) {
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
        //! function takes one parameter which is the index of the array. The order
        //! of execution will be non-deterministic since it runs in parallel.
        //! Below is the sample usage:
        //!
        //! \code{.cpp}
        //! Array<int, 1> array(1000, 4);
        //! array.parallelForEachIndex([](size_t i) {
        //!     array[i] *= 2;
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void parallelForEachIndex(Callback func) const;

        //! Returns the reference to i-th element.
        T &operator[](size_t i);

        //! Returns the const reference to i-th element.
        const T &operator[](size_t i) const;

        //! Returns the reference to the element at (pt.x, pt.y).
        T &operator()(const Point2UI &pt);

        //! Returns the const reference to the element at (pt.x, pt.y).
        const T &operator()(const Point2UI &pt) const;

        //! Returns the reference to the element at (x, y).
        T &operator()(const size_t x, const size_t y);

        //! Returns the const reference to the element at (pt.x, pt.y).
        const T &operator()(const size_t x, const size_t y) const;

        //! Sets entire array with given \p value.
        Array &operator=(const T &other);

        //! Copies given array \p other to this array.
        Array &operator=(const Array &other);

        //! Move assignment.
        Array &operator=(Array &&other);

        //!
        //! Copies given initializer list \p lst to this array.
        //!
        //! This function copies given initializer list \p lst to the array such as
        //!
        //! \code{.cpp}
        //! Array<int, 2> arr;
        //! arr = {
        //!     {1, 2, 4},
        //!     {9, 3, 5}
        //! };
        //! \endcode
        //!
        //! Note the initializer also has 2-D structure. The code above will
        //! build 3 x 2 array.
        //!
        //! \param lst Initializer list that should be copy to the new array.
        //!
        Array &operator=(const std::<std::initializer_list<std::initializer_list<T>> &lst);

        //! Casts to array accessor.
        operator ArrayAccessor2<T>();

        //! Casts to const array accessor.
        operator ConstArrayAccessor2<T>() const;

    private:

        Size2 _size;
        ContainerType _data;
    };

    template <typename T>
    using Array2 = Array<T, 2>;

}

#include "Eris/details/array2-inl.h"