
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <memory>
#include <cstdlib>

//[assertion_statement_ialloc
CONTRACT_FUNCTION(
    template( typename T )
    (T*) (ialloc) ( void )
        precondition(
            namespace mpl = boost::mpl,                 // Namespace aliasing.
            using namespace std,                        // Using directive.
            typedef typename allocator<T>::pointer ptr, // Type definition.
            static_assert(
                  (mpl::or_<
                      mpl::bool_<sizeof(T) <= sizeof(int)>
                    , mpl::bool_<sizeof(ptr) <= sizeof(int*)>
                  >::value)
                , "within max size"
            )
        )
) {
    return static_cast<T*>(malloc(sizeof(T)));
}
//]

int main ( void )
{
    char* p = ialloc<char>();
    BOOST_TEST(p);
    return boost::report_errors();
}

