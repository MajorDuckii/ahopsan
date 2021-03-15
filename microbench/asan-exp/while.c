
#include <stdio.h>
#include <stdlib.h>

int f(char *p)
{
  // p can be any pointer pointing anywhere including OOB
  int x = 0;
  while (*p) {
    x += *p;
    p++;
  }

  return x;
}

int main(int argc, char *argv[])
{
  int x = f(argv[0]);
  printf("sum = %d\n", x);
  return 0;
}