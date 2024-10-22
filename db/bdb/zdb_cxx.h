#ifndef __Z_DB_CXX_H__
/**
MIT License 
 
Copyright (c) 2020 bbqz007 <cnblogs.com/bbqzsl, github.com/bbqz007> 
 
Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions: 
 
The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software. 
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/
#ifdef _WIN32
#define __NO_SYSTEM_INCLUDES
#define pthread_t uintptr_t
#define mkdir(path, ...) _mkdir(path)
#endif
#include "db_cxx.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <sys/unistd.h>
#else
#include <unistd.h>
#endif

#include <map>
#include <unordered_map>
#include <queue>
#include <vector>
#include <set>
namespace zhelper {

namespace concept {
using namespace std;
    template <typename key, typename data>
    class model_of_libdb
    {
        // mutex, without any thread lib, you can use spinlock in user sapce
        // lock, supports atomic locking many locks (, deadlock detection as well), and priority locks.
        typedef vector<pair<int, data> > queue;
        typedef map<int, data> recno;
        typedef map<key, data> btree;
        typedef map<key, vector<data> > btree_dup;
        typedef map<key, set<data> > btree_dupsort;
        typedef unordered_map<key, data> hash;
        typedef unordered_map<key, vector<data> > hash_dup;
        typedef unordered_map<key, set<data> > hash_dupsort;
        typedef pair<key, int64_t>& sequence;
        template<typename Map> class cursor : public Map::iterator {};
        auto get_set(btree db, key k, data& d)
        {
            auto it = db.find(k);
            d = it->second;
            return it;
        }
        auto get_set_range(btree db, key k, data& d)
        {
            auto it = db.lower_bound(k);
            d = it->second;
            return it;
        }
        int put(btree_dup db, key k, data d)
        {
            auto it = db.find(k);
            it->push_back(d);
        }
        int put(btree_dupsort db, key k, data d)
        {
            auto it = db.find(k);
            it->insert(d);
        }
    };
};

// usage:
// CrsrOpt().mix_multiple().next();
// CrsrOpt opt; opt.mix_multiple().next(); *opt;
class CrsrOpt
{
public:
	#define GETTER_DEFINATION(func, macro) \
	int func() { return tmpopt_ = DB_##macro; }
	GETTER_DEFINATION(first, FIRST)
	GETTER_DEFINATION(prev, PREV)
	GETTER_DEFINATION(prev_dup, PREV_DUP)
	GETTER_DEFINATION(prev_nodup, PREV_NODUP)
	GETTER_DEFINATION(set, SET)
	GETTER_DEFINATION(set_range, SET_RANGE)
	GETTER_DEFINATION(search_key, SET)
	GETTER_DEFINATION(lower_bound_key, SET_RANGE)
	GETTER_DEFINATION(get_both, GET_BOTH)
	GETTER_DEFINATION(get_both_range, GET_BOTH_RANGE)
	GETTER_DEFINATION(search_key_and_data, GET_BOTH)
	GETTER_DEFINATION(search_key_lower_bound_data, GET_BOTH_RANGE)
    GETTER_DEFINATION(current, CURRENT)
	GETTER_DEFINATION(next_nodup, NEXT_NODUP)
	GETTER_DEFINATION(next_dup, NEXT_DUP)
	GETTER_DEFINATION(next, NEXT)
	GETTER_DEFINATION(last, LAST)
	#undef GETTER_DEFINATION
	#define MIX_DEFINATION(func, macro) \
	CrsrOpt& mix_##func() { tmpopt_ |= DB_##macro; return *this; }
	MIX_DEFINATION(multiple, MULTIPLE)
	MIX_DEFINATION(multiple_key, MULTIPLE_KEY)
	#undef MIX_DEFINATION
	int operator * () { return tmpopt_; }
	int clear() { int tmp = tmpopt_; return tmp; }
private:
	int tmpopt_;
};

class scope_mem
{
public:
	scope_mem(size_t size)
		: size_(size)
	{
		priv_ = malloc(size);
	}
	~scope_mem()
	{
		free(priv_);
	}
	void* mem() { return priv_; }
	size_t size() { return size_; }
private:
	void* operator new (size_t);
	void* priv_;
	const size_t size_;
};

template<size_t Size>
class stack_mem
{
public:
	void* mem() { return priv_; }
	size_t size() { return Size; }
private:
	void* operator new(size_t);
	stack_mem(stack_mem&);
	void operator = (stack_mem&);
	char priv_[Size];
};

template<size_t Size>
struct nchar_tp
{
    typedef char type[Size];
    typedef type* pointer_type;
    typedef type& reference_type;
};




#define MINIMUM_BULK_LEN 16
#define MINIMUM_GET_BULK_LEN (1<<12)


class KVt
{
public:
	~KVt()
	{
		check_if_clear(key_);
		check_if_clear(data_);
	}
	Dbt* key() { return &key_; }
	Dbt* data() { return &data_; }
	Dbt& ref_key() { return key_; }
	Dbt& ref_data() { return data_; }
	template <class type>
	void bind_key(type& k)
	{
		check_if_clear(key_);
		key_.set_data(&k);
		key_.set_ulen(sizeof(k));	// Z#20241023, bug; when DB_DBT_USERMEM, ulen should be set. otherwise db.get() return DB_BUFFER_SMALL
		key_.set_size(sizeof(k));
		key_.set_flags(DB_DBT_USERMEM);
	}
	void bind_key(void* k, size_t size)
	{
		check_if_clear(key_);
		key_.set_data(k);
		key_.set_ulen(size);
		key_.set_size(size);
		key_.set_flags(DB_DBT_USERMEM);
	}
	void build_realloc_key()
	{
		check_if_clear(key_, true);
		key_.set_flags(DB_DBT_REALLOC);
	}
	template <class type>
	void bind_data(type& d)
	{
		check_if_clear(data_);
		data_.set_data(&d);
		data_.set_ulen(sizeof(d));
		data_.set_size(sizeof(d));
		data_.set_flags(DB_DBT_USERMEM);
	}
	void bind_data(void* d, size_t size)
	{
		check_if_clear(data_);
		data_.set_data(d);
		data_.set_ulen(size);
		data_.set_size(size);
		data_.set_flags(DB_DBT_USERMEM);
	}
	void build_realloc_data()
	{
		check_if_clear(data_, true);
		data_.set_flags(DB_DBT_REALLOC);
	}
	void zero_key()
	{
	    check_if_clear(key_);
	}
	void zero_data()
    {
        check_if_clear(data_);
    }
private:
	void check_if_clear(Dbt& dbt, bool reuse = false)
	{
		if (dbt.get_flags() & (DB_DBT_REALLOC | DB_DBT_MALLOC))
			if (dbt.get_data())
				if (!reuse)
					free(dbt.get_data());
				else
					return;
		dbt = Dbt();
	}
	template <class type>
	void bind_key(const type*);
	template <class type>
	void bind_data(const type*);
	Dbt key_;
	Dbt data_;
};

class IRt // index result
{
public:
    IRt(Dbt& attach) : res_(attach) {}
    template<class type>
    void bind(type& d)
    {
        res_.set_data(&d);
        res_.set_size(sizeof(d));
        res_.set_flags(DB_DBT_USERMEM);
    }
    void bind(void* d, size_t n)
    {
        res_.set_data(&d);
        res_.set_size(n);
        res_.set_flags(DB_DBT_USERMEM);
    }
    void copy(void* d, size_t n)
    {
        res_.set_flags(DB_DBT_APPMALLOC);
        void* p = malloc(n);
        memcpy(p, d, n);
        res_.set_data(p);
        res_.set_size(n);
    }
private:
    template<class type>
    void bind(const type*);
    IRt& operator= (const Dbt&);
    IRt();
    Dbt& res_;
};

template<class type>
class DbtAccessor
{
public:
    DbtAccessor(const Dbt& dbt) : dbt_(dbt) {}
    type& operator * ()
    {
        return *(type*)dbt_.get_data();
    }
    type* operator -> ()
    {
        return (type*)dbt_.get_data();
    }
private:
    const Dbt& dbt_;
};

class KBulk;
class KVBulk;
typedef DbMultipleDataBuilder DbMultipleKeyBuilder;
#define DESTRUCTOR(type, obj) (&obj)->~type()
#define CONSTRUCTOR(type, obj) new (&obj) type

class KBulk
{
public:
    KBulk()
        :dbt_(dummy, sizeof(dummy)),
            builder_(dbt_),
            eof_(true),
            eoi_(true)
    {
        attach(dummy, sizeof(dummy));
    }
    void attach(void* bulk, size_t size)
    {
        DESTRUCTOR(Dbt, dbt_);
        CONSTRUCTOR(Dbt, dbt_)(bulk, size);
        dbt_.set_ulen(size);
        dbt_.set_flags(DB_DBT_USERMEM);
        DESTRUCTOR(DbMultipleKeyBuilder, builder_);
        CONSTRUCTOR(DbMultipleKeyBuilder, builder_)(dbt_);
        eof_ = false;
        eoi_ = true;
    }
    void detach()
    {
        attach(dummy, sizeof(dummy));
    }
    void flush()
    {
        attach(dbt_.get_data(), dbt_.get_size());
    }
    void reserve_and_attach_itself(size_t n)
    {
        back_.reserve(std::max(n, (size_t)MINIMUM_BULK_LEN<<3) & ~(size_t)3);
        attach_itself();
    }
    void reserve_get_and_attach_itself(size_t n)
    {
        back_.reserve(std::max(n, (size_t)MINIMUM_GET_BULK_LEN) & ~(size_t)((1<<10)-1));
        attach_itself();
    }
    bool append(void* p, size_t n)
    {
        return builder_.append(p, n);
    }
    template<class type>
    bool append(type& val)
    {
        if (eof_) return false;
        eof_ = !builder_.append(&val, sizeof(val));
        return eof_;
    }
    Dbt* dbt() { return &dbt_; }
protected:
    void attach_itself()
    {
        attach(&back_[0], back_.capacity());
    }
    template<class type>
    bool append(const type*);
    bool eof_;
    bool eoi_;  // end of iteration
    char dummy[MINIMUM_BULK_LEN];
    Dbt dbt_;
    DbMultipleKeyBuilder builder_;
    std::vector<char> back_;
};
//char KBulk::dummy[64];
class VBulk : public KBulk
{
public:
    VBulk() :
            iter_(dbt_) {}
    void begin_iter()
    {
        DESTRUCTOR(DbMultipleDataIterator, iter_);
        CONSTRUCTOR(DbMultipleDataIterator, iter_)(dbt_);
        eoi_ = false;
    }
    bool next(Dbt& v)
    {
        if (eoi_) return false;
        eoi_ = !iter_.next(v);
        return !eoi_;
    }
protected:
    DbMultipleDataIterator iter_;
};
class KVBulk
{
public:
    KVBulk()
        :dbt_(dummy, sizeof(dummy)),    // prevent DbMultipleBuilder from crashing
            builder_(dbt_),
            iter_(dbt_),
            eof_(true)
    {
        attach(dummy, sizeof(dummy));
    }
    void attach(void* bulk, size_t size)
    {
        DESTRUCTOR(Dbt, dbt_);
        CONSTRUCTOR(Dbt, dbt_)(bulk, size);
        dbt_.set_ulen(size);    // BULK uses ulen other than size
        dbt_.set_flags(DB_DBT_USERMEM);
        DESTRUCTOR(DbMultipleKeyDataBuilder, builder_);
        CONSTRUCTOR(DbMultipleKeyDataBuilder, builder_)(dbt_);
        eof_ = false;
        eoi_ = true;
    }
    void detach()
    {
        attach(dummy, sizeof(dummy));
    }
    void flush()
    {
        attach(dbt_.get_data(), dbt_.get_size());
    }
    void reserve_and_attach_itself(size_t n)
    {
        back_.reserve(std::max(n, (size_t)MINIMUM_BULK_LEN<<3) & ~(size_t)3);
        attach_itself();
    }
    void reserve_get_and_attach_itself(size_t n)
    {
        back_.reserve(std::max(n, (size_t)MINIMUM_GET_BULK_LEN) & ~(size_t)((1<<10)-1));
        attach_itself();
    }
    bool append(void* kp, size_t kn, void* vp, size_t vn)
    {
        // bugly, sigseg while twice return false;
        if (eof_) return false;
        eof_ = !builder_.append(kp, kn, vp, vn);
        return !eof_;
    }
    template<class ktype>
    bool append(ktype& key, void* p, size_t n)
    {
        if (eof_) return false;
        eof_ = !builder_.append(&key, sizeof(key), p, n);
        return !eof_;
    }
    template<class vtype>
    bool append(void* p, size_t n, vtype& val)
    {
        if (eof_) return false;
        eof_ = !builder_.append(p, n, &val, sizeof(val));
        return !eof_;
    }
    template<class ktype, class vtype>
    bool append(ktype& key, vtype& val)
    {
        if (eof_) return false;
        eof_ = !builder_.append(&key, sizeof(key), &val, sizeof(val));
        return !eof_;
    }
    void begin_iter()
    {
        DESTRUCTOR(DbMultipleKeyDataIterator, iter_);
        CONSTRUCTOR(DbMultipleKeyDataIterator, iter_)(dbt_);
        eoi_ = false;
    }
    bool next(Dbt& k, Dbt& v)
    {
        if (eoi_) return false;
        eoi_ = !iter_.next(k, v);
        return !eoi_;
    }
    Dbt* dbt() { return &dbt_; }
private:
    void attach_itself()
    {
        attach(&(back_)[0], back_.capacity());
    }
    template<class ktype, class vtype>
    bool append(const ktype*, const vtype*);
    bool eof_;
    bool eoi_;
    char dummy[MINIMUM_BULK_LEN<<3];
    Dbt dbt_;
    DbMultipleKeyDataBuilder builder_;
    DbMultipleKeyDataIterator iter_;
    std::vector<char> back_;
};
#undef DESTRUCTOR
#undef CONSTRUCTOR

class DbEnvSwitch;
struct DbEnvConfig
{
    DbEnvConfig() { zero(); }
    void zero() { memset(this, 0, sizeof(*this)); }
    bool need_set_data_dir_;
    bool need_set_errcall_;
    typedef void (*db_errcall_fcn)(const DbEnv *dbenv, const char *errpfx, const char *msg);
    db_errcall_fcn set_errcall_fcn_;
    bool need_set_errfile_;
    FILE* set_errfile_errfile_;
    bool need_set_errpfx_;
    bool need_set_feedback_;
    typedef void (*db_feedback_fcn)(DbEnv *dbenv, int opcode, int percent);
    db_feedback_fcn set_feedback_fcn_;
    bool need_set_encrypt_;
    bool need_set_event_notify_;    // rep
    typedef void (*db_event_fcn)(DbEnv *dbenv, u_int32_t event, void *event_info);
    db_event_fcn set_event_notify_fcn_;
    bool need_set_metadata_dir_;    // rep
    bool need_set_msgcall_;
    typedef void (*db_msgcall_fcn)(const DbEnv *dbenv, const char *msg);
    db_msgcall_fcn set_msgcall_fcn_;
    bool need_set_msgfile_;
    FILE* set_msgfile_msgfile_;
    bool need_set_thread_count_;
    u_int32_t set_thread_count_count_;
    bool need_set_timeout_lock_;
    bool need_set_timeout_recover_;
    bool need_set_timeout_txn_;
    db_timeout_t set_timeout_lock_;
    db_timeout_t set_timeout_recover_;
    db_timeout_t set_timeout_txn_;
    bool need_set_tmp_dir_;
    bool need_set_verbose_;
    u_int32_t set_verbose_flags_;
    bool need_set_cachesize_;
    u_int32_t set_cachesize_gbytes_;
    u_int32_t set_cachesize_bytes_;
    int set_cachesize_ncache_;
    u_int32_t flags_;
};

struct DbEnvBuilderErr
{
    int err_set_data_dir_;
    int err_set_errcall_;
    int err_set_errfile_;
    int err_set_errpfx_;
    int err_set_feedback_;
    int err_set_encrypt_;
    int err_set_event_notify_;
    int err_set_metadata_dir_;    // rep
    int err_set_msgcall_;
    int err_set_msgfile_;
    int err_set_thread_count_;
    int err_set_timeout_;
    int err_set_tmp_dir_;
    int err_set_verbose_;
    int err_set_cachesize_;
};

class DbEnvMutableBuilder;
class DbEnvBuilder : protected DbEnvConfig
{
public:
    int open(DbEnv& dbenv, bool need_create = true, DbEnvBuilderErr& err = __unused_err)
    {
        prebuild(dbenv, err);
        if (!tmpDir_.empty())
            dbenv.set_tmp_dir(tmpDir_.c_str());
        if (!logDir_.empty())
            dbenv.set_lg_dir(logDir_.c_str());
#if DB_VERSION_MAJOR > 4
        if (!metadataDir_.empty())
            dbenv.set_metadata_dir(metadataDir_.c_str());
#endif
        if (!dataDirs_.empty())
            for (int i = 0; i < dataDirs_.size(); ++i)
                dbenv.set_create_dir(dataDirs_[i].c_str());
        return dbenv.open(homeDir_.c_str(),
                          flags_ | ((need_create)?DB_CREATE:0), 0);
    }
    DbEnvMutableBuilder mutableBuilder();
protected:
    static DbEnvBuilderErr __unused_err;
    void prebuild(DbEnv& dbenv, DbEnvBuilderErr& err = __unused_err)
    {
        #define CHECK_IF_SET(func, arg) \
        if(c.need_##func##_) { \
            err.err_##func##_ = dbenv.func(arg);   \
        }
        #define CHECK_IF_SET_NORETURN(func, arg) \
        if(c.need_##func##_) { \
            dbenv.func(arg);   \
        }
        #define CHECK_IF_SET2(func, arg1, arg2) \
        if(c.need_##func##_) { \
            err.err_##func##_ = dbenv.func(arg1, arg2);   \
        }
        #define CHECK_IF_SETX2(func, what, arg1, arg2) \
        if(c.need_##func##_##what##_) { \
            err.err_##func##_ = dbenv.func(arg1, arg2);   \
        }
        #define CHECK_IF_SET3(func, arg1, arg2, arg3) \
        if(c.need_##func##_) { \
            err.err_##func##_ = dbenv.func(arg1, arg2, arg3);   \
        }
        DbEnvConfig& c = static_cast<DbEnvConfig&>(*this);
        //CHECK_IF_SET(set_data_dir_;
        CHECK_IF_SET_NORETURN(set_errcall, set_errcall_fcn_);
        CHECK_IF_SET_NORETURN(set_errfile, set_errfile_errfile_);
        CHECK_IF_SET_NORETURN(set_errpfx, set_errpfx_errpfx_.c_str());
        CHECK_IF_SET(set_feedback, set_feedback_fcn_);
        CHECK_IF_SET2(set_encrypt, set_encrypt_passwd_.c_str(), DB_ENCRYPT_AES);
        CHECK_IF_SET(set_event_notify, set_event_notify_fcn_);
        //CHECK_IF_SET(set_metadata_dir_;    // rep
        CHECK_IF_SET_NORETURN(set_msgcall, set_msgcall_fcn_);
        CHECK_IF_SET_NORETURN(set_msgfile, set_msgfile_msgfile_);
        CHECK_IF_SET(set_thread_count, set_thread_count_count_);
        CHECK_IF_SETX2(set_timeout, lock, set_timeout_lock_, DB_SET_LOCK_TIMEOUT);
        CHECK_IF_SETX2(set_timeout, recover, set_timeout_recover_, DB_SET_REG_TIMEOUT);
        CHECK_IF_SETX2(set_timeout, txn, set_timeout_txn_, DB_SET_TXN_TIMEOUT);
        //CHECK_IF_SET(set_tmp_dir_;
        //CHECK_IF_SET2(set_verbose, set_verbose_flags_, 1);
        if (set_verbose_flags_)
        {
            u_int32_t bits = set_verbose_flags_;
            while (bits)
            {
                u_int32_t bit = bits & ~(bits - 1);
                dbenv.set_verbose(bit, 1);
                bits -= bit;
            }
        }
        CHECK_IF_SET3(set_cachesize, set_cachesize_gbytes_, set_cachesize_bytes_, set_cachesize_ncache_);
        #undef CHECK_IF_SET
        #undef CHECK_IF_SET_NORETURN
        #undef CHECK_IF_SETX2
        #undef CHECK_IF_SET2
        #undef CHECK_IF_SET3
    }
    void set_flags(u_int32_t flag, bool set=true)
    {
        if (set)
            flags_ |= flag;
        else
            flags_ &= ~flag;

    }
    std::string set_errpfx_errpfx_;
    std::string set_encrypt_passwd_;
    std::string homeDir_;
    std::string tmpDir_;
    std::string logDir_;
    std::string metadataDir_;
    std::vector<std::string> dataDirs_;
};
DbEnvBuilderErr DbEnvBuilder::__unused_err;

class DbEnvMutableBuilder : public DbEnvBuilder
{
public:
    DbEnvMutableBuilder() {}
    typedef DbEnvMutableBuilder this_type;
    this_type& init_subsys_cdb(bool set=true) {set_flags(DB_INIT_CDB, set); return *this;}
    this_type& init_subsys_lock(bool set=true) {set_flags(DB_INIT_LOCK, set); return *this;}
    this_type& init_subsys_log(bool set=true) {set_flags(DB_INIT_LOG, set); return *this;}
    this_type& init_subsys_mpool(bool set=true) {set_flags(DB_INIT_MPOOL, set); return *this;}
    this_type& init_subsys_rep(bool set=true) {set_flags(DB_INIT_REP, set); return *this;}
    this_type& init_subsys_txn(bool set=true) {set_flags(DB_INIT_TXN, set); return *this;}
	this_type& init_as_inmemory(bool set = true) { set_flags(DB_PRIVATE, set); return *this; }
	this_type& init_using_systemmemory(bool set = true) { set_flags(DB_SYSTEM_MEM, set); return *this; }
    this_type& check_if_recovery_needs(bool set=true) {set_flags(DB_REGISTER, set); return *this;}
    this_type& check_if_failchk_before_recovery(bool set=true) {set_flags(DB_FAILCHK, set); return *this;}
    this_type& recovery_before_open(bool set=true) {set_flags(DB_RECOVER, set); return *this;}
    this_type& set_free_threaded(bool set=true) {set_flags(DB_THREAD, set); return *this;}
    this_type& set_lg_dir(const char* dir)
    {
        logDir_ = dir;
        return *this;
    }
    this_type& set_home_dir(const char* dir)
    {
        homeDir_ = dir;
        return *this;
    }
    this_type& ensure_home_dir()
    {
        struct stat st = {0};
        if (stat(homeDir_.c_str(), &st) == -1)
        {
            mkdir(homeDir_.c_str(), 0700);
        }
        return *this;
    }
    this_type& set_data_dir(const char* dir)
    {
        need_set_data_dir_ = true;
        dataDirs_.push_back(dir);
        return *this;
    }
    this_type& set_errcall(db_errcall_fcn fcn)
    {
        need_set_errcall_ = true;
        set_errcall_fcn_ = fcn;
        return *this;
    }
    this_type& set_errfile(FILE* errfile)
    {
        need_set_errfile_ = true;
        set_errfile_errfile_ = errfile;
        return *this;
    }
    this_type& set_errpfx(const char* errpfx)
    {
        need_set_errpfx_ = true;
        set_errpfx_errpfx_ = errpfx;
        return *this;
    }
    this_type& set_feedback(db_feedback_fcn fcn)
    {
        need_set_feedback_ = true;
        set_feedback_fcn_ = fcn;
        return *this;
    }
    this_type& set_encrypt(const char* passwd)
    {
        need_set_encrypt_ = true;
        set_encrypt_passwd_ = passwd;
        return *this;
    }
    this_type& set_event_notify(db_event_fcn fcn)
    {
        need_set_event_notify_ = true;
        set_event_notify_fcn_ = fcn;
        return *this;
    }
    this_type& set_metadata_dir(const char* dir)    // rep
    {
        need_set_metadata_dir_ = true;
        metadataDir_ = dir;
        return *this;
    }
    this_type& set_msgcall(db_msgcall_fcn fcn)
    {
        need_set_msgcall_ = true;
        set_msgcall_fcn_ = fcn;
        return *this;
    }
    this_type& set_msgfile(FILE* msgfile)
    {
        need_set_msgfile_ = true;
        set_msgfile_msgfile_ = msgfile;
        return *this;
    }
    this_type& set_thread_count(u_int32_t count)
    {
        need_set_thread_count_ = true;
        set_thread_count_count_ = count;
        return *this;
    }
    this_type& set_timeout_lock(db_timeout_t t)
    {
        need_set_timeout_lock_ = true;
        set_timeout_lock_ = t;
        return *this;
    }
    this_type& set_timeout_recover(db_timeout_t t)
    {
        need_set_timeout_recover_ = true;
        set_timeout_recover_ = t;
        return *this;
    }
    this_type& set_timeout_txn(db_timeout_t t)
    {
        need_set_timeout_txn_ = true;
        set_timeout_txn_ = t;
        return *this;
    }
    this_type& set_tmp_dir(const char* dir)
    {
        need_set_tmp_dir_ = true;
        tmpDir_ = dir;
        return *this;
    }
    this_type& set_verbose(u_int32_t flags, bool onoff)
    {
        need_set_verbose_ = true;
        if (onoff)
            set_verbose_flags_ |= flags;
        else
            set_verbose_flags_ &= ~flags;
        return *this;
    }
    this_type& trace_deadlock(bool b = true)
    {
        return set_verbose(DB_VERB_DEADLOCK, b);
    }
    this_type& trace_file_ops(bool b = true)
    {
        return set_verbose(DB_VERB_FILEOPS, b);
    }
    this_type& trace_file_ops_all(bool b = true)
    {
        return set_verbose(DB_VERB_FILEOPS_ALL, b);
    }
    this_type& trace_recover(bool b = true)
    {
        return set_verbose(DB_VERB_RECOVERY, b);
    }
    this_type& trace_register(bool b = true)
    {
        return set_verbose(DB_VERB_REGISTER, b);
    }
    this_type& trace_replication_all()
    {
        trace_replication().trace_rep_elect().trace_rep_misc();
        trace_rep_msgs().trace_rep_sync().trace_rep_system();
        return trace_repmgr_connfail().trace_repmgr_misc().trace_waitsfor();
    }
    this_type& trace_replication(bool b = true)
    {
        return set_verbose(DB_VERB_REPLICATION, b);
    }
    this_type& trace_rep_elect(bool b = true)
    {
        return set_verbose(DB_VERB_REP_ELECT, b);
    }
    this_type& trace_rep_lease(bool b = true)
    {
        return set_verbose(DB_VERB_REP_LEASE, b);
    }
    this_type& trace_rep_misc(bool b = true)
    {
        return set_verbose(DB_VERB_REP_MISC, b);
    }
    this_type& trace_rep_msgs(bool b = true)
    {
        return set_verbose(DB_VERB_REP_MSGS, b);
    }
    this_type& trace_rep_sync(bool b = true)
    {
        return set_verbose(DB_VERB_REP_SYNC, b);
    }

    this_type& trace_rep_system(bool b = true)
    {
#if DB_VERSION_MAJOR > 4
        return set_verbose(DB_VERB_REP_SYSTEM, b);
#else 
		return *this;
#endif
    }

    this_type& trace_repmgr_connfail(bool b = true)
    {
        return set_verbose(DB_VERB_REPMGR_CONNFAIL, b);
    }
    this_type& trace_repmgr_misc(bool b = true)
    {
        return set_verbose(DB_VERB_REPMGR_MISC, b);
    }
    this_type& trace_waitsfor(bool b = true)
    {
        return set_verbose(DB_VERB_WAITSFOR, b);
    }
    this_type& set_cachesize(u_int32_t gbytes, u_int32_t bytes, int ncache)
    {
        need_set_cachesize_ = true;
        set_cachesize_gbytes_ = gbytes;
        set_cachesize_bytes_ = bytes;
        set_cachesize_ncache_ = ncache;
        return *this;
    }
    DbEnvMutableBuilder(DbEnvBuilder& builder) : DbEnvBuilder(builder) {}
};

DbEnvMutableBuilder DbEnvBuilder::mutableBuilder()
{
    return DbEnvMutableBuilder(*this);
}

struct DbBuilderConfig
{
    DbBuilderConfig() { zero(); }
    void zero() { memset(this, 0, sizeof(*this)); }
    u_int32_t flags_;
    bool need_set_cachesize_;
    u_int32_t set_cachesize_gbytes_;
    u_int32_t set_cachesize_bytes_;
    int set_cachesize_ncache_;
    bool need_set_pagesize_;
    u_int32_t set_pagesize_pagesize_;
    bool need_set_dup_compare_;
#if DB_VERSION_MAJOR <= 5
    typedef int (*dup_compare_fcn)(Db *, const Dbt *, const Dbt *);
#else
	typedef int(*dup_compare_fcn)(Db *, const Dbt *, const Dbt *, size_t*);
#endif
    dup_compare_fcn set_dup_compare_fcn_;
    bool need_set_encrypt_;
    bool need_set_errcall_;
    typedef void (*db_errcall_fcn)(const DbEnv *, const char *, const char *);
    db_errcall_fcn set_errcall_fcn_;
    bool need_set_errfile_;
    FILE* set_errfile_errfile_;
    bool need_set_errpfx_;
    bool need_set_feedback_;
    typedef void (*db_feedback_fcn)(Db *dbp, int opcode, int percent);
    db_feedback_fcn set_feedback_fcn_;
    bool need_set_lk_exclusive_;
    int set_lk_exclusive_nowait_onoff_;
    bool need_set_lorder_;
    int set_lorder_lorder_;
    typedef void (*db_msgcall_fcn)(const DbEnv *dbenv, const char *msg);
    bool need_set_msgcall_;
    db_msgcall_fcn set_msgcall_fcn_;
    bool need_set_msgfile_;
    FILE* set_msgfile_msgfile_;
    bool need_set_partition_;
    typedef u_int32_t (*db_partition_fcn) (Db *db, Dbt *key);
    db_partition_fcn set_partition_fcn_;
    bool need_set_partition_dirs_;
    typedef int (*db_append_recno_fcn)(Db *, Dbt *, db_recno_t);
    bool need_set_append_recno_;
    db_append_recno_fcn set_append_recno_fcn_;
#if DB_VERSION_MAJOR <= 5
    typedef int (*bt_compare_fcn)(Db *, const Dbt *, const Dbt *);
#else
	typedef int(*bt_compare_fcn)(Db *, const Dbt *, const Dbt *, size_t*);
#endif
    bool need_set_bt_compare_;
    bt_compare_fcn set_bt_compare_fcn_;
    bool need_set_bt_minkey_;
    u_int32_t set_bt_minkey_bt_minkey_;
    typedef size_t (*bt_prefix_match_fcn)(Db *, const Dbt *, const Dbt *);
    bool need_set_bt_prefix_;    // smallest match up between two keys
    bt_prefix_match_fcn set_bt_prefix_fcn_;
    bool need_set_re_delim_;
    int set_re_delim_re_delim_;
    bool need_set_re_len_;
    u_int32_t set_re_len_re_len_;
    bool need_set_re_pad_;
    u_int32_t set_re_pad_re_pad_;
    bool need_set_h_compare_;
    bt_compare_fcn set_h_compare_fcn_;
    bool need_set_h_ffactor_;
    u_int32_t set_h_ffactor_ffactor_;
    typedef u_int32_t (*h_hash_fcn)(Db *, const void *, u_int32_t);
    bool need_set_h_hash_;
    h_hash_fcn set_h_hash_fcn_;
    bool need_set_h_nelem_;
    u_int32_t set_h_nelem_h_nelem_;
    bool need_set_q_extentsize_;
    u_int32_t set_q_extentsize_q_extentsize_;
};

struct DbBuilderErr
{
    DbBuilderConfig c;
    int err_set_append_recno_;
    int err_set_bt_compare_;
    int err_set_bt_minkey_;
    int err_set_bt_prefix_;
    int err_set_cachesize_;
    int err_set_dup_compare_;
    int err_set_encrypt_;
    int err_set_errcall_;
    int err_set_errfile_;
    int err_set_errpfx_;
    int err_set_feedback_;
    int err_set_h_compare_;
    int err_set_h_ffactor_;
    int err_set_h_hash_;
    int err_set_h_nelem_;
    int err_set_lk_exclusive_;
    int err_set_lorder_;
    int err_set_msgcall_;
    int err_set_msgfile_;
    int err_set_pagesize_;
    int err_set_partition_;
    int err_set_partition_dirs_;
    int err_set_q_extentsize_;
    int err_set_re_delim_;
    int err_set_re_len_;
    int err_set_re_pad_;
};



// usgae:
// Db db(env);dbt
// DbMutalbeBuilder builder;
// builder.set_xxx(x).set_yyy(y).openZZZ(db, ...);
class DbMutableBuilder;
class DbBuilder : protected DbBuilderConfig
{
public:
    // dup: key/data can be duplicate.
    // dupsort: key can be duplicate, key/data should be unique.
    int openBtreeDb(Db& db, DbTxn* txnid, const char* dbname, bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_BTREE, need_create, err);
    }
    int openBtreePrimaryDb(Db& db, DbTxn* txnid, const char* dbname, bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_BTREE, need_create, err);
    }
    int openBtreeForeignDb(Db& db, DbTxn* txnid, const char* dbname, bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_BTREE, need_create, err);
    }
    int openBtreeRecnumDb(Db& db, DbTxn* txnid, const char* dbname,
                          bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_BTREE, need_create, err, DB_RECNUM);
    }
    int openBtreeDuplicateDb(Db& db, DbTxn* txnid, const char* dbname,
                          bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_BTREE, need_create, err, DB_DUP);
    }
    int openBtreeDupSortDb(Db& db, DbTxn* txnid, const char* dbname,
                          bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_BTREE, need_create, err, DB_DUPSORT);
    }
    int openHashDb(Db& db, DbTxn* txnid, const char* dbname,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_HASH, need_create, err);
    }
    int openHashPrimaryDb(Db& db, DbTxn* txnid, const char* dbname,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_HASH, need_create, err);
    }
    int openHashForeignDb(Db& db, DbTxn* txnid, const char* dbname,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_HASH, need_create, err);
    }
    int openHashDuplicateDb(Db& db, DbTxn* txnid, const char* dbname,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_HASH, need_create, err, DB_DUP);
    }
    int openHashDupSortDb(Db& db, DbTxn* txnid, const char* dbname,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_HASH, need_create, err, DB_DUPSORT);
    }
    int openQueueDb(Db& db, DbTxn* txnid, const char* dbname,
                    bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_QUEUE, need_create, err);
    }
    int openQueueInOrderDb(Db& db, DbTxn* txnid, const char* dbname,
                    bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_QUEUE, need_create, err, DB_INORDER);
    }
    int openRecnoDb(Db& db, DbTxn* txnid, const char* dbname,
                    bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_RECNO, need_create, err);
    }
    int openRecnoRenumberDb(Db& db, DbTxn* txnid, const char* dbname,
                    bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_RECNO, need_create, err, DB_RENUMBER);
    }
    int openRecnoDbFromSource(Db& db, DbTxn* txnid, const char* dbname, const char* source, int delim,
                              bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return open(db, txnid, dbname, DB_RECNO, need_create, err, DB_SNAPSHOT);
    }

    DbMutableBuilder mutableBuilder();
protected:
    static DbBuilderErr __unused_err;
    void prebuild(Db& db, DbBuilderErr& err)
    {
        DbBuilder& c = static_cast<DbBuilder&>(*this);
        #define CHECK_IF_SET(func, arg) \
        if(c.need_##func##_) { \
            err.err_##func##_ = db.func(arg);   \
        }
        #define CHECK_IF_SET_NORETURN(func, arg) \
        if(c.need_##func##_) { \
            db.func(arg);   \
        }
        #define CHECK_IF_SET2(func, arg1, arg2) \
        if(c.need_##func##_) { \
            err.err_##func##_ = db.func(arg1, arg2);   \
        }
        #define CHECK_IF_SET3(func, arg1, arg2, arg3) \
        if(c.need_##func##_) { \
            err.err_##func##_ = db.func(arg1, arg2, arg3);   \
        }
        CHECK_IF_SET(set_append_recno, c.set_append_recno_fcn_);
        CHECK_IF_SET(set_bt_compare, c.set_bt_compare_fcn_);
        CHECK_IF_SET(set_bt_minkey, c.set_bt_minkey_bt_minkey_);
        CHECK_IF_SET_NORETURN(set_bt_prefix, c.set_bt_prefix_fcn_);
        CHECK_IF_SET3(set_cachesize, c.set_cachesize_gbytes_, c.set_cachesize_bytes_, c.set_cachesize_ncache_);
        CHECK_IF_SET(set_dup_compare, c.set_dup_compare_fcn_);
        CHECK_IF_SET2(set_encrypt, c.set_encrypt_passwd_.c_str(), DB_ENCRYPT_AES);
        CHECK_IF_SET_NORETURN(set_errcall, c.set_errcall_fcn_);
        CHECK_IF_SET_NORETURN(set_errfile, c.set_errfile_errfile_);
        CHECK_IF_SET_NORETURN(set_errpfx, c.set_errpfx_errpfx_.c_str());
        CHECK_IF_SET(set_feedback, c.set_feedback_fcn_);
        CHECK_IF_SET(set_h_compare, c.set_h_compare_fcn_);
        CHECK_IF_SET(set_h_ffactor, c.set_h_ffactor_ffactor_);
        CHECK_IF_SET(set_h_hash, c.set_h_hash_fcn_);
        CHECK_IF_SET(set_h_nelem, c.set_h_nelem_h_nelem_);
        //CHECK_IF_SET(set_lk_exclusive, c.set_lk_exclusive_nowait_onoff_);
        CHECK_IF_SET(set_lorder, c.set_lorder_lorder_); // byte order, le or be
        CHECK_IF_SET_NORETURN(set_msgcall, c.set_msgcall_fcn_);
        CHECK_IF_SET_NORETURN(set_msgfile, c.set_msgfile_msgfile_);
        CHECK_IF_SET(set_pagesize, c.set_pagesize_pagesize_);
        //CHECK_IF_SET(set_partition, c.set_partition_fcn_);
        if (c.need_set_partition_)
        {
            if (c.set_partition_fcn_)
                err.err_set_partition_ = db.set_partition(0, NULL, c.set_partition_fcn_);
            else
                err.err_set_partition_ = db.set_partition(c.set_partition_keys_.size() + 1,
                                                          &c.set_partition_keys_[0],
                                                          NULL);
        }
        //CHECK_IF_SET(set_partition_dirs, c.set_partition_dirs_);
        CHECK_IF_SET(set_q_extentsize, c.set_q_extentsize_q_extentsize_);
        CHECK_IF_SET(set_re_delim, c.set_re_delim_re_delim_);
        CHECK_IF_SET(set_re_len, c.set_re_len_re_len_);
        CHECK_IF_SET(set_re_pad, c.set_re_pad_re_pad_);
        #undef CHECK_IF_SET
        #undef CHECK_IF_SET_NORETURN
        #undef CHECK_IF_SET2
        #undef CHECK_IF_SET3
    }
    int open(Db& db, DbTxn* txnid, const char* dbname, DBTYPE access, bool need_create = true,
             DbBuilderErr& err = __unused_err, int exflags = 0)
    {
        prebuild(db, err);
        db.set_flags(exflags);
        const char* filename = (fileName_.empty())? NULL: fileName_.c_str();
        return db.open(txnid, filename, (*dbname == '\0')?NULL:dbname, access,
                       flags_ | ((need_create)?DB_CREATE:0), 0);
    }
    std::string fileName_;
    std::string set_encrypt_passwd_;
    std::string set_errpfx_errpfx_;
    std::vector<std::vector<char> > set_partition_keys_mem_;
    std::vector<Dbt> set_partition_keys_;
    std::vector<std::string> set_partition_dirs_;
};

DbBuilderErr DbBuilder::__unused_err;


class DbMutableBuilder : public DbBuilder
{
public:
    DbMutableBuilder() {}
    typedef DbMutableBuilder this_type;
    this_type& set_cachesize(u_int32_t gbytes, u_int32_t bytes, int ncache)
    {
        need_set_cachesize_ = true;
        set_cachesize_gbytes_ = gbytes;
        set_cachesize_bytes_ = bytes;
        set_cachesize_ncache_ = ncache;
        return *this;
    }
    this_type& set_dup_compare(dup_compare_fcn fcn)
    {
        need_set_dup_compare_ = true;
        set_dup_compare_fcn_ = fcn;
        return *this;
    }
    this_type& set_encrypt(const char* passwd)
    {
        need_set_encrypt_ = true;
        set_encrypt_passwd_ = passwd;
        return *this;
    }
    this_type& set_errcall(db_errcall_fcn fcn)
    {
        need_set_errcall_ = true;
        set_errcall_fcn_ = fcn;
        return *this;
    }
    this_type& set_errfile(FILE* f)
    {
        need_set_errfile_ = true;
        set_errfile_errfile_ = f;
        return *this;
    }
    this_type& set_errpfx(const char* pfx)
    {
        need_set_errpfx_ = true;
        set_errpfx_errpfx_ = pfx;
        return *this;
    }
    this_type& set_feedback(db_feedback_fcn fcn)
    {
        need_set_feedback_ = true;
        set_feedback_fcn_ = fcn;
        return *this;
    }
    this_type& set_lk_exclusive(u_int32_t nowait_onoff)
    {
        need_set_lk_exclusive_ = true;
        set_lk_exclusive_nowait_onoff_ = nowait_onoff;
        return *this;
    }
    this_type& set_lorder(int lorder)
    {
        need_set_lorder_ = true;
        set_lorder_lorder_ = lorder;
        return *this;
    }
    this_type& set_msgcall(db_msgcall_fcn fcn)
    {
        need_set_msgcall_ = true;
        set_msgcall_fcn_ = fcn;
        return *this;
    }
    this_type& set_msgfile(FILE* msgfile)
    {
        need_set_msgfile_ = true;
        set_msgfile_msgfile_ = msgfile;
        return *this;
    }
    this_type& set_pagesize(u_int32_t pagesize)
    {
        need_set_pagesize_ = true;
        set_pagesize_pagesize_ = pagesize;
        return *this;
    }
    this_type& set_partition_dirs(std::vector<std::string>& dirs)
    {
        need_set_partition_dirs_ = true;
        set_partition_dirs_ = dirs;
        return *this;
    }
    this_type& set_partition_fcn(db_partition_fcn fcn)
    {
        need_set_partition_ = true;
        set_partition_fcn_ = fcn;
        return *this;
    }
    this_type& set_partition_keys(u_int32_t parts, Dbt* keys)
    {
        need_set_partition_ = true;
        set_partition_keys_mem_.resize(parts - 1);
        set_partition_keys_.resize(parts - 1);
        for(int i = 0; i < parts - 1; ++i)
        {
            std::vector<char>& mem = set_partition_keys_mem_[i];
            Dbt& key = set_partition_keys_[i];
            mem.assign((char*)keys[i].get_data(),
                                              (char*)keys[i].get_data() + keys[i].get_size());
            key.set_data(&mem[0]);
            key.set_size(mem.size());
            key.set_flags(DB_DBT_USERMEM);
        }
        return *this;
    }
    this_type& set_append_recno(db_append_recno_fcn fcn)
    {
        need_set_append_recno_ = true;
        set_append_recno_fcn_ = fcn;
        return *this;
    }
    this_type& set_bt_compare(bt_compare_fcn fcn)
    {
        need_set_bt_compare_ = true;
        set_bt_compare_fcn_ = fcn;
        return *this;
    }
    this_type& set_bt_minkey(uint32_t bt_minkey)
    {
        need_set_bt_minkey_ = true;
        set_bt_minkey_bt_minkey_ = bt_minkey;
        return *this;
    }
    this_type& set_bt_prefix(bt_prefix_match_fcn fcn)
    {
        need_set_bt_prefix_ = true;
        set_bt_prefix_fcn_ = fcn;
        return *this;
    }
    this_type& set_re_delim(int re_delim)
    {
        need_set_re_delim_ = true;
        set_re_delim_re_delim_ = re_delim;
        return *this;
    }
    this_type& set_re_len(uint32_t re_len)
    {
        need_set_re_len_ = true;
        set_re_len_re_len_ = re_len;
        return *this;
    }
    this_type& set_re_pad(int re_pad)
    {
        need_set_re_pad_ = true;
        set_re_pad_re_pad_ = re_pad;
        return *this;
    }
    this_type& set_h_compare(bt_compare_fcn fcn)
    {
        need_set_h_compare_ = true;
        set_h_compare_fcn_ = fcn;
        return *this;
    }
    this_type& set_h_ffactor(uint32_t ffactor)
    {
        need_set_h_ffactor_ = true;
        set_h_ffactor_ffactor_ = ffactor;
        return *this;
    }
    this_type& set_h_hash(h_hash_fcn fch)
    {
        need_set_h_hash_ = true;
        set_h_hash_fcn_ = fch;
        return *this;
    }
    this_type& set_h_nelem(uint32_t h_nelem)
    {
        need_set_h_nelem_ = true;
        set_h_nelem_h_nelem_ = h_nelem;
        return *this;
    }
    this_type& set_q_extentsize(uint32_t q_extentsize)
    {
        need_set_q_extentsize_ = true;
        set_q_extentsize_q_extentsize_ = q_extentsize;
        return *this;
    }
    // flags
    this_type& set_db_auto_commit(bool set = true)
    {
        return set_flags(DB_AUTO_COMMIT, set);
    }
    this_type& set_db_exclusive(bool set = true)
    {
        return set_flags(DB_EXCL, set);
    }
    this_type& set_db_copy_to_write(bool set = true)
    {
        return set_flags(DB_MULTIVERSION, set);
    }
    this_type& set_db_multiversion(bool set = true)
    {
        return set_flags(DB_MULTIVERSION, set);
    }
    this_type& set_db_no_mmap(bool set = true)
    {
        return set_flags(DB_NOMMAP, set);
    }
    this_type& set_db_readonly(bool set = true)
    {
        return set_flags(DB_RDONLY, set);
    }
    this_type& set_db_dirty_read(bool set = true)
    {
        return set_flags(DB_READ_UNCOMMITTED, set);
    }
    this_type& set_db_read_uncommitted(bool set = true)
    {
        return set_flags(DB_READ_UNCOMMITTED, set);
    }
    this_type& set_db_free_threaded(bool set = true)
    {
        return set_flags(DB_THREAD, set);
    }
    this_type& set_db_truncate_before_open(bool set = true)
    {
        return set_flags(DB_TRUNCATE, set);
    }
    this_type& truncate_before_open(bool set = true)
    {
        return set_flags(DB_TRUNCATE, set);
    }
    this_type& set_filename(const char* filename)
    {
        fileName_ = filename;
        return *this;
    }
    DbMutableBuilder(DbBuilder& builder) : DbBuilder(builder) {}
protected:
    this_type& set_flags(u_int32_t flags, bool set = true)
    {
        if (set)
            flags_ |= flags;
        else
            flags_ &= ~flags;
        return *this;
    }
};

DbMutableBuilder DbBuilder::mutableBuilder()
{
    return DbMutableBuilder(*this);
}

template<class Target>
class OpPut
{
public:
    static int helper_put(DbTxn*, Target&, Dbt*, Dbt*, u_int32_t);
    static int put_if_key_not_exists(Target& db, KVt& kv, DbTxn* txn = NULL)     // fail if key exists
    {
        return helper_put(txn, db, kv.key(), kv.data(), DB_NOOVERWRITE);
    }
    static int put_batch_ignore_dupsort_data(Target& db, KBulk& K, VBulk& V, DbTxn* txn = NULL)
    {
        return helper_put(txn, db, K.dbt(), V.dbt(), DB_MULTIPLE|DB_OVERWRITE_DUP);
    }
    static int put_batch_using_keybulk(Target& db, KVBulk& KV, DbTxn* txn = NULL)
    {
        Dbt null;
        return helper_put(txn, db, KV.dbt(), &null, DB_MULTIPLE_KEY);
    }
    static int put_batch_using_keybulk_ignore_dupsort_data(Target& db, KVBulk& KV, DbTxn* txn = NULL)
    {
        Dbt null;
        return helper_put(txn, db, KV.dbt(), &null, DB_MULTIPLE_KEY|DB_OVERWRITE_DUP);
    }
    static int put_batch(Target& db, KBulk& K, VBulk& V, DbTxn* txn = NULL)
    {
        return helper_put(txn, db, K.dbt(), V.dbt(), DB_MULTIPLE);
    }
    static int put_against_dupsort_data(Target& db, KVt& kv, DbTxn* txn = NULL)  // fail if key/data exists
    {
        return helper_put(txn, db, kv.key(), kv.data(), DB_NODUPDATA);
    }
    static int put_ignore_dupsort_data(Target& db, KVt& kv, DbTxn* txn = NULL)  // fail if key/data exists
    {
        return helper_put(txn, db, kv.key(), kv.data(), DB_OVERWRITE_DUP);
    }
    static int append(Target& db, KVt& kv, DbTxn* txn = NULL)
    {
        return helper_put(txn, db, kv.key(), kv.data(), DB_APPEND);
    }
    static int put(Target& db, KVt& kv, DbTxn* txn = NULL)
    {
        return helper_put(txn, db, kv.key(), kv.data(), 0);
    }
};

template<>
int OpPut<Db>::helper_put(DbTxn* txn, Db& db, Dbt* k, Dbt* v, u_int32_t flags)
{
    return db.put(txn, k, v, flags);
}
template<>
int OpPut<Dbc>::helper_put(DbTxn* txn, Dbc& dbc, Dbt* k, Dbt* v, u_int32_t flags)
{
    return dbc.put(k, v, flags);
}
typedef OpPut<Db> DbPut;

class DbcPut
{
public:
    static int put_current(Dbc& dbc, Dbt* v)
    {
        return dbc.put(NULL, v, DB_CURRENT);
    }
    static int update_current(Dbc& dbc, Dbt* v)
    {
        return put_current(dbc, v);
    }
};

class DbcDupPut : public DbcPut
{
public:
    static bool ensure(Db& db)
    {
        DBTYPE dbtype;
        u_int32_t flags = 0;
        db.get_type(&dbtype);
        db.get_flags(&flags);
        return (dbtype == DB_BTREE || dbtype == DB_HASH) && (flags & (DB_DUP|DB_DUPSORT));
    }
    static int put_after(Dbc& dbc, Dbt* v)
    {
        return dbc.put(NULL, v, DB_AFTER);
    }
    static int insert_dup_after_current(Dbc& dbc, Dbt* v)
    {
        return dbc.put(NULL, v, DB_AFTER);
    }
    static int put_before(Dbc& dbc, Dbt* v)
    {
        return dbc.put(NULL, v, DB_BEFORE);
    }
    static int insert_dup_before_current(Dbc& dbc, Dbt* v)
    {
        return dbc.put(NULL, v, DB_BEFORE);
    }
    static int put_keyfirst(Dbc& dbc, Dbt* k, Dbt* v)
    {
        return dbc.put(k, v, DB_KEYFIRST);
    }
    static int insert_as_first_dup_for_key(Dbc& dbc, Dbt* k, Dbt* v)
    {
        return dbc.put(k, v, DB_KEYFIRST);
    }
    static int put_keylast(Dbc& dbc, Dbt* k, Dbt* v)
    {
        return dbc.put(k, v, DB_KEYLAST);
    }
    static int insert_as_last_dup_for_key(Dbc& dbc, Dbt* k, Dbt* v)
    {
        return dbc.put(k, v, DB_KEYLAST);
    }
    static int put_against_dupsort_data(Dbc& dbc, KVt& kv)  // fail if key/data exists
    {
        return dbc.put(kv.key(), kv.data(), DB_NODUPDATA);
    }
};

template<class Target>
class OpGet
{
public:
    static int helper_get(DbTxn*, Target&, Dbt*, Dbt*, u_int32_t);
    static int helper_pget(DbTxn*, Target&, Dbt*, Dbt*, Dbt*, u_int32_t);
    // get, SET
    // get_lower_bound, SET_RANGE
    // get_exact, GET_BOTH
    // get_lower_bound_dup, GET_BOTH_RANGE
    // get_dup_data, SET, 1 [in] key, n [out] data
    // get_multiple, SET, n [in] key, n [out] data with key/data pair
};

class DbGet
{
public:
    static int consume_queue(Db& que, KVt& kv, DbTxn* txn = NULL)
    {
        return que.get(txn, kv.key(), kv.data(), DB_CONSUME);
    }
    static int consume_queue_wait(Db& que, KVt& kv, DbTxn* txn = NULL)
    {
        return que.get(txn, kv.key(), kv.data(), DB_CONSUME_WAIT);
    }
    static int check_if_record_exists(Db& db, KVt& kv, DbTxn* txn = NULL)
    {
        return db.get(txn, kv.key(), kv.data(), DB_GET_BOTH);
    }
    static int get_by_recnum(Db& db, KVt& kv, DbTxn* txn = NULL)
    {
        return db.get(txn, kv.key(), kv.data(), DB_GET_BOTH);
    }
	static int check_if_key_exists(Db& db, Dbt* key, DbTxn* txn = NULL)
	{
		return db.exists(txn, key, 0);
	}
};

class DbcGet : public OpGet<Dbc>
{
public:
    static int get(Dbc& dbc, KVt& kv, u_int32_t op)
    {
        return dbc.get(kv.key(), kv.data(), op);
    }
    static int get_dup_of_one_key(Dbc& dbc, Dbt* k, VBulk& vbulk, u_int32_t op)
    {
        return dbc.get(k, vbulk.dbt(), op|DB_MULTIPLE&~DB_MULTIPLE_KEY);
    }
    static int get_multiple(Dbc& dbc, Dbt* k, KVBulk& kvbulk, u_int32_t op)
    {
        return dbc.get(k, kvbulk.dbt(), op|DB_MULTIPLE_KEY&~DB_MULTIPLE);
    }
    #define DbcGetDefination(op, OPT)   \
    static int op(Dbc& dbc, KVt& kv)  \
    { \
        return get(dbc, kv, DB_##OPT);    \
    }\
    static int get_dups_at_##op##_key(Dbc& dbc, Dbt* k, VBulk& vbulk)   \
    {   \
        return get_dup_of_one_key(dbc, k, vbulk, DB_##OPT); \
    }   \
    static int get_multiple_at_##op##_key(Dbc& dbc, Dbt* k, KVBulk& kvbulk)   \
    {   \
        return get_multiple(dbc, k, kvbulk, DB_##OPT);  \
    }
    // first
    DbcGetDefination(first, FIRST);
    // prev
    DbcGetDefination(prev, PREV);
    // prev_dup
    DbcGetDefination(prev_dup, PREV_DUP);
    // prev_nodup
    DbcGetDefination(prev_nodup, PREV_NODUP);
    // current
    DbcGetDefination(current, CURRENT);
    // next
    DbcGetDefination(next, NEXT);
    // next_dup
    DbcGetDefination(next_dup, NEXT_DUP);
    // next_nodup
    DbcGetDefination(next_nodup, NEXT_NODUP);
    // last
    DbcGetDefination(last, LAST);
    #undef DbcGetDefination
};

class DbIndexConfig
{
public:
    void zero() { memset(this, 0, sizeof(*this)); }
    typedef int (*get_field_fcn)
	    (Db *, const Dbt *, const Dbt *, Dbt *);
	typedef int (*nullify_fcn)
	    (Db *, const Dbt *, Dbt *, const Dbt *, int *);
    get_field_fcn get_field_fcn_;
    nullify_fcn nullify_fcn_;
    u_int32_t index_flags_;
    u_int32_t foreign_flags_;
    bool do_truncate_before_associate;
};

class DbIndexMutableBuilder;
class DbIndexBuilder : protected DbIndexConfig
{
public:
    int openBtreeIndex(Db& db, DbTxn* txnid, const char* dbname,
                    Db& primary, Db& foreign = __unused_foreign,
                    bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = builder_.openBtreeDb(db, txnid, dbname, need_create, err);
        return open(error, db, txnid, dbname, primary, foreign, need_create, err);
    }
    int openBtreeRecnumIndex(Db& db, DbTxn* txnid, const char* dbname,
                          Db& primary, Db& foreign = __unused_foreign,
                          bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = builder_.openBtreeRecnumDb(db, txnid, dbname, need_create, err);
        return open(error, db, txnid, dbname, primary, foreign, need_create, err);
    }
    int openBtreeDuplicateIndex(Db& db, DbTxn* txnid, const char* dbname,
                             Db& primary, Db& foreign = __unused_foreign,
                          bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = builder_.openBtreeDuplicateDb(db, txnid, dbname, need_create, err);
        return open(error, db, txnid, dbname, primary, foreign, need_create, err);
    }
    int openBtreeDupSortIndex(Db& db, DbTxn* txnid, const char* dbname,
                           Db& primary, Db& foreign = __unused_foreign,
                          bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = builder_.openBtreeDupSortDb(db, txnid, dbname, need_create, err);
        return open(error, db, txnid, dbname, primary, foreign, need_create, err);
    }
    int openHashIndex(Db& db, DbTxn* txnid, const char* dbname,
                   Db& primary, Db& foreign = __unused_foreign,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = builder_.openHashDb(db, txnid, dbname, need_create, err);
        return open(error, db, txnid, dbname, primary, foreign, need_create, err);
    }
    int openHashDuplicateIndex(Db& db, DbTxn* txnid, const char* dbname,
                            Db& primary, Db& foreign = __unused_foreign,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = builder_.openHashDuplicateDb(db, txnid, dbname, need_create, err);
        return open(error, db, txnid, dbname, primary, foreign, need_create, err);
    }
    int openHashDupSortIndex(Db& db, DbTxn* txnid, const char* dbname,
                          Db& primary, Db& foreign = __unused_foreign,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = builder_.openHashDupSortDb(db, txnid, dbname, need_create, err);
        return open(error, db, txnid, dbname, primary, foreign, need_create, err);
    }
    static Db& __unused_foreign;
    static DbBuilderErr __unused_err;
protected:
    bool check_foreign_arg(Db& foreign)
    {
        return &foreign != &__unused_foreign;
    }
    int open(int error, Db& index, DbTxn* txnid, const char* dbname,
            Db& primary, Db& foreign = __unused_foreign,
            bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        if (error)
            return error;
        if (do_truncate_before_associate)
        {
            u_int32_t count = 0;
            index.truncate(NULL, &count, 0);
        }
        if (!check_foreign_arg(foreign))
            return openIndex(index, txnid, dbname, primary, foreign, need_create, err);
        else
            return openIndexUsingForeign(index, txnid, dbname, primary, foreign, need_create, err);
    }
    int openIndex(Db& index, DbTxn* txnid, const char* dbname,
                          Db& primary, Db& foreign = __unused_foreign,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        return primary.associate(txnid, &index, get_field_fcn_, index_flags_);

    }
    int openForeign(int error, Db& index, DbTxn* txnid, const char* dbname,
                          Db& primary, Db& foreign,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        if (error)
            return error;
        return foreign.associate_foreign(&index, nullify_fcn_, foreign_flags_);
    }
    int openIndexUsingForeign(Db& index, DbTxn* txnid, const char* dbname,
                          Db& primary, Db& foreign = __unused_foreign,
                   bool need_create = true, DbBuilderErr& err = __unused_err)
    {
        int error = openIndex(index, txnid, dbname, primary, foreign, need_create, err);
        if (check_foreign_arg(foreign))
            error = openForeign(error, index, txnid, dbname, primary, foreign, need_create, err);
        return error;
    }
    DbMutableBuilder builder_;
};
Db& DbIndexBuilder::__unused_foreign = *(Db*)NULL;
DbBuilderErr DbIndexBuilder::__unused_err;

class DbIndexMutableBuilder : public DbIndexBuilder
{
public:
    typedef DbIndexMutableBuilder this_type;
    DbMutableBuilder* operator-> ()
    {
        return &builder_;
    }
    this_type& set_get_field_fcn(get_field_fcn fcn)
    {
        get_field_fcn_ = fcn; return *this;
    }
    this_type& set_buildup_index_if_empty(bool b = true)
    {
        set_flags(index_flags_, DB_CREATE, b); return *this;
    }
    this_type& set_do_nothing_while_primary_update(bool b = true)
    {
        set_flags(index_flags_, DB_IMMUTABLE_KEY, b); return *this;
    }
    this_type& set_abort_while_foreign_deletion(bool b = true)
    {
        foreign_flags_ = DB_FOREIGN_ABORT;
        nullify_fcn_ = NULL; return *this;
    }
    this_type& set_cascade_while_foreign_deletion(bool b = true)
    {
        foreign_flags_ = DB_FOREIGN_CASCADE;
        nullify_fcn_ = NULL; return *this;
    }
    this_type& set_nullify_while_foreign_deletion(nullify_fcn fcn)
    {
        nullify_fcn_ = fcn;
        foreign_flags_ = (fcn)? DB_FOREIGN_NULLIFY: 0;
         return *this;
    }
    this_type& set_index_truncate_before_associate(bool set = true)
    {
        do_truncate_before_associate = true;
        return *this;
    }
protected:
    void set_flags(u_int32_t& flags, u_int32_t modify, bool b = true)
    {
        if (b)
            flags |= modify;
        else
            flags &= ~modify;
    }

};

class DbIndexPut
{
private:
    static int put(Db& index, KVt&)
    {
        return EINVAL;
    }
};

class DbcIndexPut
{
private:
    static int put(Dbc& index, KVt&)
    {
        return EINVAL;
    }
};

class DbIndexGet
{
public:
    static int get_by_index_and_primary_key(Db& index, KVt& kv, Dbt* pv, DbTxn* txn = NULL)
    {
        return index.pget(txn, kv.key(), kv.data(), pv, DB_GET_BOTH);
    }
};

class DbcIndexGet : public OpGet<Dbc>
{
public:
    static int get(Dbc& dbc, KVt& kv, u_int32_t op)
    {
        return dbc.get(kv.key(), kv.data(), op);
    }
    static int pget(Dbc& dbc, Dbt* index, KVt& kv, u_int32_t op)
    {
        return dbc.pget(index, kv.key(), kv.data(), op);
    }
    #define DbcGetDefination(op, OPT)   \
    static int op(Dbc& dbc, KVt& kv)  \
    { \
        return get(dbc, kv, DB_##OPT);    \
    }\
    static int op##_and_pkey(Dbc& dbc, Dbt* index, KVt& kv)  \
    { \
        return pget(dbc, index, kv, DB_##OPT);    \
    }
    // first
    DbcGetDefination(first, FIRST);
    // prev
    DbcGetDefination(prev, PREV);
    // prev_dup
    DbcGetDefination(prev_dup, PREV_DUP);
    // prev_nodup
    DbcGetDefination(prev_nodup, PREV_NODUP);
    // current
    DbcGetDefination(current, CURRENT);
    // next
    DbcGetDefination(next, NEXT);
    // next_dup
    DbcGetDefination(next_dup, NEXT_DUP);
    // next_nodup
    DbcGetDefination(next_nodup, NEXT_NODUP);
    // last
    DbcGetDefination(last, LAST);
    #undef DbcGetDefination
};

class DbCount
{
public:
    static int key_count(Db& db)
    {
        int count = 0;
        void* stat = NULL;
        db.stat(NULL, &stat, 0);
        if (stat)
        {
            DBTYPE dbtype;
            db.get_type(&dbtype);
            switch (dbtype)
            {
            case DB_BTREE:
            case DB_RECNO:
                count = ((DB_BTREE_STAT*)stat)->bt_nkeys;
                break;
            case DB_HASH:
                count = ((DB_HASH_STAT*)stat)->hash_nkeys;
                break;
            case DB_QUEUE:
                count = ((DB_QUEUE_STAT*)stat)->qs_nkeys;
                break;
            }
            free(stat);
            stat = NULL;
        }
        return count;
    }
    static int data_count(Db& db)
    {
        int count = 0;
        void* stat = NULL;
        db.stat(NULL, &stat, 0);
        if (stat)
        {
            DBTYPE dbtype;
            db.get_type(&dbtype);
            switch (dbtype)
            {
            case DB_BTREE:
            case DB_RECNO:
                count = ((DB_BTREE_STAT*)stat)->bt_ndata;
                break;
            case DB_HASH:
                count = ((DB_HASH_STAT*)stat)->hash_ndata;
                break;
            case DB_QUEUE:
                count = ((DB_QUEUE_STAT*)stat)->qs_ndata;
                break;
            }
            free(stat);
            stat = NULL;
        }
        return count;
    }
};

// ypu should not delete the Dbc or DbTxn,
class ScopeDbc
{
public:
    ScopeDbc() : dbcp(NULL), err(EINVAL) {}
    ScopeDbc(DbTxn* txn, Db& db, u_int32_t flags = 0)
    {
        err = db.cursor(NULL, &dbcp, flags);
    }
    ~ScopeDbc() { if (dbcp) dbcp->close(); dbcp = NULL; }
    operator Dbc* () { return dbcp; }
    operator Dbc** () { return &dbcp; }
    operator Dbc& () { return *dbcp; }
    Dbc* operator -> () { return dbcp; }
private:
    Dbc* dbcp;
    int err;
};

////// Replica ///////
// use repmgr_xxx apis for common usages
// if you want to use custom network layer implement,
//   1. rep_set_transport to set callback for how to send controls
//   2. rep_process_msg, called by your owned network dispatcher, and call rep_elect of rep_start
//   3. by this way, you can control the election by yourself.
// also you can use DbChannel for communications among replications,
//      to send_msg or send_request, and repmgr_msg_dispatch to set dispatcher for msg.


};

#endif //__Z_DB_CXX_H__
