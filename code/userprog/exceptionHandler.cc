// exceptionHandler.cc
// Refactor all handler

#include "copyright.h"
#include "main.h"
#include "kernel.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

int MAX_LENGTH_FILENAME = 32;

// HEADER SECTION
// 1. Handler
void haltHandle();
void addHandle();
void printNumHandle();
void printCharHandle();
void printStringHandle();

// 2. Helper function
void pcIncrement();
char *getStringFromAddress(int addr);
// IMPLEMENTATION SECTION

void haltHandle()
{
    DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

    SysHalt();

    return;
}

void addHandle()
{
    DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

    /* Process SysAdd Systemcall*/
    int result;
    result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
                    /* int op2 */ (int)kernel->machine->ReadRegister(5));

    DEBUG(dbgSys, "Add returning with " << result << "\n");
    /* Prepare Result */
    kernel->machine->WriteRegister(2, (int)result);

    /* Modify return point */
    pcIncrement();

    return;
}

void printNumHandle()
{
    int num = (int)kernel->machine->ReadRegister(4);
    SysPrintNum(num);
    pcIncrement();
    return;
}

void printCharHandle()
{
    char c = (char)kernel->machine->ReadRegister(4);
    SysPrintChar(c);
    pcIncrement();
    return;
}

void printStringHandle()
{
    // Find the head of string
    int addr = kernel->machine->ReadRegister(4);
    char *str = getStringFromAddress(addr);
    SysPrintString(str, strlen(str));
    delete str;
    pcIncrement();
}

void readNumHandle()
{
    int n;
    n = SysReadNum();
    kernel->machine->WriteRegister(2, n);
    DEBUG(dbgSys, "Readed number: " << n);
    pcIncrement();
    return;
}

// Allocating mem -> need to delete
char *getStringFromAddress(int addr)
{
    int size = 0;
    int c = -1;
    while (c != '\0')
    {
        kernel->machine->ReadMem(addr + size, 1, &c);
        size++;
        if (c == '\0')
            break;
    }

    char *str = new char[size];
    for (int i = 0; i < size; i++)
    {
        int chr;
        kernel->machine->ReadMem(addr + i, 1, &chr);
        str[i] = chr;
    }
    return str;
}
/**
 * @brief 
 * 
 *   Use standard lib to random positive integer number from 0..MAX_RAND(2 ^ 31 - 1) *
 */
void randomNumHandle()
{
    srand(time(NULL));
    int randomedNumber = rand();
    kernel->machine->WriteRegister(2, randomedNumber);
    DEBUG(dbgSys, "Randomed number: " << randomedNumber);
    pcIncrement();
    return;
}

void pcIncrement()
{
    kernel->machine->WriteRegister(PrevPCReg,
                                   kernel->machine->ReadRegister(PCReg));

    kernel->machine->WriteRegister(PCReg,
                                   kernel->machine->ReadRegister(NextPCReg));

    kernel->machine->WriteRegister(
        NextPCReg, kernel->machine->ReadRegister(NextPCReg) + 4);
    return;
}