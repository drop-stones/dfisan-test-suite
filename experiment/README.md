## How to run

### Build

```
$ cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=None \
        -DCMAKE_C_COMPILER=clang \
        ../
$ ninja tools/timeit
$ ninja insertion_sort_target find_max_target find_min_max_target
```

### Run tests

```
$ python3 ../utils/run_insertion_sort.py -n 5
$ python3 ../utils/run_find_max.py -n 5
$ python3 ../utils/run_find_min_max.py -n 5
```
