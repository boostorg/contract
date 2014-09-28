
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_courier_header
// File: courier.hpp
#ifndef COURIER_HPP_
#define COURIER_HPP_

#include <contract.hpp>
#include <string>

struct package // Basic package information.
{
    public: double weight_kg; // Weight in kilograms.
    public: std::string location; // Current location.
    public: double accepted_hour; // Hour when it was accepted for delivery.
    public: double delivered_hour; // Hour when it was delivered.

    public: explicit package (
            double const a_weight_kg,
            std::string const a_location = "",
            double const an_accepted_hour = 0.0,
            double const a_delivered_hour = 0.0
        )
        :   weight_kg(a_weight_kg),
            location(a_location),
            accepted_hour(an_accepted_hour),
            delivered_hour(a_delivered_hour)
    {}
};

CONTRACT_CLASS( // Basic courier for package delivery.
    class (courier)
) {
    CONTRACT_CLASS_INVARIANT(
        insurance_cover_dollar() >= min_insurance_dollar, // above min insur.
        static class( // Static class invariants.
            min_insurance_dollar > 0.0 // positive min insurance
        )
    )

    public: static double min_insurance_dollar;

    // Creation.

    CONTRACT_CONSTRUCTOR( // Create courier with specified insurance value.
        public explicit (courier) (
                double const an_insurance_cover_dollar,
                        default min_insurance_dollar
            )
            precondition( an_insurance_cover_dollar > 0.0 ) // positive insur.
    ) ; // Deferred body definition.

    CONTRACT_DESTRUCTOR( // Destroy courier.
        public virtual (~courier) ( void )
    ) ;

    // Queries.

    CONTRACT_FUNCTION( // Return insurance cover.
        public double (insurance_cover_dollar) ( void ) const
    ) ;

    // Commands.

    CONTRACT_FUNCTION( // Deliver package to destination.
        public virtual void (deliver) ( (package&) the_package,
                (std::string const) destination )
            precondition(
                the_package.weight_kg < 5.0 // within max wight
            )
            postcondition(
                double(the_package.delivered_hour - the_package.accepted_hour)
                        <= 3.0, // within max delivery time
                the_package.location == destination // delivered at destination
            )
    ) ;

    private: double insurance_cover_dollar_;
};

CONTRACT_CLASS( // Different courier for package delivery.
    class (different_courier) extends( public courier )
) {
    CONTRACT_CLASS_INVARIANT(
        insurance_cover_dollar() >= different_insurance_dollar,
        static class(
            different_insurance_dollar >= courier::min_insurance_dollar
        )
    )

    public: static double different_insurance_dollar;

    // Creation.

    CONTRACT_CONSTRUCTOR( // Create currier with specified insurance value.
        public explicit (different_courier) (
                double const insurance_cover_dollar,
                        default different_insurance_dollar
            )
            precondition( insurance_cover_dollar > 0.0 )
            initialize( courier(insurance_cover_dollar) )
    ) {} // Cannot separated body definition because has member initializers.

    CONTRACT_DESTRUCTOR( // Destroy courier.
        public virtual (~different_courier) ( void )
    ) ;

    // Commands.

    CONTRACT_FUNCTION(
        public virtual void (deliver) ( (package&) the_package,
                (std::string const) destination ) override final
            precondition(
                // Weaker precondition on weight (it can weight more).
                the_package.weight_kg <= 8.0
            )
            postcondition(
                // Stronger postcondition on delivery time (faster delivery).
                double(the_package.delivered_hour - the_package.accepted_hour)
                        <= 2.0
                // Inherits "delivered at destination" postcondition.
            )
    ) ;
};

#endif // #include guard
//]

