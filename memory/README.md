## a slab allocator.
it has many slab pools of different sizes based 2^.

it does not help you save memory, but avoid memory loose.

each slab pool has independent synchronours lock and quota, which can be configured by template params.

each slab do stats for lack, active, peak, require.

when a slab pool runs out, fall back to malloc/free.

it is helpfull for short-term usage of memories in multi-threading.

it is **not** a full solution for every thing.

there is a use-case sample of sqlite3's mem_methods implement at zhelper/db/sqlite3.

## be careful
you should not use it to overload the global new/delete.

slab allocator is using std containers, which will call new during allocator's constructure.

that would call the singleton instance many times during allocator's constructure, and cause dead lock.

solution 1:

replace all the std container with your implement using malloc/free.

solution 2:

you control the new/delete function does not use allocator until it complete constructure by using a global bool.
