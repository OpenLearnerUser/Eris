#pragma once
#include<Eris/matrix_expression.h>
#include<Eris/constant.h>

#include<array>
#include<type_traits>


namespace Eris{

    //!
    //! \brief Static-sized M x N matrix class.
    //!
    //! This class defines M x N row-major matrix data where its size is determined
    //! statically at compile time.
    //!
    //! \tparam T - Real number type.
    //! \tparam M - Number of rows.
    //! \tparam N - Number of columns.
    //!
    template<typename T,size_t M,size_t N>
    class Matrix final:public MatrixExpression<T,Matrix<T,M,N>>{
        public:
            static_assert(
                M > 0,
                "Number of rows for static-sized matrix should be greater than zero.");
            static_assert(
                N > 0,
                "Number of columns for static-sized matrix should be greater than "
                "zero.");
            static_assert(!(M == 2 && N == 2) && !(M == 3 && N == 3) &&
                              !(M == 4 && N == 4),
                          "Use specialized matrix for 2z2, 3x3, and 4x4 matricies.");
            static_assert(std::is_floating_point<T>::value,
                          "Matrix only can be instantiated with floating point types");

            typedef std::array<T,M*N> ContainerType;
            
            typedef typename ContainerType::iterator Iterator;
            typedef typename ContainerType::const_iterator ConstIterator;

            //! Default constructor.
            //! \warning This constructor will create zero matrix.
            Matrix();

            //! Constructs matrix instance with parameters.
            template<typename... Params>
            explicit Matrix(Params... params);

            //! Copy constructor.
            Matrix(const Matrix&) ;

            //!
            //! \brief Constructs a matrix with given initializer list \p lst.
            //!
            //! This constructor will build a matrix with given initializer list \p lst
            //! such as
            //!
            //! \code{.cpp}
            //! Matrix<float, 3, 4> mat = {
            //!     {1.f, 2.f, 4.f, 3.f},
            //!     {9.f, 3.f, 5.f, 1.f},
            //!     {4.f, 8.f, 1.f, 5.f}
            //! };
            //! \endcode
            //!
            //! \param lst Initializer list that should be copy to the new matrix.
            //!

            Matrix(const std::initializer_list<std::initializer_list<T>>& lst);


            //! Constructs matrix instance with given matrix expression.
            template<typename E>
            Matrix(const MatrixExpression<T,E>& other);

            //! Resizes to m x n matrix with initial value \p s.
            void resize(size_t m,size_t n,const T& value=T(0));

            //! Sets all elements to \p value.
            void set(const T& value);

            //!
            //! \brief Sets a matrix with given initializer list \p lst.
            //!
            //! This function will fill the matrix with given initializer list \p lst
            //! such as
            //!
            //! \code{.cpp}
            //! Matrix<float, 3, 4> mat;
            //! mat.set({
            //!     {1.f, 2.f, 4.f, 3.f},
            //!     {9.f, 3.f, 5.f, 1.f},
            //!     {4.f, 8.f, 1.f, 5.f}
            //! });
            //! \endcode
            //!
            //! \param lst Initializer list that should be copy to the new matrix.
            //!
            template<typename U>
            void set(const std::initializer_list<std::initializer_list<U>>& lst);

            //! Copies from input matrix expression.
            template <typename E>
            void set(const MatrixExpression<T, E> &other);

            //! Sets diagonal elements to \p value.
            void setDiagonal(const T& value);


            //! Sets off-diagonal elements to \p value.
            //!
            //! This function will fill the off-diagonal elements of the matrix with
            //! given value.
            //!
            //! \code{.cpp}
            //! Matrix<float, 3, 4> mat;
            //! mat.setOffDiagonal(1.f);
            //! \endcode
            //!
            //! \param value Value to be set to the off-diagonal elements.
            //!
            void setOffDiagonal(const T& value);

            //! Sets i-th row with input vector.
            template<typename E>
            void setRow(size_t row,const VectorExpression<T, E>& other);


            //! Sets i-th column with input vector.
            template<typename E>
            void setColumn(size_t col,const VectorExpression<T, E>& other);


            //! Checks if the matrix is equal to input matrix expression.
            template<typename E>
            bool isEqual(const MatrixExpression<T, E>& other)const;

            //! Checks if the matrix is similar to input matrix expression.
            //!
            //! This function will check if the matrix is similar to input matrix expression
            //! with given tolerance \p tol.
            //!
            //! \param other Tolerance value to be used for comparison.
            //! \param tol Tolerance value to be used for comparison.
            //! \return True if the matrix is similar to input matrix expression, False otherwise.
            //!
            template <typename E>
            bool isSimilar(const MatrixExpression<T, E> &other, double tol = std::numeric_limits<double>::epsilon())const;


