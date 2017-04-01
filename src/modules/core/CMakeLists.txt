

set(SRCS
        factory.c
        producer_colour.c
        producer_consumer.c
        producer_hold.c
        producer_loader.c
        producer_melt.c
        producer_noise.c
        producer_timewarp.c
        producer_tone.c
        filter_audiochannels.c
        filter_audiomap.c
        filter_audioconvert.c
        filter_audiowave.c
        filter_brightness.c
        filter_channelcopy.c
        filter_crop.c
        filter_data_feed.c
        filter_data_show.c
        filter_fieldorder.c
        filter_gamma.c
        filter_greyscale.c
        filter_imageconvert.c
        filter_luma.c
        filter_mirror.c
        filter_mono.c
        filter_obscure.c
        filter_panner.c
        filter_region.c
        filter_rescale.c
        filter_resize.c
        filter_transition.c
        filter_watermark.c
        transition_composite.c
        transition_luma.c
        transition_mix.c
        transition_region.c
        transition_matte.c
        consumer_multi.c
        consumer_null.c
        )
if(X64)
    set(SRC ${SRC} composite_line_yuv_sse2_simple.c)
endif(X64)

set(HDRS
        factory.h
        producer_colour.h
        producer_consumer.h
        producer_hold.h
        producer_loader.h
        producer_melt.h
        producer_noise.h
        producer_timewarp.h
        producer_tone.h
        filter_audiochannels.h
        filter_audiomap.h
        filter_audioconvert.h
        filter_audiowave.h
        filter_brightness.h
        filter_channelcopy.h
        filter_crop.h
        filter_data_feed.h
        filter_data_show.h
        filter_fieldorder.h
        filter_gamma.h
        filter_greyscale.h
        filter_imageconvert.h
        filter_luma.h
        filter_mirror.h
        filter_mono.h
        filter_obscure.h
        filter_panner.h
        filter_region.h
        filter_rescale.h
        filter_resize.h
        filter_transition.h
        filter_watermark.h
        transition_composite.h
        transition_luma.h
        transition_mix.h
        transition_region.h
        transition_matte.h
        consumer_multi.h
        consumer_null.h
        )

if(WIN32)
    set(SRCS ${SRCS} ../../win32/fnmatch.c)
    set(HDRS ${HDRS} ../../win32/fnmatch.h)
endif(WIN32)

add_library(mltcore MODULE ${SRCS})
if(WIN32)
    target_link_libraries(mltcore mlt pthread)
    target_include_directories(mltcore PRIVATE ../../win32)
else()
    target_link_libraries(mltcore mlt m pthread)
endif()

set_target_properties( mltcore
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MLT_MODULE_DIRECTORY})

set( ymls ${CMAKE_CURRENT_SOURCE_DIR}/*.yml)
add_custom_command(
        TARGET mltcore
        POST_BUILD
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt
        COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/share/mlt/core
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/data_fx.properties ${MLT_META_DATA_DIRECTORY}/core/
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/loader.dict  ${MLT_META_DATA_DIRECTORY}/core/
        COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/loader.ini    ${MLT_META_DATA_DIRECTORY}/core/
#        COMMAND cmake -E copy ${ymls}           ${MLT_META_DATA_DIRECTORY}/core/
        )
file(GLOB ymls *.yml)
foreach(yml ${ymls})
    file(COPY ${yml}
        DESTINATION ${MLT_META_DATA_DIRECTORY}/core/)
endforeach()

install(TARGETS mltcore EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} 
DESTINATION share/ 
FILES_MATCHING 
PATTERN "data_fx.properties"
PATTERN "loader.dict"
PATTERN "loader.ini"
PATTERN "*.yml"
)  #install dir
