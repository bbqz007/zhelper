a benchmark for leader-follower threading model.

it essentially has two wait queues.

one is message wait queue or event-poller

the other is follower wait queue.

the benefit is that it limits the number of threads which race to access message queue. although the old usage of lf is to avoid the buffer memory copied from socket from re-caching to cpu. nowadays it is commonly used for disaptch executions taking context.

at first, i assume you are unstanding what futexes are. mutexes and condition_variables are essential wait queues.

benchmark models use 10 threads to produce message and other 10 threads to consume. each thread deals with 10k messages, there is 100k messages in total.

there is a basical threading model `deque0`, all the readers and writers use one lock to synchronously access message queue. message queue use one condition variable notify readers.

there is a LF threading model `deque_lf`, using another condition variable to implement follower wait queue. the `deque_lf_s` is a version use spinlock to avoid followers from sleeping before waiting for
condition.

there is a LF threading model `deque2_lf`, using double queue to reduce the race condition of queue between writer and reader. there is a `deque2_lf_s` version as well.

there is a LF-like threading model `deque`, using rlock to implement follower wait queue.

there is a best threading model `ypipe`, using ypipe which is a core part of zeromq and let a reader and a writer access message queue parallely.

finally there is a LF threading model `ypipe_lf`, using ypipe and lf threading model. could ypipe enhance lf threads, or could lf threading model fits ypipe. could they two together bring more performance? 

the cpu cycles are nearly the same, google benchmark do not count cycles for customer spawn threads.

the wall time are much different. wall time shows how much time to finish a specified amount of messages (produce and consume) in one threading model, including the waste for waiting and blocking.

`yield0` model shows yielding in single threading.

`cvnotify0` model shows condition varaiable notify in single threading.

`yield` model shows yielding in multi-threading.

`yield2` model shows condition varaiable notify in multi-threading.

a single thread yield 10k times in multi-cores platform, it is more expensive than multi threads either yields 10k times. 

condition variable notify perform poorly in multi parallel threads.

### workload
test a threading model which applying to empty workloads, it has no sence. 

i add two kind of workloads.
1. computing only, and random cycles.
2. mock real user logic (may access redis, rpc, sql database, or local critical resources) to block.

### test platform
1. i5 450m, year 2010 (10 yrs before today, 10 yrs after lf pattern), 2 cores(4 threads)@2.4ghz, 3MB L3 cache.
2. mkt mt6797, 3 clusters arm cpu, no L3 cache, cores share L2 cache in same cluster.
when lf pattern was created, there was not multi-core platform but only multi-cpu platform.

### background
lf pattern is created before year 2000, when xeon was under p3 arch. a first dual core cpu is released by ibm at 2001. 
