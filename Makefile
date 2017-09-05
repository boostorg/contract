# Copyright (C) 2009-2010 Lorenzo Caminiti.
# Use, modification, and distribution is subject to the
# Contract++ Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt.)

# Default target.
help:
	@echo "Contract Programming for C++ (Contract++)"
	@echo
	@echo "This library does not need to be built. It is composed of "
	@echo "C++ header files only (contained in the \"src/\" directory)."
	@echo
	@echo "make [OPTION] example"
	@echo "    Build example programs to \"build/example/\" and their"
	@echo "    code documentation to \"codedoc/example/\"."
	@echo
	@echo "make [OPTION] test"
	@echo "    Build test programs to \"build/test/\" and their"
	@echo "    code documentation to \"codedoc/test/\"."
	@echo
	@echo "make doc"
	@echo "    Build libaray HTML documentation into \"doc/html/\" (requires"
	@echo "    Boost.QuickBook to be installed and compiled on your system)."
	@echo
	@echo "make clean"
	@echo "    Clean all (build etc)."
	@echo
	@echo "OPTION"
	@echo "    CXX    Specify 'GCC' to use GNU C++ compiler 'g++' (e.g., on"
	@echo "           Linux) or 'MSVC' to use Microsoft Visual C++ compiler "
	@echo "           (e.g., MSVC version 8 under Cygwin). CXX=GCC by default."
	@echo "    debug  Specify '1' to enable library debug messages and"
	@echo "           C++ debug symbols."
	@echo
	@echo "EXAMPLE"
	@echo "    # Build all examples using g++ with debug messages enabled."
	@echo "    make CXX=GCC debug=1 example# Build all examples using g++"
	exit 0

force_:

clean: force_
	rm -rf build/*
	
example: force_
	make -f example/Makefile

test: force_
	make -f test/Makefile

doc: force_
	# Requires Boost.QuickBook to be installed and compiled on your system.
	# Workaround: QuickBook uses all full paths but the ones relative to "boost/", Perl removes full path prefixes from HTML.
	cd ../boost-quickbook/doc && bjam --v2 && perl -p -i -e 'use Cwd; $$x=getcwd()."/qbk/src/contract"; s/$$x/contract/g' html/*.html html/contract/*.html
	# Copies documentation examples into doc/html directory.
	tmp="/tmp/contract-example.`date +%s`" && mkdir -p $$tmp && cp -R example $$tmp && find $$tmp -depth -name ".svn" -exec rm -rf {} \; && cp -R $$tmp/example doc/html
clean_doc: force_
	rm -rf doc/html/*.html
	rm -rf doc/html/contract/*.html
	rm -rf doc/html/contract__/*.html
	find doc/html/example -depth -name "*.[hc]pp -exec rm -rf {} \;

