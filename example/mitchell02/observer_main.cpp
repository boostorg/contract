
//[mitchell02_observer_main
#include "observer/observer.hpp"
#include "observer/subject.hpp"
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>

int test_state; // For unit testing only.

// Implement an actual subject.
class concrete_subject
    #define BASES public subject
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types; // Subcontracting.
    #undef BASES

    typedef int state; // Some state being observed.

    concrete_subject() : state_() {
        auto c = boost::contract::constructor(this);
    }

    ~concrete_subject() { auto c = boost::contract::destructor(this); }

    void set_state(state const& new_state) {
        auto c = boost::contract::public_function(this);

        state_ = new_state;
        BOOST_TEST_EQ(state_, test_state);
        notify(); // Notify all observers.
    }

    state get_state() const {
        auto c = boost::contract::public_function(this);
        return state_;
    }

private:
    state state_;
};

// Implement an actual observer.
class concrete_observer
    #define BASES public observer
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types; // Subcontracting.
    #undef BASES

    // Create concrete observer.
    explicit concrete_observer(concrete_subject const& subj) :
            subject_(subj), observed_state_() {
        auto c = boost::contract::constructor(this); // Check subcontracts.
    }

    ~concrete_observer() { auto c = boost::contract::destructor(this); }

    // Implement base virtual functions.

    bool up_to_date_with_subject(boost::contract::virtual_* v = 0)
            const /* override */ {
        bool result;
        auto c = boost::contract::public_function<
            override_up_to_date_with_subject
        >(v, result, &concrete_observer::up_to_date_with_subject, this);

        return result = true; // For simplicity, assume always up-to-date.
    }
    BOOST_CONTRACT_OVERRIDE(up_to_date_with_subject)

    void update(boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_update>(
                v, &concrete_observer::update, this);

        observed_state_ = subject_.get_state();
        BOOST_TEST_EQ(observed_state_, test_state);
    }
    BOOST_CONTRACT_OVERRIDE(update)

private:
    concrete_subject const& subject_;
    concrete_subject::state observed_state_;
};

int main() {
    concrete_subject subj;
    concrete_observer ob(subj);
    subj.attach(&ob);

    subj.set_state(test_state = 123);
    subj.set_state(test_state = 456);

    return boost::report_errors();
}
//]

