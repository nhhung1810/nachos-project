#include "syscall.h"

const int MAXN = 100;

int main()
{
  int arr[MAXN];
  int i, j, n, opt, tmp;
  
  PrintString("Enter n: ");
  n = ReadNum();
  
  if (n <= 0 || n > MAXN) {
    PrintString("Error! Number of elements must between 1 and 100");
    Halt();
  }

  PrintString("Please enter ");
  PrintNum(n);
  PrintString(" numbers:\n");
  for (i=0; i<n; ++i) {
    PrintString("a[");
    PrintNum(i);
    PrintString("] = ");
    arr[i] = ReadNum();
  }

  PrintString("Option (1:ascending, 2:descending): ");
  opt = ReadNum();

  if (opt != 1 && opt != 2) {
    PrintString("Invalid option\n");
    Halt();
  }

  BubbleSort(&arr, n);
  if (opt == 2) {
    for(i=0; n-i-1>i; ++i) {
      tmp = arr[i];
      arr[i] = arr[n-i-1];
      arr[n-i-1] = tmp;
    }
  }
  PrintString("Sorted Array: \n");
  for (i=0; i<n; ++i) {
    PrintString("a[");
    PrintNum(i);
    PrintString("] = ");
    PrintNum(arr[i]);
    PrintString("\n");
  }

  // for (i=0; i<n; ++i) {
  //   for (j=0; j)
  // }

  Halt();
  /* not reached */
}
