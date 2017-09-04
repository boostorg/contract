
Design By Contract for C++ (DBC++)
==================================

This library supports all Eiffel Design By Contract (DBC) features for C++.
Among others:
    * Optional contract compilation/checking; 
    * Subcontracting;
    * "old" in postconditions;
    * Automatic contract documentation (with doxygen).
See http://dbcpp.sourceforge.net

Copyright (C) 2009 Lorenzo Caminiti.
Distributed under DBC++ Software License (see file LICENSE_1_0.txt).


INSTALL
-------

This library does not have to be built. It is composed only of the header files
in the "include" directory. To install this library, you simply have to add
this library header files your compiler's include path (see the documentation
for more details).


DOCUMENTATION
-------------

See "doc/html/index.html" for documentation on how to install and use this
library.

Run `make' in the main directory to see how to build examples, tests, etc.

The library source is contained in "include/". Every directory contains a
README.txt files describing its contents.


RELEASE HISTORY
---------------

Releases from newset to oldest with number format "Major.Minor.SVN_Revision".

Release 0.2.190 (2009-11-21)
    Compiled on both GCC (Linux and Cygwin) and Microsoft Visual C++ (Windows).
    Requiring to use "void" to specify empty function argument list.
Release 0.1.126 (2009-06-17)
    Completed 1st documentation draft.
Release 0.1.55 (2009-04-19)
    Reorganized files to cleanup root directory.
    Added installation program.
Release 0.1.50 (2009-04-19)
    First public release.

