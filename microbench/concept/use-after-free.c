#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *x = (char *)malloc(10 * sizeof(char *));
  char *x_shadow = x;
  free(x);

  if (x_shadow - (&x[5]) < 64) {
    printf("Do check\n");
    x_shadow = x;
  }
  return x[5];
}
