
#include <stdio.h>
#include <stdlib.h>

int access_array(int *p, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
        sum += p[i];
    return sum;
}

struct Object
{
    int x;
    int y;
    int z;
};

int access_object(struct Object *obj)
{
    int sum = 0;
    sum += obj->x;
    sum += obj->y;
    sum += obj->z;
    return sum;
}

int main(int argc, char *argv[], char *env[])
{
    struct Object obj;
    char **p;
    int i = 0, j = 0;
    for (p = argv; *p != NULL; p++, i++)
        ;
    for (p = env; *p != NULL; p++, j++)
        ;
    obj.x = argc;
    obj.y = i;
    obj.z = j;

    i = access_object(&obj);
    j = access_array((int *)&obj, 3);
    printf("%d =? %d\n", i, j);
    return 0;
}
