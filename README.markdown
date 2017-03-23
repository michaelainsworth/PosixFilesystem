PosixFilesystem
===============

Overview
--------

The PosixFilesystem project is a simple C++ library that abstracts some
of the details of POSIX-based filesystems.

It's features include:

-   Directories
-   Files
-   Advisory locking
-   Flushing (via `fsync()`)

Examples
--------

The `example` directory contains some basic examples of usage.

You can test advisory locking with the `lock` example program. Type:

    lock lockfile.lock "Hello, world." 30 &
    lock lockfile.lock 'Heeey!' 0 &

The first process will write the message "Hello, world." and wait for 30
seconds before releasing the lock. Concatenate the file with:

    cat lockfile.lock

and you should see the contents "Hello, world."

After 30 seconds, both processes should be finished. At this point,
concatenate the file again. You should see "Heeey! world."

Note that both files start writing at position 0, which is why "Hello,"
from the first process was overwritten.

Portability
-----------

This library should compile without issues on Mac OS X and Fedora Linux.

It uses the pointer-to-implementation idiom, meaning that it should be
reasonably easily made to work with other platforms as appropriate.

Feedback
--------

This is a very simple library. If you have any suggestions for
improvement, please don't hesitate to let me know.
