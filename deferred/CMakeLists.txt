cmake_minimum_required (VERSION 3.7)
project (deferred)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(glfw3 REQUIRED)
IF(glfw3_FOUND)
    message("*** glfw3 is found!")
ENDIF(glfw3_FOUND)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_DEFINITIONS})

find_package(assimp 3.2 REQUIRED)
IF(assimp_FOUND)
    message("*** assimp is found")
ENDIF(assimp_FOUND)
include_directories(${assimp_INCLUDE_DIRS})
link_directories(${assimp_LIBRARY_DIRS})
add_definitions(${assimp_DEFINITIONS})
add_definitions(-std=c++11
        -DGLEW_STATIC)

add_subdirectory(./AntTweakBar)
set_target_properties(AntTweakBar PROPERTIES LINKER_LANGUAGE CXX)
include_directories(./AntTweakBar/TweakBar/include)

ADD_EXECUTABLE (main main.cpp ShadersLoader.cpp ShadersLoader.h camera.h
        Lights.h Scene.cpp Scene.h)
target_link_libraries(main glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} AntTweakBar)
