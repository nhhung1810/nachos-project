/* createFile.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

int main()
{
  char str[256];
  ReadString(str, 255);
  PrintString("\n Filename is: ");
  PrintString(str);
  PrintString("\n");
  Create(str);
  Halt();
  /* not reached */
}
