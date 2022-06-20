# dfsan-test-suite

## Build

```bash
$ export LLVM_COMPILER=clang
$ export LLVM_COMPILER_PATH=/path/to/clang
$ cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_C_COMPILER=wllvm \
        -DTEST_SUITE_SPEC2006_ROOT=/path/to/speccpu2006 \
        ../
$ ninja <benchmark-name>
```

## Run tests

```bash
$ lit . --filter=<benchmark-name>
```
