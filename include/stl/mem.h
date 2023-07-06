/*!
  @file mem.h
  @brief This header file provides an interface to a collections of macros and implementations that deals
  with the dynamic memory allocation of the structures.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef STL_MEM_INCLUDED
#define STL_MEM_INCLUDED

#include <stddef.h>

extern unsigned long stl_heapaddr;

extern unsigned char *stl_alloc_struct(size_t st_size);
extern unsigned char *stl_alloc_container(size_t container_size);
extern unsigned char *stl_realloc_container(unsigned char *container_ptr, size_t new_container_size);
extern void stl_free_container(unsigned char *container_ptr, size_t container_size);
extern void stl_free_struct(unsigned char *st_ptr);

#endif
