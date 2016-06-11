
#ifndef BOOST_CONTRACT_DETAIL_ALWAYS_TRUE_HPP_
#define BOOST_CONTRACT_DETAIL_ALWAYS_TRUE_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

namespace boost { namespace contract { namespace detail {

struct always_true {
    template<class> struct result; // To support boost::result_of.
    template<class F> struct result<F()> { typedef bool type; };

    bool operator()() { return true; }
};

} } } // namespace

#endif // #include guard

