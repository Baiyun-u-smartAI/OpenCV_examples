cmake_minimum_required(VERSION 3.14)
project(cuda_test_yoloV5)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND CMAKE_PREFIX_PATH C:/Users/X-Studio/Downloads/opencv-4.x/build/install) # 这里填的是OpenCVConfig.cmake所在的文件夹，该文件一般在install文件里面，不然下面就无法找到 ${OpenCV_LIBS} ${OpenCV_INCLUDE_DIRS}等等的变量


find_package(OpenCV CONFIG REQUIRED) # 根据OpenCVConfig.cmake导入${OpenCV_xxxxxxx}变量到当前工程
set(OpenCV_DIR ${OpenCV_INCLUDE_DIRS}/../x64/vc16/lib) # 需要手动设置OpenCV_DIR变量，这里可以填关于include文件夹${OpenCV_INCLUDE_DIRS}的相对路径，或者绝对路径，例如C:/Users/X-Studio/Downloads/opencv-4.x/build/install/x64/vc16/lib

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS}) # 添加头文件搜索路径
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}) # 添加库的名
