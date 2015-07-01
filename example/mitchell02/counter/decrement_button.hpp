
//[mitchell02_decrement_button
#ifndef DECREMENT_BUTTON_HPP_
#define DECREMENT_BUTTON_HPP_

#include "push_button.hpp"
#include "counter.hpp"
#include "../observer/observer.hpp"
#include <boost/contract.hpp>
#include <boost/noncopyable.hpp>

class decrement_button
    #define BASES public push_button, public observer, \
            private boost::noncopyable
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    /* Creation */

    explicit decrement_button(counter& _counter) : counter_(_counter) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                // Enable iff positive value.
                BOOST_CONTRACT_ASSERT(enabled() == (_counter.value() > 0));
            })
        ;
        counter_.attach(this);
    }

    // Destroy button.
    virtual ~decrement_button() { auto c = boost::contract::destructor(this); }

    /* Commands */

    virtual void on_bn_clicked(boost::contract::virtual_* v = 0)
            /* override */ {
        auto old_value = BOOST_CONTRACT_OLDOF(v, counter_.value());
        auto c = boost::contract::public_function<override_on_bn_clicked>(
                v, &decrement_button::on_bn_clicked, this)
            .postcondition([&] {
                // Counter decremented.
                BOOST_CONTRACT_ASSERT(counter_.value() == *old_value - 1);
            })
        ;
        counter_.decrement();
    }
    BOOST_CONTRACT_OVERRIDE(on_bn_clicked)

    virtual bool up_to_date_with_subject(boost::contract::virtual_* v = 0)
            const /* override */ {
        bool result;
        auto c = boost::contract::public_function<
            override_up_to_date_with_subject
        >(v, result, &decrement_button::up_to_date_with_subject, this);

        return result = true; // For simplicity, assume always up-to-date.
    }
    BOOST_CONTRACT_OVERRIDE(up_to_date_with_subject)

    virtual void update(boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_update>(
                v, &decrement_button::update, this)
            .postcondition([&] {
                // Enabled iff positive value.
                BOOST_CONTRACT_ASSERT(enabled() == (counter_.value() > 0));
            })
        ;

        if(counter_.value() == 0) disable();
        else enable();
    }
    BOOST_CONTRACT_OVERRIDE(update);

private:
    counter& counter_;
};

#endif // #include guard
//]

