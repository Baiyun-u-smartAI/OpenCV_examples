cmake_minimum_required(VERSION 3.15)
# opencv_work为工程输出的exe名字
project(opencv_work CXX)
set(OUT_NAME "test") # 输出文件名test
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/Release) # 输出的可执行文件在bin文件夹下
set(CMAKE_BUILD_TYPE Release) # 可以填Debug或Release
find_package(PkgConfig REQUIRED)
if (PKG_CONFIG_FOUND)
    #! msys64 可以用pkg-config进行管理
    
    # PKGS_DEP是用户自定义的cmake模块名，REQUIRED后面是要导入的模块名称（以空格分割）
    pkg_search_module(OPENCV4 REQUIRED opencv4)

    # 输出找到的库配置信息
    message(STATUS "=== OPENCV4_LIBRARIES: ${OPENCV4_LIBRARIES}")
    message(STATUS "=== OPENCV4_INCLUDE_DIRS: ${OPENCV4_INCLUDE_DIRS}")

    # C++标准是c++11
    set(CMAKE_CXX_STANDARD 11)
    # 让工程输出的可执行文件在当前目录下

    # 该工程编译成exe文件需要依赖xxxx.cpp
    add_executable(${PROJECT_NAME} main.cpp)
    # 将PkgConfig搜索到库名应用到当前目录
    target_link_libraries(${PROJECT_NAME} ${OPENCV4_LIBRARIES} libstdc++)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENCV4_INCLUDE_DIRS})
else(PKG_CONFIG_FOUND) #! 手动编译的CV需要添加CMAKE_PREFIX_PATH变量

    list(APPEND CMAKE_PREFIX_PATH .../build/install) # 这里填的是OpenCVConfig.cmake所在的文件夹，该文件一般在install文件里面，不然下面就无法找到 ${OpenCV_LIBS} ${OpenCV_INCLUDE_DIRS}等等的变量

    find_package(OpenCV CONFIG REQUIRED) # 根据OpenCVConfig.cmake导入${OpenCV_xxxxxxx}变量到当前工程
    if(MINGW)
    set(OpenCV_DIR ${OpenCV_INCLUDE_DIRS}/../x64/mingw/lib) # 需要手动设置OpenCV_DIR变量，这里可以填关于include文件夹${OpenCV_INCLUDE_DIRS}的相对路径，或者绝对路径，例如C:/Users/X-Studio/Downloads/opencv-4.x/build/install/x64/mingw/lib
    endif(MINGW)

    if(MSVC)
        if(MSVC_TOOLSET_VERSION EQUAL "142") #? VS 2019 (16.0)
            set(OpenCV_DIR ${OpenCV_INCLUDE_DIRS}/../x64/vc16/lib) # 需要手动设置OpenCV_DIR变量，这里可以填关于include文件夹${OpenCV_INCLUDE_DIRS}的相对路径，或者绝对路径，例如C:/Users/X-Studio/Downloads/opencv-4.x/build/install/x64/vc16/lib (vc16是vs2019的版本)
        elseif(MSVC_TOOLSET_VERSION EQUAL "143")  #? VS 2022 (17.0)
            set(OpenCV_DIR ${OpenCV_INCLUDE_DIRS}/../x64/vc17/lib) # 需要手动设置OpenCV_DIR变量，这里可以填关于include文件夹${OpenCV_INCLUDE_DIRS}的相对路径，或者绝对路径，例如C:/Users/X-Studio/Downloads/opencv-4.x/build/install/x64/vc17/lib (vc17是vs2022的版本)
        endif()

    endif(MSVC)

    add_executable(${PROJECT_NAME} main.cpp)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS}) # 添加头文件搜索路径
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}) # 添加库的名


endif (PKG_CONFIG_FOUND)
# 为了让输出文件名不同于工程名
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME ${OUT_NAME}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/Release # 输出的可执行文件在bin/Release文件夹下
        )
