#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

void overwrite(char *src, char *dst) {
  if (src < dst) {
    for (int i = 0; &src[i] <= dst; i++) {
      src[i] = 'a';
    }
  } else {
    for (int i = 0; &src[i] >= dst; i--) {
      src[i] = 'a';
    }
  }
}

struct Foo {
  char buffer[16];
  jmp_buf jmp_buffer;
};

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

  struct Foo *f = malloc(sizeof(*f));
  void *addr = (void *)Bar;

  if (setjmp(f->jmp_buffer)) {
    printf("test\n");
    return 0;
  }
  printf("plz input:\n");
  // read(0, f->buffer, 0x100);
  overwrite(f->buffer, f->buffer + sizeof(jmp_buf));
  longjmp(f->jmp_buffer, 1);

  return 0;
}
