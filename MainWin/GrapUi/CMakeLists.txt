project(GrapUiManager)

# 资源文件
# add_library(ui_res STATIC ui_res.cpp)
# target_link_libraries(ui_res
#     PUBLIC
#     Qt6::Core
# )

set(${PROJECT_NAME}_SRC
    GrapUi.cpp
    GrapUiManager.cpp
    #ui_res.cpp
)
# GrapUiManager
add_library(GrapUiManager SHARED ${${PROJECT_NAME}_SRC})
# 生成资源文件

# add_custom_target(ui_resX
#     COMMAND rcc ui_res.qrc -o ui_res.cpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
#     DEPENDS GrapUiManager
# )

target_compile_definitions(GrapUiManager
    PRIVATE
    GRAPUI_BIN
)
target_link_libraries(GrapUiManager
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    ##ui_res
)
target_include_directories(GrapUiManager
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
