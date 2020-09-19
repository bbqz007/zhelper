#include "zdb_cxx.h"
#include <iostream>

typedef enum
{
    health = 0,
    woody,
    poison,
    dying,
    dead,
    max
} state_t;

struct record_t
{
    void zero() { memset(this, 0, sizeof(*this)); }
    record_t() { zero(); }
    struct key_t
    {
        int id;
    } key_;
    struct data_t
    {
        union {
            int64_t name_iraw;
            char name[8];
        };
        u_int32_t hp;
        u_int32_t mp;
        u_int32_t ap;
        u_int32_t dp;
        u_int32_t exp;
        u_int32_t level;
        state_t state;
    } data_;
};


using namespace std;
using namespace zhelper;

char names[][8] = {
    "one", "two", "three", "four", "five",
    "six", "seven", "eight", "nine", "ten",
    "cat", "dog", "bird", "shark", "snake",
    "apple", "banana", "orange"
};

int get_name_fcn(Db *index, const Dbt *pkey, const Dbt *pdata, Dbt *idxres)
{
    DbtAccessor<record_t::data_t> record(*pdata);
    IRt ir(*idxres);
    ir.bind(record->name);
    return 0;
}

int refill_foreigndb(Db& foreign)
{
    int err;
    KVt kv;
    u_int32_t count = 0;
    foreign.truncate(NULL, &count, 0);
    for (int i = 0; i < sizeof(names) / sizeof(int64_t); ++i)
    {
        kv.bind_key(names[i]);
        kv.bind_data(names[i]);
        err = DbPut::put(foreign, kv);
        if (err)
            cout << foreign.get_env()->strerror(err) << endl;
    }
}

void gen_new_rec(record_t& rec, int id)
{
    static size_t kmax = sizeof(names) / sizeof(int64_t);
    rec.key_.id = id;
    rec.data_.name_iraw = *(int64_t*)names[ id % kmax ];
    rec.data_.ap = rand() % 100;
    rec.data_.hp = 100;
    rec.data_.dp = rand() % 100;
    rec.data_.exp = rand();
    rec.data_.level = rand() % 10;
    rec.data_.mp = 100;
    rec.data_.state = (state_t)(rand() % state_t::max);
}

int refill_primarydb(Db& primary)
{
    int err;
    KVt kv;
    record_t new_rec;
    kv.bind_key(new_rec.key_);
    kv.bind_data(new_rec.data_);
    u_int32_t count = 0;
    primary.truncate(NULL, &count, 0);
    for (int i = 0; i < 100; ++i)
    {
        gen_new_rec(new_rec, i);
        err = DbPut::put(primary, kv);
        if (err)
            cout << primary.get_env()->strerror(err) << endl;
    }
}

typedef int (*help_build)(DbIndexBuilder&, Db&, Db&, Db&);
int help_build_unique_bt(DbIndexBuilder& builder, Db& index, Db& primary, Db& foreign)
{
    return builder.openBtreeIndex(index, NULL, "idx-bt-unique", primary, foreign);
}
int help_build_dup_bt(DbIndexBuilder& builder, Db& index, Db& primary, Db& foreign)
{
    return builder.openBtreeDuplicateIndex(index, NULL, "idx-bt-dup", primary, foreign);
}
int help_build_dupsort_bt(DbIndexBuilder& builder, Db& index, Db& primary, Db& foreign)
{
    return builder.openBtreeDupSortIndex(index, NULL, "idx-bt-dupsort", primary, foreign);
}
int help_build_unique_hash(DbIndexBuilder& builder, Db& index, Db& primary, Db& foreign)
{
    return builder.openHashIndex(index, NULL, "idx-hash-unique", primary, foreign);
}
int help_build_dup_hash(DbIndexBuilder& builder, Db& index, Db& primary, Db& foreign)
{
    return builder.openHashDuplicateIndex(index, NULL, "idx-hash-dup", primary, foreign);
}
int help_build_dupsort_hash(DbIndexBuilder& builder, Db& index, Db& primary, Db& foreign)
{
    return builder.openHashDupSortIndex(index, NULL, "idx-hash-dupsort", primary, foreign);
}

