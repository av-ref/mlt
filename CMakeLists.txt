cmake_minimum_required(VERSION 3.0.0)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH
    ${CMAKE_PREFIX_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake  )

message( "path in cmake_prefix_path" )
foreach( path ${CMAKE_PREFIX_PATH} )
    message( ${path} )
endforeach( path )

project(mlt)

if(WIN32)
    set(CMAKE_INSTALL_PREFIX "F:/github.cpp-repo/mlt_shotcut_ffmpeg/install")
    set(ThirdPartyPath "F:/github.cpp-repo/mlt_shotcut_ffmpeg/install")
    link_directories( ${ThirdPartyPath}/lib )
    INCLUDE_DIRECTORIES(${ThirdPartyPath}/include)

    set( WinFFmpegPath "F:/github.cpp-repo/mlt_shotcut_ffmpeg/ffmpeg-3.2.4-win32-dev/")
    set(WinFFmpegCOMPONENTS avcodec avdevice avfilter avformat avutil swscale)
    foreach(comp ${WinFFmpegCOMPONENTS})
        set( _${comp}_INCLUDE_DIRS ${WinFFmpegPath}include  )
        set( _${comp}_LIBRARY_DIRS ${WinFFmpegPath}lib  )
    endforeach(comp)
#    link_directories( ${FFMPEG_WIN_PATH}/lib )

    #set( PTHREAD_PATH "f:///github.cpp-repo/pthread-release-x64-msvc2015")
endif()

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/) #add_library(MODULE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/mlt) #add_library(STATIC)
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #add_library(SHARED)
set(MLT_META_DATA_DIRECTORY ${CMAKE_BINARY_DIR}/share/mlt)
set(MLT_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/lib/mlt)


#################################################################################
# Setup C/C++ compiler options
#################################################################################

if(NOT MSVC_IDE)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
                "Choose the type of build, options are: None Debug Release" FORCE)
    endif()
endif()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
endif()


#################################################################################
# options
#################################################################################
option(ENABLE_CPPUNIT "Enable the CppUnit" ON)
option(ENABLE_XML "Enable the XML" ON)
option(ENABLE_JSON "Enable the JSON" ON)
option(ENABLE_MONGODB "Enable MongoDB" ON)
option(ENABLE_PDF "Enable PDF" OFF)
option(ENABLE_UTIL "Enable Util" ON)
option(ENABLE_NET "Enable Net" ON)
option(ENABLE_NETSSL "Enable NetSSL" ON)
option(ENABLE_NETSSL_WIN "Enable NetSSL Windows" OFF)


set( PREFIX_LIB "lib/mlt")
set( PREFIX_DATA "share/mlt")

set( VERSION 5)

configure_file(./src/config_mlt.h.in ${CMAKE_BINARY_DIR}/src/config_mlt.h)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src)


add_subdirectory(src)
