#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../util.h"

// struct Foo {
//   char buffer[16];
//   jmp_buf jmp_buffer;
// };

int Vul(void) {
  printf("In %s\n", __FUNCTION__);
  exit(0);
}

void Bar(void) {
  printf("In %s\n", __FUNCTION__);
  exit(0);
}

int main(int argc, const char *argv[], const char *envp[]) {
/*
  if (argc != 1) {
    printf("Do not need the argc");
    printf("the vul is scanf\n");
    printf("if hacked successfully,it will jump to %p\n", (void *)Vul);
    return 1;
  }
*/

  char *buffer = (char *)malloc(sizeof(char) * 16);
  jmp_buf *jmp_buffer = (jmp_buf *)malloc(sizeof(jmp_buf));
  void *addr = (void *)Bar;

  if (setjmp(jmp_buffer)) {
    printf("test\n");
    return 0;
  }
  printf("plz input:\n");
  // read(0, f->buffer, 0x100);
  overflow(buffer, (char *)jmp_buffer);
  longjmp(jmp_buffer, 1);

  return 0;
}
