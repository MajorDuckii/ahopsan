#include <iostream>
#include <stdio.h>

using namespace std;

void do_sanitize(const int *ptr) {}
int main()
{
  int arr[] = {9, 18, 31, 40, 42};
  int sum = 0;
  const int *arr_shadow;

  for (auto cbeg = cbegin(arr); cbeg != cend(arr); ++cbeg) {
    // #ifdef YPH_OPTIMIZTION
    //         if (abs(arr_shadow - cbeg) < 64)
    //         {
    //             do_sanitize(cbeg);
    //             arr_shadow = cbeg;
    //         }
    // #else
    //         do_sanitize(cbeg);
    // #endif
    // cout << *cbeg << endl;
    sum += *cbeg;
  }
}
