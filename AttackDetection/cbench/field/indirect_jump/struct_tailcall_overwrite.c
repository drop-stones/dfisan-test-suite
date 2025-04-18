#include <stdio.h>
#include <stdlib.h>
#include "../util.h"

typedef int (*Fptr)(int, int);

int SameTypeFunc(int a, int b) {
  printf("In %s \n", __FUNCTION__);
  return 0;
}

void DiffRetFunc(int a, int b) { printf("In %s \n", __FUNCTION__); }

int DiffArgFunc(int a, float b) {
  printf("In %s \n", __FUNCTION__);
  return 0;
}

int MoreArgFunc(int a, int b, int c) {
  printf("In %s \n", __FUNCTION__);
  return 0;
}

int LessArgFunc(int a) {
  printf("In %s \n", __FUNCTION__);
  return 0;
}

int VoidArgFunc(void) {
  printf("In %s \n", __FUNCTION__);
  return 0;
}

int VulEntryFunc(int a, int b) {
  __asm__ volatile("nop\n"
                   "nop\n"
                   "nop\n"
                   "nop\n"
                   "nop\n"
                   "nop\n"
                   "nop\n"
                   "nop\n"
                   "nop\n"
                   "nop\n");
  printf("In %s\n", __FUNCTION__);
  exit(0);
}

int Foo(int a, int b) {
  printf("In %s\n", __FUNCTION__);
  return 0;
}

int excute(void) {
  printf("In %s\n", __FUNCTION__);
  int len;
  int data_len;
  printf("plz input your name length:\n");
  // integer overflow
  // scanf("%uld", &data_len);
  data_len = -1;
  len = data_len + 0x10;
  struct FuncPtr fptr;
  fptr.ptr = Foo;
  // If the compiler version is too low, use the following line instead
  // char name[0x10];
  printf("name is : %p \n", fptr.name);
  printf("ptr is : %p \n", &fptr.ptr);
  // buffer overflow
  printf("plz input your name:\n");
  // read(0, name, data_len);
  // strncpy(name, input, data_len);
  overflow(fptr.name, &fptr.ptr);   // asan aborted

  return fptr.ptr(0, 0);
}

int main(int argc, const char *argv[]) {
  if (argc != 1) {
    printf("\tSameTypeFunc: %p\n", (void *)SameTypeFunc);
    printf("\tDiffRetFunc: %p\n", (void *)DiffRetFunc);
    printf("\tDiffArgFunc: %p\n", (void *)DiffArgFunc);
    printf("\tMoreArgFunc: %p\n", (void *)MoreArgFunc);
    printf("\tLessArgFunc: %p\n", (void *)LessArgFunc);
    printf("\tVoidArgFunc: %p\n", (void *)VoidArgFunc);
    printf("\tnot_entry: %p\n", (void *)(VulEntryFunc + 0x10));
  }

  printf("In %s\n", __FUNCTION__);
  excute();
  return 0;
}
