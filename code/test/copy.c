/* createFile.c
 *
 *	Simple program to test reading a string
 *
 */

#include "syscall.h"

char sourceFileName[256], destinationFileName[256], str[256];

int main()
{
  int f, g, size;
  PrintString("Enter source file: ");
  ReadString(sourceFileName, 256);

  PrintString("Enter destination file: ");
  ReadString(destinationFileName, 256);

  PrintString("\n");
  f = Open(sourceFileName);
  if (f < 0) {
    PrintString("Can not open source file\n");
    Halt();
  }

  if (Create(destinationFileName) == 0) {
    PrintString("Can not create dest file\n");
    Halt();
  }
  g = Open(destinationFileName);
  if (g < 0) {
    PrintString("Can not open dest file\n");
    Halt();
  }

  size = Read(str, 256, f);
  Close(f);

  Write(str, size, g);
  Close(g);

  Halt();
  /* not reached */
}
