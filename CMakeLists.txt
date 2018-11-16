cmake_minimum_required (VERSION 2.6)
project (Step01_Graphics)

# SET VARIABLES
set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)

# VERSION NUMBER HERE
set (KCPPGame01_VERSION_MAJOR 0)
set (KCPPGame01_VERSION_MINOR 1)

# OPTIONS


# JUST SOME LOGIC (IGNORE)

if (TARGET_WEB_EM_GLES3_0)
	set(TARGET_ATTR_BIGENV_WEB 1)
	set(TARGET_ATTR_TOOL_EM 1)
	set(TARGET_ATTR_REND_GLES_3_0 1)
endif (TARGET_WEB_EM_GLES3_0)

if (TARGET_ATTR_TOOL_EM)
	set(TARGET_ATTR_WIND_GLFW 1)
	set(TARGET_ATTR_NET_EM 1)
endif (TARGET_ATTR_TOOL_EM)


# STANDARD CONFIGURATION
configure_file (
	"${PROJECT_SOURCE_DIR}/CMakeConfig.hpp.in"
	"${PROJECT_SOURCE_DIR}/CMakeConfig.hpp"
	)

include_directories("${PROJECT_BINARY_DIR}")


# SPECIFIC CONFIGURATION (sets specific)



# EXECUTABLE!
if (TARGET_SERVER)
	add_executable(Step01_Graphics src/server/main.cpp)
else (TARGET_SERVER)
	add_executable(Step01_Graphics src/client/main.cpp)
endif (TARGET_SERVER)

sET(CMAKE_CXX_FLAGS  "-o index.html ${CMAKE_CXX_FLAGS}")

# TESTS


