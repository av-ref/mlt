
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Core
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Widgets
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Test
        )

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

add_subdirectory(test_filter)
add_subdirectory(test_frame )
add_subdirectory(test_properties )
add_subdirectory(test_repository )
add_subdirectory(test_animation )
add_subdirectory(test_tractor)