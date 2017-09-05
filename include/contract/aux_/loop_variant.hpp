
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_LOOP_VARIANT_HPP_
#define CONTRACT_AUX_LOOP_VARIANT_HPP_

#include <contract/aux_/macro/code_/loop_variant.hpp>

namespace contract { namespace aux { namespace loop_variant {

// NOTE: Loop variant must be >= 0 however that property is asserted instead of
// using unsigned type here because C++ will still allow to assign signed
// numbers to unsigned variables causing the variable to silently overflow
// (instead of generating a compile-time error).
typedef long value_type;

static const value_type uninitialized = -1;

// Declared/undeclared trick to handle duplicate decl (from Boost.ScopeExit).
// NOTE: This declared/undeclared mechanism cannot be made generic with respect
// to value_type because otherwise sizeof used for tpl spec below will depend
// of the tparam used instead of value_type.
template< int DUMMY = 0 > struct declared {
    value_type value;
    static int const cmp2 = 0;
    friend void operator> ( int, declared const& ) {}
};

struct undeclared { declared<> dummy[2]; };

template< int > struct resolve;
template<> struct resolve<sizeof(declared<>)>
    { static const int cmp1 = 0; };
template<> struct resolve<sizeof(undeclared)>
    { template< int > struct cmp1 { static int const cmp2 = 0; }; };

}}} // namespace contract::aux::loop_variant

// This must be decl extern and in global namepsace (so visible to any later
// decl of OLD_VAR in any namespace or local context). Later decl should be of
// the form `declared<resolve<sizeof(OLD_VAR)>::cmp1<0>::cmp2> OLD_VAR` which
// will decl OLD_VAR in a given context iff OLD_VAR not previously decl in that
// context (such duplicate decl will have no effect and will not error).
// NOTE: This declared/undeclared mechanism is used for loop variants so to
// avoid the introduction of another macro LOOP_END (that could be used to
// close a local block used to make the loop variant decl local). This way
// there is one less macro plus the library doesn't use _END macros for CLASS,
// FUNCTION, etc (so the macro API is more symmetric without LOOP_END).
extern contract::aux::loop_variant::undeclared
        CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR;

#endif // #include guard

