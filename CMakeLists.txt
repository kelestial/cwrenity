cmake_minimum_required (VERSION 3.18)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_C_STANDARD 11)

project (cwrenity)

if (WIN32)
	set (NATIVE_SRC "src/win32_layer.c")
	set (LIB_DEFINES "CWREN_PLATFORM_WIN" "CWREN_BUILD_SHARED")
	set (LIB_DEPS "opengl32" "glu32")

elseif (UNIX)
	set (NATIVE_SRC "")
	set (LIB_DEFINES "CWREN_PLATFORM_UNIX" "CWREN_BUILD_SHARED")
	set (LIB_DEPS "")

else()
	set (NATIVE_SRC "")
	set (LIB_DEFINES "CWREN_BUILD_SHARED")
	set (LIB_DEPS "")

endif ()

set (LIB_SRC 
	"src/application.c"
	"src/debugger.c")

set (VENDOR_SRC "vendor/glad/src/glad.c")

add_library (cwrenity SHARED ${LIB_SRC} ${NATIVE_SRC} ${VENDOR_SRC})
target_compile_definitions (cwrenity PUBLIC ${LIB_DEFINES})

target_include_directories (cwrenity PUBLIC "include" "vendor/glad/include" "vendor/glfw/include")
target_link_libraries (cwrenity PUBLIC opengl32 glu32)

add_subdirectory ("example")