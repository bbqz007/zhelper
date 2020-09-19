#include "zdb_cxx.h"
#include <iostream>

using namespace std;
using namespace zhelper;
typedef int (*help_build)(DbBuilder&, Db&);
int help_build_unique_bt(DbBuilder& builder, Db& db)
{
    return builder.openBtreeDb(db, NULL, "bt-unique");
}
int help_build_dup_bt(DbBuilder& builder, Db& db)
{
    return builder.openBtreeDuplicateDb(db, NULL, "bt-dup");
}
int help_build_dupsort_bt(DbBuilder& builder, Db& db)
{
    return builder.openBtreeDupSortDb(db, NULL, "bt-dupsort");
}
int help_build_unique_hash(DbBuilder& builder, Db& db)
{
    return builder.openHashDb(db, NULL, "hash-unique");
}
int help_build_dup_hash(DbBuilder& builder, Db& db)
{
    return builder.openHashDuplicateDb(db, NULL, "hash-dup");
}
int help_build_dupsort_hash(DbBuilder& builder, Db& db)
{
    return builder.openHashDupSortDb(db, NULL, "hash-dupsort");
}
int sample(DbEnvBuilder& ebuilder, DbBuilder& builder, help_build help_open_db)
{
    // what does this sample do
    // 1. open a db, and truncate it
    // 2. from 0 to 100, put 5 every single data for each key.
    // 3. from 100 to 120, put batch using key bulk and data bulk
    // 4. from 120 to 140, put batch using keydata bulk
    // 5. reopen the db, try many conflict puts at keys between 4 and 8.
    // 6. open a cursor
    // 7. traversal all records, one by one.
    // 8, traversal all records, every time by all dups for each key.
    // 9. traversal all records, every time by prefetching many records.

    bool verbose = true;
    int err = 0;
    DbEnv dbenv( DB_CXX_NO_EXCEPTIONS );
    err = ebuilder.open(dbenv);
    if (err)
        cout << dbenv.strerror(err) << endl;
    Db db(&dbenv,  DB_CXX_NO_EXCEPTIONS );
    err = help_open_db(builder, db);
    if (err)
        cout << dbenv.strerror(err) << endl;

    u_int32_t count = 0;
    db.truncate(NULL, &count, 0);
    if (err)
        cout << dbenv.strerror(err) << endl;

    int ikey, idata;
    KVt kv;
    kv.bind_key(ikey);
    kv.bind_data(idata);
    for (int i = 0; i < 100; ++i)
    {
        ikey = i;
        idata = i;
        for (int j = i; j < i + 5; ++j)
        {
            idata = j;
            err = DbPut::put(db, kv);
            if (err)
                cout << dbenv.strerror(err) << " at " << ikey << "/" << idata << endl;
        }
    }
    KBulk kbulk; //kbulk.reserve_and_attach_itself(1024);
    VBulk vbulk; //vbulk.reserve_and_attach_itself(1024);
    for (int i = 100; i < 120; ++i)
    {
        ikey = i;
        for (int j = i; j < i + 5; ++j)
        {
            idata = j;
            if (!kbulk.append(ikey) || !vbulk.append(idata))
            {
                err = DbPut::put_batch(db, kbulk, vbulk);
                if (err)
                    cout << "put_batch " << dbenv.strerror(err) << endl;
                err = DbPut::put_batch(db, kbulk, vbulk);
                if (err)
                    cout << "put_batch 2nd " << dbenv.strerror(err) << endl;
                err = DbPut::put_batch_ignore_dupsort_data(db, kbulk, vbulk);
                if (err)
                    cout << "put_batch_ignore_dup_data " << dbenv.strerror(err) << endl;
                kbulk.flush();
                vbulk.flush();
                kbulk.append(ikey);
                vbulk.append(idata);
            }
        }
    }
    err = DbPut::put_batch(db, kbulk, vbulk);
    if (err)
        cout << dbenv.strerror(err) << endl;

    KVBulk kvbulk;
    for (int i = 120; i < 140; ++i)
    {
        ikey = i;
        for (int j = i; j < i + 5; ++j)
        {
            idata = j;
            if (!kvbulk.append(ikey, idata))
            {
                err = DbPut::put_batch_using_keybulk(db, kvbulk);
                if (err)
                    cout << "put_batch_key " << dbenv.strerror(err) << endl;
                err = DbPut::put_batch_using_keybulk(db, kvbulk);
                if (err)
                    cout << "put_batch_key 2nd " << dbenv.strerror(err) << endl;
                err = DbPut::put_batch_using_keybulk_ignore_dupsort_data(db, kvbulk);
                if (err)
                    cout << "put_batch_key_ignore_dup_data " << dbenv.strerror(err) << endl;
                kvbulk.flush();
                kvbulk.append(ikey, idata);
            }
        }
    }
    err = DbPut::put_batch_using_keybulk(db, kvbulk);
    if (err)
        cout << dbenv.strerror(err) << endl;

    db.close(0);

    Db db2(&dbenv,  DB_CXX_NO_EXCEPTIONS );
    help_open_db(builder, db2);

    ikey = 4;
    idata = 5;
    err = DbPut::put(db2, kv);
    if (err)
        cout << "put " << dbenv.strerror(err) << endl;
    ikey++;
    idata++;
    err = DbPut::put_if_key_not_exists(db2, kv);
    if (err)
        cout << "put_if_not_exists " << dbenv.strerror(err) << endl;
    ikey++;
    idata++;
    err = DbPut::put_against_dupsort_data(db2, kv);
    if (err)
        cout << "put_against_dup_data " << dbenv.strerror(err) << endl;
    ikey++;
    idata++;
    err = DbPut::put_ignore_dupsort_data(db2, kv);
    if (err)
        cout << "put_ignore_dup_data " << dbenv.strerror(err) << endl;

    Dbc* dbcp = NULL;
    err = db2.cursor(NULL, &dbcp, 0);
    if (err)
        cout << dbenv.strerror(err) << endl;
    else
    {
        Dbc& dbc = *dbcp;
        KVt kv;
        kv.build_realloc_key();
        kv.build_realloc_data();
        err = DbcGet::first(dbc, kv);
        if (!err)
        {
            do
            {
                DbtAccessor<int> ikey(kv.ref_key());
                DbtAccessor<int> idata(kv.ref_data());
                if (verbose)
                    cout << *ikey << "/" << *idata << endl;
                err = DbcGet::next(dbc, kv);
                if (err)
                    cout << dbenv.strerror(err) << endl;
            } while (!err);
        }
        VBulk vbulk;
        KVBulk kvbulk;
        vbulk.reserve_get_and_attach_itself(0);
        kvbulk.reserve_get_and_attach_itself(0);
        kv.build_realloc_key();
        err = DbcGet::get_multiple_at_first_key(dbc, kv.key(), kvbulk);
        if (!err)
        {
            do
            {
                kv.zero_key();
                DbtAccessor<int> ikey(kv.ref_key());
                DbtAccessor<int> idata(kv.ref_data());
                kvbulk.begin_iter();
                while(kvbulk.next(kv.ref_key(), kv.ref_data()))
                {
                    int k = *ikey;
                    int v = *idata;
                    if (verbose)
                        cout << *ikey << "/" << *idata << endl;
                }

                kv.build_realloc_key();
                err = DbcGet::get_multiple_at_next_key(dbc, kv.key(), kvbulk);
                if (err)
                    cout << dbenv.strerror(err) << endl;
            } while (!err);
        }

        kv.build_realloc_key();
        err = DbcGet::get_dups_at_first_key(dbc, kv.key(), vbulk);
        if (!err)
        {
            do
            {
                DbtAccessor<int> ikey(kv.ref_key());
                DbtAccessor<int> idata(kv.ref_data());
                vbulk.begin_iter();
                while(vbulk.next(kv.ref_data()))
                {
                    int k = *ikey;
                    int v = *idata;
                    if (verbose)
                        cout << *ikey << "/" << *idata << endl;
                }

                err = DbcGet::get_dups_at_next_key(dbc, kv.key(), vbulk);
                if (err)
                    cout << dbenv.strerror(err) << endl;
            } while (!err);
        }

    }
    db2.close(0);
    dbenv.close(0);

    return 0;
}

int main()
{
    DbEnvMutableBuilder ebuilder;
    DbMutableBuilder builder;
    ebuilder.init_subsys_mpool().init_subsys_log().init_subsys_txn();
    ebuilder.set_home_dir("./dbenv").ensure_home_dir();
    builder.set_filename("db1");
    sample(ebuilder, builder, help_build_unique_bt);
    sample(ebuilder, builder, help_build_dup_bt);
    sample(ebuilder, builder, help_build_dupsort_bt);
    sample(ebuilder, builder, help_build_unique_hash);
    sample(ebuilder, builder, help_build_dup_hash);
    sample(ebuilder, builder, help_build_dupsort_hash);
    return 0;
}
