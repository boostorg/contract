
//[mitchell02_observer
#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <boost/contract.hpp>

// Observer.
class observer {
public:
    // No inv so contracts could have been omitted when also no pre/post...

    /* Creation */

    observer() { auto c = boost::contract::constructor(this); }
    
    virtual ~observer() { auto c = boost::contract::destructor(this); }

    /* Commands */

    // If up-to-date with related subject.
    virtual bool up_to_date_with_subject(boost::contract::virtual_* v = 0)
            const = 0;

    // Update this observer.
    virtual void update(boost::contract::virtual_* v = 0) = 0;

private:
    friend class subject;
};

bool observer::up_to_date_with_subject(boost::contract::virtual_* v) const {
    auto c = boost::contract::public_function(this);
    return false; // Never reached.
}

void observer::update(boost::contract::virtual_* v) {
    auto c = boost::contract::public_function(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(up_to_date_with_subject()); // Up-to-date.
        })
    ;
}

#endif // #include guard
//]

