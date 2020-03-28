# SystemProgramming

SIS1 - Virtual Filesystem:

how to run:
1) run Makefile
2) sudo insmod new_proc.ko # this creates the virtual filesystem and put it into the kernel

purpose of VFS: to make abstraction over the different formats of filesystem (ntfs, ext4,  ext3, etc.)

where to use:
1) local (to have access to all types of files despite differences of formats in your device)
2) remote access (to have access to all types of files despite differences of formats in your servers, cloud databases, etc.)

how to implement VFS:
1) override system calls that manipulates files: open(), write(), read(), create()
2) put your overriden system calls to the kernel

