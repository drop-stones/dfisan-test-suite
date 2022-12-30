## Build

```bash
$ cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=None \
        -DCMAKE_C_COMPILER=/path/to/clang \
        -DCMAKE_C_FLAGS="-fsanitize=..." \
        ../
$ ninja tools/timeit
$ ninja AttackDetection/all
```

## Run

```bash
$ ninja test
```
