a benchmark for leader-follower threading model.

it essentially has two wait queues.

one is message wait queue or event-poller

the other is follower wait queue.

the benefit is that it limits the number of threads which race to access message queue. although the old usage of lf is to avoid the buffer memory copied from socket from re-caching to cpu. nowadays it is commonly used for disaptch executions taking context.

at first, i assume you are unstanding what futexes are. mutexes and condition_variables are essential wait queues.

there is a basical threading model `deque0`, all the readers and writers use one lock to synchronously access message queue. message queue use one condition variable notify readers.

there is a lf threading model `deque_lf`, using another condition variable to implement follower wait queue.

there is a lf-like threading model `deque`, using rlock to implement follower wait queue.

there is a best threading model `ypipe`, using ypipe which is a core part of zeromq and let a reader and a writer access message queue parallely.

