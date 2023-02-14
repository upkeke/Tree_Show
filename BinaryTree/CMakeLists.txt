
project(BinaryTree)

add_subdirectory(container)

find_package(Qt6 REQUIRED Sql Widgets Core)

add_library(FuncForHeadNode SHARED FuncForHeadNode.cpp)
target_link_libraries(FuncForHeadNode
        PUBLIC
        Qt6::Core
)



add_library(test_data SHARED get_test_data.cpp)
target_link_libraries(test_data
        PUBLIC
        Qt6::Core
        Qt6::Sql
)

add_custom_command(TARGET test_data
        COMMAND copy "..\\..\\data\\somedata.db" "..\\..\\bin"
)

add_executable(bin_main main.cpp)

target_link_libraries(bin_main
        PUBLIC
        test_data
)