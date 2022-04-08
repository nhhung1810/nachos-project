/* close.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"
// typedef int OpenFileId;

int main()
{
  int id = Open("hung.txt");
  int indicator = Close(id);
  PrintNum(indicator);
  // PrintNum(id);
  Halt();
  /* not reached */
}