int sample(DbEnvBuilder& ebuilder, DbIndexBuilder& index_builder, DbBuilder& primary_builder,
           DbBuilder& foreign_builder, help_build help_open_index)
{
    bool verbose = true;
    int err = 0;
    DbEnv dbenv( DB_CXX_NO_EXCEPTIONS );
    err = ebuilder.open(dbenv);
    if (err)
        cout << dbenv.strerror(err) << endl;
    Db primarydb(&dbenv,  DB_CXX_NO_EXCEPTIONS );
    Db foreigndb(&dbenv,  DB_CXX_NO_EXCEPTIONS );
    Db indexdb(&dbenv,  DB_CXX_NO_EXCEPTIONS );
    primary_builder.openBtreePrimaryDb(primarydb, NULL, "primary");
    foreign_builder.openBtreeForeignDb(foreigndb, NULL, "foreign-constrain");

    refill_primarydb(primarydb);
    refill_foreigndb(foreigndb);

    err = help_open_index(index_builder, indexdb, primarydb, foreigndb);
    if (err)
        cout << dbenv.strerror(err) << endl;

    struct lambda
    {
        static void check(Db& primarydb, Db& foreigndb, Db& indexdb)
        {
            cout << "primary has " << DbCount::key_count(primarydb) << " keys and "
                    << DbCount::data_count(primarydb) << " records" << endl;
            cout << "foreign has " << DbCount::key_count(foreigndb) << " keys and "
                    << DbCount::data_count(foreigndb) << " records" << endl;
            cout << "index has " << DbCount::key_count(indexdb) << " keys and "
                    << DbCount::data_count(indexdb) << " records" << endl;
        }
        static void check(Db& indexdb)
        {
            KVt kv;
            db_recno_t count = 0;
            int64_t name_iraw = *(int64_t*)names[0];
            kv.bind_key(name_iraw);
            kv.build_realloc_data();
            ScopeDbc dbc(NULL, indexdb);
            DbcGet::get(dbc, kv, DB_SET);
            {
                DbtAccessor<record_t::data_t> data(kv.ref_data());
                dbc->count(&count, 0);
                cout << "index at key : " <<  data->name << " has " << count << " dups" << endl;
            }
            name_iraw = *(int64_t*)names[1];
            kv.bind_key(name_iraw);
            kv.build_realloc_data();
            DbcGet::get(dbc, kv, DB_SET);
            {
                DbtAccessor<record_t::data_t> data(kv.ref_data());
                dbc->count(&count, 0);
                cout << "index at key : " <<  data->name << " has " << count << " dups" << endl;
            }
        }
    };
    cout << "---" << "OPEN INDEX" << "---" << endl;
    lambda::check(primarydb, foreigndb, indexdb);

    KVt kv;
    record_t record;
    record.key_.id = 101;
    record.data_.name_iraw = *(int64_t*)names[0];
    kv.bind_key(record.key_);
    kv.bind_data(record.data_);
    err = DbPut::put(primarydb, kv);
    if (err)
        cout << dbenv.strerror(err) << endl;


    lambda::check(indexdb);

    record.data_.name_iraw = *(int64_t*)"1234567";
    err = DbPut::put(primarydb, kv);
    if (err)
        cout << dbenv.strerror(err) << endl;

    record.data_.name_iraw = *(int64_t*)names[1];
    err = DbPut::put(primarydb, kv);
    if (err)
        cout << dbenv.strerror(err) << endl;

    lambda::check(indexdb);

    cout << "---" << "UPDATE INDEX" << "---" << endl;
    lambda::check(primarydb, foreigndb, indexdb);

    indexdb.close(0);
    primarydb.close(0);
    foreigndb.close(0);
    dbenv.close(0);
    return 0;
}

int main()
{
    DbEnvMutableBuilder ebuilder;
    DbMutableBuilder primary_builder;
    DbMutableBuilder foreign_builder;
    DbIndexMutableBuilder index_builder;
    ebuilder.init_subsys_mpool().init_subsys_log().init_subsys_txn();
    ebuilder.set_home_dir("./dbenv").ensure_home_dir();
    primary_builder.set_filename("db2");
    foreign_builder.set_filename("db2");
    index_builder->set_filename("db2");
    index_builder.set_buildup_index_if_empty()
    .set_abort_while_foreign_deletion()
    .set_get_field_fcn(get_name_fcn)
    .set_index_truncate_before_associate();
    sample(ebuilder, index_builder, primary_builder, foreign_builder, help_build_unique_bt);
    sample(ebuilder, index_builder, primary_builder, foreign_builder, help_build_dup_bt);
    sample(ebuilder, index_builder, primary_builder, foreign_builder, help_build_dupsort_bt);
    sample(ebuilder, index_builder, primary_builder, foreign_builder, help_build_unique_hash);
    sample(ebuilder, index_builder, primary_builder, foreign_builder, help_build_dup_hash);
    sample(ebuilder, index_builder, primary_builder, foreign_builder, help_build_dupsort_hash);
    return 0;
}
