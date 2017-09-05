
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[member_named_params_callable2
namespace calls {

CONTRACT_PARAMETER(arg1)
CONTRACT_PARAMETER(arg2)

CONTRACT_CLASS(
    struct (callable2)
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION( // Member function with named parameters.
        public void (call) ( in int arg1, in int arg2 )
    ) ; // Body definition can be separated...

    CONTRACT_FUNCTION( // Constant member with named parameters.
        public void (call) ( in int arg1, in int arg2 ) const
    ) {
        total = arg1 + arg2;
    }

    CONTRACT_FUNCTION( // Static member with named parameters.
        public static void (static_call) ( in int arg1, in int arg2 )
    ) {
        total = arg1 + arg2;
    }

    static int total;
};

// ... but body definition uses template parameters and special `BODY` macro.
template< typename Arg1, typename Arg2 >
void callable2::CONTRACT_PARAMETER_BODY(call)( Arg1 arg1, Arg2 arg2 )
{
    total = arg1 + arg2;
}

int callable2::total = 0;

} // namespace
//]

int main ( void )
{
    //[member_named_params_callable2_calls
    calls::callable2::static_call(calls::arg2_ = 2, calls::arg1_ = 1);
    BOOST_TEST(calls::callable2::total == 3);
    
    calls::callable2 c;
    c.call(calls::arg2_ = 3, calls::arg1_ = 4);
    BOOST_TEST(calls::callable2::total == 7);
    
    calls::callable2 const& cc = c;
    cc.call(calls::arg2_ = 5, calls::arg1_ = 6);
    BOOST_TEST(calls::callable2::total == 11);
    //]
    return boost::report_errors();
}
//]

