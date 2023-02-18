project(Res)

include_directories(${Qt6Widgets_INCLUDE_DIRS})
add_custom_target(Res
    COMMAND uic BinaryTreeWin.ui -o ./include/uix_BinaryTreeWin.h
    COMMAND uic settingWin.ui -o ./include/uix_settingWin.h
    COMMAND rcc -binary -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res.rcc  res.qrc
    #COMMAND tree /f
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

#settingWin
