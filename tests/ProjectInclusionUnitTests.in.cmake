function(assert_file_included filename)
    foreach(directory ${ARGN})
        if(EXISTS "${directory}/${filename}")
            return()
        endif()
    endforeach()
    message(FATAL_ERROR "Could not include file ${filename}")
endfunction()

# Check include directories
if(NOT DEFINED BEMPP_INCLUDE_DIRS)
    message(FATAL_ERROR "Expected BEMPP_INCLUDE_DIRS to be defined")
endif()
assert_file_included(bempp/config_bempp.hpp          ${BEMPP_INCLUDE_DIRS})
assert_file_included(bempp/fiber/types.hpp           ${BEMPP_INCLUDE_DIRS})
assert_file_included(Trilinos/Teuchos_Serializer.hpp ${BEMPP_INCLUDE_DIRS})
assert_file_included(armadillo                       ${BEMPP_INCLUDE_DIRS})
assert_file_included(boost/array.hpp                 ${BEMPP_INCLUDE_DIRS})
assert_file_included(dune/grid/onedgrid.hh           ${BEMPP_INCLUDE_DIRS})
assert_file_included(dune_config.h                   ${BEMPP_INCLUDE_DIRS})
assert_file_included(tbb/atomic.h                    ${BEMPP_INCLUDE_DIRS})

if(NOT DEFINED BEMPP_PYTHON_INCLUDE_DIRS)
    message(FATAL_ERROR "Expected BEMPP_PYTHON_INCLUDE_DIRS to be defined")
endif()
assert_file_included(Python.h ${BEMPP_PYTHON_INCLUDE_DIRS})
assert_file_included(numpy/arrayobject.h ${BEMPP_PYTHON_INCLUDE_DIRS})
