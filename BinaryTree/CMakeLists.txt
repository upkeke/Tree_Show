

project(data_source)
find_package(Qt6 REQUIRED Sql Widgets)

add_library(${PROJECT_NAME} STATIC data_source.cpp)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt6::Sql
)
message("Qt6Sql_INCLUDE_DIRS >> ${Qt6Sql_INCLUDE_DIRS}")

add_executable(testBin main1.cpp)
target_link_libraries(testBin
    PRIVATE
    data_source
)