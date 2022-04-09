/* createFile.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

char firstFileName[256], secondFileName[256], str1[256], str2[256];

int main()
{
  int f, g, size;
  PrintString("Enter first file name: ");
  ReadString(firstFileName, 256);

  PrintString("Enter second file name: ");
  ReadString(secondFileName, 256);

  f = Open(firstFileName);
  g = Open(secondFileName);

  Read(str1, 256, f);
  Read(str2, 256, g);

  PrintString(str1);
  PrintString(str2);
  
  Close(f);
  Close(g);
  Halt();
  /* not reached */
}
