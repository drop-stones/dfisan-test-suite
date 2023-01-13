# sample_apps in Phoenix project

## Build

```bash
$ make DFISAN=/path/to/clang CLANG=/path/to/clang
```

## Protection targets

### histogram

- hit-pthread.c: `int main(int argc, char *argv[])`
  - 215-216: `pid = (pthread_t *)safe_malloc(sizeof(pthread_t) * num_procs)`  
             `arg = (thread_arg_t *)safe_calloc(sizeof(thread_arg_t), num_procs)`
    - FSAMによるmulti-forked threads解析のため，一部コードを変更
      - ```c
        for (i = 0; i < num_procs; i++)
          pthread_create(&(pid[i]), &attr, calc_hist, (void *)(&(arg[i])));
        ```

### kmeans

- kmeans-pthread.c: global
  - 50-55: `int num_points,...`
- kmeans-pthread.c: `int main(int argc, char *argv[])`
  - 318: `arg = (thread_arg *)malloc(sizeof(thread_arg))`
  - 340: `arg = (thread_arg *)malloc(sizeof(thread_arg))`

### linear_regression

- linear_regression_pthread.c: `int main(int argc, char *argv[])`
  - 135: `tid_args = (lreg_args *)safe_calloc(sizeof(lreg_args), num_procs)`
    - FSAMによるmulti-forked threads解析のため，一部のコードを変更
      - ```c
        for (i = 0; i < num_threads; i++)
          pthread_create(&tid_args[i].tid, &attr, linear_regression_pthread, (void *)&tid_args[i]);
        for (i = 0; i < num_threads; i++)
          pthread_join(tid_args[i].tid, (void **)(void *)&ret_val);
        ```

### pca

- pca-pthread.c: `void pthread_mean()`
  - 198: `tid = (pthread_t *)MALLOC(num_procs * sizeof(pthread_t))`
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

At runtime, `IOT instruction (core dumped)`

Stack trace: `dlmalloc:mspace_malloc()`が原因か
```
#0  __pthread_kill_implementation (threadid=<optimized out>, signo=signo@entry=6, no_tid=no_tid@entry=0) at pthread_kill.c:44
#1  0x00007f37db82b6b3 in __pthread_kill_internal (signo=6, threadid=<optimized out>) at pthread_kill.c:78
#2  0x00007f37db7db958 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#3  0x00007f37db7c553d in __GI_abort () at abort.c:79
#4  0x000000000051abec in mspace_malloc ()
#5  0x000000000051f22c in insert_sorted ()
#6  0x0000000000520005 in getlinks ()
#7  0x00007f37db8298fd in start_thread (arg=<optimized out>) at pthread_create.c:442
#8  0x00007f37db8aba60 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
```

### matrix_multiply

At runtime, `bus error (core dumped)`
