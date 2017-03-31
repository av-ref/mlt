


#ifeq ($(targetos), Darwin)
#NAME = libmlt$(LIBSUF)
#TARGET = libmlt.$(version)$(LIBSUF)
#SONAME = libmlt.$(soversion)$(LIBSUF)
#SHFLAGS += -install_name $(libdir)/$(SONAME) -current_version $(version) -compatibility_version $(soversion)
#else ifeq ($(targetos), MinGW)
#NAME = libmlt$(LIBSUF)
#TARGET = libmlt-$(soversion)$(LIBSUF)
#SHFLAGS += -Wl,--output-def,libmlt.def
#else
#NAME = libmlt$(LIBSUF)
#TARGET = $(NAME).$(version)
#SONAME = $(NAME).$(soversion)
#SHFLAGS += -Wl,-soname,$(SONAME)
#endif

#ifeq ($(targetos), Linux)
#SHFLAGS += -Wl,--version-script=mlt.vers
#endif

set( SRCS
        mlt_frame.c
mlt_version.c
mlt_geometry.c
mlt_deque.c
mlt_property.c
mlt_properties.c
mlt_events.c
mlt_parser.c
mlt_service.c
mlt_producer.c
mlt_multitrack.c
mlt_playlist.c
mlt_consumer.c
mlt_filter.c
mlt_transition.c
mlt_field.c
mlt_tractor.c
mlt_factory.c
mlt_repository.c
mlt_pool.c
mlt_tokeniser.c
mlt_profile.c
mlt_log.c
mlt_cache.c
mlt_animation.c
mlt_slices.c
        )

set(HDRS
        mlt_consumer.h
mlt_version.h
mlt_factory.h
mlt_filter.h
mlt.h
mlt_multitrack.h
mlt_pool.h
mlt_properties.h
mlt_events.h
mlt_parser.h
mlt_repository.h
mlt_tractor.h
mlt_types.h
mlt_deque.h
mlt_field.h
mlt_frame.h
mlt_geometry.h
mlt_playlist.h
mlt_producer.h
mlt_property.h
mlt_service.h
mlt_transition.h
mlt_tokeniser.h
mlt_profile.h
mlt_log.h
mlt_cache.h
mlt_animation.h
mlt_slices.h
        )

#add_definitions( -DPREFIX_DATA="\"${mltdatadir}\"" -DPREFIX_LIB="\"$(moduledir)\"")

if(WIN32)
    set(SRCS ${SRCS}
            ../win32/win32.c
            )
    #LDFLAGS += -liconv
endif(WIN32)

add_library(mlt SHARED ${SRCS} )

if(WIN32)
#    target_include_directories(mlt PRIVATE ${PTHREAD_PATH}/include)
#    target_link_libraries( mlt pthread_dll.lib)
    target_link_libraries( mlt pthread dl)
else()
    target_link_libraries( mlt pthread m dl)
endif(WIN32)

