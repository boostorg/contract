
all:
	@echo "Design by Contract for C++ (DBC++)"
	@echo
	@echo "This library does not need to be built. It is composed of "
	@echo "C/C++ header files only (contained int the \"include/\" directory)."
	@echo
	@echo "make install"
	@echo "    Install DBC++ files onto your system (you might need to "
	@echo "    be root). It will prompt you for the installation path."
	@echo "make doc"
	@echo "    Build library documentation to \"doc/html/\"."
	@echo "make [OPTION] example"
	@echo "    Build example programs to \"build/example/\" and their"
	@echo "    documentation to \"codedoc/example/\"."
	@echo "make [OPTION] test"
	@echo "    Build test programs to \"build/test/\" and their"
	@echo "    documentation to \"codedoc/test/\"."
	@echo
	@echo "OPTION"
	@echo "CXX GCC to use GNU C++ compiler 'g++' (e.g., under Linux)"
	@echo "    or MVVC to use Microsoft Visual C++ compiler (e.g.,"
	@echo "    MSVC version 8 under Cygwin). CXX=GCC by default."
	@echo
	@echo "EXAMPLE"
	@echo "make CXX=GCC example    # Build all examples using g++"
	@echo "make CXX=MSVC test      # Build all tests using MSVC"
	exit 0

force_:

install:
	bin/install

example: force_
	make -f build/Makefile.example

test: force_
	make -f build/Makefile.test

doc: force_
	rm -f doc/html/*.*
	rm -f doc/html/str/*.*
	# Build str example, run it to upd str.out, create its doc.
	make -f build/Makefile.example str_codeapi
	make -f build/Makefile.example str
	/bin/bash -c "./build/example/str &> doc/src/str.out"
	doxygen doc/src/Doxyfile.str
	# Create library doc (will href to str example).
	cd doc/src && doxygen # From doc/src for correct path names.

