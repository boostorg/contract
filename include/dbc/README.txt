Design by Contract for C++ (DBC++) header files.

DbC++ should be included only by `#including "dbc.hpp"/ from parent directory.
Do NOT include other header files separately.
The "detail" directory contains library implementation files which must NOT be included directly.

The library is composed of only these header files (no object file needs to be built or linked).
This header files and the "dbc.hpp" from the parent directory must be located in a directory part of your C++ compiler include path (`-I' option).

