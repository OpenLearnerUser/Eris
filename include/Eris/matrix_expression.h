#pragma once
#include <Eris/macro.h>
#include "Eris/functors.h"
#include <Eris/size2.h>
#include <Eris/vector_expression.h>

namespace Eris
{

    // MARK : MatrixExpression

    //!
    //! \brief Base class for matrix expression.
    //!
    //! matrix expression is a meta type that enables template expression pattern.
    //!
    //! \tparam T - Real number type.
    //! \tparam E - Subclass type.

    template <typename T, typename E>
    class MatrixExpression
    {

    public:
        Size2 size() const;
        size_t rows() const;
        size_t cols() const;
        const E &operator()() const;
    };

    //!
    //! \brief Constant matrix expression.
    //!
    //! This matrix expression represents a constant matrix.
    //!
    //! \tparam T  Real number type.
    //!
    template <typename T>
    class MatrixConstant : public MatrixExpression<T, MatrixConstant<T>>
    {
    public:
        MatrixConstant(const size_t &m, size_t n, const T &c);
        //! Size of the matrix.
        Size2 size() const;
        size_t rows() const;
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    public:
        size_t _m;
        size_t _n;
        T _c;
    };

    //!
    //! \brief Identity matrix expression.
    //!
    //! This matrix expression represents an identity matrix.
    //!
    //! \tparam T  Real number type.
    //!
    template <typename T>
    class MatrixIdentity : public MatrixExpression<T, MatrixIdentity<T>>
    {
    public:
        MatrixIdentity(const size_t &m);
        //! Size of the matrix.
        Size2 size() const;
        size_t rows() const;
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    public:
        size_t _m;
    };

    // MARK: MatrixUnaryOp

    //!
    //! \brief Matrix expression for unary operation.
    //!
    //! This matrix expression represents an unary matrix operation that takes
    //! single input matrix expression.
    //!
    //! \tparam T   Real number type.
    //! \tparam E   Input expression type.
    //! \tparam Op  Unary operation.
    //!
    template <typename T, typename E, typename Op>
    class MatrixUnaryOp : public MatrixExpression<T, MatrixUnaryOp<T, E, Op>>
    {
    public:
        MatrixUnaryOp(const E &u);
        //! Size of the matrix.
        Size2 size() const;
        size_t rows() const;
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    public:
        const E &_u;
        Op _op;
    };

    //!
    //! \brief Diagonal matrix expression.
    //!
    //! This matrix expression represents a diagonal matrix for given input matrix
    //! expression.
    //!
    //! \tparam T  Real number type.
    //! \tparam E  Input expression type.
    //!
    template <typename T, typename E>
    class MatrixDiagonal : public MatrixExpression<T, MatrixDiagonal<T, E>>
    {
    public:
        MatrixDiagonal(const E &u, bool isDiag = true);
        //! Size of the matrix.
        Size2 size() const;
        //! Number of rows.
        size_t rows() const;
        //! Number of columns.
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    public:
        bool _isDiag;
        const E &_u;
    };

    //!
    //! \brief Triangular matrix expression.
    //!
    //! This matrix expression represents a triangular matrix for given input matrix
    //! expression.
    //!
    //! \tparam T  Real number type.
    //! \tparam E  Input expression type.
    //!
    template <typename T, typename E>
    class MatrixTriangular : public MatrixExpression<T, MatrixTriangular<T, E>>
    {
    public:
        MatrixTriangular(const E &u_, bool isUpper = true, bool isStrict = false);
        //! Size of the matrix.
        Size2 size() const;
        //! Number of rows.
        size_t rows() const;
        //! Number of columns.
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    private:
        const E &_u;
        bool _isUpper;
        bool _isStrict;
    };

    // MARK: MatrixUnaryOp Aliases
    //!
    //! \brief Matrix expression for cast operation.
    //!
    //! This matrix expression represents a cast operation that takes
    //! single input matrix expression.
    //!
    //! \tparam T  Real number type.
    //! \tparam E  Input expression type.
    //!
    template <typename T, typename E>
    using MatrixTypeCast = MatrixUnaryOp<T, E, Cast<T>>;

    // MARK: MatrixBinaryOp
    //!
    //! \brief Matrix expression for binary operation.
    //!
    //! This matrix expression represents a binary matrix operation that takes
    //! two input matrix expressions.
    //!
    //! \tparam T   Real number type.
    //! \tparam E1  First input expression type.
    //! \tparam E2  Second input expression type.
    //! \tparam Op  Binary operation.
    //!
    template <typename T, typename E1, typename E2, typename Op>
    class MatrixBinaryOp : public MatrixExpression<T, MatrixBinaryOp<T, E1, E2, Op>>
    {
    public:
        MatrixBinaryOp(const E1 &u1_, const E2 &u2_);
        //! Size of the matrix.
        Size2 size() const;
        //! Number of rows.
        size_t rows() const;
        //! Number of columns.
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    private:
        const E1 &_u1;
        const E2 &_u2;
        Op _op;
    };

    // MARK: MatrixScalarBinaryOp
    //!
    //! \brief Matrix expression for scalar binary operation.
    //!
    //! This matrix expression represents a binary matrix operation that takes
    //! single input matrix expression and a scalar value.
    //!
    //! \tparam T   Real number type.
    //! \tparam E   Input expression type.
    //! \tparam Op  Binary operation.
    //!
    template <typename T, typename E, typename Op>
    class MatrixScalarBinaryOp : public MatrixExpression<T, MatrixScalarBinaryOp<T, E, Op>>
    {
    public:
        MatrixScalarBinaryOp(const E &u, const T &v);
        //! Size of the matrix.
        Size2 size() const;
        //! Number of rows.
        size_t rows() const;
        //! Number of columns.
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    private:
        const E &_u;
        T _v;
        Op _op;
    };

