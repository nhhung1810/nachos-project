/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include "synchconsole.h"
#include <stdlib.h>

int getNumBufferLength(int num);

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

void SysPrintNum(int num)
{
  if (!num)
    return kernel->synchConsoleOut->PutChar('0');

  if (num < 0)
  {
    kernel->synchConsoleOut->PutChar('-');
    num = -num;
  }

  while (num)
  {
    // need to load buffer as to not reverse the number
    int bufferLength = getNumBufferLength(num) + 1;
    int *buffer = new int(bufferLength);
    for (int i = 0; i < bufferLength; i++)
    {
      buffer[i] = num % 10;
      num /= 10;
    }
    for (int i = bufferLength - 1; i >= 0; i--)
    {
      kernel->synchConsoleOut->PutChar('0' + buffer[i]);
    }
    delete buffer;
  }
  return;
}
// 100 / 100
int getNumBufferLength(int num)
{
  int size = 1;
  int length = 0;
  while (num / size >= 1.0)
  {
    size *= 10;
    length++;
  }
  return length;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
