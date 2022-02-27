#include "syscall.h"

char *str = 
"STUDENT_ID | NAME \n\
19125002    | Nguyen Ngoc Cuong \n\
19125046    | Nguyen Huu Hung \n\
 \n\
Sort: \n\
    nachos -x bubbleSort \n\
    Input: \n\
        - n: size \n\
        - next n numbers \n\
        - Option (1|2): 1 is ascendant, 2 is descendant \n\
    Output: \n\
        - Sorted Array \n\
 \n\
Ascii: \n\
    nachos -x ascii \n\
    Input: \n\
    Output: \n\
        - Readable ascii characters \n\
";
int main()
{
    PrintString(str);
    Halt();
    /* not reached */
}
