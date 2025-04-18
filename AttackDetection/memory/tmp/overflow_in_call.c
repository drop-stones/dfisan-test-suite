// Tests that dfisan can detect buffer overflow in another funcs.

#include <stdio.h>

void nullify40bytes(char *str) {
  for (int i = 0; i < 40; i++)
    str[i] = 0;
}

int main(void) {
  char buf[40];
  char str[8];
  int x = 100;
  char buf2[40];

  printf("&x = %p\n", (void *)&x);
  printf("str = %p, &str[32] = %p\n", (void *)str, (void *)&str[32]);

  printf("Before nullify40bytes: x = %d\n", x);
  nullify40bytes(str);
  printf("After nullify40bytes : x = %d\n", x);

  return 0;
}
