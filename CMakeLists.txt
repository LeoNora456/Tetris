cmake_minimum_required(VERSION 3.16)
project(Tetris LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE)

add_executable(Tetris src/main.cpp
        src/graphics/window.cpp
        include/window.h
        src/game/Tetris.cpp
        include/Tetris.h
        src/game/Piece.cpp
        include/Piece.h
        src/network/NetworkHandler.cpp
        src/main.cpp
        src/network/Server.cpp
        include/Server.h
        src/network/Client.cpp
        include/Client.h
)
target_link_libraries(Tetris PRIVATE sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
target_compile_features(Tetris PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Tetris
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Tetris>
        VERBATIM)
endif()

install(TARGETS Tetris)
