

set(SRCS
        main.cpp
        mainwindow.cpp
        FrameWdg.cpp
        mltcontroller.cpp
        )

set(HDRS
        mainwindow.h
        FrameWdg.h
        mltcontroller.h
        )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Core
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Widgets
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Gui
        )
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Generate code from ui files
qt5_wrap_ui(UI_HEADERS mainwindow.ui)

# Generate rules for building source files from the resources
qt5_add_resources(QRCS resources.qrc)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(sampleapp ${SRCS} )
target_link_libraries(sampleapp mlt++ mlt Qt5::Widgets Qt5::Core Qt5::Gui)