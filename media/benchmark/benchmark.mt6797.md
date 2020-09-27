```
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_rgb2bgr              31069 ns        31067 ns        22521 opencv
BM_yuv2bgr             108066 ns       108060 ns         6458 opencv
BM_ffyuv2bgr            45702 ns        45699 ns        15477
BM_ffyuv2bgr_alloc      79480 ns        79471 ns         8696 opencv
BM_encpng              765452 ns       765415 ns          894
BM_enczpng/1/1/3/2     802883 ns       802886 ns          864
BM_enczffpng          2836479 ns      2835868 ns          256
BM_encjpg              576389 ns       576341 ns         1113 opencv
BM_enczjpg/0           545919 ns       545878 ns         1258
BM_enczjpg/1           542538 ns       542506 ns         1252
BM_enczffjpg          2277968 ns      2277875 ns          310
BM_decpng              613330 ns       613316 ns         1099 opencv
BM_deczpng             447361 ns       447346 ns         1559
BM_decjpg              398046 ns       398048 ns         1751 opencv
BM_deczjpg/0           368986 ns       368976 ns         1898
BM_deczjpg/1           367199 ns       367185 ns         1905
BM_decbmp               14856 ns        14856 ns        46965 opencv
BM_loadpng             665514 ns       665518 ns         1022 opencv
BM_loadzpng            479056 ns       479018 ns         1451
BM_loadzffpng          968687 ns       968639 ns          667
BM_loadjpg             440647 ns       440431 ns         1582 opencv
BM_loadzjpg/0          391618 ns       391609 ns         1769
BM_loadzjpg/1          389742 ns       389704 ns         1792
BM_loadzffjpg          620144 ns       620079 ns         1043
BM_loadbmp              56376 ns        55889 ns        12320 opencv
```
