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

src:=./example
build:=./build/example
codedoc:=./codedoc/example

all: myvector myvector_checks commas throw storage friend exspecs struct cv inline extern Crowl2006 Mitchell2002 Meyer1997 Stroustrup1997

clean:
	rm -rf $(build)

mkdir_:
	mkdir -p $(build)

myvector: mkdir_
	$(cpp) $(src)/myvector/main.cpp $(out)$(build)/myvector
myvector_checks: mkdir_
	# Compile with all different contract checking combinations.
	$(cpp_nodef) $(src)/myvector/main.cpp $(out)$(build)/myvector-check_none
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(src)/myvector/main.cpp $(out)$(build)/myvector-check_inv
	$(cpp_nodef) $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block_inv
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_inv_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_inv_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_pre_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_inv_pre_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block_pre_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block_inv_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block_inv_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main.cpp $(out)$(build)/myvector-check_block_inv_pre_post

myvector_nomacros: mkdir_
	$(cpp) $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros
myvector_nomacros_checks: mkdir_
	# Compile with all different contract checking combinations.
	$(cpp_nodef) $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_none
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_inv
	$(cpp_nodef) $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block_inv
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_inv_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_inv_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_pre_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_inv_pre_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block_pre_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block_inv_post
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block_inv_pre
	$(cpp_nodef) $(def)CONTRACT_CHECK_BLOCK_INVARIANT $(def)CONTRACT_CHECK_CLASS_INVARIANT $(def)CONTRACT_CHECK_PRECONDITION $(def)CONTRACT_CHECK_POSTCONDITION $(src)/myvector/main_nomacros.cpp $(out)$(build)/myvector_nomacros-check_block_inv_pre_post

commas: mkdir_
	$(cpp) $(src)/commas/main.cpp $(out)$(build)/commas
throw: mkdir_
	$(cpp) $(src)/throw/main.cpp $(out)$(build)/throw
storage: mkdir_
	$(cpp) $(src)/storage/main.cpp $(out)$(build)/storage
friend: mkdir_
	$(cpp) $(src)/friend/main.cpp $(out)$(build)/friend
exspecs: mkdir_
	$(cpp) $(src)/exspecs/main.cpp $(out)$(build)/exspecs
struct: mkdir_
	$(cpp) $(src)/struct/main.cpp $(out)$(build)/struct
cv: mkdir_
	$(cpp) $(src)/cv/main.cpp $(out)$(build)/cv
inline: mkdir_
	$(cpp) $(src)/inline/main.cpp $(out)$(build)/inline
extern: mkdir_
	$(cpp) $(src)/extern/main.cpp $(out)$(build)/extern

Crowl2006: sqrt block sum factorial circle operator_equal vector
sqrt: mkdir_
	$(cpp) $(src)/Crowl2006/sqrt/main.cpp $(out)$(build)/sqrt
block: mkdir_
	$(cpp) $(src)/Crowl2006/block/main.cpp $(out)$(build)/block
sum: mkdir_
	$(cpp) $(src)/Crowl2006/sum/sum.cpp $(src)/Crowl2006/sum/main.cpp $(out)$(build)/sum
factorial: mkdir_
	$(cpp) $(src)/Crowl2006/factorial/main.cpp $(out)$(build)/factorial
circle: mkdir_
	$(cpp) $(src)/Crowl2006/circle/main.cpp $(out)$(build)/circle
operator_equal: mkdir_
	$(cpp)  $(src)/Crowl2006/operator_equal/main.cpp $(out)$(build)/operator_equal
vector: mkdir_
	$(cpp) $(src)/Crowl2006/vector/main.cpp $(out)$(build)/vector

Mitchell2002: name_list stack simple_queue dictionary courier customer_manager observe counter
name_list: mkdir_
	$(cpp) $(src)/Mitchell2002/name_list/names.cpp $(src)/Mitchell2002/name_list/main.cpp $(out)$(build)/name_list
stack: mkdir_
	$(cpp) $(src)/Mitchell2002/stack/main.cpp $(out)$(build)/stack
simple_queue: mkdir_
	$(cpp) $(src)/Mitchell2002/simple_queue/main.cpp $(out)$(build)/simple_queue
dictionary: mkdir_
	$(cpp) $(src)/Mitchell2002/dictionary/main.cpp $(out)$(build)/dictionary
courier: mkdir_
	$(cpp) $(src)/Mitchell2002/courier/couriers.cpp $(src)/Mitchell2002/courier/main.cpp $(out)$(build)/courier
customer_manager: mkdir_
	$(cpp) $(src)/Mitchell2002/customer_manager/customer_manager.cpp $(src)/Mitchell2002/customer_manager/main.cpp $(out)$(build)/customer_manager
observe: mkdir_
	$(cpp) $(src)/Mitchell2002/observe/main.cpp $(out)$(build)/observe
counter: mkdir_
	$(cpp) $(src)/Mitchell2002/counter/main.cpp $(out)$(build)/counter

Meyer1997: stack4 stack3 gcd maxarray
stack4: mkdir_
	$(cpp) $(src)/Meyer1997/stack4/main.cpp $(out)$(build)/stack4
stack3: mkdir_
	$(cpp) $(src)/Meyer1997/stack3/main.cpp $(out)$(build)/stack3
gcd: mkdir_
	$(cpp) $(src)/Meyer1997/gcd/main.cpp $(out)$(build)/gcd
maxarray: mkdir_
	$(cpp) $(src)/Meyer1997/maxarray/main.cpp $(out)$(build)/maxarray

Stroustrup1997: string
string: mkdir_
	$(cpp) $(src)/Stroustrup1997/string/string.cpp $(src)/Stroustrup1997/string/main.cpp $(out)$(build)/string

