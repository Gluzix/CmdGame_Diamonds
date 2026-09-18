cmake_minimum_required(VERSION 3.20)

project(Diamonds_CmdGame LANGUAGES CXX)

# The game talks to the Win32 console API directly (windows.h, conio.h,
# GetAsyncKeyState), so there is nothing to build anywhere else.
if(NOT WIN32)
    message(FATAL_ERROR
        "Diamonds is Windows-only: it uses the Win32 console API (windows.h, conio.h). "
        "Configure this project on Windows with an MSVC toolchain.")
endif()

set(DIAMONDS_MAIN
    main.cpp
)

set(DIAMONDS_SOURCES
    source/Application.cpp
    source/Console.cpp
    source/Enemy.cpp
    source/FastEnemy.cpp
    source/FastestEnemy.cpp
    source/FileReader.cpp
    source/GameHandler.cpp
    source/Map.cpp
    source/MapCheck.cpp
    source/Menu.cpp
    source/MenuHandler.cpp
    source/Player.cpp
    source/Score.cpp
    source/SlowEnemy.cpp
)

set(DIAMONDS_HEADERS
    header/Application.h
    header/Console.h
    header/Coordinates.h
    header/Enemy.h
    header/FastEnemy.h
    header/FastestEnemy.h
    header/FileReader.h
    header/GameHandler.h
    header/Map.h
    header/MapCheck.h
    header/Menu.h
    header/MenuHandler.h
    header/Player.h
    header/Score.h
    header/SlowEnemy.h
)

add_executable(Diamonds_CmdGame
    ${DIAMONDS_MAIN}
    ${DIAMONDS_SOURCES}
    ${DIAMONDS_HEADERS}
)

# Same grouping the old .vcxproj.filters gave: main.cpp sits at the root of the
# tree, everything else under Source Files / Header Files.
source_group("" FILES ${DIAMONDS_MAIN})
source_group("Source Files" FILES ${DIAMONDS_SOURCES})
source_group("Header Files" FILES ${DIAMONDS_HEADERS})

# Several headers include their neighbours with angle brackets
# (#include <FileReader.h>, #include <Coordinates.h>), so this is required.
target_include_directories(Diamonds_CmdGame PRIVATE header)

set_target_properties(Diamonds_CmdGame PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:Diamonds_CmdGame>"
)

# _CONSOLE came from the old project; UNICODE/_UNICODE are what its
# CharacterSet=Unicode expanded to. _DEBUG and NDEBUG are supplied by the
# per-configuration flags MSVC and CMake already pass.
target_compile_definitions(Diamonds_CmdGame PRIVATE
    _CONSOLE
    _CRT_SECURE_NO_WARNINGS
    UNICODE
    _UNICODE
)

# ConformanceMode=true and SDLCheck=true came from the old project, which built
# at WarningLevel=Level3. The tree is clean at /W4, so that is the level it gets.
# Either way it has to be passed explicitly: policy CMP0092, which
# cmake_minimum_required(VERSION 3.20) turns on, drops the /W3 that CMake used
# to put in CMAKE_CXX_FLAGS by default, and MSVC falls back to /W1 without it.
if(MSVC)
    target_compile_options(Diamonds_CmdGame PRIVATE /permissive- /sdl /W4)
endif()

# WholeProgramOptimization was on for Release only. Guarded, so configuring
# still works on a toolchain that cannot do it.
include(CheckIPOSupported)
check_ipo_supported(RESULT DIAMONDS_IPO_SUPPORTED OUTPUT DIAMONDS_IPO_MESSAGE LANGUAGES CXX)
if(DIAMONDS_IPO_SUPPORTED)
    set_property(TARGET Diamonds_CmdGame PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
else()
    message(STATUS "Interprocedural optimization unavailable, Release will build without it: ${DIAMONDS_IPO_MESSAGE}")
endif()

# The game loads resources/... through relative paths, so the text files
# have to sit next to the binary for every configuration.
add_custom_command(TARGET Diamonds_CmdGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:Diamonds_CmdGame>/resources"
    COMMENT "Copying resources next to Diamonds_CmdGame.exe"
)
