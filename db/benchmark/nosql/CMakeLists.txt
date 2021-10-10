set (lvldbdir ..)
set (lvldbbuild ${lvldbdir}/../build)

include_directories(/usr/include
		${lvldbdir}/include
		${lvldbdir}
                    .)

set(lvldbsrc ${lvldbdir}/util/histogram.cc
        ${lvldbdir}/util/histogram.h
        ${lvldbdir}/util/testutil.cc
        ${lvldbdir}/util/testutil.h)
        
find_library(lvldblib libleveldb.a PATH ${lvldbbuild} NO_DEFAULT_PATH)
get_filename_component(lvldblib_abs ${lvldblib} ABSOLUTE)
        
add_executable(db_bench_bdb db_bench_bdb.cc
                ${lvldbsrc})
add_executable(db_bench_bdb2 db_bench_bdb2.cc
                ${lvldbsrc})
add_executable(db_bench_sqlite3_2 db_bench_sqlite3.cc
                ${lvldbsrc})

target_link_libraries(db_bench_bdb -ldb -pthread ${lvldblib_abs})
target_link_libraries(db_bench_bdb2 -ldb -pthread ${lvldblib_abs})
target_link_libraries(db_bench_sqlite3_2 -lsqlite3 -pthread  ${lvldblib_abs})
