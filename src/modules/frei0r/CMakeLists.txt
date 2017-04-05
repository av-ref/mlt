

set(SRCS
        factory.c
        producer_frei0r.c
        filter_frei0r.c
        transition_frei0r.c
        frei0r_helper.c
        )

set(HDRS
        frei0r_helper.h
        )


add_library(mltfrei0r MODULE ${SRCS})
if(WIN32)
    target_link_libraries(mltfrei0r mlt frei0r)
else()
    target_link_libraries(mltfrei0r mlt frei0r)
endif()

set_target_properties( mltfrei0r
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY})

add_custom_command(
        TARGET mltfrei0r
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/frei0r
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/blacklist.txt ${MLT_META_DATA_DIRECTORY}/frei0r/
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/not_thread_safe.txt ${MLT_META_DATA_DIRECTORY}/frei0r/
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/param_name_map.yaml ${MLT_META_DATA_DIRECTORY}/frei0r/
        )

file(GLOB ymls *.yml)
foreach(yml ${ymls})
    file(COPY ${yml}
        DESTINATION ${MLT_META_DATA_DIRECTORY}/xml/)
endforeach()

install(TARGETS mltfrei0r EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} 
DESTINATION share/mlt
FILES_MATCHING 
PATTERN "param_name_map.yaml"
PATTERN "blacklist.txt"
PATTERN "not_thread_safe.txt"
PATTERN "*.yml"
)  #install dir
