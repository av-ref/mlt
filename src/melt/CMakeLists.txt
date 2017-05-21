
set(SRCS melt.c io.c)
set(HDRS io.h )
add_executable(melt ${SRCS})

if(WIN32)
    target_include_directories(melt  
        PRIVATE ${PTHREAD_PATH}/include)
    target_link_libraries( melt pthread_dll.lib)
else()
target_link_libraries(melt mlt pthread)
endif()