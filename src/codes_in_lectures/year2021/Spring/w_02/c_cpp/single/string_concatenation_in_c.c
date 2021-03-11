// Onder Suvak (C) 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
print_string_content_info
(
  const char *  str_ptr
);

int
main (void)
{
  char str_1st[256] = "Ali topu at.";
  char str_2nd[256] = "Bana mesaj geldi.";
  
  print_string_content_info (str_1st);
  print_string_content_info (str_2nd);
  
  const unsigned int  size_initial
    = strlen(str_1st);
  str_1st[    size_initial] = ' ';
//   str_1st[1 + size_initial] = 0;
  str_1st[1 + size_initial] = '\0';
  
  print_string_content_info (str_1st);
  
  char * returned_ptr
    = strcat( str_1st , str_2nd );
  print_string_content_info (str_1st);
  print_string_content_info (str_2nd);
  
  printf( "Whether \"returned_ptr\" is the same as \"str_1st\" :\n  %s\n" , 
          (returned_ptr == str_1st) ? "YES" : "NO" );
  
  return 0;
}

void
print_string_content_info
(
  const char *  str_ptr
)
{
  printf( "String :\n  %s\n  (%3d characters)\n" , 
          str_ptr , strlen(str_ptr) );
}
