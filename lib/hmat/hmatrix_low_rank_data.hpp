// vi: set et ts=4 sw=2 sts=2:

#ifndef HMAT_HMATRIX_LOW_RANK_DATA_HPP
#define HMAT_HMATRIX_LOW_RANK_DATA_HPP

#include "common.hpp"
#include "hmatrix_data.hpp"
#include "eigen_fwd.hpp"

namespace hmat {

template <typename ValueType>
class HMatrixLowRankData : public HMatrixData<ValueType> {

public:
  void apply(const Matrix<ValueType> &X, Matrix<ValueType> &Y,
             TransposeMode trans, ValueType alpha, ValueType beta) const
      override;

  const Matrix<ValueType> &A() const;
  Matrix<ValueType> &A();

  const Matrix<ValueType> &B() const;
  Matrix<ValueType> &B();

  int rows() const override;
  int cols() const override;
  int rank() const override;

  typename ScalarTraits<ValueType>::RealType frobeniusNorm() const override;

  double memSizeKb() const override;

private:
  Matrix<ValueType> m_A;
  Matrix<ValueType> m_B;
};
}

#include "hmatrix_low_rank_data_impl.hpp"

#endif
