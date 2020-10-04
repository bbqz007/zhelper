a benchmark for leader-follower threading model.

it essentially has two wait queues.

one is message wait queue or event-poller

the other is follower wait queue.

the benefit is that it limits the number of threads which race to access message queue. although the old usage of lf is to avoid the buffer memory copied from socket from re-caching to cpu. nowadays it is commonly used for disaptch executions taking context.

at first, i assume you are unstanding what futexes are. mutexes and condition_variables are essential wait queues.

