
#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include "../observer/subject.hpp"
#include <boost/contract.hpp>

class counter
    #define BASES public subject
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    /* Creation */

    // Construct counter with specified value.
    explicit counter(int _value = 10) : value_(_value) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(value() == _value); // Value set.
            })
        ;
    }

    // Destroy counter.
    virtual ~counter() { auto c = boost::contract::destructor(this); }

    /* Queries */

    // Current counter value.
    int value() const {
        auto c = boost::contract::public_function(this);
        return value_;
    }

    /* Commands */

    // Decrement counter value.
    void decrement() {
        auto old_value = BOOST_CONTRACT_OLDOF(value());
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(value() == *old_value - 1); // Decrement.
            })
        ;

        --value_;
        notify(); // Notify all attached observers.
    }

private:
    int value_;
};

#endif // #include guard

