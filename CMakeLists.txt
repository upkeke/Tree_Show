cmake_minimum_required(VERSION 3.16)

project(XXX VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64") # 设置qt动态库的路径
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#添加定义，是否使用标准容器
add_compile_definitions(USE_STL_VECTOR=1)
include_directories(
    ./
    ${CMAKE_CURRENT_LIST_DIR}/BinaryTree
    ${CMAKE_CURRENT_LIST_DIR}/BinaryTree/container
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
if(MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()
#message("Qt6Widgets_INCLUDE_DIRS >> ${Qt6Widgets_INCLUDE_DIRS}")
#include_directories(BEFORE ${Qt6Widgets_INCLUDE_DIRS})


add_subdirectory(BinaryTree)
add_subdirectory(MainWin)



 