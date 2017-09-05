// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "couriers.hpp"

// Courier //

double courier::min_insurance_dollar = 10.0e+6; 

CONTRACT_CONSTRUCTOR_BODY(courier, courier)(
        const double& insurance_cover_dollar) {}

CONTRACT_DESTRUCTOR_BODY(courier, ~courier)(void) {}

double courier::CONTRACT_BODY(insurance_cover_dollar)(void) const {
    return insurance_cover_dollar_;
}

void courier::CONTRACT_BODY(deliver)(package& the_package,
        const std::string& destination) {
    the_package.location = destination;
    // Delivery takes 2.5 hours.
    the_package.delivered_hour = the_package.accepted_hour + 2.5;
}

// Different Courier //

double different_courier::different_insurance_dollar = 20.0e+6; 

CONTRACT_CONSTRUCTOR_BODY(different_courier, different_courier)(
        const double& insurance_cover_dollar) {}

CONTRACT_DESTRUCTOR_BODY(different_courier, ~different_courier)(
        void) {}

void different_courier::CONTRACT_BODY(deliver)(package& the_package,
        const std::string& destination) {
    the_package.location = destination;
    // Delivery takes only 0.5 hours.
    the_package.delivered_hour = the_package.accepted_hour + 0.5;
}

