
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[cline90_calendar
// File: calendar.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

CONTRACT_CLASS(
    class (calendar)
) {
    CONTRACT_CLASS_INVARIANT(
        month() >= 1,
        month() <= 12,
        date() >= 1,
        date() <= days_in(month())
    )

    CONTRACT_CONSTRUCTOR(
        public (calendar) ( void )
            postcondition( month() == 1, date() == 31 )
            initialize( month_(1), date_(31) )
    ) {}

    CONTRACT_DESTRUCTOR(
        public virtual (~calendar) ( void )
    ) {}

    CONTRACT_FUNCTION(
        public int (month) ( void ) const
    ) {
        return month_;
    }

    CONTRACT_FUNCTION(
        public int (date) ( void ) const
    ) {
        return date_;
    }

    CONTRACT_FUNCTION(
        public void (reset) ( int new_month )
            precondition( new_month >= 1, new_month <= 12 )
            postcondition( month() == new_month )
    ) {
        month_ = new_month;
    }

    CONTRACT_FUNCTION(
        private static int (days_in) ( int month )
            precondition( month >= 1, month <= 12 )
            postcondition( auto result = return, result >= 1, result <= 31 )
    ) {
        return 31; // For simplicity, assume all months have 31 days.
    }
    
    private: int month_, date_;
};

int main ( void )
{
    calendar c;
    BOOST_TEST(c.date() == 31);
    BOOST_TEST(c.month() == 1);
    c.reset(8); // Set month to August.
    BOOST_TEST(c.month() == 8);
    return boost::report_errors();
}
//]

