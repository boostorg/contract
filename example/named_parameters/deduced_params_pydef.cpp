
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <boost/python.hpp> // First include (a bug uses and, or, etc keywords).
#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/regex.hpp>
#include <iostream>

namespace py {

// Helpers.

template< class P >
struct CallPolicies
{
    // Following concepts could also be programmed:
    // BOOST_CONCEPT_ASSERT((ResultConverterGenerator<P::result_converter>));
    // BOOST_CONCEPT_ASSERT((Metafunction<P::extract_return_type>));

    BOOST_CONCEPT_USAGE(CallPolicies)
    {
        convertible_to_bool(x.precall(a));
        convertible_to_pyobject(x.postcall(a, r));
    }
    
private:
    void convertible_to_bool ( bool );
    void convertible_to_pyobject ( PyObject* );

    P x;
    PyObject* a;
    PyObject* r;
};

bool is_identifier ( char const* name )
{
    static const boost::regex re("(\\l|\\u|_)(\\l|\\u|\\d|_)*");
    return boost::regex_match(name, re);
}

template< typename T > struct is_keyword_expression :
    boost::mpl::bool_< boost::python::detail::is_keywords<T>::value >
{};

boost::python::detail::keywords<0> no_keywords ( void )
    { return boost::python::detail::keywords<0>(); }

} // namespace

//[deduced_params_pydef_decl
namespace py {

CONTRACT_PARAMETER(name)
CONTRACT_PARAMETER(func)
CONTRACT_PARAMETER(docstring)
CONTRACT_PARAMETER(keywords)
CONTRACT_PARAMETER(policies)

CONTRACT_FUNCTION(
    void (def) (
            // Non-deduced (and also required) named parameters.
            in (char const*) name,
            in auto func,
            // Deduced (and also optional) named parameters.
            deduce in (char const*) docstring, default (""),
            deduce in requires(is_keyword_expression<boost::mpl::_>) keywords,
                    default no_keywords(),
            // Type requirements also used to uniquely deduce parameters.
            deduce in requires(
                boost::mpl::not_<
                    boost::mpl::or_<
                          boost::is_convertible<boost::mpl::_, char const*>
                        , is_keyword_expression<boost::mpl::_>
                    >
                >
            ) policies, default boost::python::default_call_policies()
        // Concepts for named parameters.
        ) requires( CallPolicies<CONTRACT_PARAMETER_TYPEOF(policies)> )
        precondition( is_identifier(name) ) // Contracts.
) {
    boost::python::def(name, func, docstring, keywords, policies);
}

} // namespace
//]

template< char Name >
void print ( void ) { std::cout << "called " << Name << std::endl; }

#ifndef PYMODULE
#   error "PYMODULE must define a valid Boost.Python module name"
#endif

// Python module, in a Python shell from this directory run:
// >>> from <PYMODULE> import * # Check contracts (preconditions, etc).
// >>> help("<PYMODULE>"), f(), g(), h()
BOOST_PYTHON_MODULE(PYMODULE)
{
    boost::python::default_call_policies nonstring_policies, string_policies;
    //[deduced_params_pydef_calls
    py::def("f", print<'f'>, nonstring_policies, "Documentation for f");
    py::def("g", print<'g'>, "Documentation for g", nonstring_policies);
    py::def("h", print<'h'>, py::policies_ = string_policies,
            "Documentation for h");
    //]
}

