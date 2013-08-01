cmake_minimum_required  (VERSION 2.6)
project(KDSLib)

set(SOURCES
   test.cpp
   glutil.cpp
   glprogram.cpp
)
set(HEADERS
   include/test.h
   include/glutil.h
   include/glprogram.h
   glm/glm.hpp
)


SET(LIBNAME KDSLib)

if(APPLE)
   FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
   MARK_AS_ADVANCED(OPENGL_LIBRARY)
   SET(EXTRA_LIBS ${OPENGL_LIBRARY})
ENDIF(APPLE)

include_directories(include)
include_directories(glm)
add_library(${LIBNAME} STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${LIBNAME} ${EXTRA_LIBS})
