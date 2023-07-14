/*!
  @file ex.h
  @brief This file contains general exceptions for the st (structures) library, such as insufficient
  capacity or empty structures.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef EX_INCLUDED
#define EX_INCLUDED

#include <tc.h>

extern Except NotEnoughCapacity;
extern Except EmptyStructure;
extern Except NotEnoughMemory;
extern Except NotEnoughMemoryToRealloc;
extern Except InvalidIndex;
extern Except NotEnoughCapacityAtStructure;
extern Except CapacityAlreadyInitialized;
extern Except InvalidKey;
extern Except UninitializedIter;
extern Except LastElementReached;
extern Except PointingToNullValue;

#endif
