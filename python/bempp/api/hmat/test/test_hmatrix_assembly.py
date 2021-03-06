import unittest
from unittest import TestCase
import numpy as np
import bempp.api

TOL_FINE = 1E-5
TOL_COARSE = 1E-3
TOL_FACTOR = 10

class TestHMatrixAssembly(TestCase):

    requiresgmsh = unittest.skipIf(bempp.api.GMSH_PATH is None, reason="Needs GMSH")

    def test_laplace_single_layer_sphere(self):

        parameters_hmat_coarse = bempp.api.common.global_parameters()
        parameters_hmat_fine = bempp.api.common.global_parameters()
        parameters_dense = bempp.api.common.global_parameters()

        parameters_dense.assembly.boundary_operator_assembly_type = 'dense'

        parameters_hmat_coarse.assembly.boundary_operator_assembly_type = 'hmat'
        parameters_hmat_coarse.hmat.eps = TOL_COARSE

        parameters_hmat_fine.assembly.boundary_operator_assembly_type = 'hmat'
        parameters_hmat_fine.hmat.eps = TOL_FINE

        grid = bempp.api.shapes.sphere(4)
        space = bempp.api.function_space(grid, "DP", 0)

        slp_hmat_coarse = bempp.api.as_matrix(
                bempp.api.operators.boundary.laplace.single_layer(space, space, space, parameters=parameters_hmat_coarse).weak_form())
        slp_hmat_fine = bempp.api.as_matrix(
                bempp.api.operators.boundary.laplace.single_layer(space, space, space, parameters=parameters_hmat_fine).weak_form())

        slp_dense = bempp.api.as_matrix(
                bempp.api.operators.boundary.laplace.single_layer(space, space, space, parameters=parameters_dense).weak_form())

        rel_diff_coarse = np.linalg.norm(slp_hmat_coarse-slp_dense)/np.linalg.norm(slp_dense)
        self.assertTrue(rel_diff_coarse < TOL_FACTOR * TOL_COARSE)

        rel_diff_fine = np.linalg.norm(slp_hmat_fine-slp_dense)/np.linalg.norm(slp_dense)
        self.assertTrue(rel_diff_fine < TOL_FACTOR * TOL_FINE)

    @requiresgmsh
    def test_laplace_double_layer_cube(self):

        parameters_hmat_coarse = bempp.api.common.global_parameters()
        parameters_hmat_fine = bempp.api.common.global_parameters()
        parameters_dense = bempp.api.common.global_parameters()

        parameters_dense.assembly.boundary_operator_assembly_type = 'dense'

        parameters_hmat_coarse.assembly.boundary_operator_assembly_type = 'hmat'
        parameters_hmat_coarse.hmat.eps = TOL_COARSE

        parameters_hmat_fine.assembly.boundary_operator_assembly_type = 'hmat'
        parameters_hmat_fine.hmat.eps = TOL_FINE

        grid = bempp.api.shapes.cube()
        space = bempp.api.function_space(grid, "DP", 0)

        slp_hmat_coarse = bempp.api.as_matrix(
                bempp.api.operators.boundary.laplace.double_layer(space, space, space, parameters=parameters_hmat_coarse).weak_form())
        slp_hmat_fine = bempp.api.as_matrix(
                bempp.api.operators.boundary.laplace.double_layer(space, space, space, parameters=parameters_hmat_fine).weak_form())

        slp_dense = bempp.api.as_matrix(
                bempp.api.operators.boundary.laplace.double_layer(space, space, space, parameters=parameters_dense).weak_form())

        rel_diff_coarse = np.linalg.norm(slp_hmat_coarse-slp_dense)/np.linalg.norm(slp_dense)
        self.assertTrue(rel_diff_coarse < TOL_FACTOR * TOL_COARSE)

        rel_diff_fine = np.linalg.norm(slp_hmat_fine-slp_dense)/np.linalg.norm(slp_dense)
        self.assertTrue(rel_diff_fine < TOL_FACTOR * TOL_FINE)

    def test_helmholtz_single_layer_sphere_linear_space(self):

        parameters_hmat_coarse = bempp.api.common.global_parameters()
        parameters_hmat_fine = bempp.api.common.global_parameters()
        parameters_dense = bempp.api.common.global_parameters()

        parameters_dense.assembly.boundary_operator_assembly_type = 'dense'

        parameters_hmat_coarse.assembly.boundary_operator_assembly_type = 'hmat'
        parameters_hmat_coarse.hmat.eps = TOL_COARSE

        parameters_hmat_fine.assembly.boundary_operator_assembly_type = 'hmat'
        parameters_hmat_fine.hmat.eps = TOL_FINE

        grid = bempp.api.shapes.sphere(4)
        space = bempp.api.function_space(grid, "P", 1)

        slp_hmat_coarse = bempp.api.as_matrix(
                bempp.api.operators.boundary.helmholtz.single_layer(space, space, space, 1, parameters=parameters_hmat_coarse).weak_form())
        slp_hmat_fine = bempp.api.as_matrix(
                bempp.api.operators.boundary.helmholtz.single_layer(space, space, space, 1, parameters=parameters_hmat_fine).weak_form())

        slp_dense = bempp.api.as_matrix(
                bempp.api.operators.boundary.helmholtz.single_layer(space, space, space, 1, parameters=parameters_dense).weak_form())

        rel_diff_coarse = np.linalg.norm(slp_hmat_coarse-slp_dense)/np.linalg.norm(slp_dense)
        self.assertTrue(rel_diff_coarse < TOL_FACTOR * TOL_COARSE)

        rel_diff_fine = np.linalg.norm(slp_hmat_fine-slp_dense)/np.linalg.norm(slp_dense)
        self.assertTrue(rel_diff_fine < TOL_FACTOR * TOL_FINE)

if __name__ == "__main__":
    from unittest import main
    main()





