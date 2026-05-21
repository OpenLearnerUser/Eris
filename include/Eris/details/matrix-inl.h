#pragma once
#include <Eris/matrix_expression.h>
#include <Eris/constant.h>

#include <array>
#include <type_traits>

namespace Eris
{

    template <typename T, size_t M,size_t N>
    Matrix<T, M, N>::Matrix()
    {
        set(T(0));
    }

    template <typename T, size_t M,size_t N>
    template <typename... Params>
    Matrix<T, M, N>::Matrix(Params... params)
    {
        ERIS_ASSERT(sizeof...(params) == M * N);
        setRowAt(0, params...);
    }

    template <typename T, size_t M,size_t N>
    Matrix<T, M, N>::Matrix(const Matrix &other)
    {
        set(other);
    }

    template <typename T, size_t M,size_t N>
    template <typename U>
    Matrix<T, M, N>::Matrix(const std::initializer_list<std::initializer_list<U>> &lst)
    {
        set(lst);
    }

    template <typename T, size_t M,size_t N>
    template <typename E>
    Matrix<T, M, N>::Matrix(const MatrixExpression<T, E> &other)
    {
        set(other);
    }

    template <typename T, size_t M,size_t N>
    void Matrix<T, M, N>::set(T value)
    {
        _elements.fill(value);
    }

    template <typename T, size_t M,size_t N>
    void Matrix<T, M, N>::set(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        size_t rows = lst.size();
        size_t cols = lst.end() - lst.begin();
        ERIS_ASSERT(rows == M && cols == N);

        auto rowIter = begin();
        for (size_t i = 0; i < rows; i++)
        {
            Eris_ASSERT(rowIter->size() == cols);
            auto colIter = rowIter->begin();
            for (size_t j = 0; j < cols; j++)
            {
                (*this)(i, j) = *colIter++;
            }
            rowIter++;
        }
    }

    //! Copies from input matrix expression.
    template <typename T, size_t M,size_t N>
    template <typename E>
    void Matrix<T, M, N>::set(const MatrixExpression<T, E> &other)
    {
        const E &expression = other();
        forEachIndex([&](size_T i, size_t j)
                     { (*this)(i, j) = expression(i, j); });
    }

    template <typename T, size_t M,size_t N>
    void Matrix<T, M, N>::setDiagonal(T value)
    {
        const size_t l = std::min(rows(), cols());
        for (size_t i = 0; i < l; i++)
        {
            (*this)(i, i) = value;
        }
    }

    template <typename T, size_t M,size_t N>

    void Matrix<T, M, N>::setOffDiagonal(T value)
    {
        forEachIndex([&](size_t i, size_t j)
                     {
            if(i!=j)
                (*this)(i,j)=value; });
    }

    template <typename T, size_t M,size_t N>
    template <typename E>
    void Matrix<T, M, N>::setRow(size_t row, const VectorExpression<T, E> &other){
        Eris_ASSERT(other.size()==cols());
        const E& e=other();
        for(size_t j=0;j<cols();j++){
            *(this)(row,j)=e[j];
        }
    }

    template <typename T, size_t M,size_t N>
    template <typename E>
    void Matrix<T, M, N>::setCol(size_t col, const VectorExpression<T, E> &other){
        ERIS_ASSERT(other.size()==rows());
        const E& e=other();
        for(size_t i=0;i<rows();i++){
            *(this)(i,col)=e[i];
        }

    }

    template <typename T, size_t M,size_t N>
    template <typename E>
    bool Matrix<T, M, N>::isEqual(const MatrixExpression<T, E> &other) const{
        const E& expression=other();
        if(size()!=other.size()){
            return false;
        }
        for(size_t i=0;i<rows();i++){
            for(size_t j=0;j<cols();j++){
                if((*this)(i,j)!=expression(i,j)){
                    return false;
                }
            }
        }

        return true;
    }

