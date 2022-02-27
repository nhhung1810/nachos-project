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

  for (i=0; i<n; ++i) {
    for (j=0; j<n-1; ++j) {
      if (opt == 1) { //ascending
        if (arr[j] > arr[j+1]) {
          tmp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = tmp;
        }
      } else {
        if (arr[j] < arr[j+1]) { //descending
          tmp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = tmp;
        }
      }
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
