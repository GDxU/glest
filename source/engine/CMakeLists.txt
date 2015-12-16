file(GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/gl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/sdl/*.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/platform/win32/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/openal/*.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/sound/ds8/*.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/util/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xml/*.cpp
)

list(APPEND SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/platform/win32/socket.cpp)

setup_lib(engine)
