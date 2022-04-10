/* createFile.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

char filename[256];

int main()
{
  int f, g, size;
  PrintString("Enter file name: ");
  ReadString(filename, 256);

  Remove(filename);
  Halt();
  /* not reached */
}
