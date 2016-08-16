cmake_minimum_required(VERSION 2.6)
project(SDLTest)

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)
set(SDLTEST_SRCS ${PROJECT_SOURCE_DIR}/main.cpp
                 ${PROJECT_SOURCE_DIR}/player.cpp
                 ${PROJECT_SOURCE_DIR}/renderer.cpp
                 ${PROJECT_SOURCE_DIR}/vector.cpp
                 ${PROJECT_SOURCE_DIR}/state.cpp
                 ${PROJECT_SOURCE_DIR}/input_handler.cpp
                 ${PROJECT_SOURCE_DIR}/ray.cpp
                 ${PROJECT_SOURCE_DIR}/target.cpp)

add_executable(SDLTest ${SDLTEST_SRCS})

if (MSVC)
  target_link_libraries(SDLTest ${PROJECT_ROOT_DIR}/lib/SDL2.lib
                                ${PROJECT_ROOT_DIR}/lib/SDL2main.lib)
  include_directories(${PROJECT_ROOT_DIR}/include)
	set (CMAKE_CXX_FLAGS "/MD /EHsc")
endif (MSVC)

include_directories(${PROJECT_ROOT_DIR}/include)

if (MSVC)
  target_link_libraries(SDLTest ${PROJECT_ROOT_DIR}/lib/SDL2.lib
                                ${PROJECT_ROOT_DIR}/lib/SDL2main.lib)
	set (CMAKE_CXX_FLAGS "/MD /EHsc")
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCXX)
  link_directories(/usr/local/lib)
	target_link_libraries(SDLTest SDL2 m dl pthread rt GL)
	set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")
endif (CMAKE_COMPILER_IS_GNUCXX)

