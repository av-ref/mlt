
set(SRCS
        MltAnimation.cpp
        MltConsumer.cpp
        MltDeque.cpp
        MltEvent.cpp
        MltFactory.cpp
        MltField.cpp
        MltFilter.cpp
        MltFilteredConsumer.cpp
        MltFilteredProducer.cpp
        MltFrame.cpp
        MltGeometry.cpp
        MltMultitrack.cpp
        MltParser.cpp
        MltPlaylist.cpp
        MltProducer.cpp
        MltProfile.cpp
        MltProperties.cpp
        MltPushConsumer.cpp
        MltRepository.cpp
        MltService.cpp
        MltTokeniser.cpp
        MltTractor.cpp
        MltTransition.cpp
        )

set(HDRS
        MltConfig.h
        Mlt.h
        MltAnimation.h
        MltConsumer.h
        MltDeque.h
        MltEvent.h
        MltFactory.h
        MltField.h
        MltFilter.h
        MltFilteredConsumer.h
        MltFilteredProducer.h
        MltFrame.h
        MltGeometry.h
        MltMultitrack.h
        MltParser.h
        MltPlaylist.h
        MltProducer.h
        MltProfile.h
        MltProperties.h
        MltPushConsumer.h
        MltRepository.h
        MltService.h
        MltTokeniser.h
        MltTractor.h
        MltTransition.h
        )

add_library( mlt++ SHARED ${SRCS})
target_link_libraries(mlt++ mlt)