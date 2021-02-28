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

#ifndef CWRENITY_H
#define CWRENITY_H

#if defined(CWREN_PLATFORM_WIN) && defined(CWREN_BUILD_SHARED)
#	define CWREN_API __declspec(dllexport)
#elif defined (CWREN_PLATFORM_WIN)
#	define CWREN_API __declspec(dllimport)
#elif defined (CWREN_PLATFORM_UNIX) && defined(CWREN_BUILD_SHARED)
#	define CWREN_API __attribute__((visibility("default")))
#else
#	define CWREN_API
#endif

#if defined(CWREN_PLATFORM_UNIX)
#	define CWREN_INT __attribute__((visibility("hidden")))
#else
#	define CWREN_INT
#endif

typedef enum {false, true} bool;

#endif