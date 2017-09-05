
Contract Programming for C++ (Contract++)
=========================================

See "doc/html/index.html" for the library documentation.

All Contract Programming features of the Eiffel programming language
are supported by this library, among others:
*   Optional compilation and checking of invariants, preconditions,
    and postconditions.
*   Customizable actions on contract failure (terminate by default
    but it can throw, exit, etc).
*   Subcontracting for derived classes (with support for multiple
    inheritance).
*   Access to "old" variable values (before body execution) and
    return value "result" in postconditions.
*   Block invariants and loop variants.

Files organization:
*   All library source is in the "src/" directory.
*   Examples are in "example/" and test programs in "test/".
*   Run `make' in the main directory to see how to build examples, etc.

