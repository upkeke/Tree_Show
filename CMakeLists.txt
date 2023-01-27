cmake_minimum_required (VERSION 3.18)
project(Tree_Show)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
if (MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(src 
    main.cpp
    some_func.cpp
)


add_executable(${PROJECT_NAME} ${src})


message("vvv ${CMAKE_CURRENT_LIST_DIR}")
# target_include_directories(${PROJECT_NAME}
#     PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}
# )