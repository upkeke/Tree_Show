

project(some_func)


add_library(${PROJECT_NAME} STATIC some_func.cpp)


add_executable(testBin main1.cpp )
target_link_libraries(testBin
    PRIVATE
    some_func
)