    template <typename T, size_t M,size_t N>
    template <typename E>
    bool Matrix<T, M, N>::isSimilar(const MatrixExpression<T, E> &other, double tol = std::numeric_limits<double>::epsilon()) const{
        const E &expression = other();
        if (size() != other.size())
        {
            return false;
        }
        for (size_t i = 0; i < rows(); i++)
        {
            for (size_t j = 0; j < cols(); j++)
            {
                if (std::abs((*this)(i, j) - expression(i, j)) > tol)
                {
                    return false;
                }
            }
        }
        return true;

    }


    template <typename T, size_t M,size_t N>
    bool Matrix<T, M, N>::isSquare() const{
        return rows()==cols();
    }

    template <typename T, size_t M,size_t N>
    constexpr Size2 Matrix<T, M, N>::size() const{
        return Size2(M, N);
    }

    template <typename T, size_t M,size_t N>
    constexpr size_t Matrix<T, M, N>::rows() const{
        return M;
    }

    template <typename T, size_t M,size_t N>
    constexpr size_t Matrix<T, M, N>::cols() const{
        return N;
    }

    template <typename T, size_t M,size_t N>
    T *Matrix<T, M, N>::data() const{
        return _elements.data();
    }

    template <typename T, size_t M,size_t N>
    const T *const Matrix<T, M, N>::data() const{
        return _elements.data();
    }

    template <typename T, size_t M,size_t N>
    Iterator Matrix<T, M, N>::begin(){
        return _elements.begin();
    }

    template <typename T, size_t M,size_t N>
    ConstIterator Matrix<T, M, N>::begin() const{
        return _elements.begin();
    }

    template <typename T, size_t M,size_t N>
    typename Matrix<T,M,N>::Iterator Matrix<T, M, N>::end(){
        return _elements.end();
    }
    template <typename T, size_t M,size_t N>
   typename Matrix<T,M,N>::ConstIterator Matrix<T, M, N>::end()const{
        return _elements.end();
    }

    template <typename T, size_t M, size_t N>
    MatrixScalarAdd<T, Matrix<T,M,N>> Matrix<T, M, N>::add(const T &value)
    {
        return MatrixScalarAdd<T, Matrix<T,M,N>>(*this, value);
    }

    template <typename T, size_t M,size_t N>
    template <typename E>
    MatrixAdd<T, Matrix<T,M,N>, E> Matrix<T, M, N>::add(const E &m) const{
        return MatrixAdd<T,Matrix<T,M,N>>(*this,m);
    }

    template <typename T, size_t M,size_t N>
    MatrixScalarSub<T, Matrix<T,M,N>> Matrix<T, M, N>::sub(const T &value){
        return MatrixScalarSub<T, Matrix<T,M,N>>(*this, value);
    }

    template <typename T, size_t M,size_t N>
    template <typename E>
    MatrixSub<T, Matrix<T,M,N>, E> Matrix<T, M, N>::sub(const E &m) const{
        return MatrixSub<T,Matrix<T,M,N>,E>(*this,m);
    }

    template <typename T, size_t M,size_t N>
    MatrixScalarMul<T, Matrix<T,M,N>> Matrix<T,M,N>::mul(const T &value){
        return MatrixScalarMul<T, Matrix<T,M,N>>(*this, value);
    }

    //! Multiplies this matrix by input vector.
    template<typename T,size_t M,size_t N>
    template <typename VE>
    MatrixVectorMul<T, Matrix<T,M,N>, VE> Matrix<T,M,N>::mul(const VectorExpression<T, VE> &other){
        return MatrixVectorMul<T, Matrix<T,M,N>, VE>(*this, other);
    }

    template<typename T,size_t M,size_t N>
    template <size_t L>
    MatrixMul<T, Matrix<T,M,N>, Matrix<T, N, L>> Matrix<T,M,N>::Matrmul(const Matrix<T, N, L> &other){
        return MatrixMul<T, Matrix<T,M,N>, Matrix<T, N, L>>(*this, other);
    }

