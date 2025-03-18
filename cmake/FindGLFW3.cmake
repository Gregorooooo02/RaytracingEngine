set( _glfw3_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include"
    "${CMAKE_SOURCE_DIR}/include"
    "C:/Program Files/GLFW/include"
)

set( _glfw3_LIB_SEARCH_DIRS
    "/usr/lib"
    "/usr/local/lib"
    "${CMAKE_SOURCE_DIR}/lib"
    "C:/Program Files/GLFW/lib"
)

set( _glfw3_ENV_ROOT $ENV{GLFW3_ROOT} )
if(NOT GLFW3_ROOT AND _glfw3_ENV_ROOT)
    set( GLFW3_ROOT ${_glfw3_ENV_ROOT} )
endif()

if(GLFW3_ROOT)
    list( INSERT _glfw3_HEADER_SEARCH_DIRS "${GLFW3_ROOT}/include" )
    list( INSERT _glfw3_LIB_SEARCH_DIRS "${GLFW3_ROOT}/lib" )
endif()

# Search for the GLFW header
FIND_PATH(GLFW3_INCLUDE_DIR "GLFW/glfw3.h"
    PATHS ${_glfw3_HEADER_SEARCH_DIRS}
)

# Search for the GLFW library
FIND_LIBRARY(GLFW3_LIBRARY
    NAMES glfw3 glfw
    PATHS ${_glfw3_LIB_SEARCH_DIRS}
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glfw3 DEFAULT_MSG GLFW3_LIBRARY GLFW3_INCLUDE_DIR)