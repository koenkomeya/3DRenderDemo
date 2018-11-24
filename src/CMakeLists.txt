cmake_minimum_required (VERSION 2.8)
project (Step01_Graphics)

# STANDARD CONFIGURATION
configure_file (
    "${PROJECT_SOURCE_DIR}/CMakeConfig.hpp.in"
    "${PROJECT_SOURCE_DIR}/CMakeConfig.hpp"
    )
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories("${PROJECT_BINARY_DIR}")

# SPECIFIC CONFIGURATION (sets specific)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (TARGET_ATTR_TOOL_EM)
        set(CMAKE_CXX_FLAGS  "-g4 -s EXCEPTION_DEBUG=1 -s WASM=0 -s DISABLE_EXCEPTION_CATCHING=0 --js-opts 0 ${CMAKE_CXX_FLAGS}")
    else (TARGET_ATTR_TOOL_EM)
        set(CMAKE_CXX_FLAGS  "-Og -g3 ${CMAKE_CXX_FLAGS}")
    endif (TARGET_ATTR_TOOL_EM)
    message("DEBUG MODE TRIGGERED")
else()
    set(CMAKE_CXX_FLAGS  "-O3 ${CMAKE_CXX_FLAGS}")
endif()

if (TARGET_ATTR_TOOL_EM)
    if (TARGET_ATTR_REND_GLES_3_0)
        set(CMAKE_CXX_FLAGS  "-s USE_WEBGL2=1 ${CMAKE_CXX_FLAGS}")
    endif (TARGET_ATTR_REND_GLES_3_0)
    if (TARGET_ATTR_WIND_GLFW)
        set(CMAKE_CXX_FLAGS  "-s USE_GLFW=3 ${CMAKE_CXX_FLAGS}")   
    endif (TARGET_ATTR_WIND_GLFW)
endif (TARGET_ATTR_TOOL_EM)

file (GLOB PROJ_SRC
    "*.h"
    "*.hpp"
    "*.c"
    "*.cpp"
)
file (GLOB_RECURSE PROJ_SRC_COM 
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp"
)
file (GLOB_RECURSE PROJ_SRC_GEN 
    "${CMAKE_CURRENT_SOURCE_DIR}/generic/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/generic/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/generic/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/generic/*.cpp"
)
if (TARGET_SERVER)
    file(GLOB_RECURSE PROJ_SRC_SC 
        "${CMAKE_CURRENT_SOURCE_DIR}/server/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/server/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/server/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp"
    )
else (TARGET_SERVER)
    file (GLOB_RECURSE PROJ_SRC_SC 
        "${CMAKE_CURRENT_SOURCE_DIR}/client/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/client/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/client/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp"
    )
endif (TARGET_SERVER)
#message (s ${PROJECT_SOURCE_DIR} ${PROJ_SRC} ${PROJ_SRC_GEN} ${PROJ_SRC_COM} ${PROJ_SRC_SC})

# EXECUTABLE!
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${BTARGET}/${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS  "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXECUTABLE_SUFFIX ".html")
add_executable(${PROJECT_NAME} ${PROJ_SRC} ${PROJ_SRC_COM} ${PROJ_SRC_GEN} ${PROJ_SRC_SC})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")

# TESTS