#pragma once

#include <Eris/macro.h>
#include <Eris/math_utils.h>
#include <Eris/parallel.h>


namespace Eris{



    template<typename T>
    VectorN<T>::Vector(){
        setZero();
    }

   
    template <typename T>
    VectorN<T>::VectorN(size_t n ,const T &val = 0):_elements(n,val){
    }

    template <typename T>
    template <typename U>
    VectorN<T>::VectorN(const std::initializer_list<T> &lst){
        set(lst);
    }

    template <typename T>
    template <typename E>
    VectorN<T>::VectorN(const VectorExpression<T, E> &others){
        set(others);
    }

    template <typename T>
    void VectorN<T>::VectorN(const VectorN &others){
        set(others);
    }

    template <typename T>
    void VectorN<T>::VectorN(VectorN &&others){
        (*this)=std::move(others);
    }

    // MARK: Basic setters
    template <typename T>
    void VectorN<T>::resize(size_t n, const T &val = 0){
        _elements.resize(n,val);
    }
    template <typename T>
    void VectorN<T>::clear(){
        _elements.clear();
    }

    template <typename T>
    void set(const T &s){
        parallelFill(begin(), end(), s);
    }

    template <typename T>
    template <typename U>
    void VectorN<T>::set(const std::initializer_list<U> &lst){
        _elements=lst;
    }

    template <typename T>
    template <typename E>
    void VectorN<T>::set(const VectorExpression<T, E> &other){
        _elements.resize(other.size());

        const E& e=other();
        parallelForEachIndex([&](size_t i){_elements[i]=e[i];});
    }

    template <typename T>
    void VectorN<T>::append(const T &val){
        _elements.push_back(val);
    }

    template <typename T>
    void VectorN<T>::swap(VectorN &other){
        std::swap(other._elements, _elements);
    }

    template <typename T>
    void VectorN<T>::setZero(){
        set(T(0));
    }

    template <typename T>
    void VectorN<T>::normalize(){
        idiv(length());
    }
    // MARK: Basic getters

    template <typename T>
    constexpr VectorN<T>::size_t size() const{
        return _elements.size();
    }

    template <typename T>
    T* VectorN<T>::data(){
        return _elements.data();
    }

    template <typename T>
    const T *const VectorN<T>::data() const{
        return _elements.data();
    }

    template <typename T>
    typename VectorN<T>::ContainerType::iterator begin(){
        return _elements.begin();
    }

    template <typename T>
    typename VectorN<T>::ContainerType::const_iterator begin() const{
        _elements.cbegin();
    }

    template <typename T>
    typename VectorN<T>::ContainerType::iterator end(){
        _elements.end();
    }

    template <typename T>
    typename VectorN<T>::ContainerType::const_iterator end() const{
        _elements.cend();
    }

    template <typename T>
    ArrayAccessor1<T> VectorN<T>::accessor(){
        return ArrayAccessor1(size(),data());
    }

