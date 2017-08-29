
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include "free_concept_operator_preinc.hpp"
#include <boost/detail/lightweight_test.hpp>

struct num
{
    explicit num ( int value ) : value_(value) {}

    // Intentionally missing `operator+`.
    public: bool operator== ( num const& right ) const
        { return value_ == right.value_; }

    private: int value_;
};

int main ( void )
{
    num n(1), m(2);
    ++n; // Correctly error, `num` not `Addable`.
    BOOST_TEST(n == m);
    return boost::report_errors();
}

