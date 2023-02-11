project(AnimManager)

set(Anim_src 
    AnimManager.cpp
    xxpop.cpp
)


#add_library(${PROJECT_NAME} SHARED ${Anim_src})
add_library(${PROJECT_NAME} SHARED AnimManager.cpp)
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
    ${CMAKE_SOURCE_DIR}/MainWin/GraphicsItemManager
    ${CMAKE_SOURCE_DIR}/MainWin/GrapUi
)






