int *ret_ptr(void) {
  int x __attribute__((annotate("dfi_protection"))) = 100;
  return &x;
}

int *ret_ptr2(void) {
  int y __attribute__((annotate("dfi_protection"))) = 200;
  return &y;
}

int main(void) {
  int *returned = ret_ptr();
  ret_ptr2();
  *returned;

  return 0;
}