    // MARK: MatrixVectorMul
    //!
    //! \brief Matrix expression for vector multiplication.
    //!
    //! This matrix expression represents a vector multiplication operation that takes
    //! two input matrix expressions.
    //!
    //! \tparam T   Real number type.
    //! \tparam MV  Matrix expression type.
    //! \tparam VE  Vector expression type.
    //!
    template <typename T, typename MV, typename VE>
    class MatrixVectorMul : public VectorExpression<T, MatrixVectorMul<T, MV, VE>>
    {
    public:
        MatrixVectorMul(const MV &m, const VE &v);
        //! Size of the matrix.
        size_t size() const;
        T operator[](size_t i) const;

    private:
        const MV &_m;
        const VE &_v;
    };

    // MARK: MatrixMul
    //!
    //! \brief Matrix expression for multiplication.
    //!
    //! This matrix expression represents a multiplication operation that takes
    //! two input matrix expressions.
    //!
    //! \tparam T   Real number type.
    //! \tparam E1  First input expression type.
    //! \tparam E2  Second input expression type.
    //!
    template <typename T, typename E1, typename E2>
    class MatrixMul : public MatrixExpression<T, MatrixMul<T, E1, E2>>
    {
    public:
        MatrixMul(const E1 &u1, const E2 &u2);
        //! Size of the matrix.
        Size2 size() const;
        //! Number of rows.
        size_t rows() const;
        //! Number of columns.
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    private:
        const E1 &_u1;
        const E2 &_u2;
    };

    // MARK: MatrixBinaryOp Aliases

    //!
    //! \brief Matrix expression for addition.
    //!
    template <typename T, typename E1, typename E2>
    using MatrixAdd = MatrixBinaryOp<T, E1, E2, std::plus<T>>;

    //!
    //! \brief Matrix expression for scalar addition.
    //!
    template <typename T, typename E>
    using MatrixScalarAdd = MatrixScalarBinaryOp<T, E, std::plus<T>>;

    //!
    //! \brief Matrix expression for subtraction.
    //!
    template <typename T, typename E1, typename E2>
    using MatrixSub = MatrixBinaryOp<T, E1, E2, std::minus<T>>;

    //!
    //! \brief Matrix expression for scalar subtraction.
    //!
    template <typename T, typename E>
    using MatrixScalarSub = MatrixScalarBinaryOp<T, E, std::minus<T>>;

    template <typename T, typename E>
    using MatrixScalarRSub = MatrixScalarBinaryOp<T, E, RMinus<T>>;

    //!
    //! \brief Matrix expression for scalar multiplication .
    //!
    template <typename T, typename E>
    using MatrixScalarMul = MatrixScalarBinaryOp<T, E, std::multiplies<T>>;

    //!
    //! \brief Matrix expression for scalar division .
    //!
    template <typename T, typename E>
    using MatrixScalarDiv = MatrixScalarBinaryOp<T, E, std::divides<T>>;

    //!
    //! \brief Matrix expression for scalar division .
    //!
    template <typename T, typename E>
    using MatrixScalarRDiv = MatrixScalarBinaryOp<T, E, RDivides<T>>;

    // MARK: Operator overloadings

    template <typename T, typename E>
    MatrixScalarMul<T, E> operator-(const MatrixExpression<T, E> &u);

    //! Returns a + b (element-size).
    template <typename T, typename E1, typename E2>
    MatrixAdd<T, E1, E2> operator+(const MatrixExpression<T, E1> &u1, const MatrixExpression<T, E2> &u2);

    //! Returns a + b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixScalarAdd<T, E> operator+(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a` + b, where every element of matrix b` is b.
    template <typename T, typename E>
    MatrixScalarAdd<T, E> operator+(const T &a, const MatrixExpression<T, E> &u);

    //! Returns a - b (element-size).
    template <typename T, typename E1, typename E2>
    MatrixSub<T, E1, E2> operator-(const MatrixExpression<T, E1> &u1, const MatrixExpression<T, E2> &u2);

    //! Returns a - b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixScalarSub<T, E> operator-(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a` - b, where every element of matrix b` is b.
    template <typename T, typename E>
    MatrixScalarSub<T, E> operator-(const T &a, const MatrixExpression<T, E> &u);

    //! Returns a * b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixScalarMul<T, E> operator*(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a' * b, where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixScalarMul<T, E> operator*(const T &a, const MatrixExpression<T, E> &u);

    template <typename T, typename ME, typename VE>
    MatrixVectorMul<T, ME, VE> operator*(const MatrixExpression<T, ME> &u, const VectorExpression<T, VE> &v);

    //! Returns a * b (element-size).
    template <typename T, typename E1, typename E2>
    MatrixMul<T, E1, E2> operator*(const MatrixExpression<T, E1> &u1, const MatrixExpression<T, E2> &u2);

    //! Returns a / b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixScalarDiv<T, E> operator/(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a' / b, where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixScalarDiv<T, E> operator/(const T &a, const MatrixExpression<T, E> &u);

}

#include "details/matrix_expression-inl.h"