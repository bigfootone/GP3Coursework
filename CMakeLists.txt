cmake_minimum_required (VERSION 2.8)
PROJECT (GP3Game)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
LIST(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")

#find packages
message("3rd party dependencies: $ENV{CMAKE_PREFIX_PATH}")
SET(CMAKE_PREFIX_PATH "$ENV{CMAKE_PREFIX_PATH}")

#make sure packages are installed before continue
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_Image REQUIRED)
FIND_PACKAGE(SDL2_TTF REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(GLM REQUIRED)
FIND_PACKAGE(FBX REQUIRED)
FIND_PACKAGE(Bullet REQUIRED)
FIND_PACKAGE(OpenAL REQUIRED)

#GP3Engine library
FILE(GLOB GP3Engine_SRC GP3Engine/src/*.cpp GP3Engine/src/Components/*.cpp GP3Engine/include/*.h GP3Engine/include/Components/*.h)
add_library(GP3Engine ${GP3Engine_SRC})
SET_TARGET_PROPERTIES(GP3Engine PROPERTIES LINKER_LANGUAGE CXX)

#source files
FILE(GLOB SRC src/*.cpp include/*.h)
ADD_EXECUTABLE(GP3Game ${SRC})

#include header files
INCLUDE_DIRECTORIES(GP3Game include/ GP3Engine/include/ ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${FBX_INCLUDE_DIR} ${BULLET_INCLUDE_DIR} ${ALUT_INCLUDE_DIR})

#link libraries
TARGET_LINK_LIBRARIES(GP3Game GP3Engine ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${FBX_LIBRARY} ${BULLET_LIBRARIES} ${ALUT_LIBRARY})

#copy assets folder
if (MSVC)
add_custom_command(TARGET GP3Game  POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/dlls $<TARGET_FILE_DIR:GP3Game>)
endif (MSVC)

add_custom_command(TARGET GP3Game  PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                 ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:GP3Game>/assets)