    template <typename T>
    ConstArrayAccessor1<T> VectorN<T>::constAccessor() const{
        return ConstArrayAccessor1(size(), data());
    }
    }

    template <typename T>
    T VectorN<T>::at(size_t i) const{
        _elements[i];
    }

    template <typename T>
    T &VectorN<T>::at(size_t i){
        _elements[i];
    }

    template <typename T>
    T VectorN<T>::sum() const{
        return paralleReduce(KZeroSize,size(),T(0),[&](size_t start,size_t end,T init){
            T result=init;
            for(size_t i=start;i<end;++i){
                result +=_elements[i];
            }
            return result;
        },std::plus<T>());
    }

    template <typename T>
    T VectorN<T>::avg() const;

    template <typename T>
    T VectorN<T>::min() const{
        const T &(*_min)(const T &, const T &) = std::min<T>;
        return parallelReduce(kZeroSize, size(), std::numeric_limits<T>::max(), [&](size_t start, size_t end, T init)
                              {
                              T result = init;
                              for (size_t i = start; i < end; ++i) {
                                  result = std::min(result, _elements[i]);
                              }
                              return result; }, _min);
    }

    template <typename T>
    T VectorN<T>::max() const{
        return parallelReduce(kZeroSize, size(), std::numeric_limits<T>::min(), [&](size_t start, size_t end, T init)
                              {
                              T result = init;
                              for (size_t i = start; i < end; ++i) {
                                  result = std::max(result, _elements[i]);
                              }
                              return result; }, _max);
    }

    template <typename T>
    T VectorN<T>::absmin() const{
        return parallelReduce(kZeroSize, size(), std::numeric_limits<T>::max(), [&](size_t start, size_t end, T init)
                              {
                              T result = init;
                              for (size_t i = start; i < end; ++i) {
                                  result = jet::absmin(result, _elements[i]);
                              }
                              return result; }, jet::absmin<T>);
    }

    template <typename T>
    T VectorN<T>::absmax() const{
        return parallelReduce(kZeroSize, size(), T(0), [&](size_t start, size_t end, T init)
                              {
                              T result = init;
                              for (size_t i = start; i < end; ++i) {
                                  result = jet::absmax(result, _elements[i]);
                              }
                              return result; }, jet::absmax<T>);
    }

    template <typename T>
    size_t VectorN<T>::dominantAxis() const{
        auto iter = std::max_element(begin(), end(), [](const const T &a, const T &b)
                                     { return std::fabs(a) < std::fabs(b); });
        return iter-begin();
    }

    template <typename T>
    size_t VectorN<T>::subminantAxis() const{
        auto iter = std::max_element(begin(), end(), [](const T &a, const T &b)
                                     { return std::fabs(a) > std::fabs(b); });
        return iter - begin();
    }

    VectorScalarDiv<T, VectorN> VectorN<T>::normalized() const{
        T len = length();
        return VectorScalarDiv<T, VectorN>(*this, len);
    }

    template <typename T>
    T VectorN<T>::length() const{
        return std::sqrt(lengthSquared());
    }

    template <typename T>
    T VectorN<T>::lengthSquared() const{
        return dot(*this);
    }

    template <typename T>
    template <typename E>
    T VectorN<T>::distanceTo(const E &other) const{
        return std::sqrt(distanceSquaredTo(other));
    }

    template <typename T>
    template <typename E>
    T VectorN<T>::distanceSquaredTo(const E &other) const{
        ERIS_ASSERT(size()==other.size());
        return parallelReduce(kZeroSize,size(),T(0),
                                [&](size_t start,size_t end,T init){
                                    T result=init;
                                    for(size_t i=start;i<end;++i){
                                        T diff=(_elements[i]-other[i]);
                                        result+=diff*diff;
                                    }
                                    return result;
                                },std::plus<T>());
                    
    }

    template <typename T>
    template <typename U>
    VectorTypeCast<U, VectorN<T>, T> VectorN<T>::castTo() const
    {
        return VectorTypeCast<U, VectorN<T>, T>(*this);
    }

    template <typename T>
    template <typename E>
    bool VectorN<T>::isEqual(const E &other) const{
        if(size()!=other.size()){
            return false;
        }
        for(size_t i=0;i<size();++i){
            if(at(i)!=other[i]){
                return false;
            }
        }
        return true;
    }

    template <typename T>
    template <typename E>
    bool VectorN<T>::isSimilar(const E &other, T epsilon = std::numeric_limits<T>::epsilin()) const{
        if(size()!=other.size()){
            return false;
        }
        for (size_t i = 0; i < size(); ++i)
        {
            if (std::fabs(at(i) - other[i]) > epsilon)
            {
                return false;
            }
        }
        return true;
    }

    // MARK: Binary operations: new instance = this (+) v

    template <typename T>
    template <typename E>
    VectorAdd<T, VectorN, E> VectorN<T>::add(const E &v) const{
        return VectorAdd<T,VectorN,E>(*this,v);
    }

    template <typename T>
    VectorScalarAdd<T, VectorN> VectorN<T>::add(const T &s) const{
        return VectorScalarAdd<T, VectorN>(*this,s);
    }

    template <typename T>
    template <typename E>
    VectorSub<T, VectorN, E> VectorN<T>::sub(const E &v) const{
        return VectorSub<T, VectorN, E>(*this, v);
    }

    template <typename T>
    VectorScalarSub<T, VectorN> VectorN<T>::sub(const T &s) const{
        return VectorScalarSub<T, VectorN>(*this, s);
    }

    template <typename T>
    template <typename E>
    VectorMul<T, VectorN, E> VectorN<T>::mul(const E &v) const{
        return VectorMul<T, VectorN, E>(*this, v);
    }
    template <typename T>
    VectorScalarMul<T, VectorN> VectorN<T>::mul(const T &s) const{
        return VectorScalarMul<T, VectorN>(*this,s);
    }

    template <typename T>
    template <typename E>
    VectorDiv<T, VectorN, E> VectorN<T>::div(const E &v) const{
        return VectorDiv<T, VectorN, E>(*this, v);
    }
    template <typename T>
    VectorScalarDiv<T, VectorN> VectorN<T>::div(const T &s) const{
        return VectorScalarDiv<T, VectorN>(*this, s);
    }

    template <typename T>
    template <typename E>
    T VectorN<T>::dot(const E &v) const{
        ERIS_ASSERT(size()==v.size());

        return parallelReduce(kZeroSize,size(),T(0),[&](size_t start,size_t end,T init){
                        T result=init;
                        for(size_t i=start;i<end;i++){
                            result+=_elements[i]*v[i];
                        }
                        return result;


        },std::plus<T>());


    }

    // MARK: Binary operations: new instance = v (+) this

    template <typename T>
    VectorScalarRSub<T, VectorN> VectorN<T>::rsub(const T &s){
        return VectorScalarRSub<T, VectorN>(*this, s);
    }

    template <typename T>
    template <typename E>
    VectorSub<T, VectorN, E> VectorN<T>::rsub(const E &v) const{
        return VectorSub<T, VectorN, E>(v, *this);
    }

    template <typename T>
    VectorScalarRDiv<T, VectorN> VectorN<T>::rdiv(const T &s){
        return VectorScalarRDiv<T, VectorN>(*this, s);
        
    }

    template <typename T>
    template <typename E>
    VectorDiv<T, VectorN, E> VectorN<T>::rdiv(const E &v) const{
        return VectorDiv<T, VectorN, E>(v, *this);
    }

    // MARK: Augmented operations: this (+)= v

    template <typename T>

    void VectorN<T>::iadd(const T &s){
        set(add(s));

    }
    

    template <typename T>
    template <typename E>
    void VectorN<T>::iadd(const E &v){
        set(add(v));
    }

    template <typename T>
    void VectorN<T>::isub(const T &s){
        set(sub(s));
    }

    template <typename T>
    template <typename E>
    void VectorN<T>::isub(const E &v){
        set(sub(v));
    }

    template <typename T>
    void VectorN<T>::imul(const T &s){
        set(mul(s));
    }

    template <typename T>
    template <typename E>
    void VectorN<T>::imul(const E &v){
        set(mul(v));
    }

    template <typename T>
    void VectorN<T>::idiv(const T &s){
        set(div(s));
    }

    template <typename T>
    template <typename E>
    void VectorN<T>::idiv(const E &v){
        set(div(v));
    }

    template <typename T>
    template <typename Callback>
    void VectorN<T>::forEach(Callback func) const{
        constAccessor().forEach(func);
    }

    template <typename T>
    template <typename Callback>
    void VectorN<T>::forEachIndex(Callback func) const{
        constAccessor().forEachIndex(func);
    }

    template <typename T>
    const T &VectorN<T>::operator[](size_t i) const{
        return _elements[i];
    }

    template <typename T>
    T &VectorN<T>::operator[](size_t){
        return _elements[i];
    }

    template <typename T>
    template <typename U>
    VectorN &VectorN<T>::operator=(const std::initializer_list<U> &lst){
        set(lst);
        return *this;
    }

    template <typename T>
    template <typename E>
    VectorN &VectorN<T>::operator=(const VectorExpression<T, E> &other){
        set(other);
        return *this;
    }
    template <typename T>
    VectorN &operator=(const VectorN &other){
        set(other);
        return *this;
    }

    template <typename T>
    VectorN &operator=(const VectorN &&other)
    {
        _elements = std::move(other._elements);
        return *this;
    }

    template<typename T>
    VectorN &VectorN<T>::operator+=(const T &s){
        iadd(s);
        return *this;
    }

    //! Computes this += v
    template <typename E>
    VectorN &VectorN<T>::operator+=(const E &v){
        iadd(v);
        return *this;
    }

    template<typename T>
    VectorN &VectorN<T>::operator-=(const T &s){
        isub(s);
        return *this;
    }

    //! Computes this -= v
    template <typename E>
    VectorN &VectorN<T>::operator-=(const E &v){
        isub(v);
        return *this;
    }

    template<typename T> 
    VectorN &VectorN<T>::operator*=(const T &s){
        imul(s);
        return *this;
    }

    //! Computes this *= v
    template <typename E>
    VectorN &VectorN<T>::operator*=(const E &v){
        imul(v);
        return *this;
    }

    template<typename T> 
    VectorN &VectorN<T>::operator/=(const T &s){
        idiv(s);
        return *this;
    }

    //! Computes this /= v
    template <typename E>
    VectorN &VectorN<T>::operator/=(const E &v){
        idiv(v);
        return *this;
    }

    template <typename T>
    template <typename E>
    bool VectorN<T>::operator==(const E &v) const{
        return isEqual(v);
    }

    template <typename T>
    template <typename E>
    bool VectorN<T>::operator!=(const E &v) const{
        return !isEqual(v);
    }
};
