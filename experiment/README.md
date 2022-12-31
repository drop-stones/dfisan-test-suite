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
$ cd experiment/insertion_sort/
$ python3 experiment/insertion_sort/run_insertion_sort.py

$ cd experiment/find_max/
$ python3 experiment/find_max/run_find_max.py

$ cd experiment/find_min_max/
$ python3 experiment/find_min_max/run_find_min_max.py
```
