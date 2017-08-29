
all:
	@echo "Design by Contract for C++ (DbC++)"
	@echo
	@echo "This library does not need to be build. It is composed only of "
	@echo "C/C++ header files contained int the \"./include/\" directory."
	@echo
	@echo "make install    Install DbC++ files onto your system (you might "
	@echo "                need to be root). This will prompt for path."
	@echo "make doc        Build library documentation as"
	@echo "                \"./build/doc/index.html\"."
	@echo "make example    Build example programs in \"./build/example/\" and"
	@echo "                Doxygen documentation in \"./codedoc/example/\"."
	@echo "make test       Build test programs in \"./build/test/\" and"
	@echo "                Doxygen documentation in \"./codedoc/test/\"."
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

