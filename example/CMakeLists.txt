project (example)

add_executable (example "src/main.c" "src/app.c")
target_include_directories (example PUBLIC "../include/")
target_link_libraries (example cwrenity)

if (WIN32)
	target_compile_definitions (cwrenity PUBLIC CWREN_PLATFORM_WIN)
elseif (UNIX)
	target_compile_definitions (cwrenity PUBLIC CWREN_PLATFORM_UNIX)
endif ()
