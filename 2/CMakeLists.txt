cmake_minimum_required(VERSION 3.13)
project(OpenCV_2)

# alternative set C++ path
# REPLACE WITH your installed binary path of MingW64
# SET(CMAKE_C_COMPILER D:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/gcc)
# SET(CMAKE_CXX_COMPILER D:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++)

# use C++ VERSION
set(CMAKE_CXX_STANDARD 11)
# where to find CMake modules and OpenCV

set(OpenCV_DIR "D:\\build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# import Opencv package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# to run C++ program with all SOURCE_FILES in the directory
file(GLOB SOURCE_FILES "*.h" "*.cpp" "*.c" "*.hpp")
add_executable(OpenCV_2 ${SOURCE_FILES})

# add libs you need
set(OpenCV_LIBS ${OpenCV_LIBS})

# linking
target_link_libraries(OpenCV_2 ${OpenCV_LIBS})


# PS run command as below
# cmake CMakeLists.txt -G "MinGW Makefiles"
# mingw32-make / cmake --build "%cd%"
# .\ProjectName
