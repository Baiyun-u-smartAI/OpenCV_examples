cmake_minimum_required(VERSION 3.13)
project(OpenCV_Xampl)

# alternative set C++ path
# SET(CMAKE_C_COMPILER D:/MinGW-w64/mingw64/bin/gcc)
# SET(CMAKE_CXX_COMPILER D:/MinGW-w64/mingw64/bin/g++)
# use C++ 11
set(CMAKE_CXX_STANDARD 11)

# where to find CMake modules and OpenCV
set(OpenCV_DIR "D:\\opencv411\\build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# import Opencv package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# to run C++ program with all SOURCE_FILES in the directory
file(GLOB SOURCE_FILES "*.h" "*.cpp" "*.c" "*.hpp")
add_executable(OpenCV_Xampl ${SOURCE_FILES})


# add libs you need
set(OpenCV_LIBS ${OpenCV_LIBS})

# linking
target_link_libraries(OpenCV_Xampl ${OpenCV_LIBS})
