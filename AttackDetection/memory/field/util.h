#define SIZE 8

struct User {
  char name[SIZE];
  int id;
};

struct Nested1 {
  char str1[8];
  int i;
  float f;
};
struct Nested2 {
  char str2[8];
  long l;
  double d;
};
struct S {
  char str[8];
  struct Nested1 n1;
  struct Nested2 n2;
};
#define init_s(s)               \
  memcpy(s.str, "str", 4);      \
  memcpy(s.n1.str1, "str1", 5); \
  s.n1.i = 100;                 \
  s.n1.f = 200;                 \
  memcpy(s.n2.str2, "str2", 5); \
  s.n2.l = 300;                 \
  s.n2.d = 400;

#define overflow(src, dst)                \
  if (src < dst) {                        \
    for (int i = 0; &src[i] <= dst; i++)  \
      src[i] = 'a';                       \
  } else {                                \
    for (int i = 0; &src[i] >= dst; i--)  \
      src[i] = 'a';                       \
  }

#define non_sequential_overflow(src, dst) \
  long diff = dst - src;                  \
  src[diff] = 'a';

#define overread(src, dst)                \
  if (src < dst) {                        \
    for (int i = 0; &src[i] <= dst; i++)  \
      src[i];                             \
  } else {                                \
    for (int i = 0; &src[i] >= dst; i--)  \
      src[i];                             \
  }

#define non_sequential_overread(src, dst) \
  long diff = dst - src;                  \
  src[diff];
