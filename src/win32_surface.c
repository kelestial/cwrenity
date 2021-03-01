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

#if defined(CWREN_PLATFORM_WIN)

#include <cwrenity.h>
#include <windows.h>
#include <string.h>
#include <GL/GL.h>

#include "win32_surface.h"

static HWND w32_handle = NULL;
HDC w32_device_context = NULL;
static bool win_active = false;

LRESULT CALLBACK win32_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
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
			win32_destroy_window();
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

static void win32_opengl_context()
{
	PIXELFORMATDESCRIPTOR w32_pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

		w32_device_context = GetDC(w32_handle);

		int w32_pf = ChoosePixelFormat(w32_device_context, &w32_pfd); 
		SetPixelFormat(w32_device_context, w32_pf, &w32_pfd);

		HGLRC w32_ogl_context = wglCreateContext(w32_device_context);
		wglMakeCurrent(w32_device_context, w32_ogl_context);

		char gl_str[30] = "OpenGL Version: ";
		strcat(gl_str, glGetString(GL_VERSION));
		cw_log_message(gl_str, NOTE);
}

void win32_create_window(const char *title, unsigned int width, unsigned int height)
{
	WNDCLASSEX w32_class = {0};
	w32_class.cbSize = sizeof(WNDCLASSEX);
	w32_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	w32_class.lpfnWndProc = win32_callback;
	w32_class.hInstance = GetModuleHandle(NULL);
	w32_class.lpszClassName = "cwrenw32class";

	if (!width || !height)
	{
		cw_log_message("(win32) illegal size params. defaulting to (800x600)", ERR);
		width = 800;
		height = 600;
	}

	if (!RegisterClassEx(&w32_class))
	{
		cw_log_message("(win32) class registration failed!", FATAL);
	}

	w32_handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, w32_class.lpszClassName, 
		title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		0, 0, w32_class.hInstance, 0);

	if (!w32_handle)
	{
		cw_log_message("(win32) failed to create valid window handle!", FATAL);
	}

	win32_opengl_context();
	ShowWindow(w32_handle, SW_SHOWNORMAL);
}

void win32_update_window()
{
	MSG msg;

	UpdateWindow(w32_handle);

	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void win32_destroy_window()
{
	if (w32_handle)
	{
		DestroyWindow(w32_handle);
	}
}

bool win32_is_window_alive()
{
	return win_active;
}

#endif