cmake_minimum_required  (VERSION 2.6)
project(KDSLib)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
  message("cmake compilation is in debug mode, target will be kdslib_d")
  set(TARGET_NAME kdslib_d)
else(CMAKE_BUILD_TYPE MATCHES DEBUG)
  message("cmake compilation is in release mode, target will be kdslib")
  set(TARGET_NAME ksdlib)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

set(SOURCES
  test.cpp
  glutil.cpp
  glprogram.cpp
)
set(HEADERS
  include/test.h
  include/utils.h
  include/glutil.h
  include/glprogram.h
  include/glmesh.h
  include/vector2.h
  include/vector3.h
  include/vertex.h
  include/color.h
  glm/glm.hpp
)


SET(LIBNAME KDSLib)


# -g adds debugging symbols
# -Wall turns on all warnings
# -Wextra turns on a lot of warnings (but not too pedantic)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wextra -Wno-ignored-qualifiers -Wno-unused-parameter -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -g -Wextra -Wno-ignored-qualifiers -Wno-unused-parameter")

#SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -Wextra -Wno-ignored-qualifiers -Wno-unused-parameter -std=c++11 -stdlib=libc++ -O3 -msse -msse2")
#SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -Wextra -Wno-ignored-qualifiers -Wno-unused-parameter -O3 -msse -msse2")

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    message("adding debug flags")
    add_definitions(-DDEBUG)
    add_definitions(-D_DEBUG)
    add_definitions(-DBREAK_ON_EXCEPTION)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)


if(APPLE)
   FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
   MARK_AS_ADVANCED(OPENGL_LIBRARY)
   SET(EXTRA_LIBS ${OPENGL_LIBRARY})
ENDIF(APPLE)

include_directories(include)
include_directories(glm)
add_library(${LIBNAME} STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${LIBNAME} ${EXTRA_LIBS})
