cmake_minimum_required(VERSION 2.6)


include (CheckIncludeFiles)

macro (setup_library name)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    include_directories(${INCLUDE_DIRS})

    foreach(src_file ${SOURCE_FILES})
        get_filename_component ("PATH"  "${src_file}"  "PATH")
        string (REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" "PATH" "${PATH}")
        string (REPLACE / \\ "PATH" "${PATH}")
        source_group ("Source Files\\${PATH}" FILES ${src_file})
    endforeach()

    add_library(${name} STATIC ${SOURCE_FILES})
endmacro()

set(DEPS_INCLUDE 
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/lua-5.1.5/src
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2-2.0.3/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/OggDecoder/include

    #${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype-2.5.0/include
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_ttf-2.0.12
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/tolua
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/tinyxml2
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/tinycthread
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/kazmath/include
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/xxtea
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/zlib
)
set(DEPS_LIB
    ${CMAKE_CURRENT_SOURCE_DIR}/OggDecoder/prebuilt

)

add_subdirectory(source)
add_subdirectory(deps)

