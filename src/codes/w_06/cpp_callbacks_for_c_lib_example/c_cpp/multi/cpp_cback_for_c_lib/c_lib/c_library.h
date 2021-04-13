// Onder Suvak (C) 2021

#pragma once

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*ManipulatorFuncPtrType)(int, void *); 

typedef struct LibraryContainer_
{
  int 
    number;
  ManipulatorFuncPtrType
    func_ptr;
  void *
    custom_instance_ptr;
} LibraryContainer;

LibraryContainer *
CLibrary_create_new_instance
();

void
CLibrary_destroy_instance
(
  LibraryContainer *  instance_ptr
);

void
CLibrary_register_manipulator_function
(
  LibraryContainer *      instance_ptr,
  ManipulatorFuncPtrType  func_ptr
);

void
CLibrary_register_custom_instance_ptr
(
  LibraryContainer *  instance_ptr,
  void *              custom_instance_ptr
);

void
CLibrary_call_callback_function
(
  LibraryContainer *  instance_ptr
);
  
#ifdef __cplusplus
}
#endif