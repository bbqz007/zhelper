the original benchmark project from http://lh3lh3.users.sourceforge.net/reb.shtml

this svn's http address is https://sourceforge.net/p/klib/code/HEAD/tree/

usgae:
1. make
2. run
```
for i in `find -type f -executable`; do echo $i; time cat howto | $i $pattern 1>/dev/null; done
```

