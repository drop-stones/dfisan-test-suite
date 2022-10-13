# dfsan-test-suite

## Build

```bash
$ export LLVM_COMPILER=clang
$ export LLVM_COMPILER_PATH=/path/to/clang
$ cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_C_COMPILER=wllvm \
        -DTEST_SUITE_SPEC2006_ROOT=/path/to/speccpu2006 \
        -DDFISAN=On \
        -DUNALIGNED_REGION_ONLY=OFF \
        ../
$ ninja <benchmark-name>
```

### Options

- `-DDFISAN`: Sanitize with dfisan
- `-DUNALIGNED_REGION_ONLY`: All protection targets are replaced in unaligned region

## Run tests

```bash
$ lit . --filter=<benchmark-name>
```

Save the results to json file
```bash
$ lit . -o <filename>.json .
```

### Run tests n-times

```bash
$ cd build
$ ../utils/average.py -n <times> -o <filename>.json
```

## Show and compare the results

Show a single result file:
```bash
$ python3 utils/compare.py <filename>.json
```

Compare two result files:
```bash
$ python3 utils/compare.py <filename_a>.json <filename_b>.json
```
