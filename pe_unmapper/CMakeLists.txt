cmake_minimum_required (VERSION 3.0)

# replace "project_template" by your own project name:
project ( pe_unmapper )

option(UNMAPPER_BUILD_TESTING "Enable testing for pe_unmapper" OFF)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

# include libpeconv headers:
include_directories ( ${PECONV_DIR}/include )

set (srcs
#put your sources here
)

# general headers - they will be used for both EXE and DLL:
set (hdrs
#put your headers here
)

set (rsrc
#put your resources here
)

add_executable ( ${PROJECT_NAME} ${hdrs} ${srcs} ${rsrc} main.cpp )

# link with libpeconv.lib
target_link_libraries ( ${PROJECT_NAME} ${PECONV_LIB} )

#dependencies:
add_dependencies( ${PROJECT_NAME} libpeconv )

# Setup testing
if(UNMAPPER_BUILD_TESTING)
	enable_testing()

	# 0) does the application run
	add_test (TestRuns ${CMAKE_INSTALL_PREFIX}/pe_unmapper)
	set_tests_properties(TestRuns PROPERTIES PASS_REGULAR_EXPRESSION "PE Unmapper v:")
endif()

INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )
