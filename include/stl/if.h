/*!
  @file def.h
  @brief This file provides the necessary macros to compile two types of structures: structures with
  containers based on regular data types and structures with containers based on pointer data types.
  
  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef IF_INCLUDED
#define IF_INCLUDED

#include "def.h"

#define __STL_IF_ELSE(condition) __STL__IF_ELSE(__STL_BOOL(condition))
#define __STL__IF_ELSE(condition) __STL_CAT(__STL_IF_, condition)

#define __STL_IF_1(...) __VA_ARGS__ __STL_IF_1_ELSE
#define __STL_IF_0(...)             __STL_IF_0_ELSE

#define __STL_IF_1_ELSE(...)
#define __STL_IF_0_ELSE(...) __VA_ARGS__

#define __STL_IS_PROBE(...) __STL_SECOND(__VA_ARGS__, 0)
#define __STL_PROBE() ~, 1

#define __STL_NOT(x) __STL_IS_PROBE(__STL_CAT(__STL_NOT_, x))
#define __STL_NOT_0 __STL_PROBE()

#define __STL_CAT(a, b, ...) a ## b
#define __STL_BOOL(x) __STL_NOT(__STL_NOT(x))

#define STL_IF_ELSE_PTR_DTYPE(dtype_or_cond, ...)			\
	__STL__IF_ELSE(__STL_IS_PROBE(__STL_CAT(__STL_IS_PTR_, dtype_or_cond)))

#define __STL_IS_PTR_1 __STL_PROBE()

#endif

