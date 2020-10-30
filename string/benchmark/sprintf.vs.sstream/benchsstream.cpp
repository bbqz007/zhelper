#include <benchmark/benchmark.h>
#include <string.h>
#include <sstream>

void BM_template(benchmark::State& state)
{

}

//BENCHMARK(BM_template);

void BM_sprintf(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		sprintf(buf, "%d%lld%f%s", i, i64, d, s);
	}
}

BENCHMARK(BM_sprintf);

void BM_sprintf_labels(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		sprintf(buf, "i = ; i64 = ; d = ; s = ", i, i64, d, s);
	}
}

BENCHMARK(BM_sprintf_labels);

void BM_sprintf_append_labels(benchmark::State& state)
{
    int i = 123456789;
    int64_t i64 = 1234567890123456;
    double d = i64;
    char* s = "1234567890123456";
    char buf[512];
    while (state.KeepRunning())
    {
		char* p = buf;
		sprintf(p, "i = ");
		p += strlen(p);
		sprintf(p, "; i64 = ");
        p += strlen(p);
		sprintf(p, "; d = ");
        p += strlen(p);
		sprintf(p, "; s = ");
        p += strlen(p);
    }
}

BENCHMARK(BM_sprintf_append_labels);

void BM_sprintf_append_args(benchmark::State& state)
{
    int i = 123456789;
    int64_t i64 = 1234567890123456;
    double d = i64;
    char* s = "1234567890123456";
    char buf[512];
    while (state.KeepRunning())
    {
		char* p = buf;
		sprintf(p, "%d", i);
		p += strlen(p);
        sprintf(p, "%lld", i64);
        p += strlen(p);
        sprintf(p, "%f", d);
        p += strlen(p);
        sprintf(p, "%s", s);
        p += strlen(p);
    }
}

BENCHMARK(BM_sprintf_append_args);

void BM_sprintf2(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		sprintf(buf, "i = %d; i64 = %lld; d = %f; s = %s", i, i64, d, s);
	}
}

BENCHMARK(BM_sprintf2);

void BM_sprintf2_append(benchmark::State& state)
{
    int i = 123456789;
    int64_t i64 = 1234567890123456;
    double d = i64;
    char* s = "1234567890123456";
    char buf[512];
    while (state.KeepRunning())
    {
		char* p = buf;
		sprintf(p, "i = ");
		p += strlen(p);
		sprintf(p, "%d", i);
		p += strlen(p);
		sprintf(p, "; i64 = ");
        p += strlen(p);
        sprintf(p, "%lld", i64);
        p += strlen(p);
		sprintf(p, "; d = ");
        p += strlen(p);
        sprintf(p, "%f", d);
        p += strlen(p);
		sprintf(p, "; s = ");
        p += strlen(p);
        sprintf(p, "%s", s);
        p += strlen(p);
    }
}

BENCHMARK(BM_sprintf2_append);

void BM_sstream_noop(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
	    std::stringstream ss;
	}
}

BENCHMARK(BM_sstream_noop);

void BM_sstream_labels(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
	    std::stringstream ss;
		ss << "i = ; i64 = ; d = ; s = ";
	}
}

BENCHMARK(BM_sstream_labels);

void BM_sstream_labels_usebuf(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
	    std::stringstream ss;
	    ss.rdbuf()->pubsetbuf(buf, sizeof(buf));
		ss << "i = ; i64 = ; d = ; s = ";
	}
}

BENCHMARK(BM_sstream_labels_usebuf);

void BM_sstream_labels_usebuf2(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	std::stringstream ss;
	while (state.KeepRunning())
	{
	    ss.rdbuf()->pubsetbuf(buf, sizeof(buf));
		ss << "i = ; i64 = ; d = ; s = ";
	}
}

BENCHMARK(BM_sstream_labels_usebuf2);

void BM_sstream_append_labels(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		std::stringstream ss;
		ss << "i = " << "; i64 = " << "; d = " << "; s = ";
	}
}

BENCHMARK(BM_sstream_append_labels);

void BM_sstream_append_args(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		std::stringstream ss;
		ss << i << i64 << d << s;
	}
}

BENCHMARK(BM_sstream_append_args);

void BM_sstream_append_args_usebuf(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		std::stringstream ss;
		ss.rdbuf()->pubsetbuf(buf, sizeof(buf));
		ss << i << i64 << d << s;
	}
}

BENCHMARK(BM_sstream_append_args_usebuf);

void BM_sstream_append_args_usebuf2(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	std::stringstream ss;
	while (state.KeepRunning())
	{
		ss.rdbuf()->pubsetbuf(buf, sizeof(buf));
		ss << i << i64 << d << s;
	}
}

BENCHMARK(BM_sstream_append_args_usebuf2);

void BM_sstream2(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		std::stringstream ss;
		ss << "i = " << i
			<< "; i64 = " << i64
			<< "; d = " << d
			<< "; s = " << s;
	}
}

BENCHMARK(BM_sstream2);

void BM_sstream2_usebuf(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	while (state.KeepRunning())
	{
		std::stringstream ss;
		ss.rdbuf()->pubsetbuf(buf, sizeof(buf));
		ss << "i = " << i
			<< "; i64 = " << i64
			<< "; d = " << d
			<< "; s = " << s;
	}
}

BENCHMARK(BM_sstream2_usebuf);

void BM_sstream2_usebuf2(benchmark::State& state)
{
	int i = 123456789;
	int64_t i64 = 1234567890123456;
	double d = i64;
	char* s = "1234567890123456";
	char buf[512];
	std::stringstream ss;
	while (state.KeepRunning())
	{
		ss.rdbuf()->pubsetbuf(buf, sizeof(buf));
		ss << "i = " << i
			<< "; i64 = " << i64
			<< "; d = " << d
			<< "; s = " << s;
	}
}

BENCHMARK(BM_sstream2_usebuf2);




BENCHMARK_MAIN();
