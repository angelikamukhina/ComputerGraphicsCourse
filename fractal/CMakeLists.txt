cmake_minimum_required (VERSION 3.7)
project (CG)

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

add_definitions(-std=c++11
                -DGLEW_STATIC)
ADD_EXECUTABLE (main main.cpp ShadersLoader.cpp ShadersLoader.h Window.cpp Window.h)
target_link_libraries(main glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})