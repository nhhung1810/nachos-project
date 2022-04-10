/* createFile.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

char fileName[256], str[256];

int main()
{
  int f, size;
  PrintString("Enter filename: ");
  
  ReadString(fileName, 256);

  f = Open(fileName);

  if (f < 0) {
    Halt();
  }
  
  while (1) {
    size = Read(str, 255, f);
    if (size == 0) 
      break;
    PrintString(str);
  }
  // Read(str, 2, f);
  Close(f);
  
  PrintString("\n");
  Halt();
  /* not reached */
}
