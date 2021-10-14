# benchmark
* [google-benchmark](https://github.com/google/benchmark)
  * [Going Nowhere Faster](https://www.youtube.com/watch?v=2EWejmkKlxs&index=127&list=PLHTh1InhhwT6bwIpRk0ZbCA0N2p1taxd6&t=0s) 
* [Stabilizer](https://github.com/ccurtsinger/stabilizer)
# profile
* `drltrace`
  * edit filter.config, \[whitelist]\[blacklist]
* `ltrace` or `strace`
* `valgrind --tool=callgrind`
  * `kcachegrind` to analysis 
* `perf record`
  * `perf report` to analysis 
* `perf stat -e `
* [coz](https://github.com/plasma-umass/coz), which is a causal profiler.
  * [Coz: Finding Code that Counts with Causal Profiling (pdf)](http://arxiv.org/pdf/1608.03676v1.pdf)

# troubleshooting
* hyper-v
  * win 10 should close the hyper-v for the vmware.
    * `bcdedit /set hypervisorlaunchtype off`
    * vmware version > 15.5.5
 
