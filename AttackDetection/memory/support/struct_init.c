
#define SIZE 8

struct Array {
  char arr[SIZE];
  int id;
};

void init_arr(struct Array *arr) {
  char *ptr = arr;
  for (int i = 0; i < sizeof(struct Array); i++)
    ptr[i] = 0;
}

int main(int argc, char **argv) {
  struct Array arr;
  init_arr(&arr);

  arr.arr[0];
  arr.id;

  return 0;
}
