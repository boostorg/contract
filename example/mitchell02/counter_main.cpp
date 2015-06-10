
#include "counter/counter.hpp"
#include "counter/decrement_button.hpp"
#include "observer/observer.hpp"
#include <boost/detail/lightweight_test.hpp>

int test_counter;

class view_of_counter
    #define BASES public observer
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    /* Creation */

    // Create view associated with given counter.
    explicit view_of_counter(counter& _counter) : counter_(_counter) {
        auto c = boost::contract::constructor(this);

        counter_.attach(this);
        BOOST_TEST_EQ(counter_.value(), test_counter);
    }

    // Destroy view.
    virtual ~view_of_counter() { auto c = boost::contract::destructor(this); }

    /* Commands */

    virtual bool up_to_date_with_subject(boost::contract::virtual_* v = 0)
            const /* override */ {
        bool result;
        auto c = boost::contract::public_function<
            override_up_to_date_with_subject
        >(v, result, &view_of_counter::up_to_date_with_subject, this);

        return result = true; // For simplicity, assume always up-to-date.
    }
    BOOST_CONTRACT_OVERRIDE(up_to_date_with_subject)

    virtual void update(boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_update>(
                v, &view_of_counter::update, this);

        BOOST_TEST_EQ(counter_.value(), test_counter);
    }
    BOOST_CONTRACT_OVERRIDE(update)

private:
    counter& counter_;
};

int main() {
    counter cnt(test_counter = 1);
    view_of_counter view(cnt);

    decrement_button dec(cnt);
    BOOST_TEST(dec.enabled());

    test_counter--;
    dec.on_bn_clicked();
    BOOST_TEST(!dec.enabled());

    return boost::report_errors();
}

