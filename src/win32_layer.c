/*
*  ██████╗██╗    ██╗██████╗ ███████╗███╗   ██╗██╗████████╗██╗   ██╗
* ██╔════╝██║    ██║██╔══██╗██╔════╝████╗  ██║██║╚══██╔══╝╚██╗ ██╔╝
* ██║     ██║ █╗ ██║██████╔╝█████╗  ██╔██╗ ██║██║   ██║    ╚████╔╝ 
* ██║     ██║███╗██║██╔══██╗██╔══╝  ██║╚██╗██║██║   ██║     ╚██╔╝  
* ╚██████╗╚███╔███╔╝██║  ██║███████╗██║ ╚████║██║   ██║      ██║   
*  ╚═════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═╝   ╚═╝      ╚═╝
* 
* Cwrenity is a lightweight, data-oriented game framework!
* 
* 
* Copyright (c) 2021 Victor Sarkisov
*
* This library/source is free (as in free beer and speech): you can
* redistribute it and/or modify it under the terms of the 
* Apache License 2.0 as published by the Apache Software Foundation.
* No warranty or liability is given with the use of this library
* or any of its contents.
*/

#include <cwrenity.h>
#include <windows.h>
#include <string.h>
#include <glad/glad.h>
#include <GL/glext.h>

#include "native_layer.h"

//window and device contexts
static HWND w32_handle = NULL;
static HDC w32_device_context = NULL;
static HGLRC w32_ogl_context = NULL;
static bool win_active = false;

//console information
static HANDLE c_handle = NULL;
static WORD def_attrib = 0;
static bool buffer_active = false;

/*
#############################################
#              WIN32 WINDOWING              #
#############################################
*/

static LRESULT CALLBACK win32_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//EVENT: window creation
		case WM_CREATE:
		{
			win_active = true;
			break;
		}

		//EVENT: window destruction
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			win_active = false;
			break;
		}

		//EVENT: send events back to windows
		default:
		{
			return DefWindowProc(window, msg, wParam, lParam);
		}
	}

	return 0;
}

void native_create_window(const char *title, unsigned int width, unsigned int height)
{
	WNDCLASSEX w32_class = {0};
	w32_class.cbSize = sizeof(WNDCLASSEX);
	w32_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	w32_class.lpfnWndProc = win32_callback;
	w32_class.hInstance = GetModuleHandle(NULL);
	w32_class.lpszClassName = "cwrenw32class";

	if (!width || !height)
	{
		cw_log_message("(win32) illegal size params. defaulting to (800x600)", LOG_ERROR);
		width = 800;
		height = 600;
	}

	if (!RegisterClassEx(&w32_class))
	{
		cw_log_message("(win32) class registration failed!", LOG_FATAL);
	}

	w32_handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, w32_class.lpszClassName, 
		title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		0, 0, w32_class.hInstance, 0);

	if (!w32_handle)
	{
		cw_log_message("(win32) failed to create valid window handle!", LOG_FATAL);
	}
}

void native_show_window(bool win_show)
{
	if (win_show)
	{
		ShowWindow(w32_handle, SW_SHOWNORMAL);
	}

	else
	{
		ShowWindow(w32_handle, SW_HIDE);
	}

}

void native_set_window_title(const char *title)
{
	SetWindowTextA(w32_handle, title);
}

void native_set_window_size(int width, int height)
{
	RECT rect;
	GetWindowRect(w32_handle, &rect);
	SetWindowPos(w32_handle, HWND_TOP, rect.left, rect.top, width, height, 0);
}

CWREN_INT void native_set_window_fullscreen()
{
	//TODO: set window fullscreen
}

CWREN_INT void native_set_window_borderless()
{
	//TODO: set window borderless
}

CWREN_INT void native_set_window_bordered()
{
	//TODO: set window bordered
}

void native_update_window()
{
	MSG msg;

	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	SwapBuffers(w32_device_context);
}

void native_destroy_window()
{
	if (w32_device_context)
	{
		wglDeleteContext(w32_device_context);
	}

	if (w32_handle)
	{
		DestroyWindow(w32_handle);
	}
}

bool native_is_window_alive()
{
	return win_active;
}

/*
#############################################
#           WIN32 GRAPHICS API              #
#############################################
*/

void native_create_gl_context(bool vsync)
{
	PIXELFORMATDESCRIPTOR w32_pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,			// The kind of framebuffer. RGBA or palette.
		24,						// Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,					// Number of bits for the depthbuffer
		0,					// Number of bits for the stencilbuffer
		0,					// Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	w32_device_context = GetDC(w32_handle);

	int w32_pf = ChoosePixelFormat(w32_device_context, &w32_pfd); 
	SetPixelFormat(w32_device_context, w32_pf, &w32_pfd);

	w32_ogl_context = wglCreateContext(w32_device_context);
	wglMakeCurrent(w32_device_context, w32_ogl_context);

	gladLoadGL();
	glViewport(0, 0, 800, 600);

	char gl_str[30] = "OpenGL Version: ";
	strcat(gl_str, glGetString(GL_VERSION));
	cw_log_message(gl_str, LOG_NOTE);

	((BOOL(WINAPI*)(int))wglGetProcAddress("wglSwapIntervalEXT"))(vsync);
}

void native_destroy_gl_context()
{
	ReleaseDC(w32_handle, w32_device_context);
	wglDeleteContext(w32_ogl_context);
}

/*
#############################################
#               WIN32 CONSOLE               #
#############################################
*/

void native_console_colour(int colour)
{
	if (!buffer_active)
	{
		c_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO c_info;
		GetConsoleScreenBufferInfo(c_handle, &c_info);
		def_attrib = c_info.wAttributes;

		buffer_active = true;
	}

	switch (colour)
	{
		case 0:
		{
			SetConsoleTextAttribute(c_handle, def_attrib);
			break;
		}

		case 1:
		{
			SetConsoleTextAttribute(c_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		}

		case 2:
		{
			SetConsoleTextAttribute(c_handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		}

		case 3:
		{
			SetConsoleTextAttribute(c_handle, FOREGROUND_RED | COMMON_LVB_UNDERSCORE | 
				BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY); 

			break;
		}

		default: 
		{
			SetConsoleTextAttribute(c_handle, def_attrib); 
			break;
		}
	}
}

void native_debug_break()
{
	__debugbreak();
}