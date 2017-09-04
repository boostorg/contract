/* $Id$ */

#include "couriers.hpp"

double Courier::DBC_BODY(insuranceCoverDollar)() const 
    { return insuranceCoverDollar_; }

void Courier::DBC_BODY(deliver)(Package& package, 
        const std::string& destination) {
    package.location = destination;
    package.deliveredHour = package.acceptedHour + 2.5;
}

void DifferentCourier::DBC_BODY(deliver)(
        Package& package, const std::string& destination) {
    package.location = destination;
    package.deliveredHour = package.acceptedHour + 0.5;
}

