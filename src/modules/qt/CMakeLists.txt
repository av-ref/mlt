
set(CSRCS
        factory.c
        producer_qimage.c
        producer_kdenlivetitle.c
        )

set(CPPSRCS
        common.cpp
        graph.cpp
        filter_audiowaveform.cpp
        qimage_wrapper.cpp
        kdenlivetitle_wrapper.cpp
        producer_qtext.cpp
        transition_qtblend.cpp
        filter_qtblend.cpp

        consumer_qglsl.cpp
        transition_vqm.cpp
        )

add_definitions( -DGPL3 -DUSE_QT_OPENGL )

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Core
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Widgets
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Gui
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Svg
        /opt/Qt/Qt5.7.0-linux/5.7/gcc_64/lib/cmake/Qt5Xml
        )

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Xml REQUIRED)

add_library(mltqt MODULE ${CSRCS} ${CPPSRCS})
target_link_libraries(mltqt mlt mlt++ m pthread Qt5::Widgets Qt5::Gui Qt5::Core Qt5::Svg Qt5::Xml)
set_target_properties( mltqt
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY})

add_custom_command(
        TARGET mltqt
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/qt
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.yml  ${MLT_META_DATA_DIRECTORY}/qt/
)