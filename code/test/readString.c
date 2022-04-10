/* readString.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

int main()
{
  char str[256];
  ReadString(str, 256);
  PrintString("\nRead string is: ");
  PrintString(str);
  PrintString("\n");

  Halt();
  /* not reached */
}
