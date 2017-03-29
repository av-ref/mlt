
# - Try to find MLT
# Once done this will define
#   MLT_FOUND
#   MLT_INCLUDE_DIRS
#   MLT_LIBRARIES
#   MLT_INCLUDE_FILES

include(FindPackageHandleStandardArgs)

if (NOT MLT_FIND_COMPONENTS)
	set(MLT_FIND_COMPONENTS mlt mlt++ )
endif(NOT MLT_FIND_COMPONENTS)

# Generate component include files and requirements
foreach(comp ${MLT_FIND_COMPONENTS})
	if(MLT_FIND_REQUIRED_${comp})
		list(APPEND required "MLT_${comp}_FOUND")
	endif()
endforeach(comp)


# Find libraries
find_package(PkgConfig QUIET)
foreach(comp ${MLT_FIND_COMPONENTS})
	if(PKG_CONFIG_FOUND)
		pkg_check_modules(_${comp} QUIET lib${comp})
	endif()
	find_path(MLT_${comp}_INCLUDE_DIR
		NAMES "${comp}/framework/${comp}.h"
		PATHS
			/usr/include /usr/local/include /opt/local/include /sw/include /usr/include/x86_64-linux-gnu/
		DOC "MLT include directory")
	find_library(MLT_${comp}_LIBRARY
		NAMES ${comp}
		PATHS
			/usr/lib /usr/local/lib /opt/local/lib /sw/lib /usr/lib/x86_64-linux-gnu/
		PATH_SUFFIXES ${comp} lib${comp}
		DOC "MLT ${comp} library")
	find_package_handle_standard_args(MLT_${comp}
		FOUND_VAR MLT_${comp}_FOUND
		REQUIRED_VARS MLT_${comp}_LIBRARY MLT_${comp}_INCLUDE_DIR)
	if(${MLT_${comp}_FOUND})
		list(APPEND MLT_INCLUDE_DIRS ${MLT_${comp}_INCLUDE_DIR})
		list(APPEND MLT_LIBRARIES ${MLT_${comp}_LIBRARY})
	endif()
endforeach(comp)

# Run checks via find_package_handle_standard_args
find_package_handle_standard_args(MLT
	FOUND_VAR MLT_FOUND
	REQUIRED_VARS ${required} MLT_INCLUDE_DIRS MLT_LIBRARIES)
