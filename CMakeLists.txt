cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH
    ${CMAKE_PREFIX_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake  )

project(mlt)


#install
if(WIN32)
    set(CMAKE_INSTALL_PREFIX "E:/workspace_ffmpeg/build")
endif(WIN32)

# ffmpeg
set(FFmpegPath       "E:/workspace_ffmpeg/3rd/ffmpeg")
if(WIN32)
        set(WinFFmpegCOMPONENTS avcodec avdevice avfilter avformat avutil swscale)
        foreach(comp ${WinFFmpegCOMPONENTS})
            set( _${comp}_INCLUDE_DIRS ${FFmpegPath}/include  )
            set( _${comp}_LIBRARY_DIRS ${FFmpegPath}/lib  )
        endforeach(comp)
endif(WIN32)
#find_package(FFmpeg)

# pthread
if(WIN32)
        set(PthreadPath "E:/workspace_ffmpeg/3rd/phtread")
        link_directories( ${PthreadPath}/lib )
        INCLUDE_DIRECTORIES(${PthreadPath}/include)
endif(WIN32)

# dl
if(WIN32)
        set(DlPath "E:/workspace_ffmpeg/3rd/dl")
        link_directories( ${DlPath}/lib )
        INCLUDE_DIRECTORIES(${DlPath}/include)
endif(WIN32)

# dirent
if(WIN32)
        set(DirentPath "E:/workspace_ffmpeg/3rd/dirent")
        INCLUDE_DIRECTORIES(${DirentPath}/include)
endif(WIN32)


if(WIN32)
#    set(CMAKE_INSTALL_PREFIX "F:/github.cpp-repo/mlt_shotcut_ffmpeg/install-vc")
#    set(ThirdPartyPath       "F:/github.cpp-repo/mlt_shotcut_ffmpeg/install-vc")
#    link_directories( ${ThirdPartyPath}/lib )
#    INCLUDE_DIRECTORIES(${ThirdPartyPath}/include)
    add_definitions( -D _CRT_SECURE_NO_WARNINGS )
endif()

option(USE_QT "use qt module" ON)
#if(WIN32)
#set(QT_DIR "C:/Qt/Qt5.9.3-mingw-vc/5.9.3/msvc2015_64")
#else(WIN32)
#endif(WIn32)
set(QtCOMPONENTS Core Gui Svg Xml Widgets Test)
#foreach(comp ${QtCOMPONENTS})
#    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}    ${QT_DIR}/lib/cmake/${comp}  )
#endforeach(comp)
find_package(Qt5 COMPONENTS ${QtCOMPONENTS} REQUIRED)


# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/mlt) #add_library(MODULE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) #add_library(STATIC)
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #add_library(SHARED)
set(MLT_META_DATA_DIRECTORY ${CMAKE_BINARY_DIR}/share/mlt)
set(MLT_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/lib/mlt/plugins)


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
    set( CMAKE_BUILD_TYPE "Release" )
endif()


set( PREFIX_LIB "lib/mlt")
set( PREFIX_DATA "share/mlt")

set( VERSION 5)

configure_file(./src/config_mlt.h.in ${CMAKE_BINARY_DIR}/src/config_mlt.h)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src)

add_subdirectory(src)


