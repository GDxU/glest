cmake_minimum_required(VERSION 2.6)


include (CheckIncludeFiles)


project(glest)


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
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/xerces-c-3.1.2/src

    #${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype-2.5.0/include
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_ttf-2.0.12
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/tolua
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/tinyxml2
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/tinycthread
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/GLEW/include
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/kazmath/include
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/xxtea
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/zlib
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb

    ${CMAKE_CURRENT_SOURCE_DIR}/deps/MYGUI/MyGUIEngine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/MYGUI/Common
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/MYGUI/Common/Input/SDL
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/MYGUI/Common/Base/OpenGL
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/MYGUI/Platforms/OpenGL/OpenGLPlatform/include

    C:/wxWidgets-3.0.2/include
)

set(deps_lib_dir C:/wxWidgets-3.0.2/lib/vc_lib)
set(deps_lib comctl32 uuid rpcrt4
#wxbase30u.lib
#wxbase30u_net.lib
#wxbase30u_xml.lib
#wxexpat.lib
#wxjpeg.lib
#wxmsw30u_adv.lib
#wxmsw30u_aui.lib
#wxmsw30u_core.lib
#wxmsw30u_gl.lib
#wxmsw30u_html.lib
#wxmsw30u_media.lib
#wxmsw30u_propgrid.lib
#wxmsw30u_qa.lib
#wxmsw30u_ribbon.lib
#wxmsw30u_richtext.lib
#wxmsw30u_stc.lib
#wxmsw30u_webview.lib
#wxmsw30u_xrc.lib
#wxpng.lib
#wxregexu.lib
#wxscintilla.lib
#wxtiff.lib
#wxzlib.lib

wxbase30ud.lib
wxmsw30ud_core.lib
wxmsw30ud_gl.lib
wxpngd.lib
wxzlibd.lib

#wxbase30ud_net.lib
#wxbase30ud_xml.lib
#wxexpatd.lib
#wxjpegd.lib
#wxmsw30ud_adv.lib
#wxmsw30ud_aui.lib
#wxmsw30ud_html.lib
#wxmsw30ud_media.lib
#wxmsw30ud_propgrid.lib
#wxmsw30ud_qa.lib
#wxmsw30ud_ribbon.lib
#wxmsw30ud_richtext.lib
#wxmsw30ud_stc.lib
#wxmsw30ud_webview.lib
#wxmsw30ud_xrc.lib
#wxscintillad.lib
#wxregexud.lib
#wxtiffd.lib



    )

add_subdirectory(source)
add_subdirectory(deps)

