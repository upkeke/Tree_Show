project(mainwin)
#ui转为头文件的目录
include_directories(${CMAKE_CURRENT_LIST_DIR}/Res/include)


add_subdirectory(GraphicsItemManager)
add_subdirectory(GrapUi)
add_subdirectory(Anim)

add_subdirectory(Res)
set(${PROJECT_NAME}_SRC 
    #WIN32 #如果不需要控制台，取消这行注释
    mainwin.cpp
    ThScene.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${${PROJECT_NAME}_SRC})
#依赖Res自定义命令生成的ui头文件和rcc资源文件 这个无论rcc和ui是否修改都会执行Res中的target
#add_dependencies(${PROJECT_NAME} Res)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    FuncForHeadNode
    GrapItemManager
    test_data
    GrapUiManager
    AnimManager
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
   
)

add_executable(ts test.cpp)
target_link_libraries(ts
    PUBLIC
    Qt6::Widgets
    Qt6::Core
)