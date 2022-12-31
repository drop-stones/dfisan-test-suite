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

### smatus build

```bash
$ cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=None \
        -DCMAKE_C_COMPILER=clang \
        -DUSE_SMATUS=ON \
        ../
$ ninja -j1 AttackDetection/all
```

## Run

```bash
$ ninja test
```
