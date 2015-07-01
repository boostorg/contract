
//[mitchell02_push_button
#ifndef PUSH_BUTTON_HPP_
#define PUSH_BUTTON_HPP_

#include <boost/contract.hpp>

class push_button {
public:
    /* Creation */

    // Create an enabled button.
    push_button() : enabled_(true) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(enabled()); // Enabled.
            })
        ;
    }

    // Destroy button.
    virtual ~push_button() { auto c = boost::contract::destructor(this); }

    /* Queries */

    // If button is enabled.
    bool enabled() const {
        auto c = boost::contract::public_function(this);
        return enabled_;
    }

    /* Commands */

    // Enable button.
    void enable() {
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(enabled()); // Enabled.
            })
        ;

        enabled_ = true;
    }

    // Disable button.
    void disable() {
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(!enabled()); // Disabled.
            })
        ;

        enabled_ = false;
    }

    // Invoke externally when button clicked.
    virtual void on_bn_clicked(boost::contract::virtual_* v = 0) = 0;

private:
    bool enabled_;
};

void push_button::on_bn_clicked(boost::contract::virtual_* v) {
    auto c = boost::contract::public_function(this)
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(enabled()); // Enabled.
        })
    ;
}

#endif // #include guard
//]

