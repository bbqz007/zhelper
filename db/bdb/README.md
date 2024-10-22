db_cxx.h is a wrapper of c apis in db.h.

zdb_cxx.h is a wrapper of db_cxx.h on high level.

this is a helper header helps you easier write program with db_cxx.h regardless of the complex flags of document.

every usage of flags is wrapped as human readable method.

**DbEnvBulider**, **DbBuilder**, **DbIndexBuilder** help you configure settings, and open DbEnv, Db, Index.

**KVt**, **KBulk**, **VBulk**, **KVBulk**, **IRt** help you easier use low-level kv binding, memory manage, accession, etc.

**ScopeDbc** help you manage cursor in local scope.

**DbGet**, **DbPut**, **DbcGet**, **DbcPut**, **DbcDupPut**, **DbCount** help you operato db or dbc via meaningful methods rather than flags, 


### db-source
* https://zeroc.com/ice/downloads/archive/ice/3.4.2
		* https://download.zeroc.com/Ice/3.4/db48-4.8.30-1ice.src.rpm
