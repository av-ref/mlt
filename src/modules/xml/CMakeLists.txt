

set(SRCS
        factory.c
        consumer_xml.c
        producer_consumer.c
        producer_xml.c
        common.c
        )

set(HDRS
        common.h
        )


add_library(mltxml MODULE ${SRCS})
if(WIN32)
    target_link_libraries(mltxml mlt pthread_dll)
else()
    target_link_libraries(mltxml mlt m pthread)
endif()

set_target_properties( mltxml
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY})

add_custom_command(
        TARGET mltxml
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/xml
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/mlt-xml.dtd ${MLT_META_DATA_DIRECTORY}/xml/
        )

file(GLOB ymls *.yml)
foreach(yml ${ymls})
    file(COPY ${yml}
        DESTINATION ${MLT_META_DATA_DIRECTORY}/xml/)
endforeach()

install(TARGETS mltxml EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} 
DESTINATION share/mlt
FILES_MATCHING 
PATTERN "mlt-xml.dtd"
PATTERN "*.yml"
)  #install dir
