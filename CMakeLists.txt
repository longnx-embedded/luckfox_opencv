cmake_minimum_required(VERSION 3.0.0)
project(opencv_rkisp VERSION 0.1.0 LANGUAGES C CXX)

# rockit lib
set (ROCKIT ${CMAKE_CURRENT_SOURCE_DIR}/rockit/lib)
# set library directories
file(GLOB LIBRARY_FILES ${ROCKIT}/*.so)

foreach(LIBRARY ${LIBRARY_FILES})
    link_libraries(${LIBRARY})
endforeach()
include(CTest)
enable_testing()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rockit/include)
link_directories(${ROCKIT})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sample)
add_executable(opencv_rkisp main.cpp sample/loadbmp.c sample/sample_comm.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
