# Build options

## dfisan build

```bash
cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=None \
      -DCMAKE_C_COMPILER=wllvm \
      -DTEST_SUITE_SPEC2006_ROOT=/path/to/cpu2006-dfi-anno \
      -DDFISAN=ON \
      ../
```

## baseline build

```bash
cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=None \
      -DCMAKE_C_COMPILER=clang \
      -DTEST_SUITE_SPEC2006_ROOT=/path/to/cpu2006 \
      ../
```

## asan build

```bash
cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=None \
      -DCMAKE_C_COMPILER=clang \
      -DTEST_SUITE_SPEC2006_ROOT=/path/to/cpu2006 \
      -DCMAKE_CXX_FLAGS="-fsanitize=address" \
      -DCMAKE_C_FLAGS="-fsanitize=address" \
      ../
```
