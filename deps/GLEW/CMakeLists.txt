
file (GLOB SOURCE_FILES *.c)

set (INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package (OpenGL REQUIRED)
set (GLEW_LIBRARIES ${OPENGL_LIBRARIES})

if (WIN32)
  set (GLEW_LIB_NAME glew32)
else ()
  set (GLEW_LIB_NAME GLEW)
  set (DLL_PREFIX lib)
endif ()

set(CMAKE_DEBUG_POSTFIX d)

add_definitions (-DGLEW_NO_GLU)

setup_library (GLEW)
set_target_properties (GLEW PROPERTIES COMPILE_DEFINITIONS "GLEW_STATIC" OUTPUT_NAME "${GLEW_LIB_NAME}" PREFIX lib)
target_link_libraries (GLEW ${GLEW_LIBRARIES})

  target_compile_definitions(GLEW INTERFACE "GLEW_STATIC")