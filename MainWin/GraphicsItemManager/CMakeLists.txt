project(GrapItemManager)
set(manager_src 
    GrapNodeItem.cpp
    GrapLineItem.cpp
    GrapItemManager.cpp
)
# add_custom_target(uui_get
#     #COMMAND  "cmd.exe uic.exe mainwin.ui -o qwe.h"
#     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
# )

add_library(${PROJECT_NAME} SHARED ${manager_src})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
)
# qt6_add_resources(${PROJECT_NAME} imageresources
#     PREFIX "/img"
#     #BASE "E:/code/23-a/Tree_Show/MainWin/img"
#     FILES green.jpg pink.jpg yellow.jpg
# )
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)




