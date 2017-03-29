
find_package(sdl REQUIRED)

set(SRCS
        factory.c
	   consumer_sdl.c 
	   consumer_sdl_audio.c
	   consumer_sdl_preview.c 
	   consumer_sdl_still.c 
# 	   producer_sdl_image.c
        )


add_definitions( -DFILTERS -DCODECS -DAVDEVICE -DAVFILTER)


include_directories(${sdl_INCLUDE_DIRS})

add_library(mltsdl MODULE ${SRCS} )

target_link_libraries(mltsdl mlt  ${FFmpeg_LIBRARIES})

set_target_properties( mltsdl
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY}
        )

add_custom_command(
        TARGET mltsdl
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/mltsdl
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/blacklist.txt ${MLT_META_DATA_DIRECTORY}/mltsdl/
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.yml  ${MLT_META_DATA_DIRECTORY}/mltsdl/
)