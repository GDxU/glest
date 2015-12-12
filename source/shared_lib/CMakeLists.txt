file(GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/graphics/gl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/graphics/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/lua/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/platform/sdl/*.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/sources/platform/win32/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/sound/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/util/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/xml/*.cpp
)

setup_lib(lib)
