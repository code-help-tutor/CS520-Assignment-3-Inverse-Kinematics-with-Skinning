WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_CXX11_TENSOR_TENSOR_FORCED_EVAL_H
#define EIGEN_CXX11_TENSOR_TENSOR_FORCED_EVAL_H

namespace Eigen {

/** \class TensorForcedEval
  * \ingroup CXX11_Tensor_Module
  *
  * \brief Tensor reshaping class.
  *
  *
  */
namespace internal {
template<typename XprType>
struct traits<TensorForcedEvalOp<XprType> >
{
  // Type promotion to handle the case where the types of the lhs and the rhs are different.
  typedef typename XprType::Scalar Scalar;
  typedef traits<XprType> XprTraits;
  typedef typename traits<XprType>::StorageKind StorageKind;
  typedef typename traits<XprType>::Index Index;
  typedef typename XprType::Nested Nested;
  typedef typename remove_reference<Nested>::type _Nested;
  static const int NumDimensions = XprTraits::NumDimensions;
  static const int Layout = XprTraits::Layout;
  typedef typename XprTraits::PointerType PointerType;

  enum {
    Flags = 0
  };
};

template<typename XprType>
struct eval<TensorForcedEvalOp<XprType>, Eigen::Dense>
{
  typedef const TensorForcedEvalOp<XprType>& type;
};

template<typename XprType>
struct nested<TensorForcedEvalOp<XprType>, 1, typename eval<TensorForcedEvalOp<XprType> >::type>
{
  typedef TensorForcedEvalOp<XprType> type;
};

}  // end namespace internal



template<typename XprType>
class TensorForcedEvalOp : public TensorBase<TensorForcedEvalOp<XprType>, ReadOnlyAccessors>
{
  public:
  typedef typename Eigen::internal::traits<TensorForcedEvalOp>::Scalar Scalar;
  typedef typename Eigen::NumTraits<Scalar>::Real RealScalar;
  typedef typename internal::remove_const<typename XprType::CoeffReturnType>::type CoeffReturnType;
  typedef typename Eigen::internal::nested<TensorForcedEvalOp>::type Nested;
  typedef typename Eigen::internal::traits<TensorForcedEvalOp>::StorageKind StorageKind;
  typedef typename Eigen::internal::traits<TensorForcedEvalOp>::Index Index;

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE TensorForcedEvalOp(const XprType& expr)
      : m_xpr(expr) {}

    EIGEN_DEVICE_FUNC
    const typename internal::remove_all<typename XprType::Nested>::type&
    expression() const { return m_xpr; }

  protected:
    typename XprType::Nested m_xpr;
};


template<typename ArgType, typename Device>
struct TensorEvaluator<const TensorForcedEvalOp<ArgType>, Device>
{
  typedef TensorForcedEvalOp<ArgType> XprType;
  typedef typename ArgType::Scalar Scalar;
  typedef typename TensorEvaluator<ArgType, Device>::Dimensions Dimensions;
  typedef typename XprType::Index Index;
  typedef typename XprType::CoeffReturnType CoeffReturnType;
  typedef typename PacketType<CoeffReturnType, Device>::type PacketReturnType;
  static const int PacketSize = PacketType<CoeffReturnType, Device>::size;

  enum {
    IsAligned         = true,
    PacketAccess      = (PacketType<CoeffReturnType, Device>::size > 1),
    BlockAccess       = internal::is_arithmetic<CoeffReturnType>::value,
    PreferBlockAccess = false,
    Layout            = TensorEvaluator<ArgType, Device>::Layout,
    RawAccess         = true
  };

  typedef typename internal::TensorBlock<
      CoeffReturnType, Index, internal::traits<ArgType>::NumDimensions, Layout>
      TensorBlock;
  typedef typename internal::TensorBlockReader<
      CoeffReturnType, Index, internal::traits<ArgType>::NumDimensions, Layout>
      TensorBlockReader;

  EIGEN_DEVICE_FUNC TensorEvaluator(const XprType& op, const Device& device)
  /// op_ is used for sycl
      : m_impl(op.expression(), device), m_op(op.expression()), m_device(device), m_buffer(NULL)
  { }

  EIGEN_DEVICE_FUNC const Dimensions& dimensions() const { return m_impl.dimensions(); }

  #if !defined(EIGEN_HIPCC)
  EIGEN_DEVICE_FUNC
  #endif
  EIGEN_STRONG_INLINE bool evalSubExprsIfNeeded(CoeffReturnType*) {
    const Index numValues =  internal::array_prod(m_impl.dimensions());
    m_buffer = (CoeffReturnType*)m_device.allocate_temp(numValues * sizeof(CoeffReturnType));
    // Should initialize the memory in case we're dealing with non POD types.
    if (NumTraits<CoeffReturnType>::RequireInitialization) {
      for (Index i = 0; i < numValues; ++i) {
        new(m_buffer+i) CoeffReturnType();
      }
    }
    typedef TensorEvalToOp< const typename internal::remove_const<ArgType>::type > EvalTo;
    EvalTo evalToTmp(m_buffer, m_op);
    const bool Vectorize = internal::IsVectorizable<Device, const ArgType>::value;
    internal::TensorExecutor<const EvalTo, typename internal::remove_const<Device>::type, Vectorize>::run(evalToTmp, m_device);
    return true;
  }
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE void cleanup() {
    m_device.deallocate_temp(m_buffer);
    m_buffer = NULL;
  }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE CoeffReturnType coeff(Index index) const
  {
    return m_buffer[index];
  }

  template<int LoadMode>
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE PacketReturnType packet(Index index) const
  {
    return internal::ploadt<PacketReturnType, LoadMode>(m_buffer + index);
  }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE void getResourceRequirements(
      std::vector<internal::TensorOpResourceRequirements>*) const {}

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE void block(TensorBlock* block) const {
    assert(m_buffer != NULL);
    TensorBlockReader::Run(block, m_buffer);
  }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE TensorOpCost costPerCoeff(bool vectorized) const {
    return TensorOpCost(sizeof(CoeffReturnType), 0, 0, vectorized, PacketSize);
  }

  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE
  typename Eigen::internal::traits<XprType>::PointerType  data() const { return m_buffer; }

  /// required by sycl in order to extract the sycl accessor
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE const TensorEvaluator<ArgType, Device>& impl() { return m_impl; }
  /// used by sycl in order to build the sycl buffer
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE const Device& device() const{return m_device;}
 private:
  TensorEvaluator<ArgType, Device> m_impl;
  const ArgType m_op;
  const Device& m_device;
  CoeffReturnType* m_buffer;
};


} // end namespace Eigen

#endif // EIGEN_CXX11_TENSOR_TENSOR_FORCED_EVAL_H
