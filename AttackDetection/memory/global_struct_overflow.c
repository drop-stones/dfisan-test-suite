#define SIZE 8

struct Array {
  char arr[SIZE];
  int id;
};
struct Array a;

int main(int argc, char **argv) {
  a.id = 100;
  for (int i = 0; i < SIZE + 1; i++)
    a.arr[i] = 'a';

  a.id;      // Error: read broken 'a->id'
  return 0;
}
