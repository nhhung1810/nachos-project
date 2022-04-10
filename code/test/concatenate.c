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
  if (f < 0) {
    PrintString("Can not open first file\n");
    Halt();
  }

  g = Open(secondFileName);
  if (g < 0) {
    PrintString("Can not open second file\n");
  }
  Read(str2, 256, g);

  while (1) {
    size = Read(str2, 255, f);
    if (size == 0) 
      break;
      Write(str2, size, f);
  }
  
  Close(f);
  Close(g);
  Halt();
  /* not reached */
}
