Design By Contract for C++ (DBC++)
==================================

The DBC++ library supports Design By Contract (DBC) for the C++ programming 
language.

Essentially, all Eiffel programming language DBC features are supported by 
DBC++. Among others:
1)  "old" prefix in postconditions;
2)  Subcontracting;
3)  Optional contract compilation;
4)  Full integration with Doxygen.

IMPORTANT:  The library is still under development, its API should be 
            considered experimental and subject to change.

The documentation is yet to be written. Please look at the examples in the
"example/" directory for illustrations on how to use the library. In 
particular, the followings are good examples to get started:
    "example/OO_SW_Contruction/Stack4"
    "example/DBC_by_Example/NameList"

Run `make' to see how to build examples, test, install, etc.

The library requires the C++ Boost library http://www.boost.org/. In particular
Boost.Preprocessor and Boost.MPL are required.


INSTALL
-------

To install run `make install'.

The library is composed of C/C++ header files only so it does not need to be
built. The library files are contained in the "include/" directory, they are:
    "include/dbc.hpp"   Main file that includes entire library.
    "include/dbc/*"     All other header files that implement the library.

Executing `make install' will copy these files into your system include
directory (e.g., "/usr/include/" by default on Linux systems). Make sure the
directory on which you specify to copy the files is included in your C/C++
compiler include path (e.g., "-I" option for the gcc compiler) then you can
include and use the library simply specifying "#include <dbc.hpp>" at the top
of your C/C++ files.


RELEASE HISTORY
---------------

Release number convention:
    Release_Number ::= Major_Revision.Minor_Revision.SVN_Revision

(Release history, from newest to oldest release.)
Release 0.1.55 (2009-04-19)
    Reorganized files to cleanup root directory.
    Added installation program.
Release 0.1.50 (2009-04-19)
    First public release.


LICENSE
-------

Copyright (C) 2009 Lorenzo Caminiti. Distributed under DBC++ Software License 
(see file LICENSE_1_0.txt).

