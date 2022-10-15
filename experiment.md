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

| Bench          | Lang | kLOC  | Build   | Test    | Time(native) [s] | Time(no protection targets) [s] | Time(unaligned region only) [s] | Time(2-region protection) [s] |
| -------------- | :--: | ----: | :-----: | :-----: | ---------------: | ------------------------------: | ------------------------------: | ---------------------------:  |
| 470.lbm        |  c   | 0.9   | &check; | &check; | 39.48            |  96.29 (+143.9%)                | 485.54 (+1117.1%)               | 157.32 (+294.4%)              |
| 429.mcf        |  c   | 1.5   | &check; | &cross; | 21.15            |  29.84  (+41.1%)                |                                 |                               |
| 462.libquantum |  c   | 2.6   | &check; | &check; | 3.97             |   9.81 (+147.3%)                |  14.42  (+263.6%)               |  10.79 (+172.0%)              |
| 401.bzip2      |  c   | 5.7   | &check; | &check; | 93.01            | 182.00  (+95.7%)                | 244.99  (+163.4%)               | 233.58 (+151.1%)              |
| 433.milc       |  c   | 9.6   | &check; | &cross; | 38.93            |  50.42  (+29.5%)                |                                 |                               |
| 458.sjeng      |  c   | 10.5  | &check; | &check; | 192.10           | 381.66  (+98.7%)                | 443.66  (+130.9%)               | 389.60 (+102.8%)              |
| 482.sphinx3    |  c   | 13.1  | &cross; |         | 18.54            |  32.80  (+76.9%)                |                                 |                               |
| 456.hmmer      |  c   | 20.7  | &check; | &check; | 155.35           | 323.97 (+108.5%)                | 365.27  (+135.1%)               | 331.67 (+113.5%)              |
| 464.h264ref    |  c   | 36.1  | > 12h   |         | 169.99           | 380.70 (+124.0%)                |                                 |                               |
| 400.perlbench  |  c   | 126.4 | > 48h   |         | 28.03            |  69.03 (+146.3%)                |                                 |                               |
| 445.gobmk      |  c   | 157.6 |         |         | 152.58           | 319.20 (+109.2%)                |                                 |                               |
| 403.gcc        |  c   | 235.8 |         |         | 1.42             |   2.66  (+87.1%)                |                                 |                               |

\* 5回の実行時間の平均
