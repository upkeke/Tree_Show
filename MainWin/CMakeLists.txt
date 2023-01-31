project(mainwin)
set(mw_src 
    #WIN32
    mainwin.h
    mainwin.ui
    mainwin.cpp
    MyGraphicsItem.cpp
    MyLineItem.cpp
    res.qrc
)
# add_custom_target(uui_get
#     #COMMAND  "cmd.exe uic.exe mainwin.ui -o qwe.h"
#     COMMAND   tree "/f"
#     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
# )

add_executable(${PROJECT_NAME} main.cpp ${mw_src})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    data_source
)
# qt6_add_resources(${PROJECT_NAME} imageresources
#     PREFIX "/img"
#     #BASE "E:/code/23-a/Tree_Show/MainWin/img"
#     FILES green.jpg pink.jpg yellow.jpg
# )
target_link_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/BinaryTree
)




