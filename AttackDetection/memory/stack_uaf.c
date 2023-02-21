int *ret_ptr(void) {
  // int x __attribute__((annotate("dfi_protection"))) = 100;
  int x = 100;
  return &x;
}

int main(void) {
  int *returned = ret_ptr();
  *returned;
  return 0;
}
