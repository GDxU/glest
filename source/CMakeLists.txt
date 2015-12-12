

#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h *.c)
set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/OpenAL 1.1 SDK")
find_package(OPENGL)
find_package(OPENAL)
find_package(LUA51)


set(inc_path 

    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/lua
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/platform/sdl
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/platform/win32
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/sound
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/sound/openal
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/util
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/xml
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_lib/include/graphics/gl

    ${LUA_INCLUDE_DIR}
    ${DEPS_INCLUDE}
    ${OPENGL_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}

    #just for game project
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/ai
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/facilities
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/game
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/global
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/gui
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/main
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/menu
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/network
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/sound
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/types
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/type_instances
    ${CMAKE_CURRENT_SOURCE_DIR}/glest_game/world

    )


macro(global_define)
    foreach(src_file ${SRC_FILES})
        get_filename_component (PATH ${src_file} PATH)
        string (REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" PATH ${PATH})
        #string (REPLACE / \\ PATH ${PATH})
        source_group ("Source Files\\${PATH}" FILES ${src_file})
    endforeach()

    include_directories(${inc_path})
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endmacro()

macro(define_files name)
    file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h *.c)
    global_define()
endmacro()

macro(setup_lib name)
    global_define(name)

    add_library(${name}  STATIC ${SRC_FILES})
endmacro()

macro(setup_exe name)
    define_files(name)
    add_executable(${name} ${SRC_FILES})
    target_link_libraries(${name} lib)
endmacro()

add_subdirectory(shared_lib)

add_subdirectory(glest_map_editor)
add_subdirectory(glest_game)
add_subdirectory(g3d_viewer)
add_subdirectory(configurator)