cmake_minimum_required(VERSION 3.16)

project(XXX VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64") # 设置qt动态库的路径
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
if(MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()
include_directories(${CMAKE_CURRENT_LIST_DIR}/BinaryTree)
message("Qt5Widgets_INCLUDE_DIRS >> ${Qt6Widgets_INCLUDE_DIRS}")

include_directories(BEFORE ${Qt6Widgets_INCLUDE_DIRS})
add_subdirectory(BinaryTree)
add_subdirectory(MainWin)




add_executable(XXX main.cpp)
target_link_libraries(XXX 
    PRIVATE 
    mainwin
    #graphicsItem
)

target_include_directories(XXX
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/MainWin
    #Qt6::Widgets
    #Qt6::Core
)



