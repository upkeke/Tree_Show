project(GrapItemManager)

set(manager_src 
    GrapNodeItem.cpp
    GrapLineItem.cpp
    GrapItemManager.cpp
    GrapMoveItem.cpp
)
add_library(${PROJECT_NAME} SHARED ${manager_src})
target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
    GRAP_LIB
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

