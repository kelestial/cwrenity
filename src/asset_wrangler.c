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

#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const char *cw_load_file(const char *filename)
{
    //TODO: read file and return contents
    //TODO: throw error if file open fails!

    FILE *file_ptr = fopen(filename, "rb");

    fseek(file_ptr, 0, SEEK_END);
    long f_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    char *buffer = malloc(f_size + 1);

    fread(buffer, 1, f_size, file_ptr);
    fclose(file_ptr);

    //TODO: check if buffer is not null
    return buffer;
}

void cw_free_pointer(void *pointer)
{
    free(pointer);
}