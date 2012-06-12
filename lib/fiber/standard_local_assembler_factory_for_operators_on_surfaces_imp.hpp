// Copyright (C) 2011-2012 by the Bem++ Authors
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

#ifndef fiber_standard_local_assembler_factory_for_operators_on_surfaces_imp_hpp
#define fiber_standard_local_assembler_factory_for_operators_on_surfaces_imp_hpp

#include "standard_local_assembler_factory_for_operators_on_surfaces.hpp"

#include "standard_local_assembler_for_identity_operator_on_surface.hpp"
#include "standard_local_assembler_for_integral_operators_on_surfaces.hpp"
#include "standard_local_assembler_for_grid_functions_on_surfaces.hpp"
#include "standard_evaluator_for_integral_operators.hpp"

#include <stdexcept>

namespace Fiber
{

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase()
{
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase(
        const AccuracyOptions& accuracyOptions) :
    m_accuracyOptions(accuracyOptions)
{
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
std::auto_ptr<LocalAssemblerForOperators<ResultType> >
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
makeAssemblerForIdentityOperators(
        const shared_ptr<const GeometryFactory>& geometryFactory,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& rawGeometry,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& testBases,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& trialBases,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& testTransformations,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& trialTransformations,
        const shared_ptr<const OpenClHandler>& openClHandler) const
{
    typedef StandardLocalAssemblerForIdentityOperatorOnSurface<
            BasisFunctionType, ResultType, GeometryFactory>
            LocalAssemblerForIdentityOperator_;
    return std::auto_ptr<LocalAssemblerForOperators<ResultType> >(
                new LocalAssemblerForIdentityOperator_(
                    geometryFactory, rawGeometry,
                    testBases, trialBases,
                    testTransformations, trialTransformations,
                    openClHandler));
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
std::auto_ptr<LocalAssemblerForOperators<ResultType> >
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
makeAssemblerForIntegralOperatorsImplRealKernel(
        const shared_ptr<const GeometryFactory>& testGeometryFactory,
        const shared_ptr<const GeometryFactory>& trialGeometryFactory,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& testRawGeometry,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& trialRawGeometry,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& testBases,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& trialBases,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& testTransformations,
        const shared_ptr<const CollectionOfKernels<CoordinateType> >& kernels,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& trialTransformations,
        const shared_ptr<const TestKernelTrialIntegral<BasisFunctionType, CoordinateType, ResultType> >& integral,
        const shared_ptr<const OpenClHandler>& openClHandler,
        const ParallelisationOptions& parallelisationOptions,
        bool cacheSingularIntegrals) const
{
    typedef CoordinateType KernelType;
    typedef StandardLocalAssemblerForIntegralOperatorsOnSurfaces<
            BasisFunctionType, KernelType, ResultType, GeometryFactory>
            LocalAssemblerForIntegralOperators_;
    return std::auto_ptr<LocalAssemblerForOperators<ResultType> >(
                new LocalAssemblerForIntegralOperators_(
                    testGeometryFactory, trialGeometryFactory,
                    testRawGeometry, trialRawGeometry,
                    testBases, trialBases,
                    testTransformations, kernels, trialTransformations, integral,
                    openClHandler, parallelisationOptions,
                    cacheSingularIntegrals,
                    this->accuracyOptions()));
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
std::auto_ptr<LocalAssemblerForGridFunctions<ResultType> >
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
makeAssemblerForGridFunctionsImplRealUserFunction(
        const shared_ptr<const GeometryFactory>& geometryFactory,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& rawGeometry,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& testBases,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& testTransformations,
        const shared_ptr<const Function<CoordinateType> >& function,
        const shared_ptr<const OpenClHandler>& openClHandler) const
{
    typedef CoordinateType UserFunctionType;
    typedef StandardLocalAssemblerForGridFunctionsOnSurfaces<
            BasisFunctionType, UserFunctionType, ResultType, GeometryFactory>
            LocalAssemblerForGridFunctions_;
    return std::auto_ptr<LocalAssemblerForGridFunctions<ResultType> >(
                new LocalAssemblerForGridFunctions_(
                    geometryFactory, rawGeometry,
                    testBases,
                    testTransformations, function,
                    openClHandler));
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
std::auto_ptr<EvaluatorForIntegralOperators<ResultType> >
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
makeEvaluatorForIntegralOperatorsImplRealKernel(
        const shared_ptr<const GeometryFactory>& geometryFactory,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& rawGeometry,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& trialBases,
        const shared_ptr<const CollectionOfKernels<CoordinateType> >& kernels,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& trialTransformations,
        const shared_ptr<const KernelTrialIntegral<BasisFunctionType, CoordinateType, ResultType> >& integral,
        const shared_ptr<const std::vector<std::vector<ResultType> > >& argumentLocalCoefficients,
        const shared_ptr<const OpenClHandler>& openClHandler) const
{
    typedef CoordinateType KernelType;
    typedef StandardEvaluatorForIntegralOperators<
            BasisFunctionType, KernelType, ResultType, GeometryFactory>
            EvaluatorForIntegralOperators_;
    return std::auto_ptr<EvaluatorForIntegralOperators<ResultType> >(
                new EvaluatorForIntegralOperators_(
                    geometryFactory, rawGeometry,
                    trialBases,
                    kernels, trialTransformations, integral,
                    argumentLocalCoefficients,
                    openClHandler,
                    this->accuracyOptions().singleRegular));
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
const AccuracyOptions&
StandardLocalAssemblerFactoryForOperatorsOnSurfacesBase<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
accuracyOptions() const
{
    return m_accuracyOptions;
}

// Complex ResultType
template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
StandardLocalAssemblerFactoryForOperatorsOnSurfaces<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
StandardLocalAssemblerFactoryForOperatorsOnSurfaces() :
    Base()
{
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
StandardLocalAssemblerFactoryForOperatorsOnSurfaces<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
StandardLocalAssemblerFactoryForOperatorsOnSurfaces(
        const AccuracyOptions& accuracyOptions) :
    Base(accuracyOptions)
{
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
std::auto_ptr<LocalAssemblerForOperators<ResultType> >
StandardLocalAssemblerFactoryForOperatorsOnSurfaces<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
makeAssemblerForIntegralOperatorsImplComplexKernel(
        const shared_ptr<const GeometryFactory>& testGeometryFactory,
        const shared_ptr<const GeometryFactory>& trialGeometryFactory,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& testRawGeometry,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& trialRawGeometry,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& testBases,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& trialBases,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& testTransformations,
        const shared_ptr<const CollectionOfKernels<ResultType> >& kernels,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& trialTransformations,
        const shared_ptr<const TestKernelTrialIntegral<BasisFunctionType, ResultType, ResultType> >& integral,
        const shared_ptr<const OpenClHandler>& openClHandler,
        const ParallelisationOptions& parallelisationOptions,
        bool cacheSingularIntegrals) const
{
    typedef ResultType KernelType;
    typedef StandardLocalAssemblerForIntegralOperatorsOnSurfaces<
            BasisFunctionType, KernelType, ResultType, GeometryFactory>
            LocalAssemblerForIntegralOperators_;
    return std::auto_ptr<LocalAssemblerForOperators<ResultType> >(
                new LocalAssemblerForIntegralOperators_(
                    testGeometryFactory, trialGeometryFactory,
                    testRawGeometry, trialRawGeometry,
                    testBases, trialBases,
                    testTransformations, kernels, trialTransformations, integral,
                    openClHandler, parallelisationOptions,
                    cacheSingularIntegrals,
                    this->accuracyOptions()));
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
std::auto_ptr<LocalAssemblerForGridFunctions<ResultType> >
StandardLocalAssemblerFactoryForOperatorsOnSurfaces<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
makeAssemblerForGridFunctionsImplComplexUserFunction(
        const shared_ptr<const GeometryFactory>& geometryFactory,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& rawGeometry,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& testBases,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& testTransformations,
        const shared_ptr<const Function<ResultType> >& function,
        const shared_ptr<const OpenClHandler>& openClHandler) const
{
    typedef ResultType UserFunctionType;
    typedef StandardLocalAssemblerForGridFunctionsOnSurfaces<
            BasisFunctionType, UserFunctionType, ResultType, GeometryFactory>
            LocalAssemblerForGridFunctions_;
    return std::auto_ptr<LocalAssemblerForGridFunctions<ResultType> >(
                new LocalAssemblerForGridFunctions_(
                    geometryFactory, rawGeometry,
                    testBases,
                    testTransformations, function,
                    openClHandler));
}

template <typename BasisFunctionType, typename ResultType,
          typename GeometryFactory, typename Enable>
std::auto_ptr<EvaluatorForIntegralOperators<ResultType> >
StandardLocalAssemblerFactoryForOperatorsOnSurfaces<
BasisFunctionType, ResultType, GeometryFactory, Enable>::
makeEvaluatorForIntegralOperatorsImplComplexKernel(
        const shared_ptr<const GeometryFactory>& geometryFactory,
        const shared_ptr<const RawGridGeometry<CoordinateType> >& rawGeometry,
        const shared_ptr<const std::vector<const Basis<BasisFunctionType>*> >& trialBases,
        const shared_ptr<const CollectionOfKernels<ResultType> >& kernels,
        const shared_ptr<const CollectionOfBasisTransformations<CoordinateType> >& trialTransformations,
        const shared_ptr<const KernelTrialIntegral<BasisFunctionType, ResultType, ResultType> >& integral,
        const shared_ptr<const std::vector<std::vector<ResultType> > >& argumentLocalCoefficients,
        const shared_ptr<const OpenClHandler>& openClHandler) const
{
    typedef ResultType KernelType;
    typedef StandardEvaluatorForIntegralOperators<
            BasisFunctionType, KernelType, ResultType, GeometryFactory>
            EvaluatorForIntegralOperators_;
    return std::auto_ptr<EvaluatorForIntegralOperators<ResultType> >(
                new EvaluatorForIntegralOperators_(
                    geometryFactory, rawGeometry,
                    trialBases,
                    kernels, trialTransformations, integral,
                    argumentLocalCoefficients,
                    openClHandler,
                    this->accuracyOptions().singleRegular));
}

template <typename BasisFunctionType, typename ResultType, typename GeometryFactory>
StandardLocalAssemblerFactoryForOperatorsOnSurfaces<
        BasisFunctionType, ResultType, GeometryFactory,
        typename boost::enable_if<
        boost::is_same<ResultType,
        typename ScalarTraits<ResultType>::RealType> >::type>::
StandardLocalAssemblerFactoryForOperatorsOnSurfaces() :
    Base()
{
}

template <typename BasisFunctionType, typename ResultType, typename GeometryFactory>
StandardLocalAssemblerFactoryForOperatorsOnSurfaces<
        BasisFunctionType, ResultType, GeometryFactory,
        typename boost::enable_if<
        boost::is_same<ResultType,
        typename ScalarTraits<ResultType>::RealType> >::type>::
StandardLocalAssemblerFactoryForOperatorsOnSurfaces(
        const AccuracyOptions& accuracyOptions) :
    Base(accuracyOptions)
{
}

} // namespace Fiber

#endif
