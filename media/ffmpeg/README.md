## zff_reader and zff_writer

### zff_reader
- open()
- open_video_stream()
- read_header()
- poll()

### zff_writer
- open()
- clone_video_stream(), add_stream()
- write_header()
- write(), write2()
- write_trailer()

### zff_reader::poll() 
can poll encoded packets and decoded frames both.

### zff_writer::write()
fit for image2 out format

### zff_writer::write2()
fit for video out formats. this version does not support pts handling, you should do it by yourself.
