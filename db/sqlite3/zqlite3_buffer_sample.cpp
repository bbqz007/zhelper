#include "zqlite3_buffer.h"
#include <sq3/sq3.hpp>
#include <iostream>
#include <string.h>
#define LOGD printf
#include "zqlite3_procedure.h"

using namespace zhelper;

zqlite3_allocator* g_imp = &zqlite3_allocator::inst();
int main(int argc, char** argv)
{
    using namespace sq3;
    using namespace std;
#define COUT cout
    COUT << sqlite3_config(SQLITE_CONFIG_GETMALLOC, &ori_sqlite3_mem_methods::methods_);
    ori_sqlite3_mem_methods::initialize();
    zqlite3_mem_methods_imp::initialize();
    COUT << sqlite3_config(SQLITE_CONFIG_MALLOC, &zqlite3_mem_methods_imp::methods_);
    //COUT << sqlite3_config(SQLITE_CONFIG_MALLOC, &ori_sqlite3_mem_methods::methods_2);


	std::string fname(":memory:");
	if (argc > 1)
        fname = argv[1];
	COUT << "Starting tests using file ["<<fname<<"]\n";
	database db;
	if( SQLITE_OK != db.open( fname ) )
	{
		throw std::runtime_error( "do_nothrow_api() could not open db." );
	}
	string jmd;
    if (argc > 2 && argv[2][0] == '1')
        COUT << db.execute( "PRAGMA journal_mode=\"memory\";" ) << "\n";
	COUT << db.execute( "PRAGMA journal_mode", jmd) << std::endl;
	COUT << "journal_mode is " << jmd << endl;
	zqlite3_allocator::inst().dumpinfo(cout);
	COUT << db.execute( "create table if not exists t1(a,b,c)" ) << '\n';
	int rvi = -1;
	db.execute( "select count(*) from t1", rvi );
	if( rvi < 5 )
	{ // insert some data...
	  // We use an extra nested scope to ensure that the statement object
	  // is destroyed before the next is created.
		COUT << db.execute( "insert into t1 values(1,2,3)" ) << '\n';
		COUT << db.execute( "insert into t1 values(4,5,6)" ) << '\n';
#if 1
		statement st(db);
		if( SQLITE_OK != st.prepare( "insert into t1 values(?,?,?)") )
		{
			throw std::runtime_error( "st.prepare() failed!" );
		}
		const int nr = 100000;
		COUT << "insert " << nr << " records. \n";
		for (int i = 0; i < nr; ++i)
        {
            st.bind(1,i);
            st.bind(2,i+1);
            st.bind(3,std::string("ho, baby"));
            //COUT << "insertion via bind... " << st.execute() << '\n';
            st.execute();
        }
#else
        int err_code;
        transaction trans(db);
        BEGIN_SQLITE3_PROCEDURE(err_code)
        sqlite3_stmt* stmt;
        SQLITE3_STMT_PREPARE(db.handle(), stmt, "insert into t1 values(?,?,?)", NULL, NULL);
        const int nr = 100000;
		COUT << "insert " << nr << " records. \n";
		for (int i = 0; i < nr; ++i)
        {
            BEGIN_SQLITE3_BINDING_TO_STMT(stmt)
            SQLITE3_BIND_STMT_INT(1,i);
            SQLITE3_BIND_STMT_INT(2,i+1);
            SQLITE3_BIND_STMT_VARCHAR(3, "ho, baby", 8);
            END_SQLITE3_BINDING
            //COUT << "insertion via bind... " << st.execute() << '\n';
            SQLITE3_STMT_UPDATE_STEP(db.handle(), stmt);
            SQLITE3_STMT_NEXT_STEP(stmt)
        }
        FINALIZE_SQLITE3_PROCEDURE
        sqlite3_finalize(stmt);
        END_SQLITE3_PROCEDURE
        trans.commit();
#endif
	}
    zqlite3_allocator::inst().dumpinfo(cout);
    COUT << "query all records. \n";
	{ // Run a query and display results on std::cout...
	  // Again, we use an extra nested scope to control the lifetime
	  // of statement and cursor objects.
		statement q1( db, "select rowid,* from t1" );
		int colcount = q1.colcount();
		int at = 0;
		std::string buffer;
		char unsigned const * cpt = 0;
		int anint = 0;
		char const * colname = 0;
		cursor rd( q1 );
		char const * separator = "\t";
		for( ; SQLITE_ROW == rd.step(); ++at )
		{ // dump the data in tab-delimited format:
			if( false && 0 == at )
			{
				for( int i = 0; i < colcount; ++i )
				{
					rd.colname( i, &colname );
					std::cout << colname;
					if( i < (colcount-1) )
					{
						std::cout << separator;
					}
				}
				std::cout << '\n';
			}
			for( int i = 0; i < colcount; ++i )
			{
				cpt = 0;
				rd.get( i, &cpt, anint );
				continue;
				if( cpt ) std::cout << '['<<cpt<<']';
				else std::cout << "[null]";
				if( i < (colcount-1) )
				{
					std::cout << separator;
				}
			}
			continue;
			std::cout << '\n';
		}
		std::cout << at << " rows.\n";
	}
	zqlite3_allocator::inst().dumpinfo(cout);

	COUT << "Ending ["<<fname<<"] tests.\n";
	//db.close(true);
	zqlite3_allocator::inst().dumpinfo(cout);

    database db2;
    COUT << "=======" << std::endl;
	COUT << db2.open( fname ) << std::endl;
	COUT << db2.execute( "create table if not exists t1(a,b,c)" ) << '\n';
	COUT << db2.execute("select count(0) from t1", (rvi = 0)) << std::endl;
	COUT << rvi << std::endl;
    return 0;
}
