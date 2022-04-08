/* readString.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"
// typedef int OpenFileId;

int main()
{
  // char str[256];
  // ReadString(str, 255);
  // PrintString("\nRead string is: ");
  // PrintString(str);
  // PrintString("\n");
  // Create("hung.txt");
  int id = Open("hung.txt");
  PrintNum(id);

  // PrintNum(id);
  Halt();
  /* not reached */
}
