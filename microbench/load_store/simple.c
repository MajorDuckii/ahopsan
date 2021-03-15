void ptr_asign(int *p) { *p = 10; }

int ptr_def(int *p) { return *p; }

void ptr_add(char *p) { p++; }

void ptr_swap(char *p, char *q)
{
  char t = *p;
  *p = *q;
  *q = t;
}