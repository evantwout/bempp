// Copyright (C) 2011-2012 by the BEM++ Authors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef bempp_piecewise_linear_continuous_scalar_space_hpp
#define bempp_piecewise_linear_continuous_scalar_space_hpp

#include "scalar_space.hpp"
#include "../common/types.hpp"
#include "../fiber/piecewise_linear_continuous_scalar_basis.hpp"
#include "../grid/grid_view.hpp"

#include <map>
#include <memory>

namespace Bempp
{


template <typename BasisFunctionType>
class PiecewiseLinearContinuousScalarSpace : public ScalarSpace<BasisFunctionType>
{
public:
    typedef typename Space<BasisFunctionType>::CoordinateType CoordinateType;

    explicit PiecewiseLinearContinuousScalarSpace(Grid& grid);

    virtual int domainDimension() const;
    virtual int codomainDimension() const;

    // Element variants: 2 (linear element), 3 (triangular element),
    // 4 (quadrilateral element)
    virtual ElementVariant elementVariant(const Entity<0>& element) const;
    virtual void setElementVariant(const Entity<0>& element,
                                   ElementVariant variant);

    virtual const Fiber::Basis<BasisFunctionType>& basis(const Entity<0>& element) const;

    virtual void assignDofs();
    virtual bool dofsAssigned() const;
    virtual size_t globalDofCount() const;
    virtual void globalDofs(const Entity<0>& element,
                            std::vector<GlobalDofIndex>& dofs) const;    
    virtual void global2localDofs(
            const std::vector<GlobalDofIndex>& globalDofs,
            std::vector<std::vector<LocalDof> >& localDofs) const;

    virtual void globalDofPositions(std::vector<Point3D<CoordinateType> >& positions) const;
    virtual void dumpClusterIds(const char* fileName,
                                const std::vector<unsigned int>& clusterIds) const;

private:
    std::auto_ptr<GridView> m_view;
    Fiber::PiecewiseLinearContinuousScalarBasis<2, BasisFunctionType> m_lineBasis;
    Fiber::PiecewiseLinearContinuousScalarBasis<3, BasisFunctionType> m_triangleBasis;
    Fiber::PiecewiseLinearContinuousScalarBasis<4, BasisFunctionType> m_quadrilateralBasis;
    std::vector<std::vector<GlobalDofIndex> > m_local2globalDofs;
    std::vector<std::vector<LocalDof> > m_global2localDofs;
};

} // namespace Bempp

#endif
