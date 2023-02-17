project(AnimManager)

set(${PROJECT_NAME}_SRC 
    AnimManager.cpp
)


#add_library(${PROJECT_NAME} SHARED ${Anim_src})
add_library(AnimManager SHARED ${${PROJECT_NAME}_SRC})
target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
    ANIM_LIB_CCXX
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    GrapItemManager
    GrapUiManager
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)






