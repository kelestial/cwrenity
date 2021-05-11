project (example)

add_executable (example "src/main.c")
target_include_directories (example PUBLIC "../include/")
target_link_libraries (example cwrenity)

if (WIN32)
	target_compile_definitions (cwrenity PUBLIC CWREN_PLATFORM_WIN)
elseif (UNIX)
	target_compile_definitions (cwrenity PUBLIC CWREN_PLATFORM_UNIX)
endif ()

file(COPY "resources" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})