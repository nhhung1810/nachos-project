/* remove.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

int main()
{
  char str[256];
  ReadString(str, 255);
  PrintString("\nFilename is: ");
  PrintString(str);
  PrintString("\n");
  Remove(str);
  Halt();
  /* not reached */
}
