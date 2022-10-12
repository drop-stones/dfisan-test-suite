# Results of experiments

## Environment

- Virtual Machine: VMWare Fusion
- OS: Ubuntu 20.04.1
- CPU model: Intel(R) Core(TM) i7-1068NG7 CPU @ 2.30GHz
- CPU Core: 6
- Memory: 24GB
- Architecture: x86_64

## SPEC2006

計装コード
- 保護データへのアクセス: 関数呼び出しを挿入
  - ```c
    int key __attribute__((annotate("dfi_protection")));
    key = 100;
    _aligned_set(&key, L.2);    // function call

    _aligned_check(&key, L.2);  // function call
    key;
    ```
- 非保護データへのアクセス: アドレスのチェックを挿入
  - ```c
    int *p = &unsafe;
    if (AddrInSafeRegion(p)) {
      ReportError(p);
      exit(1);
    }
    p;
    ```

| Bench          | Lang | kLOC  | Build   | Test    | Time(native) [s] | Time(no protection targets) [s] | Time(2-region protection) [s] | Time(unaligned region only) [s] |
| -------------- | :--: | ----: | :-----: | :-----: | ---------------: | ------------------------------: | ---------------------------:  | ------------------------------: |
| 470.lbm        |  c   | 0.9   | &check; | &check; | 49.11            | 104.62                          | 446.75                        | 1102.58                         |
| 429.mcf        |  c   | 1.5   | &check; | &cross; | 23.17            | 32.52                           |                               |                                 |
| 462.libquantum |  c   | 2.6   | &check; | &check; | 4.06             | 11.17                           | 36.57                         | 101.31                          |
| 401.bzip2      |  c   | 5.7   | &check; | &check; | 110.32           | 198.53                          | 416.95                        | 454.69                          |
| 433.milc       |  c   | 9.6   | &check; | &cross; | 43.34            | 52.02                           |                               |                                 |
| 458.sjeng      |  c   | 10.5  | &check; | &check; | 219.61           | 422.48                          | 426.09                        | 432.20                          |
| 482.sphinx3    |  c   | 13.1  | &cross; |         | 19.47            | 36.30                           |                               |                                 |
| 456.hmmer      |  c   | 20.7  | &check; | &check; | 173.80           | 354.03                          | 354.65                        | 366.98                          |
| 464.h264ref    |  c   | 36.1  | > 12h   |         | 193.59           | 480.31                          |                               |                                 |
| 400.perlbench  |  c   | 126.4 | > 48h   |         | 31.25            | 74.81                           |                               |                                 |
| 445.gobmk      |  c   | 157.6 |         |         | 173.80           | 358.30                          |                               |                                 |
| 403.gcc        |  c   | 235.8 |         |         | 4.06             | 3.12                            |                               |                                 |
