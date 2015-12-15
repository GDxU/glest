

#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h *.c)

find_package(OPENGL)
find_package(OPENAL REQUIRED)
find_package(LUA51)


set(inc_path 

    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/lua
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/platform/sdl
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/platform/win32
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/sound
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/sound/openal
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/util
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/xml
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/graphics/gl
    

    ${LUA_INCLUDE_DIR}
    ${DEPS_INCLUDE}
    ${OPENGL_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}

    #just for game project
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/game/ai
    ${CMAKE_CURRENT_SOURCE_DIR}/game/facilities
    ${CMAKE_CURRENT_SOURCE_DIR}/game/game
    ${CMAKE_CURRENT_SOURCE_DIR}/game/global
    ${CMAKE_CURRENT_SOURCE_DIR}/game/graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/game/gui
    ${CMAKE_CURRENT_SOURCE_DIR}/game/main
    ${CMAKE_CURRENT_SOURCE_DIR}/game/menu
    ${CMAKE_CURRENT_SOURCE_DIR}/game/network
    ${CMAKE_CURRENT_SOURCE_DIR}/game/sound
    ${CMAKE_CURRENT_SOURCE_DIR}/game/types
    ${CMAKE_CURRENT_SOURCE_DIR}/game/type_instances
    ${CMAKE_CURRENT_SOURCE_DIR}/game/world

    )


macro(global_define)
    foreach(src_file ${SRC_FILES})
        get_filename_component (PATH ${src_file} PATH)
        string (REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" PATH ${PATH})
        string (REPLACE / \\ PATH ${PATH})
        source_group ("Source Files\\${PATH}" FILES ${src_file})
    endforeach()

    include_directories(${inc_path})
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    link_directories(${DEPS_LIB})
endmacro()

macro(define_files name)
    file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
    include_directories(${inc_path})
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    link_directories(${DEPS_LIB})
endmacro()

macro(setup_lib name)
    global_define(name)

    add_library(${name}  STATIC ${SRC_FILES})

    #message(${OPENAL_LIBRARIES})
    target_link_libraries(${name} SDL2-static tinyxml2 SDL2main
        #libvorbis libvorbisfile libogg 
       GLEW
         wsock32 ${LUA_LIBRARIES} ${OPENAL_LIBRARY}
        user32 gdi32 winmm imm32 ole32 oleaut32 version uuid ws2_32 OpenGL32 GlU32 stb
     )
endmacro()

macro(setup_tool name)
    define_files(name)

#add_definitions(-DUNICODE -D_UNICODE)

    link_directories(${deps_lib_dir})
    add_executable(${name} ${SRC_FILES})
    target_link_libraries(${name} lib)
    target_link_libraries(editor ${deps_lib})
endmacro()


#add_subdirectory(engine)
#add_subdirectory(game)
#add_subdirectory(map_editor)
#add_subdirectory(configurator)
#add_subdirectory(viewer)




file(GLOB LIB_SRC_FILES 
    engine/graphics/gl/*.cpp
    engine/graphics/*.cpp
    engine/lua/*.cpp
    engine/platform/sdl/*.cpp
    #engine/platform/win32/*.cpp
    engine/sound/*.cpp
    engine/sound/openal/*.cpp
    #engine/sound/ds8/*.cpp
    engine/util/*.cpp
    engine/xml/*.cpp
)

list(APPEND LIB_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/platform/win32/socket.cpp)

file(GLOB SRC_FILES 
game/ai/*.cpp
game/facilities/*.cpp
game/game/*.cpp
game/global/*.cpp
game/graphics/*.cpp
game/gui/*.cpp
game/main/*.cpp
game/menu/*.cpp
game/network/*.cpp
game/sound/*.cpp
game/types/*.cpp
game/type_instances/*.cpp
game/world/*.cpp
)

LIST(APPEND SRC_FILES ${LIB_SRC_FILES})

global_define()



add_executable(GLEST ${SRC_FILES})

    #message(${OPENAL_LIBRARIES})
    target_link_libraries(GLEST SDL2-static tinyxml2 SDL2main
        #libvorbis libvorbisfile libogg 
       GLEW
         wsock32 ${LUA_LIBRARIES} ${OPENAL_LIBRARY}
        user32 gdi32 winmm imm32 ole32 oleaut32 version uuid ws2_32 OpenGL32 GlU32 stb
     )