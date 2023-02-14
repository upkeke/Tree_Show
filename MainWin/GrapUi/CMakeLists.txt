project(GrapUiManager)

#[[ ++++++++++++++++++++++++++++++++++++++++++++++++
]]#

set(${PROJECT_NAME}_SRC
    GrapUi.cpp
    GrapUiManager.cpp
    ui_res.cpp
)
#add_library(UI_RES SHARED ui_res.cpp)
# target_link_libraries(UI_RES
#     PUBLIC
#     Qt6::Core
# )
add_library(GrapUiManager SHARED ${${PROJECT_NAME}_SRC})
target_compile_definitions(GrapUiManager
    PRIVATE
    GRAPUI_BIN
)
target_link_libraries(GrapUiManager
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    #UI_RES
)

target_include_directories(GrapUiManager
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
