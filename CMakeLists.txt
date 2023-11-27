cmake_minimum_required(VERSION 3.0.0)
project(opencv_rkisp VERSION 0.1.0 LANGUAGES C CXX)

# rockit lib
set (ROCKIT ${CMAKE_CURRENT_SOURCE_DIR}/rockit/lib)
set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/opencv-mobile/lib/cmake/opencv4)
# set library directories
file(GLOB LIBRARY_FILES ${ROCKIT}/*.so)
find_package(OpenCV REQUIRED)

foreach(LIBRARY ${LIBRARY_FILES})
    link_libraries(${LIBRARY})
endforeach()
include(CTest)
enable_testing()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rockit/include)
link_directories(${ROCKIT})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sample)
add_executable(opencv_rkisp main.cpp sample/loadbmp.c sample/sample_comm.c)

target_link_libraries(opencv_rkisp ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
