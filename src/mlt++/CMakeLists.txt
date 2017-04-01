
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

add_definitions(-DMLTPP_EXPORTS)

add_library( mlt++ SHARED ${SRCS})
target_link_libraries(mlt++ mlt)


set(Mlt_VERSION 1.0.0)

set_property(TARGET mlt++ PROPERTY VERSION ${Mlt_VERSION})
set_property(TARGET mlt++ PROPERTY SOVERSION 1)
set_property(TARGET mlt++ PROPERTY INTERFACE_mlt++_MAJOR_VERSION 1)
set_property(TARGET mlt++ APPEND PROPERTY  COMPATIBLE_INTERFACE_STRING mlt++_MAJOR_VERSION )

# install target lib, dll, so, exe
install(TARGETS mlt++ EXPORT MltTargets #install target: dll lib exe etc
  LIBRARY DESTINATION lib/mlt
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# install headers
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DESTINATION include/ FILES_MATCHING PATTERN "*.h")  #install dir

# install version file
include(CMakePackageConfigHelpers)
set(ConfigPackageLocation lib/cmake/mlt)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/Mlt++ConfigVersion.cmake"
  VERSION ${Mlt_VERSION}
  COMPATIBILITY AnyNewerVersion
)
install(   #install file
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/Mlt++ConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)

#install export file 
export(EXPORT MltTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/Mlt++Targets.cmake"
  NAMESPACE mlt::
)
install(EXPORT MltTargets
  FILE
    Mlt++Targets.cmake
  NAMESPACE
    mlt::
  DESTINATION
    ${ConfigPackageLocation}
)

#install config file
configure_file(../../cmake/mlt++Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/Mlt++Config.cmake"
  COPYONLY
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/Mlt++Config.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)
