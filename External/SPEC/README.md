# Build

## smatus build

```bash
$ cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_COMPILER=clang \
        -DTEST_SUITE_SPEC2006_ROOT=/path/to/cpu2006 \
        -DSMATUS=ON \
        ../
$ ninja External/all
```

### Compile error

#### 433.milc

Compile error: no name or undefined variables 

#### 458.sjeng

utils.c: `_RV_getc`を通常の`getc`へと書き換え

しかし，実行時out-of-memory(??)

#### 456.hmmer

hsregex.c: `_RV_regnode()`, `_RV_regc()`, `_RV_reginsert()`の型書き換え (`int` &rarr; `char`)

#### 464.h264ref

Compile error: Cannot handle macros correctly
