project(mainwin)
set(mw_src 
    #WIN32
    mainwin.h
    mainwin.ui
    mainwin.cpp
    res.qrc
)
add_subdirectory(GraphicsItemManager)
#测试动画
add_subdirectory(animate_test)



add_executable(${PROJECT_NAME} main.cpp ${mw_src})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    #data_source
    FuncForTreeStr
    GrapItemManager
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




