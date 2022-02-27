/* readString.c
 *	
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

int main()
{
  char c;
  c = ReadChar();
  PrintString("\nThe printed char is: ");
  PrintChar(c);
  PrintChar('\n');

  Halt();
  /* not reached */
}
