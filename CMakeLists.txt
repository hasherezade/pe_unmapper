cmake_minimum_required ( VERSION 3.0 )

project ( pe_unmapper )

option(UNMAPPER_BUILD_TESTING "Enable testing for pe_unmapper" OFF)

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
add_subdirectory ( pe_unmapper )

# Setup testing
if(UNMAPPER_BUILD_TESTING)
	enable_testing()

	# 0) does the application run
	add_test (TestRuns ${CMAKE_INSTALL_PREFIX}/pe_unmapper)
	set_tests_properties(TestRuns PROPERTIES PASS_REGULAR_EXPRESSION "PE Unmapper v:")
endif()
