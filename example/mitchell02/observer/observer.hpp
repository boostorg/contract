
//[mitchell02_observer
#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <boost/contract.hpp>
#include <cassert>

// Observer.
class observer {
    friend class subject;
public:
    // No inv and no bases so contracts optional if no pre, post, and override.

    /* Creation */

    observer() {
        boost::contract::guard c = boost::contract::constructor(this);
    }
    
    virtual ~observer() {
        boost::contract::guard c = boost::contract::destructor(this);
    }

    /* Commands */

    // If up-to-date with related subject.
    virtual bool up_to_date_with_subject(boost::contract::virtual_* v = 0)
            const = 0;

    // Update this observer.
    virtual void update(boost::contract::virtual_* v = 0) = 0;
};

bool observer::up_to_date_with_subject(boost::contract::virtual_* v) const {
    boost::contract::guard c = boost::contract::public_function(v, this);
    assert(false);
    return false;
}

void observer::update(boost::contract::virtual_* v) {
    boost::contract::guard c = boost::contract::public_function(v, this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(up_to_date_with_subject()); // Up-to-date.
        })
    ;
    assert(false);
}

#endif // #include guard
//]

