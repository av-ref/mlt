

set(SRCS
        factory.c
        consumer_sdl2.c
        ../sdl/consumer_sdl_audio.c
        )

set(HDRS
        )

find_package(sdl2)

add_library(mltsdl2 MODULE ${SRCS})

if(WIN32)
    target_link_libraries(mltsdl2 mlt pthread_dll)
else()
    target_link_libraries(mltsdl2 mlt m pthread SDL2)
    INCLUDE_DIRECTORIES(/usr/include/SDL2)
endif()

set_target_properties( mltsdl2
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY})

add_custom_command(
        TARGET mltsdl2
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/sdl2
        )

file(GLOB ymls *.yml)
foreach(yml ${ymls})
    file(COPY ${yml}
        DESTINATION ${MLT_META_DATA_DIRECTORY}/sdl2/)
endforeach()

install(TARGETS mltsdl2 EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR} 
	DESTINATION share/mlt
	FILES_MATCHING 
	PATTERN "*.yml"
)  
