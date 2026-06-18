cmake_minimum_required(VERSION 3.15)
project(linalg VERSION 0.1.0 LANGUAGES C)

# Build as a shared library so Python (ctypes) can load it at runtime and the
# C visualizer can link against it.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Put the .dll / import lib / test exes in predictable top-level folders so
# consumers (and the Python loader) can find them.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(linalg SHARED
    src/matrix.c
    src/vector.c
    src/decomp.c
    src/gfx.c
)

target_include_directories(linalg PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# LINALG_BUILD switches the LINALG_API macro to dllexport while building the lib.
target_compile_definitions(linalg PRIVATE LINALG_BUILD)

if(MSVC)
    target_compile_options(linalg PRIVATE /W4)
else()
    target_compile_options(linalg PRIVATE -Wall -Wextra)
    target_link_libraries(linalg PRIVATE m)   # libm for sqrt/sin/cos
endif()

# ---- tests ----
enable_testing()

set(LINALG_TESTS test_matrix test_vector test_decomp test_gfx)
foreach(t ${LINALG_TESTS})
    add_executable(${t} tests/${t}.c)
    target_link_libraries(${t} PRIVATE linalg)
    target_include_directories(${t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_test(NAME ${t} COMMAND ${t})
endforeach()

# ---- install (lets consumers add_subdirectory or install + find) ----
install(TARGETS linalg
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
