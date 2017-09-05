
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <boost/python.hpp> // First include (a bug uses and, or, etc keywords).
#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/regex.hpp>

namespace py {

bool is_identifier ( char const* name ) // Contract helper.
{
    static const boost::regex re("(\\l|\\u|_)(\\l|\\u|\\d|_)*");
    return boost::regex_match(name, re);
}

} // namespace

//[named_template_params_pyclass_keywords
namespace py {

CONTRACT_TEMPLATE_PARAMETER(ClassType)
CONTRACT_TEMPLATE_PARAMETER(Bases)
CONTRACT_TEMPLATE_PARAMETER(HeldType)
CONTRACT_TEMPLATE_PARAMETER(Copyable)
CONTRACT_PARAMETER(name)

} // namespace
//]

//[named_template_params_pyclass
namespace py {

CONTRACT_CLASS(
    template(
        // Required named template parameter.
        in typename requires(boost::is_class<boost::mpl::_>) ClassType,
        // Optional deduced named template parameters with requirements.
        deduce in typename requires(
            boost::python::detail::specifies_bases<boost::mpl::_>
        ) Bases, default boost::python::bases<>,
        deduce in typename requires(
            boost::mpl::not_<
                boost::mpl::or_<
                      boost::python::detail::specifies_bases<boost::mpl::_>
                    , boost::is_same<boost::noncopyable, boost::mpl::_>
                >
            >
        ) HeldType, default boost::python::detail::not_specified,
        deduce in typename requires(
            boost::is_same<boost::noncopyable, boost::mpl::_>
        ) Copyable, default boost::python::detail::not_specified
        // Unfortunately, non-type named template parameters are not supported.
    // Concepts named template parameters.
    ) requires( boost::DefaultConstructible<ClassType> )
    class (class_)
        extends( (boost::python::class_<ClassType, Bases, HeldType, Copyable>) )
) {
    CONTRACT_CLASS_INVARIANT_TPL( void ) // Contracts.

    public: typedef ClassType class_type;
    public: typedef Bases bases;
    public: typedef HeldType held_type;
    public: typedef Copyable copyable;
    
    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (class_) ( in (char const*) name )
            precondition( is_identifier(name) )
            initialize( 
                (boost::python::class_<ClassType, Bases, HeldType, Copyable>(
                        CONTRACT_CONSTRUCTOR_ARG(name)))
            )
    ) {}
};

} // namespace
//]

struct bx { virtual ~bx ( void ) {} };
struct x : bx {};

struct by { virtual ~by ( void ) {} };
struct y : by {};
    

typedef py::class_<py::ClassType_<bx>, py::Copyable_<boost::noncopyable> > c1;
BOOST_MPL_ASSERT((boost::is_same<c1::class_type, bx>));
BOOST_MPL_ASSERT((boost::is_same<c1::copyable, boost::noncopyable>));

typedef py::class_<x, py::HeldType_<boost::shared_ptr<x> >, 
            py::Bases_<boost::python::bases<bx> > > c2;
BOOST_MPL_ASSERT((boost::is_same<c2::class_type, x>));
BOOST_MPL_ASSERT((boost::is_same<c2::held_type, boost::shared_ptr<x> >));
BOOST_MPL_ASSERT((boost::is_same<c2::bases, boost::python::bases<bx> >));

typedef py::class_<by, boost::noncopyable> c3;
BOOST_MPL_ASSERT((boost::is_same<c3::class_type, by>));
BOOST_MPL_ASSERT((boost::is_same<c3::copyable, boost::noncopyable>));

typedef py::class_<y, boost::shared_ptr<y>, boost::python::bases<by> > c4;
BOOST_MPL_ASSERT((boost::is_same<c4::class_type, y>));
BOOST_MPL_ASSERT((boost::is_same<c4::held_type, boost::shared_ptr<y> >));
BOOST_MPL_ASSERT((boost::is_same<c4::bases, boost::python::bases<by> >));

#ifndef PYMODULE
#   error "PYMODULE must define a valid Boost.Python module name"
#endif

// Python module, in a Python shell from this directory run:
// >>> from <PYMODULE> import * # Check contracts (preconditions, etc).
// >>> help("<PYMODULE>"), xx = x(), yy = y()
BOOST_PYTHON_MODULE(PYMODULE)
{
    //[named_template_params_pyclass_calls
    // Named parameters.
    py::class_<py::ClassType_<bx>, py::Copyable_<boost::noncopyable> >("bx");
    py::class_<x, py::HeldType_<boost::shared_ptr<x> >, 
            py::Bases_<boost::python::bases<bx> > >("x");
    // Deduced parameters.
    py::class_<by, boost::noncopyable>("by");
    py::class_<y, boost::shared_ptr<y>, boost::python::bases<by> >(
            py::name_ = "y");
    //]
}

