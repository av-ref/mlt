
set(SRCS melt.c io.c)
set(HDRS io.h )
add_executable(melt ${SRCS})
target_link_libraries(melt mlt pthread)