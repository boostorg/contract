/* $Id$ */

#ifndef COURIERS_HPP_
#define COURIERS_HPP_

#include <dbc.hpp>
#include <string>

/** Basic package information. */
class Package {
public:
    /** Package weight in kilograms. */
    double weightKg;
    /** Package current location. */
    std::string location;
    /** Hour at which package was accepted for delivery (for "zero hours"). */
    double acceptedHour;
    /** Hour at which package was delivered (from "zero hours"). */
    double deliveredHour;

    /** Construct a package with specified information. */
    Package(const double& theWeightKg, const std::string& theLocation = "", 
            const double& theAcceptedHour = 0.0,
            const double& theDeliveredHour = 0.0):
            weightKg(theWeightKg), location(theLocation), 
            acceptedHour(theAcceptedHour), deliveredHour(theDeliveredHour) {}
};

/** A basic courier for package delivery. */
class Courier DBC_INHERIT_OBJECT(Courier) {
public:
    // Creation //

    /** Create courier with specified insurance coverage. */
    Courier(const double& insuranceCoverDollar = 10.0e+6):
            insuranceCoverDollar_(insuranceCoverDollar)
    DBC_CONSTRUCTOR( (public) (Courier)
            ( (const double&)(insuranceCoverDollar) ), {
        DBC_ASSERT(insuranceCoverDollar > 0.0, "positive insurance $");
    }, {
    }, {})

    /** Destroy this object. */
    virtual ~Courier()
    DBC_DESTRUCTOR( (public) (Courier)(), {})

    // Queries //

    /** Return insurance cover. */
    double insuranceCoverDollar() const
    DBC_MEM_FUN( (public) (double) (Courier)
            (insuranceCoverDollar)() (const), {
    }, {
    }, ;)

    // Commands //

    /** Deliver given package at specified destination. */
    virtual void deliver(Package& package, const std::string& destination)
    DBC_MEM_FUN( (public) (virtual) (void) (Courier) 
            (deliver)( (Package&)(package) 
            (const std::string&)(destination) ), {
        DBC_ASSERT_STREAM(package.weightKg <= 5, "max weight",
                err << "weight " << package.weightKg << " kg exceeds 5 kg");
    }, {
        DBC_ASSERT_STREAM(
                (package.now.deliveredHour - package.now.acceptedHour) <= 3,
                "max delivery time",
                err << "delivered at " << package.now.deliveredHour 
                << " hours in more than 3 working hours of accepted hour "
                << package.now.acceptedHour);
        DBC_ASSERT_STREAM(package.now.location == destination.now,
                "at destination",
                err << "location '" << package.now.location 
                << "' is not destination '" << destination.now << "'");
    }, ;)

private:
    double insuranceCoverDollar_;
    
    DBC_INVARIANT(Courier, {
        DBC_ASSERT_STREAM(self.insuranceCoverDollar() >= 10.0e+6,
                "min insurance",
                err << "insured $" << self.insuranceCoverDollar() 
                << " less than $10.0e+6");
    })
};

/** A different courier for package delivery. */
class DifferentCourier: public Courier DBC_TRAILING_OBJECT(DifferentCourier) {
public:
    // Creation //

    /** Create different courier with specified insurance coverage. */
    DifferentCourier(const double& insuranceCoverDollar = 20.0e+6):
            Courier(insuranceCoverDollar)
    DBC_CONSTRUCTOR( (public) (DifferentCourier)
            ( (const double&)(insuranceCoverDollar) ), {
        DBC_ASSERT(insuranceCoverDollar > 0.0, "positive insurance $");
    }, {
    }, {})
    
    /** Destroy this object. */
    virtual ~DifferentCourier()
    DBC_DESTRUCTOR( (public) (DifferentCourier)(), {})

    // Commands //

    virtual void deliver(Package& package, const std::string& destination)
    DBC_MEM_FUN( (public) (virtual) (void) (DifferentCourier)DBC_BASE(Courier)
            (deliver)( (Package&)(package) 
            (const std::string&)(destination) ), {
        DBC_ASSERT_STREAM(package.weightKg <= 8,
                "min weight",
                err << "weight " << package.weightKg 
                << " kg does exceeds 8 kg");
    }, {
        DBC_ASSERT_STREAM(
                (package.now.deliveredHour - package.now.acceptedHour) <= 2,
                "min delivery time",
                err << "delivered at " << package.now.deliveredHour 
                << " hours in more than 2 working hours of accepted hour "
                << package.now.acceptedHour);
        // Postcondition "at destination" inherited unchanged from base 
        // contract -- no need to re-write it here.
    }, ;)

private:
    DBC_INVARIANT(DifferentCourier, {
        DBC_ASSERT_STREAM(self.insuranceCoverDollar() >= 20.0e+6,
                "min insurance",
                err << "insured $" << self.insuranceCoverDollar() 
                << " less than $20.0e+6");
    })
};

#endif // COURIERS_HPP_

