
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_SUBCONTRACT_FROM_HPP_
#define CONTRACT_AUX_SUBCONTRACT_FROM_HPP_

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>

namespace contract { namespace aux {

namespace private_ { // This type should not be used outside this file.
    template< class Derived, class Base >
    struct not_subcontracted_tag {
        // NOTE: This is the special type used to tag a pair Derived-Base when
        // a function in the Derived class shall not subcontract from the Base
        // class (because no base class function is actually being overridden).
        // It is necessary to use the Derived type itself in order to compile
        // because the rest of the code will assume this tag type has
        // precondition, old-of, etc functions.
        typedef Derived type; 
    };
} // namespace private_

template< class Derived, class Base >
struct is_subcontracted_from : 
    boost::mpl::not_< boost::is_same< 
          Base
        , typename private_::not_subcontracted_tag< Derived, Base >::type
    > >
{};

// BaseHasFunction should be mpl::true_ iff Base a virtual function matching
// the overriding function being subcontracted which can either be the base
// virtual function or the (dynamic, static, or volatile) class invariant
// function (use introspection).
template< class Derived, class Base, class BaseHasFunction >
struct subcontract_from {
    // Subcontract iff Base != Derived && HasVirtualFunction
    typedef typename boost::mpl::if_<
            boost::mpl::and_<
                  boost::mpl::not_< boost::is_same< Base, Derived > >
                , BaseHasFunction
            >
        , Base // Subcontract (by returning the given base type).
        // Don't subcontract (by tagging with a special type).
        , typename private_::not_subcontracted_tag< Derived, Base >::type
    >::type type;
};

}} // namespace contract::aux

#endif // #include guard

