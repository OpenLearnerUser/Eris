#pragma once
#include "Eris/functors.h"

namespace Eris
{

    // MARK : VectorExpression

    //!
    //! \brief Base class for vector expression.
    //!
    //! Vector expression is a meta type that enables template expression pattern.
    //!
    //! \tparam T - Real number type.
    //! \tparam E - Subclass type.

    template <typename T, typename E>
    class VectorExpression
    {
    public:
        size_t size() const;

        const E &operator()() const;
    };

    // MARK: VectorUnaryOp

    //!
    //! \brief Vector expression for unary operation.
    //!
    //! This vector expression represents a unary vector operation that takes
    //! single input vector expression.
    //!
    //! \tparam T - Real number type.
    //! \tparam E - Input expression type.
    //! \tparam Op - Unary operation.

    template <typename T, typename E, typename Op>
    class VectorUnaryOp : public VectorExpression<T, VectorUnaryOp<T, E, Op>>
    {
    public:
        VectorUnaryOp(const E &e_);

        size_t size() const;

        T operator[](size_t i) const;

    private:
        const E &_e;
        Op _op;
    };

    // MARK: VectorUnaryOp Aliases

    //! Vector expression for type casting.
    template <typename T, typename E, typename U>
    using VectorTypeCast = VectorUnaryOp<T, E, TypeCast<U, T>>;

    // MARK: VectorBinaryOp

    //!
    //! \brief Vector expression for binary operation.
    //!
    //! This vector expression represents a binary vector operation that takes
    //! two input vector expressions.
    //!
    //! \tparam T - Real number type.
    //! \tparam E1 - First input expression type.
    //! \tparam E2 - Second input expression type.
    //! \tparam Op - Binary operation.

    template <typename T, typename E1, typename E2, typename Op>
    class VectorBinaryOp : public VectorExpression<T, VectorBinaryOp<T, E1, E2, Op>>
    {
    public:
        VectorBinaryOp(const E1 &e1, const E2 &e2);
        //! Size of the vector.
        size_t size() const;
        //! Returns vector element at i.
        T operator[](size_t i) const;

    private:
        const E1 &_e1;
        const E2 &_e2;
        Op _op;
    };

    //!
    //! \brief Vector expression for vector-scalar binary operation.
    //!
    //! This vector expression represents a binary vector operation that takes
    //! one input vector expression and one scalar.
    //!
    //! \tparam T - Real number type.
    //! \tparam E - Input expression type.
    //! \tparam Op - Binary operation.
    //!
    template <typename T, typename E, typename Op>
    class VectorScalarBinaryOp
        : public VectorExpression<T, VectorScalarBinaryOp<T, E, Op>>
    {
    public:
        //! Constructs a binary expression for given vector and scalar.
        VectorScalarBinaryOp(const E &u, const T &v);

        //! Size of the vector.
        size_t size() const;

        //! Returns vector element at i.
        T operator[](size_t i) const;

    private:
        const E &_u;
        T _v;
        Op _op;
    };

    // MARK: VectorBinaryOp Aliases

    //! Vector-vector addition expression.
    template <typename T, typename E1, typename E2>
    using VectorAdd = VectorBinaryOp<T, E1, E2, std::plus<T>>;

    //! Vector-scalar addition expression.
    template <typename T, typename E>
    using VectorScalarAdd = VectorScalarBinaryOp<T, E, std::plus<T>>;

    //! Vector-vector subtraction expression.
    template <typename T, typename E1, typename E2>
    using VectorSub = VectorBinaryOp<T, E1, E2, std::minus<T>>;

    //! Vector-scalar subtraction expression.
    template <typename T, typename E>
    using VectorScalarSub = VectorScalarBinaryOp<T, E, std::minus<T>>;

    //! scalar-Vector subtraction expression.
    template <typename T, typename E>
    using VectorScalarRSub = VectorScalarBinaryOp<T, E, RMinus<T>>;

    //! Element-wise vector-vector multiplication expression.
    template <typename T, typename E1, typename E2>
    using VectorMul = VectorBinaryOp<T, E1, E2, std::multiplies<T>>;

    //! Vector-scalar multiplication expression.
    template <typename T, typename E>
    using VectorScalarMul = VectorScalarBinaryOp<T, E, std::multiplies<T>>;

    //! Element-wise vector-vector division expression.
    template <typename T, typename E1, typename E2>
    using VectorDiv = VectorBinaryOp<T, E1, E2, std::divides<T>>;

    //! Vector-scalar division expression.
    template <typename T, typename E>
    using VectorScalarDiv = VectorScalarBinaryOp<T, E, std::divides<T>>;

    //! scalar-Vector division expression.
    template <typename T, typename E>
    using VectorScalarRDiv = VectorScalarBinaryOp<T, E, RDivides<T>>;

    // MARK: Global Functions

    //! Scalar-vector addition operation.

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const T &t, const VectorExpression<T, E> &b);

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const VectorExpression<T, E> &b, const T &t);

    template <typename T, typename E1, typename E2>
    VectorAdd<T, E1, E2> operator+(const VectorExpression<T, E1> &a,
                                   const VectorExpression<T, E2> &b);

    //! Scalar-vector subtraction operation.
    template <typename T, typename E>
    VectorScalarRSub<T, E> operator-(const T &a, const VectorExpression<T, E> &b);

    //! Vector-scalar subtraction operation.
    template <typename T, typename E>
    VectorScalarSub<T, E> operator-(const VectorExpression<T, E> &a, const T &b);

    //! Vector-vector subtraction operation.
    template <typename T, typename E1, typename E2>
    VectorSub<T, E1, E2> operator-(const VectorExpression<T, E1> &a,
                                   const VectorExpression<T, E2> &b);

    //! Scalar-vector multiplication operation.
    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const T &a, const VectorExpression<T, E> &b);

    //! Vector-scalar multiplication operation.
    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const VectorExpression<T, E> &a, const T &b);

    //! Element-wise vector-vector multiplication operation.
    template <typename T, typename E1, typename E2>
    VectorMul<T, E1, E2> operator*(const VectorExpression<T, E1> &a,
                                   const VectorExpression<T, E2> &b);

    //! Scalar-vector division operation.
    template <typename T, typename E>
    VectorScalarRDiv<T, E> operator/(const T &a, const VectorExpression<T, E> &b);

    //! Vector-scalar division operation.
    template <typename T, typename E>
    VectorScalarDiv<T, E> operator/(const VectorExpression<T, E> &a, const T &b);

    //! Element-wise vector-vector division operation.
    template <typename T, typename E1, typename E2>
    VectorDiv<T, E1, E2> operator/(const VectorExpression<T, E1> &a,
                                   const VectorExpression<T, E2> &b);

} // namespace Eris

#include "details/vector_expression-inl.h"
