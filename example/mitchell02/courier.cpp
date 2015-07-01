
//[mitchell02_courier
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>

struct package {
    double weight_kg;
    std::string location;
    double accepted_hour;
    double delivered_hour;

    explicit package(
        double _weight_kg,
        std::string const& _location = "",
        double _accepted_hour = 0.0,
        double _delivered_hour = 0.0
    ) :
        weight_kg(_weight_kg),
        location(_location),
        accepted_hour(_accepted_hour),
        delivered_hour(_delivered_hour)
    {}
};

// Courier for package delivery.
class courier
    #define BASES private boost::contract::constructor_precondition<courier>
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        // Above min. insurance.
        BOOST_CONTRACT_ASSERT(insurance_cover_usd() >= min_insurance_usd);
    }

    static void static_invariant() {
        // Positive min. insurance.
        BOOST_CONTRACT_ASSERT(min_insurance_usd >= 0.0);
    }
    
    static double min_insurance_usd;

    /* Creation */

    // Create courier with specified insurance value.
    explicit courier(double _insurance_cover_usd = min_insurance_usd) :
        boost::contract::constructor_precondition<courier>([&] {
            // Positive insurance.
            BOOST_CONTRACT_ASSERT(_insurance_cover_usd >= 0.0);
        }),
        insurance_cover_usd_(_insurance_cover_usd)
    {
        auto c = boost::contract::constructor(this); // Check invariants.
    }

    // Destroy courier.
    virtual ~courier() {
        auto c = boost::contract::destructor(this); // Check invariants.
    }

    /* Queries */

    // Return insurance cover.
    double insurance_cover_usd() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return insurance_cover_usd_;
    }

    /* Commands */

    // Deliver package to destination.
    virtual void deliver(
        package& package_delivery,
        std::string const& destination,
        boost::contract::virtual_* v = 0
    ) {
        auto c = boost::contract::public_function(v, this)
            .precondition([&] {
                // Within max weight of this delivery.
                BOOST_CONTRACT_ASSERT(package_delivery.weight_kg < 5.0);
            })
            .postcondition([&] {
                // Within max delivery type.
                BOOST_CONTRACT_ASSERT(double(package_delivery.delivered_hour -
                        package_delivery.accepted_hour) <= 3.0);
                // Delivered at destination.
                BOOST_CONTRACT_ASSERT(package_delivery.location == destination);
            })
        ;

        package_delivery.location = destination;
        // Delivery takes 2.5 hours.
        package_delivery.delivered_hour = package_delivery.accepted_hour + 2.5;
    }

private:
    double insurance_cover_usd_;
};

double courier::min_insurance_usd = 10.0e+6;

// Different courier for package delivery.
class different_courier
    #define BASES private boost::contract::constructor_precondition< \
            different_courier>, public courier
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types; // Subcontracting.
    #undef BASES

    void invariant() const {
        // Above different insurance value.
        BOOST_CONTRACT_ASSERT(insurance_cover_usd() >= different_insurance_usd);
    }

    static void static_invariant() {
        BOOST_CONTRACT_ASSERT( // Better insurance amount.
                different_insurance_usd >= courier::min_insurance_usd);
    }

    static double different_insurance_usd;

    /* Creation */

    // Create courier with specified insurance value.
    explicit different_courier(
            double insurance_cover_usd = different_insurance_usd) :
        boost::contract::constructor_precondition<different_courier>([&] {
            // Positive insurance value.
            BOOST_CONTRACT_ASSERT(insurance_cover_usd > 0.0);
        }),
        courier(insurance_cover_usd)
    {
        auto c = boost::contract::constructor(this); // Check invariants.
    }

    // Destroy courier.
    virtual ~different_courier() {
        auto c = boost::contract::destructor(this); // Check invariants.
    }

    /* Commands */

    virtual void deliver(
        package& package_delivery,
        std::string const& destination,
        boost::contract::virtual_* v = 0
    ) /* override */ {
        auto c = boost::contract::public_function<override_deliver>(
            v, &different_courier::deliver, this, package_delivery, destination
        )
            .precondition([&] {
                // Package can weight more (weaker precondition).
                BOOST_CONTRACT_ASSERT(package_delivery.weight_kg <= 8.0);
            })
            .postcondition([&] {
                // Faster delivery (stronger postcondition).
                BOOST_CONTRACT_ASSERT(double(package_delivery.delivered_hour -
                        package_delivery.accepted_hour) <= 2.0);
                // Inherited "delivery at destination" postcondition.
            })
        ;

        package_delivery.location = destination;
        // Delivery takes 0.5 hours.
        package_delivery.delivered_hour = package_delivery.accepted_hour + 0.5;
    }
    BOOST_CONTRACT_OVERRIDE(deliver)
};

double different_courier::different_insurance_usd = 20.0e+6;

int main() {
    package cups(3.6, "store");
    courier c;
    c.deliver(cups, "home");
    BOOST_TEST_EQ(cups.location, "home");

    package desk(7.2, "store");
    different_courier dc;
    dc.deliver(desk, "office");
    BOOST_TEST_EQ(desk.location, "office");
    
    return boost::report_errors();
}
//]

