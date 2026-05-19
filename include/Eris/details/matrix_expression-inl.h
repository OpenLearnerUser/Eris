#pragma once
#include <Eris/matrix_expression.h>

namespace Eris
{

    template <typename T, typename E>
    size_t MatrixExpression<T, E>::size() const
    {
        return static_cast<const E &>(*this).size();
    }

    template <typename T, typename E>
    size_t MatrixExpression<T, E>::rows() const
    {
        return static_cast<const E &>(*this).rows();
    }

    template <typename T, typename E>
    size_t MatrixExpression<T, E>::cols() const
    {
        return static_cast<const E &>(*this).cols();
    }

    template <typename T, typename E>
    const E &MatrixExpression<T, E>::operator()() const
    {
        return static_cast<const E &>(*this);
    }

    template <typename T>
    MatrixConstant::MatrixConstant(const size_t &m, size_t n, const T &c) : _m(m), _n(n), _c(c) {}

    template <typename T>
    size_t MatrixConstant<T>::size() const
    {
        return _m * _n;
    }

    template <typename T>
    size_t MatrixConstant<T>::rows() const
    {
        return _m;
    }

    template <typename T>
    size_t MatrixConstant<T>::cols() const
    {
        return _n;
    }

    template <typename T>
    T MatrixConstant<T>::operator()(size_t i, size_t j) const
    {
        return _c;
    }

    template <typename T>
    class MatrixIdentity : public MatrixExpression<T, MatrixIdentity<T>>

                           template <typename T>

                           MatrixIdentity::MatrixIdentity(const size_t &m) : _m(m){};

    template <typename T>
    size_t MatrixIdentity<T>::size() const
    {
        return _m * _m;
    }

    template <typename T>
    size_t MatrixIdentity<T>::rows() const
    {
        return _m;
    }
    template <typename T>
    size_t MatrixIdentity<T>::cols() const
    {
        return _m;
    }
    template <typename T>
    T MatrixIdentity<T>::operator()(size_t i, size_t j) const
    {
        return i == j ? 1 : 0;
    }

    template <typename T, typename E, typename Op>
    MatrixUnaryOp<T, E, Op>::MatrixUnaryOp(const E &u) : _u(u) {}

    template <typename T, typename E, typename Op>
    size_t MatrixUnaryOp<T, E, Op>::size() const
    {
        return _u.size();
    }

    template <typename T, typename E, typename Op>
    size_t MatrixUnaryOp<T, E, Op>::rows() const
    {
        return _u.rows();
    }
    template <typename T, typename E, typename Op>
    size_t MatrixUnaryOp<T, E, Op>::cols() const
    {
        return _u.cols();
    }
    template <typename T, typename E, typename Op>
    T MatrixUnaryOp<T, E, Op>::operator()(size_t i, size_t j) const
    {
        return _op(_u(i, j));
    }

    template <typename T, typename E>
    MatrixDiagonal::MatrixDiagonal(const E &u, bool isDiag) : _u(u), _isDiag(isDiag) {}

    template <typename T, typename E>
    size_t MatrixDiagonal<T, E>::size() const
    {
        return _u.size();
    }
    template <typename T, typename E>
    size_t MatrixDiagonal<T, E>::rows() const
    {
        return _u.rows();
    }
    template <typename T, typename E>
    size_t MatrixDiagonal<T, E>::cols() const
    {
        return _u.cols();
    }

    template <typename T, typename E>
    T MatrixDiagonal<T, E>::operator()(size_t i, size_t j) const
    {
        if (_isDiag)
        {
            return (i == j) ? _u(i, j) : 0;
        }
        else
        {
            return (i != j) ? _u(i, j) : 0;
        }
    }

    template <typename T, typename E>
    class MatrixTriangular : public MatrixExpression<T, MatrixTriangular<T, E>>

                             template <typename T, typename E>
                             MatrixTriangular::MatrixTriangular(const E &u_, bool isUpper, bool isStrict) : _u(u_), _isUpper(isUpper), _isStrict(isStrict)
    {
    }
    //! Size of the matrix.
    template <typename T, typename E>
    size_t MatrixTriangular<T, E>::size() const
    {
        return _u.size();
    }
    //! Number of rows.

    template <typename T, typename E>
    size_t MatrixTriangular<T, E>::rows() const
    {
        return _u.rows();
    }

