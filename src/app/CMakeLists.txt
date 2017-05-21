

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



# Generate code from ui files
qt5_wrap_ui(UI_HEADERS mainwindow.ui)

# Generate rules for building source files from the resources
qt5_add_resources(QRCS resources.qrc)

#find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(mltQApp ${SRCS} ${QRCS})
target_link_libraries(mltQApp mlt++ mlt Qt5::Widgets Qt5::Core Qt5::Gui)

install(TARGETS mltQApp EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
