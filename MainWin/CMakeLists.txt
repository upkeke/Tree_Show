project(mainwin)
set(mw_src 
    #WIN32
    mainwin.h
    mainwin.ui
    mainwin.cpp
    MyGraphicsItem.cpp
    MyLineItem.cpp
    #res.qrc
)
# add_custom_target(uui_get
#     #COMMAND  "cmd.exe uic.exe mainwin.ui -o qwe.h"
#     COMMAND   tree "/f"
#     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
# )

add_library(${PROJECT_NAME} STATIC ${mw_src})
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    some_func
)

target_link_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/BinaryTree
)



