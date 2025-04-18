// Sub-object overflow in function call

#include <stdio.h>
#include <string.h>

struct S {
  char str[8];
  int *ptr;
};

void Input(char *str) {
  memcpy((void *)str, "aaaaaaaaaaaaaaa", 16);
}

int main(void) {
  int x = 100;
  // struct S s __attribute__((annotate("dfi_protection"))) = { "init", &x };
  struct S s = { "init", &x };

  printf("Before: s.ptr = %p\n", (void *)s.ptr);
  printf("\ts.str = %s\n", s.str);
  s.str[0];

  Input(s.str); // Sub-object overflow

  printf("After : s.ptr = %p\n", (void *)s.ptr);
  printf("\ts.str = %s\n", s.str);
  s.str[0];

  return 0;
}
