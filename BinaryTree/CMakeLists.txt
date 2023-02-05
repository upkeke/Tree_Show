

project(data_source)

add_subdirectory(container)

find_package(Qt6 REQUIRED Sql Widgets Core)

include_directories(Qt6Core_INCLUDE_DIRS)
get_directory_property(xx INCLUDE_DIRECTORIES)



# add_library(${PROJECT_NAME} STATIC data_source.cpp)
# target_link_libraries(${PROJECT_NAME}
#         PUBLIC
#         Qt6::Sql
# )
add_library(FuncForTreeStr FuncForTreeStr.cpp)
target_link_libraries(FuncForTreeStr
        PUBLIC
        Qt6::Core
)

add_executable(bin_main main.cpp)
target_link_libraries(bin_main
        PUBLIC
        Qt6::Core
        Qt6::Sql
)