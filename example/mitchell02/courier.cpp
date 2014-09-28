
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_courier
// File: courier.cpp
#include "courier.hpp"

// Courier.

double courier::min_insurance_dollar = 10.0e+6;

CONTRACT_CONSTRUCTOR_BODY(courier, courier) (
        double const an_insurance_cover_dollar )
{
    insurance_cover_dollar_ = an_insurance_cover_dollar;
}

CONTRACT_DESTRUCTOR_BODY(courier, ~courier) ( void ) {}

double courier::CONTRACT_MEMBER_BODY(insurance_cover_dollar) ( void ) const
    { return insurance_cover_dollar_; }

void courier::CONTRACT_MEMBER_BODY(deliver) ( package& the_package,
        std::string const destination )
{
    the_package.location = destination;
    // Delivery takes 2.5 hours.
    the_package.delivered_hour = the_package.accepted_hour + 2.5;
}

// Different courier.

double different_courier::different_insurance_dollar = 20.0e+6;

CONTRACT_DESTRUCTOR_BODY(different_courier, ~different_courier) ( void ) {}

void different_courier::CONTRACT_MEMBER_BODY(deliver) ( package& the_package,
        std::string const destination )
{
    the_package.location = destination;
    // Delivery takes only 0.5 hours.
    the_package.delivered_hour = the_package.accepted_hour + 0.5;
}
//]

