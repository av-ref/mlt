
add_subdirectory(framework)
add_subdirectory(mlt++)
#add_subdirectory(melt)
#add_subdirectory(win32)

if(WIN32)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
    C:/Qt/Qt5.8.0-vc/5.8/msvc2015_64/lib/cmake/Qt5Core
    C:/Qt/Qt5.8.0-vc/5.8/msvc2015_64/lib/cmake/Qt3Widgets
    C:/Qt/Qt5.8.0-vc/5.8/msvc2015_64/lib/cmake/Qt5Gui
    C:/Qt/Qt5.8.0-vc/5.8/msvc2015_64/lib/cmake/Qt5Test
    C:/Qt/Qt5.8.0-vc/5.8/msvc2015_64/lib/cmake/Qt5Svg
    C:/Qt/Qt5.8.0-vc/5.8/msvc2015_64/lib/cmake/Qt5Xml
    )
else(WIN32)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Core
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Widgets
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Gui
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Test
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Svg
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Xml
        )
endif(WIN32)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Xml REQUIRED)


#add_subdirectory(modules)
#add_subdirectory(app)
#add_subdirectory(tests)
