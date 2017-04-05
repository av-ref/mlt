

find_package(FFmpeg REQUIRED)

set(SRCS
        factory.c
        filter_avcolour_space.c
        filter_avdeinterlace.c
        filter_avfilter.c
        filter_avresample.c
        filter_swscale.c
        producer_avformat.c
        consumer_avformat.c
        )


add_definitions( -DFILTERS -DCODECS -DAVDEVICE -DAVFILTER)


include_directories(${FFmpeg_INCLUDE_DIRS})

add_library(avformat MODULE ${SRCS} )

target_link_libraries(avformat mlt  ${FFmpeg_LIBRARIES})

set_target_properties( avformat
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY}
        )

add_custom_command(
        TARGET avformat
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/avformat
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/blacklist.txt ${MLT_META_DATA_DIRECTORY}/avformat/
#        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.yml  ${MLT_META_DATA_DIRECTORY}/avformat/
)

file(GLOB ymls *.yml)
foreach(yml ${ymls})
    file(COPY ${yml}
        DESTINATION ${MLT_META_DATA_DIRECTORY}/avformat/)
endforeach()

install(TARGETS avformat EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
DESTINATION share/mlt
FILES_MATCHING
PATTERN "blacklist.txt"
PATTERN "*.yml"
)  #install dir
