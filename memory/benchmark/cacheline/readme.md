https://www.nexthink.com/blog/smarter-cpu-testing-kaby-lake-haswell-memory/

内存地址空间三级目录，pgd pmd pte。page table 一页4kb包含64个pte。

cacheline除了加载个地址的数据，还要加载这个地址的所在的page table用作LTB。

如果数据的地址相距16mb，就要加载新的一页LTB。

所以一段逻辑代码，访问的数据在16mb以内。
