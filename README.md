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

## Test

### SPEC2006

```bash
$ lit . --filter=<benchmark-name>
```

Save the results to json file
```bash
$ lit . -o <filename>.json .
```

#### Run tests n-times

```bash
$ cd build
$ ../utils/average.py -n <times> -o <filename>.json
```

#### Show and compare the results

Show a single result file:
```bash
$ python3 utils/compare.py <filename>.json
```

Compare two result files:
```bash
$ python3 utils/compare.py <filename_a>.json <filename_b>.json
```

#### Measurement with `time` command

Run 5 time
```bash
$ cd build/
$ python3 ../utils/run_spec2006.py -n 5 --all
```

Show the results
```bash
$ python3 utils/run_spec2006.py --result
$ python3 utils/compare_spec2006.py build/ dfisan_build/
```

### Phoenix sample apps

```bash
$ python utils/run_phoenix_apps.py -n 5 --all
$ python utils/run_phoenix_apps.py --result
```

### experiment

```bash
$ python ../utils/run_insertion_sort.py -n 5
```
