
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_NAMED_PARAMS_HPP_
#define CONTRACT_AUX_NAMED_PARAMS_HPP_

#include <boost/parameter.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace contract { namespace aux { namespace named_params {

// To declare default value for required parameters (which have no default).
struct no_default
{
    // Dummy param so it can be decl as a default parameter with `... = 0`.
    no_default ( int const& ) {}
};

// Hold Boost.Parameter arg_list so it can be set during ctor member inits.
template< typename ArgList >
struct args
{
    // Dummy param so it can be decl as a default parameter with `... = 0`.
    args ( int const& ) : ptr_() {}
    int set ( ArgList const& arg_list ) {
        ptr_ = boost::shared_ptr<ArgList>(new ArgList(arg_list));
        return 0;
    }
    ArgList& get ( void ) { return *(ptr_.get()); }
private:
    boost::shared_ptr<ArgList> ptr_;
};

template< typename ArgList, typename Tag >
class find_tag {
    typedef typename ArgList::key_type current_tag;
    typedef typename ArgList::tail_type next_elem;
    typedef typename boost::mpl::if_<boost::is_same<current_tag, Tag>,
        boost::mpl::identity<ArgList>
    ,
        find_tag<next_elem, Tag>
    >::type elem;
public:
    typedef typename elem::type type;
};

template< typename Tag >
struct find_tag<boost::parameter::aux::empty_arg_list, Tag> {
    typedef boost::parameter::aux::empty_arg_list type;
};

template< typename ArgList, typename Tag, typename Default = no_default >
class arg_type {
    template< typename ArgElem >
    struct arg_reference {
        // NOTE: Using reference here prevent to assign in parameters within
        // the body (this makes in parameters equivalent to const&). If
        // value_type is used instead of reference here, in-parameters can be
        // assigned with the body but their changes are not visible to the
        // calling scope (this makes in parameters equivalent to passing by
        // value but not by const&). In either case, in-out and out parameters
        // are passed by (non-const) & so their changes are visible to the
        // calling scope. Following Ada and Boost.Parameter semantics, in
        // parameters should be const& (and not just passed by value) so
        // reference and not value_type is correctly used here.
        typedef typename ArgElem::reference type;
    };
    typedef typename find_tag<ArgList, Tag>::type arg_elem;
public:
    typedef typename boost::mpl::if_<boost::is_same<arg_elem,
            boost::parameter::aux::empty_arg_list>,
        boost::mpl::identity<Default>
    ,
        arg_reference<arg_elem>
    >::type::type type;
};

}}} // namespace contract::aux::named_params

#endif // #include guard

