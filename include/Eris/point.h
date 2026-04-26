#pragma once
#include <Eris/macro.h>
#include <array>
#include <type_traits>

namespace Eris
{

    template <typename T, size_t N>
    class Point final
    {
        public:

        static_assert(N > 0, "Size of static-sized point should be greater than zero.");
        static_assert(
            std::is_arithmetic<T>::value,
            "Point only can be instantiated with arithmetic types");

        Point();
        //! Constructs point instance with parameters.
        template <typename... Param>
        explicit Point(Param... param);

        //! Constructs point instance with initiazer list.
        template <typename U>
        explicit Point(const std::initializer_list<U> &lst);

        //! Copy constructor.

        Point(const Point &others);
        //! Set point instance with initializer list.
        template <typename U>
        void set(const std::initializer_list<U> &lst);

        //! Set point instance with other point.
        void set(const Point &others);

        //! Set point instance with initializer list.
        template <typename U>
        Point &operator=(const std::initializer_list<U> &lst);

        //! Set point instance with other point.
        Point &operator=(const Point &other);

        //! Returns the const reference to the \p i -th element.
        const T &operator[](size_t i) const;

        //! Returns the reference to the \p i -th element.
        T &operator[](size_t);

        private:
        std::array<T,N> _elements;
        

        template<typename... Param>
        void setAt(size_t i,T v,Param... param);

        void setAt(size_t i,T V);

            


    };

}

#include "Eris/details/point-inl.h"
