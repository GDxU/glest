


file(GLOB SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/MyGUIEngine/src/*.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Common/Base/OpenGL/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/Input/SDL/*.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/OpenGL/OpenGLPlatform/src/*.cpp
)

foreach(src_file ${SRC_FILES})
    get_filename_component (PATH ${src_file} PATH)
    string (REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" PATH ${PATH})
    string (REPLACE / \\ PATH ${PATH})
    source_group ("Source Files\\${PATH}" FILES ${src_file})
endforeach()


include_directories(
    MyGUIEngine/include
    Common
    Common/Input/SDL
    Platforms/OpenGL/OpenGLPlatform/include

    ${CMAKE_CURRENT_SOURCE_DIR}/../SDL2-2.0.3/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/include

)

add_definitions(-DMYGUI_STATIC)

add_library(MYGUI STATIC ${SRC_FILES})

