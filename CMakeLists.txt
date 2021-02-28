cmake_minimum_required (VERSION 3.8)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_C_STANDARD 11)

set (LIB_SRC 
	"src/application.c")

project (cwrenity)
add_library (cwrenity SHARED ${LIB_SRC})
target_include_directories (cwrenity PUBLIC "include/")

if (WIN32)
	target_compile_definitions (cwrenity PUBLIC CWREN_PLATFORM_WIN CWREN_BUILD_SHARED)
elseif (UNIX)
	target_compile_definitions (cwrenity PUBLIC CWREN_PLATFORM_UNIX CWREN_BUILD_SHARED)
endif ()

add_subdirectory ("example")