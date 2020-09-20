10k -> /dev/shm/file (auto trans)
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 92.31    0.460904           5    100007           fdatasync
  3.62    0.018079           0    900056           fcntl
  1.80    0.008974           0    200581           pwrite64
  1.02    0.005085           0    200046    200037 newfstatat
  0.96    0.004797           0    200583           pread64
  0.29    0.001435           0    100033           fstat
  0.00    0.000000           0         2           getcwd
  0.00    0.000000           0         1           unlinkat
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0         1           fchown
  0.00    0.000000           0       126       105 openat
  0.00    0.000000           0        21           close
  0.00    0.000000           0        16           read
  0.00    0.000000           0        52           write
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         1           geteuid
  0.00    0.000000           0        13           brk
  0.00    0.000000           0         3           munmap
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        49           mmap
  0.00    0.000000           0        32           mprotect
------ ----------- ----------- --------- --------- ----------------
100.00    0.499274               1701633    200143 total
```
10k -> :memory: (auto trans)
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0       122       105 openat
  0.00    0.000000           0        17           close
  0.00    0.000000           0        16           read
  0.00    0.000000           0        51           write
  0.00    0.000000           0        19        16 newfstatat
  0.00    0.000000           0        17           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         3           munmap
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        49           mmap
  0.00    0.000000           0        32           mprotect
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000                   339       122 total
```
10k -> "" (auto trans)
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  0.00    0.000000           0         1           unlinkat
  0.00    0.000000           0         3         2 faccessat
  0.00    0.000000           0       123       105 openat
  0.00    0.000000           0        18           close
  0.00    0.000000           0        16           read
  0.00    0.000000           0        51           write
  0.00    0.000000           0       183           pread64
  0.00    0.000000           0       556           pwrite64
  0.00    0.000000           0        20        16 newfstatat
  0.00    0.000000           0        18           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0        23           brk
  0.00    0.000000           0         3           munmap
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        49           mmap
  0.00    0.000000           0        32           mprotect
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000                  1105       123 total
```
10k -> "" journal-memory (auto trans)
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 97.45    0.001145         382         3           munmap
  2.55    0.000030           0       556           pwrite64
  0.00    0.000000           0         1           unlinkat
  0.00    0.000000           0         3         2 faccessat
  0.00    0.000000           0       123       105 openat
  0.00    0.000000           0        18           close
  0.00    0.000000           0        16           read
  0.00    0.000000           0        52           write
  0.00    0.000000           0       183           pread64
  0.00    0.000000           0        20        16 newfstatat
  0.00    0.000000           0        18           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0        13           brk
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        49           mmap
  0.00    0.000000           0        32           mprotect
------ ----------- ----------- --------- --------- ----------------
100.00    0.001175                  1096       123 total
```
10k -> file:?mode=memory (auto trans)
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 94.64    6.493145          16    400012           fdatasync
  2.04    0.139629           1    100003           unlinkat
  1.32    0.090389           0    200130       105 openat
  1.15    0.079137           0   1000595           pwrite64
  0.32    0.022192           0    900051           fcntl
  0.20    0.013818           0    400051    200035 newfstatat
  0.09    0.006235           0    200025           close
  0.09    0.005994           0    301157           pread64
  0.08    0.005456           0    100003           fchown
  0.06    0.003864           0    200035           fstat
  0.02    0.001241           0    100003           geteuid
  0.00    0.000000           0         2           getcwd
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0        16           read
  0.00    0.000000           0        51           write
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0        13           brk
  0.00    0.000000           0         3           munmap
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        49           mmap
  0.00    0.000000           0        32           mprotect
------ ----------- ----------- --------- --------- ----------------
100.00    6.861100               3902241    200141 total
```
10k -> file (batch, 1 trans)
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 99.44    0.010000         556        18           fdatasync
  0.56    0.000056           0       823           pread64
  0.00    0.000000           0         2           getcwd
  0.00    0.000000           0        60           fcntl
  0.00    0.000000           0         4           unlinkat
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0         4           fchown
  0.00    0.000000           0       132       105 openat
  0.00    0.000000           0        26           close
  0.00    0.000000           0        16           read
  0.00    0.000000           0        51           write
  0.00    0.000000           0       607           pwrite64
  0.00    0.000000           0        53        37 newfstatat
  0.00    0.000000           0        36           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         4           geteuid
  0.00    0.000000           0         9           brk
  0.00    0.000000           0         3           munmap
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        49           mmap
  0.00    0.000000           0        32           mprotect
------ ----------- ----------- --------- --------- ----------------
100.00    0.010056                  1939       143 total
```
