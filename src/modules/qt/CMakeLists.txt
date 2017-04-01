
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


add_library(mltqt MODULE ${CSRCS} ${CPPSRCS})
if(WIN32)
    target_link_libraries( mltqt pthread mlt mlt++ m Qt5::Widgets Qt5::Gui Qt5::Core Qt5::Svg Qt5::Xml)
else()
    target_link_libraries(mltqt mlt mlt++ m pthread Qt5::Widgets Qt5::Gui Qt5::Core Qt5::Svg Qt5::Xml)
endif()

set_target_properties( mltqt
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY})

add_custom_command(
        TARGET mltqt
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/qt
#        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.yml  ${MLT_META_DATA_DIRECTORY}/qt/
)

file(GLOB ymls *.yml)
foreach(yml ${ymls})
    file(COPY ${yml}
        DESTINATION ${MLT_META_DATA_DIRECTORY}/qt/)
endforeach()

install(TARGETS mltqt EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
DESTINATION share/
FILES_MATCHING
PATTERN "*.yml"
)  #install dir
