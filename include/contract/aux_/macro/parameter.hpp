
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_PARAMETER_HPP_
#define CONTRACT_AUX_PARAMETER_HPP_

// PUBLIC //

#define CONTRACT_AUX_PARAMETER_BOOST_TYPE(param_name) \
    /* use this name instead of Boost.Parameter's ..._type so (1) the same */ \
    /* can be used in both the parameter requirement metafunction, (2) */ \
    /* users don't have to use tag::paran_name::_ that explictly specifies */ \
    /* the tag namespace, and (3) limits the use of ..._type which can lead */ \
    /* to reserved symbols for param names ending with _ */ \
    CONTRACT_AUX_SYMBOL( (param_name)(type) )

#define CONTRACT_AUX_PARAMETER_BOOST_PARAM( \
        tag_namespace, passing_name, name) \
    BOOST_PARAMETER_NAME( (passing_name, tag_namespace) name ) \
    /* this hides the use of the tag namespace and allows to use the same */ \
    /* type name in type predicates as outside the parameter list */ \
    typedef tag_namespace::name::_ \
            CONTRACT_AUX_PARAMETER_BOOST_TYPE(name);

#define CONTRACT_AUX_PARAMETER_BOOST_TEMPLATE_PARAM( \
        tag_namespace, passing_name, name) \
    /* there's no Boost.Parameter API that allows to specify namespace and */ \
    /* passing name so we need to use Boost.Parameter details directly */ \
    namespace tag_namespace { struct name; } \
    template< typename T > \
    struct passing_name \
        : ::boost::parameter::template_keyword<tag_namespace::name, T> \
    {};

#endif // #include guard

