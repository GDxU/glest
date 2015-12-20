

add_subdirectory(stb)
#add_subdirectory(xxtea)
add_subdirectory(tinyxml2)
#add_subdirectory(tinycthread)
#add_subdirectory(kazmath)
#add_subdirectory(lua-5.1.5)
#add_subdirectory(tolua)
add_subdirectory(SDL2-2.0.3)
#add_subdirectory(freetype-2.5.0)
#add_subdirectory(SDL2_ttf-2.0.12)

if (WIN32)
    add_subdirectory(GLEW)
endif()

add_subdirectory(MYGUI)
