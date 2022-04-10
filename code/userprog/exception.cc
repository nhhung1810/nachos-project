// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "kernel.h"
#include "syscall.h"
#include "ksyscall.h"
#include "exceptionHandler.cc"

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	case SyscallException:
		switch (type)
		{
		case SC_Read:
			readFileHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_Close:
			closeFileHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_Open:
			openFileHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_Create:
			// add code here
			createFileHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_Remove:
			removeFileHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_Halt:
			haltHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_Add:
			addHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_PrintNum:
			printNumHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_ReadNum:
			readNumHandle();
			return;
			ASSERTNOTREACHED();
			break;
		case SC_ReadChar:
			readCharHandle();
			return;
			ASSERTNOTREACHED();
			break;

		case SC_ReadString:
			readStringHandle();
			return;
			ASSERTNOTREACHED();
			break;

		case SC_PrintChar:
			printCharHandle();
			return;
			ASSERTNOTREACHED();
			break;

		case SC_PrintString:
			printStringHandle();
			return;
			ASSERTNOTREACHED();
			break;

		case SC_RandomNum:
			randomNumHandle();
			return;
			ASSERTNOTREACHED();
			break;

		case SC_BubbleSort:
			bubbleSortHandle();
			return;
			ASSERTNOTREACHED();
			break;

		case SC_Write:
			writeFileHandle();
			return;
			ASSERTNOTREACHED();
			break;
		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}