## a slab allocator.
it has many slab pools of different sizes based 2^.

it does not help you save memory, but avoid memory loose.

each slab pool has independent synchronours lock and quota, which can be configured by template params.

each slab do stats for lack, active, peak, require.

when a slab pool runs out, fall back to malloc/free.

it is helpfull for short-term usage of memories in multi-threading.

it is **not** a full solution of every thing.

there is a use-case sample of sqlite3's mem_methods implement at zhelper/db/sqlite3.