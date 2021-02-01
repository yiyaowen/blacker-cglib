cmake_minimum_required(VERSION 3.10)

project(blacker-cglib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(bcg)

file(GLOB_RECURSE blacker_cg_lib_hpp_files "bcg/*.hpp")

set(blacker_cg_test_items
    b_vector_test
    bv_m_conversion_test
    matrix_test
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

foreach(test_item ${blacker_cg_test_items})
    message(STATUS  "Add test file: ${PROJECT_SOURCE_DIR}/test/${test_item}.cpp")
    add_executable(${test_item}
        "${PROJECT_SOURCE_DIR}/test/${test_item}.cpp"
        ${black_cg_lib_hpp_file}
    )
endforeach()
