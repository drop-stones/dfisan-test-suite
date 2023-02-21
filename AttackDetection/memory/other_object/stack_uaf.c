int *ret_ptr(void) {
  int x = 100;
  return &x;
}

int main(void) {
  int *returned = ret_ptr();
  *returned;
  return 0;
}