    template <typename T, typename E>
    size_t MatrixTriangular<T, E>::cols() const
    {
        return _u.cols();
    }
    template <typename T, typename E>
    T MatrixTriangular<T, E>::operator()(size_t i, size_t j) const
    {
        if (i < j)
        {
            return (_isUpper) ? _u(i, j) : 0;
        }
        else if (i > j)
        {
            return (!_isUpper) ? _u(i, j) : 0;
        }
        else
        {
            return (!_isStrict) ? _u(i, j) : 0;
        }
    }

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
        MatrixBinaryOp(const E1 &u1, const E2 &u2);
        //! Size of the matrix.
        size_t size() const;
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
    class MatrixScalarBinaryOp : public MatrixExpression<T, MatrixBinaryOp<T, E, Op>>
    {
    public:
        MatrixScalarBinaryOp(const E &u);
        //! Size of the matrix.
        size_t size() const;
        //! Number of rows.
        size_t rows() const;
        //! Number of columns.
        size_t cols() const;
        T operator()(size_t i, size_t j) const;

    private:
        const E &_u;
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
    class MatrixVectorMul : public MatrixExpression<T, MatrixBinaryOp<T, MV, VE>>
    {
    public:
        MatrixVectorMul(const MV &m, const VE &v);
        //! Size of the matrix.
        size_t size() const;
        T operator()(size_t i, size_t j) const;

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
        size_t size() const;
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
    using MatrixSclarAdd = MatrixScalarBinaryOp<T, E, std::plus<T>>;

    //!
    //! \brief Matrix expression for subtraction.
    //!
    template <typename T, typename E1, typename E2>
    using MatrixSub = MatrixBinaryOp<T, E1, E2, std::minus<T>>;

    //!
    //! \brief Matrix expression for scalar subtraction.
    //!
    template <typename T, typename E>
    using MatrixSclarSub = MatrixScalarBinaryOp<T, E, std::minus<T>>;

    template <typename T, typename E>
    using MatrixSclarRSub = MatrixScalarBinaryOp<T, E, RMinus<T>>;

    //!
    //! \brief Matrix expression for scalar multiplication .
    //!
    template <typename T, typename E>
    using MatrixSclarMul = MatrixScalarBinaryOp<T, E, std::multiplies<T>>;

    //!
    //! \brief Matrix expression for scalar division .
    //!
    template <typename T, typename E>
    using MatrixSclarDiv = MatrixScalarBinaryOp<T, E, std::divides<T>>;

    //!
    //! \brief Matrix expression for scalar division .
    //!
    template <typename T, typename E>
    using MatrixSclarRDiv = MatrixScalarBinaryOp<T, E, RDivides<T>>;

    // MARK: Operator overloadings

    template <typename T, typename E>
    MatrixSclarMul<T, E> operator-(const MatrixExpression<T, E> &u);

    //! Returns a + b (element-size).
    template <typename T, typename E1, typename E2>
    MatrixAdd<T, E1, E2> operator+(const MatrixExpression<T, E1> &u1, const MatrixExpression<T, E2> &u2);

    //! Returns a + b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixSclarAdd<T, E> operator+(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a` + b, where every element of matrix b` is b.
    template <typename T, typename E>
    MatrixSclarAdd<T, E> operator+(const T &a, const MatrixExpression<T, E> &u);

    //! Returns a - b (element-size).
    template <typename T, typename E1, typename E2>
    MatrixSub<T, E1, E2> operator-(const MatrixExpression<T, E1> &u1, const MatrixExpression<T, E2> &u2);

    //! Returns a - b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixSclarSub<T, E> operator-(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a` - b, where every element of matrix b` is b.
    template <typename T, typename E>
    MatrixSclarSub<T, E> operator-(const T &a, const MatrixExpression<T, E> &u);

    //! Returns a * b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixSclarMul<T, E> operator*(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a' * b, where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixSclarMul<T, E> operator*(const T &a, const MatrixExpression<T, E> &u);

    template <typename T, typename ME, typename VE>
    MatrixVectorMul<T, ME, VE> operator*(const MatrixExpression<T, ME> &u, const VectorExpression<T, VE> &v);

    //! Returns a * b (element-size).
    template <typename T, typename E1, typename E2>
    MatrixMul<T, E1, E2> operator*(const MatrixExpression<T, E1> &u1, const MatrixExpression<T, E2> &u2);

    //! Returns a / b', where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixSclarDiv<T, E> operator/(const MatrixExpression<T, E> &u, const T &a);

    //! Returns a' / b, where every element of matrix b' is b.
    template <typename T, typename E>
    MatrixSclarDiv<T, E> operator/(const T &a, const MatrixExpression<T, E> &u);
}
