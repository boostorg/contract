
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

// Declare parameter identifiers within `params` namespace (this should never
// be necessary) and argument identifiers ...Arg / ..._arg instead of ..._.
//[named_param_identifiers_positive_keywords
CONTRACT_TEMPLATE_PARAMETER( namespace(params) (NumberArg) Number )
CONTRACT_PARAMETER( namespace(params) (value_arg) value )
//]

//[named_param_identifiers_positive
CONTRACT_CLASS(
    // Named template parameters must specify `params` namespace.
    template( using namespace params, in typename Number )
    struct (positive)
) {
    CONTRACT_CLASS_INVARIANT_TPL( get() > 0 )

    CONTRACT_CONSTRUCTOR_TPL(
        // Named parameters must specify `params` namespace.
        public (positive) ( using namespace params, in (Number) value )
            precondition( value > 0 ) 
            postcondition( get() == value )
            initialize( value_(CONTRACT_CONSTRUCTOR_ARG(value)) )
    ) { }

    CONTRACT_FUNCTION_TPL(
        public (Number const&) (get) ( void ) const
    ) {
        return value_;
    }

    private: Number value_;
};
//]

int main ( void )
{
    //[named_param_identifiers_positive_call
    positive<NumberArg<int> > n(value_arg = 123); // Use ...Arg and ..._arg.
    //]
    BOOST_TEST(n.get() == 123);
    return boost::report_errors();
}
//]

