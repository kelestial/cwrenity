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

#include "native_layer.h"

static const char *logstr_array[4] = {"NOTE", "WARNING", "ERROR", "FATAL"};

void cw_log_message(const char *message, logtype_t type)
{
	native_console_colour(type);
	printf("%s: %s\n", logstr_array[type], message);
	native_console_colour(0);

	if (type == LOG_FATAL)
	{
		//TODO: throw exeption!
	}
}

void cw_break_point()
{
	cw_log_message("-BreakPoint Tripped-", WARNING);
	native_debug_break();
}