            //! Checks if the matrix is square.
            //!
            //! This function will check if the matrix is square.
            //!
            //! \return True if the matrix is square, False otherwise.
            //!
            constexpr bool isSquare() const;


            constexpr Size2 size()const;

            //! Returns the number of rows.
            constexpr size_t rows()const;

            //! Returns the number of columns.
            constexpr size_t cols()const;

            //! Returns the pointer to the data of the matrix.
            T* data();

            const T* const data()const;

            //! Returns the iterator to the first element of the matrix.
            Iterator begin();

            //! Returns the constant iterator to the first element of the matrix.
            ConstIterator begin()const;

            //! Returns the iterator to the last element of the matrix.
            Iterator end();
            //! Returns the constant iterator to the last element of the matrix.
            ConstIterator end()const;


            //! Adds a scalar value to all elements of the matrix.
            MatrixScalarAdd<T, Matrix> add(const T& value) const;

            //! Returns this matrix + input matrix (element-wise).
            template <typename E>
            MatrixAdd<T, Matrix, E> add(const E &m) const;

            //! Subtracts a scalar value to all elements of the matrix.
            MatrixScalarSub<T, Matrix> sub(const T &value) const;

            //! Returns this matrix - input matrix (element-wise).
            template <typename E>
            MatrixSub<T, Matrix, E> sub(const E &m) const;


            //! Multiplies all elements of the matrix by \p value.
            MatrixScalarMul<T,Matrix> mul(const T &value) const;

            //! Multiplies this matrix by input vector.
            template< typename VE>
            MatrixVectorMul<T, Matrix,VE> mul(const VectorExpression<T, VE> &other) const;

            //! Multiplies this matrix by input matrix.
            template <size_t L>
            MatrixMul<T, Matrix, Matrix<T, N, L>> mul(const Matrix<T, N, L> &other) const;


            //! Divides all elements of the matrix by \p value.
            MatrixScalarDiv<T,Matrix> div(const T &value) const;

            // MARK: Binary operator methods - new instance = input (+) this instance
            //! Returns input scalar + this matrix.
            MatrixScalarAdd<T, Matrix> radd(const T &s) const;

            //! Returns input matrix + this matrix (element-wise).
            template <typename E>
            MatrixAdd<T, Matrix, E> radd(const E &m) const;

            //! Returns input scalar - this matrix.
            MatrixScalarRSub<T, Matrix> rsub(const T &s) const;

            //! Returns input matrix - this matrix (element-wise).
            template <typename E>
            MatrixSub<T, Matrix, E> rsub(const E &m) const;

            //! Returns input scalar * this matrix.
            MatrixScalarMul<T, Matrix> rmul(const T &s) const;

            //! Returns input matrix * this matrix.
            template <size_t L>
            MatrixMul<T, Matrix<T, N, L>, Matrix> rmul(const Matrix<T, N, L> &m) const;

            //! Returns input matrix / this scalar.
            MatrixScalarRDiv<T, Matrix> rdiv(const T &s) const;

            // MARK: Augmented operator methods - this instance (+)= input

            //! Adds input scalar to this matrix.
            void iadd(const T &s);

            //! Adds input matrix to this matrix (element-wise).
            template <typename E>
            void iadd(const E &m);

            //! Subtracts input scalar from this matrix.
            void isub(const T &s);

            //! Subtracts input matrix from this matrix (element-wise).
            template <typename E>
            void isub(const E &m);

            //! Multiplies input scalar to this matrix.
            void imul(const T &s);

            //! Multiplies input matrix to this matrix.
            template <typename E>
            void imul(const E &m);

            //! Divides this matrix with input scalar.
            void idiv(const T &s);

            // MARK: Modifiers

            //! Transposes this matrix.
            void transpose();

            //!
            //! \brief Inverts this matrix.
            //!
            //! This function computes the inverse using Gaussian elimination method.
            //!
            void invert();

            // MARK: Complex getters
            //! Returns sum of all elements.
            T sum() const;

            //! Returns average of all elements.
            T avg() const;

            //! Returns minimum among all elements.
            T min() const;

            //! Returns maximum among all elements.
            T max() const;

            //! Returns absolute minimum among all elements.
            T absmin() const;

            //! Returns absolute maximum among all elements.
            T absmax() const;

            //! Returns sum of all diagonal elements.
            //! \warning Should be a square matrix.
            T trace() const;

            //! Returns determinant of this matrix.
            T determinant() const;

            //! Returns diagonal part of this matrix.
            MatrixDiagonal<T, Matrix> diagonal() const;

            //! Returns off-diagonal part of this matrix.
            MatrixDiagonal<T, Matrix> offDiagonal() const;

