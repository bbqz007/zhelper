* install path rather than `configure --prefix=<install path>` or `CMAKE_INSTALL_PREFIX`
  * [reference] (https://stackoverflow.com/questions/11307465/destdir-and-prefix-of-make)
  * ` make DESTDIR=<install path> install`, install to a temporate dir
  * ` make PREFIX=<install path> install`, install to a dir instead of configured.
