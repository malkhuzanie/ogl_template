cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

project (alaqsa)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLAD_GL "")

add_subdirectory("include/glfw")

option(USE-GLFW-GLAD "Use GLAD from GLFW" ON)

IF (USE-GLFW-GLAD)
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h")
ENDIF ()

add_subdirectory("include/glm")
add_subdirectory("include/freeglut")

IF (MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
ENDIF ()

set(SRC_DIR "src")

file(GLOB SOURCES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")


add_executable (${PROJECT_NAME} 
	 WIN32 ${SOURCES} ${GLAD_GL} ${GLFW_SOURCE_DIR}/deps/glad_gl.c
)

target_compile_options(${PROJECT_NAME} PRIVATE -O3 -g)
target_include_directories(${PROJECT_NAME} 
	PUBLIC "include"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cmake -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL OpenGL::GLU glfw glm freeglut SDL2)

IF (MSVC)
    IF (${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message("\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n")
    ELSE ()
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    ENDIF ()
ENDIF ()
