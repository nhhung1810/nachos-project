#include "syscall.h"

int main()
{
    char *str = "abcdefg\n";
    PrintString(str);
    Halt();
    /* not reached */
}
