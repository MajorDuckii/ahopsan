#include <stdio.h>

int main(void)
{
    int a[8] = {0};
    int b[8] = {0};
    b[1] = 1;
    for (int i = 0, x = 0, y = 0; i <= 8; ++i) // uh oh
    {
        // This loop looks like it only reads / writes inside b
        b[i] += x + y;
        y = x;
        x = b[i];
    }
    // a has been altered, b[8] is actually a[0]
    return a[0];
}
