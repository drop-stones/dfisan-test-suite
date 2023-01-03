// dfisan can detect the sub-object overflow

#include <stdio.h>

struct S {
  char str[8];
  int *ptr;
};

int main(void) {
  int x = 100;
  struct S s __attribute__((annotate("dfi_protection"))) = { "init", &x };

  printf("Before: s.ptr = %p\n", (void *)s.ptr);
  printf("\ts.str = %s\n", s.str);
  s.str[0];

  for (int i = 0; i < 10; i++)
    s.str[i] = 'a';
  
  printf("After : s.ptr = %p\n", (void *)s.ptr);
  printf("\ts.str = %s\n", s.str);
  s.str[0];

  return 0;
}