            //! Returns strictly lower triangle part of this matrix.
            MatrixTriangular<T, Matrix> strictLowerTri() const;

            //! Returns strictly upper triangle part of this matrix.
            MatrixTriangular<T, Matrix> strictUpperTri() const;

            //! Returns lower triangle part of this matrix (including the diagonal).
            MatrixTriangular<T, Matrix> lowerTri() const;

            //! Returns upper triangle part of this matrix (including the diagonal).
            MatrixTriangular<T, Matrix> upperTri() const;

            //! Returns transposed matrix.
            Matrix<T, N, M> transposed() const;

            //! Returns inverse matrix.
            Matrix inverse() const;

            template <typename U>
            MatrixTypeCast<U, Matrix> castTo() const;

            // MARK: Setter operators

            //! Assigns input matrix.
            template <typename E>
            Matrix &operator=(const E &m);

            //! Copies to this matrix.
            Matrix &operator=(const Matrix &other);

            //! Addition assignment with input scalar.
            Matrix &operator+=(const T &s);

            //! Addition assignment with input matrix (element-wise).
            template <typename E>
            Matrix &operator+=(const E &m);

            //! Subtraction assignment with input scalar.
            Matrix &operator-=(const T &s);

            //! Subtraction assignment with input matrix (element-wise).
            template <typename E>
            Matrix &operator-=(const E &m);

            //! Multiplication assignment with input scalar.
            Matrix &operator*=(const T &s);

            //! Multiplication assignment with input matrix.
            template <typename E>
            Matrix &operator*=(const E &m);

            //! Division assignment with input scalar.
            Matrix &operator/=(const T &s);

            // MARK: Getter operators

            //! Returns reference of i-th element.
            T &operator[](size_t i);

            //! Returns constant reference of i-th element.
            const T &operator[](size_t i) const;

            //! Returns reference of (i,j) element.
            T &operator()(size_t i, size_t j);

            //! Returns constant reference of (i,j) element.
            const T &operator()(size_t i, size_t j) const;

            //! Returns true if is equal to m.
            template <typename E>
            bool operator==(const MatrixExpression<T, E> &m) const;

            //! Returns true if is not equal to m.
            template <typename E>
            bool operator!=(const MatrixExpression<T, E> &m) const;

            // MARK: Helpers

            //!
            //! \brief Iterates the matrix and invoke given \p func for each index.
            //!
            //! This function iterates the matrix elements and invoke the callback
            //! function \p func. The callback function takes matrix's element as its
            //! input. The order of execution will be the same as the nested for-loop
            //! below:
            //!
            //! \code{.cpp}
            //! MatrixMxN<double> mat(100, 200, 4.0);
            //! for (size_t i = 0; i < mat.rows(); ++i) {
            //!     for (size_t j = 0; j < mat.cols(); ++j) {
            //!         func(mat(i, j));
            //!     }
            //! }
            //! \endcode
            //!
            //! Below is the sample usage:
            //!
            //! \code{.cpp}
            //! MatrixMxN<double> mat(100, 200, 4.0);
            //! mat.forEach([](double elem) {
            //!     printf("%d\n", elem);
            //! });
            //! \endcode
            //!
            template <typename Callback>
            void forEach(Callback func) const;

            //!
            //! \brief Iterates the matrix and invoke given \p func for each index.
            //!
            //! This function iterates the matrix elements and invoke the callback
            //! function \p func. The callback function takes two parameters which are
            //! the (i, j) indices of the matrix. The order of execution will be the
            //! same as the nested for-loop below:
            //!
            //! \code{.cpp}
            //! MatrixMxN<double> mat(100, 200, 4.0);
            //! for (size_t i = 0; i < mat.rows(); ++i) {
            //!     for (size_t j = 0; j < mat.cols(); ++j) {
            //!         func(i, j);
            //!     }
            //! }
            //! \endcode
            //!
            //! Below is the sample usage:
            //!
            //! \code{.cpp}
            //! MatrixMxN<double> mat(100, 200, 4.0);
            //! mat.forEachIndex([&](size_t i, size_t j) {
            //!     mat(i, j) = 4.0 * i + 7.0 * j + 1.5;
            //! });
            //! \endcode
            //!
            template <typename Callback>
            void forEachIndex(Callback func) const;

            // MARK: Builders

            //! Makes a M x N matrix with zeros.
            static MatrixConstant<T> makeZero();

            //! Makes a M x N matrix with all diagonal elements to 1, and other elements
            //! to 0.
            static MatrixIdentity<T> makeIdentity();


        private:

            ContainerType  _elements;

            template<typename... Params>
            void setRowAt(size_t i,T v,Params... params);
            void setRowAt(size_t i,T v);
    };


}

#include "details/matrix-inl.h"
