cmake_minimum_required ( VERSION 3.0 )

# replace "peconv_project" by your own project name:
project ( peconv_project )

# libs
# modules:
set ( M_PARSER "libpeconv/libpeconv" )

option(PECONV_UNICODE "Enable Unicode" OFF)

# enable unicode support
if(PECONV_UNICODE)
	add_definitions (-DUNICODE -D_UNICODE)
endif()

# modules paths:
set (PECONV_DIR "${CMAKE_SOURCE_DIR}/${M_PARSER}" CACHE PATH "PEConv main path")
add_subdirectory ( ${PECONV_DIR} )
set ( PECONV_LIB $<TARGET_FILE:libpeconv> CACHE PATH "PEConvLib library path" )

# Add sub-directories
#
add_subdirectory ( project_template )

