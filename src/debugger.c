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
#include <stdio.h>

#if defined(CWREN_PLATFORM_WIN)
#include <windows.h>

static HANDLE c_handle;
static WORD def_attrib;
static bool buffer_active = false;

static void console_colour_type(logtype_t type)
{
	if (!buffer_active)
	{
		c_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO c_info;
		GetConsoleScreenBufferInfo(c_handle, &c_info);
		def_attrib = c_info.wAttributes;

		buffer_active = true;
	}

	switch (type)
	{
		case NOTE:
		{
			SetConsoleTextAttribute(c_handle, def_attrib);
			break;
		}

		case WARNING:
		{
			SetConsoleTextAttribute(c_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		}

		case ERR:
		{
			SetConsoleTextAttribute(c_handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		}

		case FATAL:
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

#elif defined(CWREN_PLATFORM_UNIX)
//TODO: add unix console colours (ANSII)

static void console_colour_type(logtype_t type){}

#endif

static const char *logstr_array[4] = {"NOTE", "WARNING", "ERROR", "FATAL"};

void cw_log_message(const char *message, logtype_t type)
{
	console_colour_type(type);
	printf("%s: %s\n", logstr_array[type], message);
	console_colour_type(0);
}