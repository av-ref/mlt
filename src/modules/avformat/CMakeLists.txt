
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

add_library(mltffmpeg MODULE ${SRCS} )

target_link_libraries(mltffmpeg mlt  ${FFmpeg_LIBRARIES})

set_target_properties( mltffmpeg
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY}
        )

add_custom_command(
        TARGET mltffmpeg
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/avformat
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/blacklist.txt ${MLT_META_DATA_DIRECTORY}/avformat/
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.yml  ${MLT_META_DATA_DIRECTORY}/avformat/
)