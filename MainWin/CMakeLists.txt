project(mainwin)
set(mw_src 
    #WIN32 #如果不需要控制台，取消这行注释
    mainwin.h
    BinaryTreeWin.ui
    mainwin.cpp
    #KGraphicsView.
    mainRes.qrc
)
add_subdirectory(GraphicsItemManager)
add_subdirectory(GrapUi)
add_subdirectory(Anim)
add_subdirectory(test) 

add_executable(${PROJECT_NAME} main.cpp ${mw_src})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    FuncForTreeStr
    GrapItemManager
    test_data
    GrapUiManager
    AnimManager
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)


add_executable(testWin main2.cpp widget.cpp)

target_link_libraries(testWin
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    test_data
    GrapUiManager
    AnimManager
)
