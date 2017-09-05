// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Subcontracting and static invariant example (ported from Eiffel code).

#ifndef COURIERS_HPP_
#define COURIERS_HPP_

#include <contract.hpp>
#include <string>

/** Basic package information. */
struct package {
    /** Weight in kilograms. */ 
    double weight_kg;
    /** Current location. */
    std::string location;
    /** Hour when it was accepted for delivery (from some 0-hour). */
    double accepted_hour;
    /** Hour when was delivered (from some 0-hour). */
    double delivered_hour;
    
    package(const double& the_weight_kg,
            const std::string the_location = "",
            const double& the_accepted_hour = 0.0,
            const double& the_delivered_hour = 0.0):
            weight_kg(the_weight_kg),
            location(the_location),
            accepted_hour(the_accepted_hour),
            delivered_hour(the_delivered_hour)
            {}
};

/** Basic courier for package delivery. */
class courier {

    CONTRACT_INVARIANT( (static) ({
        CONTRACT_ASSERT( min_insurance_dollar > 0.0 );
    }) ({
        CONTRACT_ASSERT( insurance_cover_dollar() >=
                min_insurance_dollar );
    }) )

public:
    static double min_insurance_dollar;

    // Creation //

    /** Create courier with specified insurance value. */
    courier(const double& insurance_cover_dollar = 
            min_insurance_dollar):
            insurance_cover_dollar_(insurance_cover_dollar)
    CONTRACT_CONSTRUCTOR( (class) (courier)
            (public) (courier)(
                    (const double&)(insurance_cover_dollar) )
    (precondition) ({
        CONTRACT_ASSERT( insurance_cover_dollar > 0.0 );
    })
    (body) (
        ;
    ) )

    /** Destroy courier. */
    virtual ~courier(void)
    CONTRACT_DESTRUCTOR( (class) (courier)
            (public) (courier)( (void) )
    (body) (
        ;
    ) )

    // Queries //

    /** Return insurance cover. */
    double insurance_cover_dollar(void) const
    CONTRACT_FUNCTION( (class) (courier)
            (public) (double) (insurance_cover_dollar)( (void) )
            (const)
    (body) (
        ;
    ) )

    // Commands //

    /** Deliver package to destination. */
    virtual void deliver(package& the_package,
            const std::string& destination)
    CONTRACT_FUNCTION( (class) (courier)
            (public) (virtual) (void) (deliver)(
                    (package&)(the_package)
                    (const std::string&)(destination) )
    (precondition) ({
        CONTRACT_ASSERT_MSG( the_package.weight_kg <= 5.0,
                "max weight" );
    })
    (postcondition) ({
        CONTRACT_ASSERT_MSG( (the_package.delivered_hour -
                the_package.accepted_hour) <= 3.0,
                "max delivery time" );
        CONTRACT_ASSERT_MSG( the_package.location == destination,
                "delivered at destination" );
    })
    (body) (
        ;
    ) )

private:
    double insurance_cover_dollar_;
};

/** Different courier for package delivery. */
class different_courier: public courier {

    CONTRACT_INVARIANT( (static) ({
        // Stronger invariant on insurance value (higher amount).
        CONTRACT_ASSERT( different_insurance_dollar >=
                courier::min_insurance_dollar );
    }) ({
        CONTRACT_ASSERT( insurance_cover_dollar() >=
                different_insurance_dollar );
    }) )

public:
    static double different_insurance_dollar;

    // Creation //

    /** Create courier with specified insurance value. */
    different_courier(const double& insurance_cover_dollar =
            different_insurance_dollar):
            courier(insurance_cover_dollar)
    CONTRACT_CONSTRUCTOR( (class) (different_courier)
            (public) (different_courier)(
                    (const double&)(insurance_cover_dollar) )
    (precondition) ({
        CONTRACT_ASSERT( insurance_cover_dollar >= 0.0 );
    })
    (body) (
        ;
    ) )

    /** Destroy courier. */
    virtual ~different_courier(void)
    CONTRACT_DESTRUCTOR( (class) (different_courier)
            (public) (virtual) (different_courier)( (void) )
    (body) (
        ;
    ) )

    // Commands //

    virtual void deliver(package& the_package,
            const std::string& destination)
    CONTRACT_FUNCTION( (class) (different_courier) (inherit)(courier)
            (public) (virtual) (void) (deliver)(
                    (package&)(the_package)
                    (const std::string&)(destination) )
    (precondition) ({
        // Weaker precondition on weight (can weight more).
        CONTRACT_ASSERT( the_package.weight_kg <= 8.0 );
    })
    (postcondition) ({
        // Stronger postcondition on deliver time (faster deliver).
        CONTRACT_ASSERT( (the_package.delivered_hour -
                the_package.accepted_hour) <= 2.0 );
        // Inherits "delivered at destination" postcondition.
    })
    (body) (
        ;
    ) )
};

#endif // #include guard

