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

#ifdef CWREN_PLATFORM_WIN

#include <cwrenity.h>
#include <windows.h>

#include "win32_surface.h"

LRESULT CALLBACK win32_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//TODO: handle win32 api class callbacks
}

void win32_create_surface()
{
	WNDCLASS w32_class = {0};
	w32_class.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	w32_class.lpfnWndProc = win32_callback;
	w32_class.hInstance = GetModuleHandle(0);
	w32_class.lpszClassName = "cwrenw32class";
	//W32_class.hIcon; -- for later

	if (!RegisterClass(&w32_class))
	{
		//TODO: throw error
	}

	HWND w32_handle = CreateWindowEx(0, w32_class.lpszClassName, "cwrenity (win32 api)", 
		WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, 
		w32_class.hInstance, 0);
}

#endif