    //! Divides all elements of the matrix by \p value.
    MatrixScalardiv<T, Matrix> div(const T &value);

    // MARK: Binary operator methods - new instance = input (+) this instance
    template <typename T, size_t M,size_t N>
    MatrixScalarAdd<T, Matrix> radd(const T &s) const;

    template <typename T, size_t M,size_t N>
    template <typename E>
    MatrixAdd<T, Matrix, E> radd(const E &m) const;

    template <typename T, size_t M,size_t N>
    MatrixScalarRSub<T, Matrix> rsub(const T &s) const;

    template <typename T, size_t M,size_t N>
    template <typename E>
    MatrixSub<T, Matrix, E> rsub(const E &m) const;

    template <typename T, size_t M,size_t N>
    MatrixScalarMul<T, Matrix> rmul(const T &s) const;

    template <typename T, size_t M,size_t N>
    template <size_t L>
    MatrixMul<T, Matrix<T, N, L>, Matrix> rmul(const Matrix<T, N, L> &m) const;

    template <typename T, size_t M,size_t N>
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
    template <typename T, size_t M,size_t N>
    T sum() const;

    template <typename T, size_t M,size_t N>
    T avg() const;

    template <typename T, size_t M,size_t N>
    T min() const;

    template <typename T, size_t M,size_t N>
    T max() const;

    template <typename T, size_t M,size_t N>
    T absmin() const;

    template <typename T, size_t M,size_t N>
    T absmax() const;

    template <typename T, size_t M,size_t N>
    //! \warning Should be a square matrix.
    T trace() const;

    template <typename T, size_t M,size_t N>
    T determinant() const;

    template <typename T, size_t M,size_t N>
    MatrixDiagonal<T, Matrix> diagonal() const;

    template <typename T, size_t M,size_t N>
    MatrixDiagonal<T, Matrix> offDiagonal() const;

    template <typename T, size_t M,size_t N>
    MatrixTriangular<T, Matrix> strictLowerTri() const;

    template <typename T, size_t M,size_t N>
    MatrixTriangular<T, Matrix> strictUpperTri() const;

    template <typename T, size_t M,size_t N>
    MatrixTriangular<T, Matrix> lowerTri() const;

    template <typename T, size_t M,size_t N>
    MatrixTriangular<T, Matrix> upperTri() const;

    template <typename T, size_t M,size_t N>
    Matrix<T, M, N> transposed() const;

    template <typename T, size_t M,size_t N>
    Matrix inverse() const;

    template <typename U>
    MatrixTypeCast<U, Matrix, T> castTo() const;

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

    template <typename T, size_t M,size_t N>
    T &operator[](size_t i);

    template <typename T, size_t M,size_t N>
    const T &operator[](size_t i) const;

    template <typename T, size_t M,size_t N>
    T &operator()(size_t i, size_t j);

    template <typename T, size_t M,size_t N>
    const T &operator()(size_t i, size_t j) const;

    template <typename T, size_t M,size_t N>
    template <typename E>
    bool operator==(const MatrixExpression<T, E> &m) const;

    template <typename T, size_t M,size_t N>
    template <typename E>
    bool operator!=(const MatrixExpression<T, E> &m) const;

    template <typename T, size_t M,size_t N>
    template <typename Callback>
    void forEach(Callback func) const;

    template <typename T, size_t M,size_t N>
    template <typename Callback>
    void forEachIndex(Callback func) const;

    template <typename T, size_t M,size_t N>
    static MatrixConstant<T> makeZero();

    template <typename T, size_t M,size_t N>
    static MatrixIdentity<T> makeIdentity();

    template <typename T, size_t M, size_t N>
    template <typename... Params>
    void Matrix<T, M, N>::setRowAt(size_t i, T v, Params... params)
    {
    }

    template <typename T, size_t M, size_t N>
    void setRowAt(size_t i, T v)
    {
    }
}
