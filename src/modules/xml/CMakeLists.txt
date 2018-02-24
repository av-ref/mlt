

set(SRCS
        factory.c
        consumer_xml.c
        producer_xml.c
        common.c
        )

set(HDRS
        common.h
        )

#find_package(xml)

add_library(mltxml MODULE ${SRCS})

if(WIN32)
    target_link_libraries(mltxml mlt pthread_dll)
else()
    target_link_libraries(mltxml mlt m pthread xml2)
    INCLUDE_DIRECTORIES(/usr/include/libxml2)
endif()

set_target_properties( mltxml
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY})

add_custom_command(
        TARGET mltxml
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/xml
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
)  
