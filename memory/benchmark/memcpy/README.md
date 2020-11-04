centos 7 release with glibc-2.17 which had not ported to aarch64.

so memcpy of glibc-2.17 performance poorly.

glibc-2.18 begin to ported to aarch64, there comes a very simple memcpy.S.

i choose the glibc-2.28 with which the centos 8 release.

you can just compile this memcpy.S rather than a whole glibc.

it performances twice better than the glibc-2.17, no memory alignment problems.
