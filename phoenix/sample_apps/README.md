# sample_apps in Phoenix project

## Build

```bash
$ make DFISAN=/path/to/clang CLANG=/path/to/clang
```

## Protection targets

### kmeans

- kmeans-pthread.c: global
  - 50-55: `int num_points,...`
- kmeans-pthread.c: `int main(int argc, char *argv[])`
  - 318: `arg = (thread_arg *)malloc(sizeof(thread_arg))`
  - 340: `arg = (thread_arg *)malloc(sizeof(thread_arg))`

### pca

- pca-pthread.c: global
  - 51: `int **matrix` &rarr; `int *matrix[DEF_NUM_ROWS]`
    - グローバルポインタ &rarr; グローバル変数へと変更
- pca-pthread.c: `void pthread_mean()`
  - 199: `mean_args = (mean_arg_t *)MALLOC(num_procs * sizeof(mean_arg_t))`

### string_match

- string_match_pthreads.c: `void string_match_splitter(void *data_in)`
  - 160: `str_map_data_t *map_data = (str_map_data_t*)malloc(sizeof(str_map_data_t) * num_procs)`
  - 162: `map_args_t *out = (map_args_t*)malloc(sizeof(map_args_t) * num_procs)`
- string_match_pthreads.c: `int main(int argc, char *argv[])`
  - 299: `str_data_t str_data`

### word_count

- wordcount_pthread.c: `wordcount_splitter(void *data_in)`
  - 149: `t_args_t *out = (t_args_t*)malloc(sizeof(t_args_t))`
  - 185: `wc_count_t **mwords = (wc_count_t**)malloc(num_procs*sizeof(wc_count_t*))`
  - 191: `merge_data_t *m_args = (merge_data_t*)malloc(sizeof(merge_data_t))`
  - (198: `mwords[i] = (wc_count_t*)malloc(tlen*sizeof(wc_count_t))`)
- wordcount_pthread.c: `int main(int argc, char *argv[])`
  - 434: `wc_data_t wc_data`

### reverse_index (no support)

At compilation, `Instruction does not dominate all uses! in function merge_sections`

### matrix_multiply (no support)

At runtime, `bus error (core dumped)`

### 
