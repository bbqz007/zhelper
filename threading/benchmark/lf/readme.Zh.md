# Overview
`deque0`基础版本，所有的读线程与所有的写线程使用一个锁`qlock`互斥访问queue

`deque`同一时刻只有一个读线程与一个写线程使用一个锁`qlock`互斥访问queue，所有的读线程在`rlock`的等待队列成为follower，所有的写线程在`wlock`的等待队列成为follower。

`ypipe`与`deque`版本基本相同，queue应用了ypipe

`_lf`后缀为LeaderFollowers的实现版本，读线程池实现成LeaderFollowers。读线程使用`rlock`互斥访问LF状态，条件变量`can_lead`用作followers等待队列。

`_lf_s`后缀，在`_lf`后缀的版本的基础上，读线程使用spinlock。

# affine
内存亲和性模拟
1. HSHA，写线程产生一个消息，读线程访问这个消息，消息不在L3内
