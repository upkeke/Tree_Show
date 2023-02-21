cmake_minimum_required(VERSION 3.20)

project(XXX VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64") # 设置qt动态库的路径
set(CMAKE_AUTOMOC ON)

# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

# option(WRITING "内部使用" OFF)
# if(WRITING)
# #添加定义，是否使用标准容器
#     add_compile_definitions(USE_STL_VECTOR=0)
#     include_directories(${CMAKE_CURRENT_LIST_DIR}/BinaryTree/container)
# endif()

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/BinaryTree
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
if(MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)


add_subdirectory(BinaryTree)
add_subdirectory(MainWin)



 
