
struct FuncPtr {
  char name[8];
  int (*ptr)(int, int);
};

#define overflow(src, dst)                \
  if (src < dst) {                        \
    for (int i = 0; &src[i] <= dst; i++)  \
      src[i] = 'a';                       \
  } else {                                \
    for (int i = 0; &src[i] >= dst; i--)  \
      src[i] = 'a';                       \
  }

/*
void overflow(char *src, char *dst) {
  if (src < dst) {
    for (int i = 0; &src[i] <= dst; i++)
      src[i] = 'a';
  } else {
    for (int i = 0; &src[i] >= dst; i--)
      src[i] = 'a';
  }
}
*/