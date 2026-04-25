#pragma once 
#include <Eris/ArrayAccessor.h>
#include <utility> 


namespace Eris{

//!
//! \brief 1-D array accessor class.
//!
//! This class represents 1-D array accessor. Array accessor provides array-like
//! data read/write functions, but does not handle memory management. Thus, it
//! is more like a random access iterator, but with multi-dimension support.
//!
//! \see Array1<T, 2>
//!
//! \tparam T - Array value type.
//!
template<typename T>
class ArrayAccessor<T,1> final{
public:
    //! Constructs empty 1-D array accessor.
    ArrayAccessor();
    //! Constructs an array accessor that wraps given array.
    ArrayAccessor(size_t t, T* const data);
    //! Copy constructor.
    ArrayAccessor(const ArrayAccessor& other);

    //! Replaces the content with given \p other array accessor.
    void set(const ArrayAccessor& other);


    void reset(size_t i, T* const data);

    T& at(size_t t);
    //! Returns the const reference to the i-th element.
    const T& at(size_t i) const;

    //! Returns the begin iterator of the array.
    T* const begin() const;

    //! Returns the end iterator of the array.
    T* const end() const;

    //! Returns the begin iterator of the array.
    T* begin();

    //! Returns the end iterator of the array.
    T* end();

    //! Returns size of the array.
    size_t size() const;

    //! Returns the raw pointer to the array data.
    T* const data() const;

    //! Swaps the content of with \p other array accessor.
    void swap(ArrayAccessor& other);

    //!
    //! \brief Iterates the array and invoke given \p func for each element.
    //!
    //! This function iterates the array elements and invoke the callback
    //! function \p func. The callback function takes array's element as its
    //! input. The order of execution will be 0 to N-1 where N is the size of
    //! the array. Below is the sample usage:
    //!
    //! \code{.cpp}
    //! int data = {1, 2, 3, 4, 5, 6};
    //! ArrayAccessor<int, 1> acc(6, data);
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
    //! function \p func. The callback function takes one parameter which is the
    //! index of the array. The order of execution will be 0 to N-1 where N is
    //! the size of the array. Below is the sample usage:
    //!
    //! \code{.cpp}
    //! int data = {1, 2, 3, 4, 5, 6};
    //! ArrayAccessor<int, 1> acc(6, data);
    //! acc.forEachIndex([&](size_t i) {
    //!     acc[i] = 4.f * i + 1.5f;
    //! });
    //! \endcode
    //!
    template <typename Callback>
    void forEachIndex(Callback func) const;


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
    //! int data = {1, 2, 3, 4, 5, 6};
    //! ArrayAccessor<int, 1> acc(6, data);
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
    //! function takes one parameter which is the index of the array. The order
    //! of execution will be non-deterministic since it runs in parallel.
    //! Below is the sample usage:
    //!
    //! \code{.cpp}
    //! int data = {1, 2, 3, 4, 5, 6};
    //! ArrayAccessor<int, 1> acc(6, data);
    //! acc.parallelForEachIndex([](size_t i) {
    //!     acc[i] *= 2;
    //! });
    //! \endcode
    //!
    template <typename Callback>
    void parallelForEachIndex(Callback func) const;

    //! Returns the reference to i-th element.
    T& operator[](size_t i);

    //! Returns the const reference to i-th element.
    const T& operator[](size_t i) const;

    ArrayAccessor&  operator=(const ArrayAccessor& other);

    operator ConstArrayAccessor<T,1>()const;

    private:
        size_t _size;
        T* _data;
};


template<typename T> using ArrayAccessor1=ArrayAccessor<T,1>;


//!
//! \brief 1-D read-only array accessor class.
//!
//! This class represents 1-D read-only array accessor. Array accessor provides
//! array-like data read/write functions, but does not handle memory management.
//! Thus, it is more like a random access iterator, but with multi-dimension
//! support.
//!
template <typename T>
class ConstArrayAccessor<T, 1> {

    public:
        ConstArrayAccessor();
        //! Constructs an read-only array accessor that wraps given array.
        ConstArrayAccessor(size_t t,const T* const data);

        explicit ConstArrayAccessor(const ArrayAccessor<T,1>& other);

        ConstArrayAccessor(const ConstArrayAccessor& other);

        const T& at(size_t)const;

        const T* const begin()const;

        const T* const end()const;
        //! Returns size of the array.
        size_t size() const;

        //! Returns the raw pointer to the array data.
        const T* const data() const;

         //!
    //! \brief Iterates the array and invoke given \p func for each element.
    //!
    //! This function iterates the array elements and invoke the callback
    //! function \p func. The callback function takes array's element as its
    //! input. The order of execution will be 0 to N-1 where N is the size of
    //! the array. Below is the sample usage:
    //!
    //! \code{.cpp}
    //! int data = {1, 2, 3, 4, 5, 6};
    //! ConstArrayAccessor<int, 1> acc(6, data);
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
    //! function \p func. The callback function takes one parameter which is the
    //! index of the array. The order of execution will be 0 to N-1 where N is
    //! the size of the array. Below is the sample usage:
    //!
    //! \code{.cpp}
    //! int data = {1, 2, 3, 4, 5, 6};
    //! ConstArrayAccessor<int, 1> acc(6, data);
    //! acc.forEachIndex([&](size_t i) {
    //!     data[i] = acc[i] * acc[i];
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
    //! function takes one parameter which is the index of the array. The order
    //! of execution will be non-deterministic since it runs in parallel.
    //! Below is the sample usage:
    //!
    //! \code{.cpp}
    //! int data = {1, 2, 3, 4, 5, 6};
    //! ConstArrayAccessor<int, 1> acc(6, data);
    //! accessor.parallelForEachIndex([](size_t i) {
    //!     data[i] = acc[i] * acc[i];
    //! });
    //! \endcode
    //!
    template <typename Callback>
    void parallelForEachIndex(Callback func) const;

    const T& operator[](size_t i)const;

    private:
        size_t _size;
        const T* _data;


};

//! Type alias for 1-D const array accessor.
template <typename T> using ConstArrayAccessor1 = ConstArrayAccessor<T, 1>;





}
#include "details/ArrayAccessor1-inl.h"




