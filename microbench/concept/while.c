
#include <stdio.h>
#include <stdlib.h>

// int f(char *p)
// {
//   // p can be any pointer pointing anywhere including OOB
//   int x = 0;
//   while (*p) {
//     x += *p;
//     p++;
//   }
//   return x;
// }

void do_sanitize(const char *p) { printf("%s\n", __FUNCTION__); }

int f(char *p)
{
  const char *shadow_p;
  // p can be any pointer pointing anywhere including OOB
  int x = 0;
  if (((long)shadow_p ^ (long)p) > 128) {
    do_sanitize(p);
    shadow_p = p;
  }
  while (*p) {
    if (((long)shadow_p ^ (long)p) > 128) {
      do_sanitize(p);
      shadow_p = p;
    }
    x += *p;
    p++;
  }

  // check all the pointers to test if they are pointing a red-zone.
  // Which implies their last operations do OOB read/write
  do_sanitize(p);
  return x;
}

int main(int argc, char *argv[])
{
  int x = f(argv[0]);
  printf("sum = %d\n", x);

  return 0;
}