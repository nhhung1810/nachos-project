/* readString.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"
// typedef int OpenFileId;

int main()
{
  char *str;
  int id = Open("hung.txt");
  Read(str, 255, id);
  PrintString("\nRead string is: ");
  PrintString(str);
  PrintString("\n");

  // PrintNum(id);
  Halt();
  /* not reached */
}
