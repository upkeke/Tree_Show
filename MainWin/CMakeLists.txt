project(mainwin)
set(mw_src 
    #WIN32 #如果不需要控制台，取消这行注释
    mainwin.h
    mainwin.ui
    mainwin.cpp
)
add_subdirectory(GraphicsItemManager)


add_executable(${PROJECT_NAME} main.cpp ${mw_src})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    FuncForTreeStr
    GrapItemManager
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)




