cmake_minimum_required(VERSION 3.0)
project(proy-buscaminas-raylib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
function(add_git_dependency libName gitURL gitTag)
  FetchContent_Declare(
    ${libName}
    GIT_REPOSITORY ${gitURL}
    GIT_TAG ${gitTag}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)
  FetchContent_MakeAvailable(${libName})
  target_compile_options(${libName} PRIVATE "-w")
endfunction()

# Adding Raylib
set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES
    OFF
    CACHE BOOL "" FORCE) # don't build the supplied example games
add_git_dependency(raylib https://github.com/raysan5/raylib.git 4.5.0)

# Adding our source files Define PROJECT_SOURCES as a list of all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") # Define
# PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# ##############################################################################
# Project build settings
# ##############################################################################

add_definitions(-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

# Setting ASSETS_PATH
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG")

  # Set the asset path macro to the absolute path on the dev machine
  target_compile_definitions(
    ${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
else()
  # Set the asset path macro in release mode to a relative path that assumes the
  # assets folder is in the same directory as the game executable
  target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")
endif()

# Set common compiler flags SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall
# -Wswitch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# ----- Web compile opts -----
# if (${PLATFORM} STREQUAL "Web") # Tell Emscripten to build an .html file.
# set(CMAKE_EXECUTABLE_SUFFIX ".html") SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}
# -Os") set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s
# ASSERTIONS=1 -s WASM=1 -Os -Wall -s TOTAL_MEMORY=67108864 -s
# FORCE_FILESYSTEM=1 --preload-file assets/ --shell-file
# ../sources/minshell.html") set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is
# used to set your executable to build with the emscripten html template so that
# you can directly open it. set_target_properties(${PROJECT_NAME} PROPERTIES
# SUFFIX ".html") target_compile_definitions(${PROJECT_NAME} PUBLIC
# ASSETS_PATH="/assets/") # Set the asset path macro in release mode to a
# relative path that assumes the assets folder is in the same directory as the
# game executable endif()

# Ensure that hot-reload is enabled for VS
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
endif()