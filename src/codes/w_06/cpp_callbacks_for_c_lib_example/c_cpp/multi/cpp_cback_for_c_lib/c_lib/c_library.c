// Onder Suvak (C) 2021

#include "c_library.h"

LibraryContainer *
CLibrary_create_new_instance
()
{
  LibraryContainer *instance_ptr
    = (LibraryContainer *) 
        calloc(1, sizeof(LibraryContainer));
  return instance_ptr;
}

void
CLibrary_destroy_instance
(
  LibraryContainer *  instance_ptr
)
{
  if (!instance_ptr)
    free(instance_ptr);
}

void
CLibrary_register_manipulator_function
(
  LibraryContainer *      instance_ptr,
  ManipulatorFuncPtrType  func_ptr
)
{
  instance_ptr->func_ptr = func_ptr;
}

void
CLibrary_register_custom_instance_ptr
(
  LibraryContainer *  instance_ptr,
  void *              custom_instance_ptr
)
{
  instance_ptr->custom_instance_ptr
    = custom_instance_ptr;
}

void
CLibrary_call_callback_function
(
  LibraryContainer *  instance_ptr
)
{
  instance_ptr->number =
    instance_ptr->func_ptr
      (instance_ptr->number, instance_ptr->custom_instance_ptr);
}
