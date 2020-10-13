original benchmark project homepage: http://openresty.org/misc/re/bench/

github commit path: https://github.com/openresty/sregex/tree/ee5944f108f76217760f9b5548e842971c0281b2/

it is not true on other platforms such as aarch64.

results tested on x64 platform in the project homepage, sregex > re2 > pcre2.jit > pcre.jit > pcre2 > pcre in almost cases. pcre and pcre2 perform very very poorly, so much worse than jit.

but in aarch64 platform, sregex under pl perform poorly, re2 poorly too, jit pcre is just a little better than non-jit pcre. pcre is not so much from pcre2.

i doubt that the players playing well on x64 use sse2 which aarch64 does not have.

you should install to run the benchmark
* pcre-devel
* pcre2-devel
* re2-devel
* perl-IPC/Run, perl-IPC/Run3, perl-List/????
* https://raw.githubusercontent.com/ronsavage/GraphViz/master/lib/GraphViz.pm
