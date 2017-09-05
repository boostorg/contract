# Copyright (C) 2009-2010 Lorenzo Caminiti.
# Use, modification, and distribution is subject to the
# Contract++ Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt.)

# Supported C++ compliers `make CXX=compiler ...', where compiler is:
# 	GCC		GNU g++ (e.g., on Linux) (default)
# 	MSVC	Microsoft Visual C++ (e.g., on Cygwin)
CXX=GCC

bin:=./bin
ifeq ($(CXX), GCC)
	cpp_nodef:=g++ -Wall -Werror -I./src
	def:=-D
	out:=-o 
endif
ifeq ($(CXX), MSVC)
	# Don't use /Wall for MSVC has very verbose warnings (even in Boost?!).
	cpp_nodef:=source $(bin)/env-MSVC8.sh && cl.exe /EHsc /I./src
	def:=/D
	out:=/Fe
endif
cpp:=$(cpp_nodef)
ifeq ($(debug), 1)
	cpp:=$(cpp) $(def)CONTRACT_CONFIG_DEBUG_=1
endif
ifneq ($(block_inv), 0)
	cpp:=$(cpp) $(def)CONTRACT_CHECK_BLOCK_INVARIANT 
endif
ifneq ($(class_inv), 0)
	cpp:=$(cpp) $(def)CONTRACT_CHECK_CLASS_INVARIANT
endif
ifneq ($(pre), 0)
	cpp:=$(cpp) $(def)CONTRACT_CHECK_PRECONDITION
endif
ifneq ($(post), 0)
	cpp:=$(cpp) $(def)CONTRACT_CHECK_POSTCONDITION
endif

src:=./test
build:=./build/test
codedoc:=./codedoc/test

all: usages subcontracting overloading templates

clean:
	rm -rf $(build)

mkdir_:
	mkdir -p $(build)

usages: mkdir_
	$(cpp) $(src)/usages/main.cpp $(out)$(build)/usages
subcontracting: mkdir_
	$(cpp) $(src)/subcontracting/main.cpp $(out)$(build)/subcontracting
overloading: mkdir_
	$(cpp) $(src)/overloading/main.cpp $(out)$(build)/overloading
templates: mkdir_
	$(cpp) $(src)/templates/main.cpp $(out)$(build)/templates

