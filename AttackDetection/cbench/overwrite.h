
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
