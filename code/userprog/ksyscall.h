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
#define MAX_OPEN_FILE 10

#include "kernel.h"
#include "synchconsole.h"
#include <stdlib.h>

const int MIN_INT = (int)-2147483648;
const int MAX_INT = (int)2147483647;

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

  // need to load buffer as to not reverse the number
  int bufferLength = getNumBufferLength(num);
  int *buffer = (int *)malloc(sizeof(int) * bufferLength);
  for (int i = 0; i < bufferLength; i++)
  {
    buffer[i] = num % 10;
    num /= 10;
  }
  for (int i = bufferLength - 1; i >= 0; i--)
  {
    kernel->synchConsoleOut->PutChar('0' + buffer[i]);
  }
  free(buffer);
  return;
}

void SysPrintChar(char c)
{
  c = (int)c % 128; // ensure ascii
  kernel->synchConsoleOut->PutChar(c);
  return;
}

void SysPrintString(char *str, int length)
{
  for (int i = 0; i < length; i++)
  {
    kernel->synchConsoleOut->PutChar(str[i]);
  }
  return;
}

int getNumBufferLength(int num)
{
  int size = 0;
  int length = 0;
  while (num)
  {
    num /= 10;
    length++;
  }
  // DEBUG(dbgSys, "DEBUG->getNumBufferLength->"
  //                   << "num=" << num << " length=" << length << "\n");
  return length;
}

int SysReadNum()
{
  DEBUG(dbgSys, "Reading number");
  char c = kernel->synchConsoleIn->GetChar();

  bool isNegative = 0;
  unsigned int res = 0;
  int len = 0;

  if (c == '-')
  {
    isNegative = 1;
  }
  else if (c == EOF || c == ' ' || c == '\n' || c == '\t' || c < '0' || c > '9')
  {
    DEBUG(dbgSys, "Invalid (start with EOF or blank)");
    return 0;
  }
  else
  {
    res = (c - '0');
    len = 1;
  }

  while (true)
  {
    c = kernel->synchConsoleIn->GetChar();
    if (c == EOF || c == ' ' || c == '\n' || c == '\t')
      break;
    if (c < '0' && c > '9')
    {
      DEBUG(dbgSys, "Invalid (digits only)");
    }

    int digit = c - '0';

    len += 1;
    if (len > 10)
    {
      DEBUG(dbgSys, "Invalid (exceed 32-bit integer)");
    }

    if (len == 10)
    {
      if (isNegative)
      {
        if (res < (unsigned int)abs(MIN_INT) / 10)
        {
          res = res * 10 + digit;
        }
        else if (res == (unsigned int)abs(MIN_INT) / 10 && digit <= 8)
        {
          res = res * 10 + digit;
        }
        else
        {
          DEBUG(dbgSys, "Exceed 32-bit integer");
          return 0;
        }
      }
      else
      {
        if (res < (unsigned int)MAX_INT / 10)
        {
          res = res * 10 + digit;
        }
        else if (res == (unsigned int)MAX_INT / 10 && digit <= 7)
        {
          res = res * 10 + digit;
        }
        else
        {
          DEBUG(dbgSys, "Exceed 32-bit integer");
          return 0;
        }
      }
    }
    else
    {
      res = res * 10 + digit;
    }
  }

  DEBUG(dbgSys, "End reading number");
  return isNegative ? -(int)res : (int)res;
}

void SysBubbleSort(int *arr, int n)
{
  int i, j, tmp;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n - 1; ++j)
    {
      if (arr[j] > arr[j + 1])
      {
        tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
  }
}

char *SysReadString(int bufferSize)
{
  int index = 0;
  char *str = new char(bufferSize);
  do
  {
    if (!bufferSize)
      break;

    char c = kernel->synchConsoleIn->GetChar();
    // Only accept readable string
    if (c == EOF || c == '\n' || c == '\t' || c == ' ')
      break;
    if (c < 32 || c > 126)
    {
      DEBUG(dbgSys, "Unreadable character");
    }

    str[index] = c;
    bufferSize--;
    index++;
  } while (true);
  return str;
}

// bool SysCreateFile(char* fileName) {
//     bool success;
//     int fileNameLength = strlen(fileName);

//     if (fileNameLength == 0) {
//         DEBUG(dbgSys, "\nFile name can't be empty");
//         success = false;

//     } else if (fileName == NULL) {
//         DEBUG(dbgSys, "\nNot enough memory in system");
//         success = false;

//     } else {
//         DEBUG(dbgSys, "\nFile's name read successfully");
//         if (!kernel->fileSystem->Create(fileName)) {
//             DEBUG(dbgSys, "\nError creating file");
//             success = false;
//         } else {
//             success = true;
//         }
//     }

//     return success;
// }

bool SysCreateFille(char *filename)
{
  if (filename == NULL)
  {
    DEBUG(dbgSys, "Null filename? Are you sure?");
    return false;
  }

  int size = strlen(filename);

  if (size == 0)
  {
    DEBUG(dbgSys, "Empty filename? Are you sure");
    return false;
  }

  if (!kernel->fileSystem->Create(filename))
  {
    DEBUG(dbgSys, "Failed to create file!");
    return false;
  }
  return true;
}

bool SysRemoveFile(char *filename)
{
  if (filename == NULL)
  {
    DEBUG(dbgSys, "Null filename? Are you sure?");
    return false;
  }

  int size = strlen(filename);

  if (size == 0)
  {
    DEBUG(dbgSys, "Empty filename? Are you sure");
    return false;
  }

  if (!kernel->fileSystem->Remove(filename))
  {
    DEBUG(dbgSys, "Failed to delete file.");
    return false;
  }
  return true;
}

OpenFileId SysOpenFile(char *filename)
{
  if (filename == NULL)
  {
    DEBUG(dbgSys, "Null filename? Are you sure?");
    return false;
  }

  int size = strlen(filename);

  if (size == 0)
  {
    DEBUG(dbgSys, "Empty filename? Are you sure");
    return false;
  }

  OpenFile *op = kernel->fileSystem->Open(filename);
  int index = MAX_OPEN_FILE;
  for (int i = 0; i < MAX_OPEN_FILE; i++)
  {
    // Scan for the first null pos
    if (kernel->openfiles[i] == NULL)
    {
      index = i;
      break;
    }
  }

  if (index >= MAX_OPEN_FILE)
    return -1;
  kernel->openfiles[index] = op;
  return index;
}

int SysCloseFile(OpenFileId id)
{
  if (id > MAX_OPEN_FILE)
  {
    DEBUG(dbgSys, "Invalid id");
    return -1;
  }
  OpenFile **openfiles = kernel->openfiles;
  delete openfiles[id];
  openfiles[id] = NULL;
  DEBUG(dbgSys, "Closed file with id" << id);
  return 1;
}

char *SysReadFile(int size, OpenFileId id)
{
  DEBUG(dbgSys, "Reading " << size << " bytes from file id " << id);
  if (id > MAX_OPEN_FILE)
  {
    DEBUG(dbgSys, "Invalid id");
    return NULL;
  }
  OpenFile *f = kernel->openfiles[id];
  int len = min(size, f->Length());
  char *str = new char[len + 1];
  f->Read(str, len);
  return str;
}

int SysWriteFile(char* str, int size, OpenFileId id)
{
  if (id > MAX_OPEN_FILE || kernel->openfiles[id] == NULL)
  {
    DEBUG(dbgSys, "Invalid id " << id);
    return NULL;
  }
  OpenFile *f = kernel->openfiles[id];
  return f->Write(str, size);
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
