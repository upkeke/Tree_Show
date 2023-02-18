project(AnimManager)

set(${PROJECT_NAME}_SRC 
    AnimManager.cpp
    GrapAnimItem.cpp
)


#add_library(${PROJECT_NAME} SHARED ${Anim_src})
add_library(AnimManager SHARED ${${PROJECT_NAME}_SRC})
target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
    ANIM_LIB_X
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    GrapItemManager
    HeadNode
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)






