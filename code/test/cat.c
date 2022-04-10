/* createFile.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

char fileName[256], str[256];

int main()
{
  int f;
  PrintString("Enter filename: ");
  
  ReadString(fileName, 256);
  PrintString(fileName);
  PrintString("\n");
  f = Open(fileName);
  
  Read(str, 256, f);
  Close(f);
  PrintString(str);
  PrintString("\n");
  Halt();
  /* not reached */
}