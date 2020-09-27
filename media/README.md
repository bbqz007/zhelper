## **Reader** and **Writer** wrappers to libjpeg, libpng, ffmpeg.

the thinking comes from imread and imwrite of opencv.

**Reader** load file( or protocol source), and read the decoded pixel format (or color space) frame(s).

**Writer** encode the pixel format (or color space) frame(s), and restore to file( or protocol sink).

help you to code with longjmp/setjmp, and get out of the hard work with the apis and routines and procedures.

Reader 
- open()
- read_header()
- read()
- read_trailer()

**Todo:** do filtering on the raw frame.

Writer
- open()
- write_header()
- write()
- write_trailer()

  
## samples
there is sample for each wrapper.

## benchmark
- color space convertion, 
- encoding to memory, 
- decoding from memory, 
- loading from file and decoding, 
- encoding and restoring to file. 

benchmarks among using opencv, libpng, libjpeg, ffmpeg.

libpng, libjpeg, ffmpeg cases use wrapper zpng, zjpg, zffmpeg.



