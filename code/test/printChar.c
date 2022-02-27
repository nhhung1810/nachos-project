#include "syscall.h"

int main()
{
    PrintChar('a');
    PrintChar('\n');
    PrintChar('b');
    PrintChar('\n');
    PrintChar('c');
    PrintChar('\n');
    PrintChar('d');
    PrintChar('\n');

    Halt();
    /* not reached */
}
