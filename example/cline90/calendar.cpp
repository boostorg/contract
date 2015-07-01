
//[cline90_calendar
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>

class calendar {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(month() >= 1);
        BOOST_CONTRACT_ASSERT(month() <= 12);
        BOOST_CONTRACT_ASSERT(date() >= 1);
        BOOST_CONTRACT_ASSERT(date() <= days_in(month()));
    }

    calendar() : month_(1), date_(31) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(month() == 1);
                BOOST_CONTRACT_ASSERT(date() == 31);
            })
        ;
    }

    virtual ~calendar() {
        auto c = boost::contract::destructor(this); // Check invariants.
    }

    int month() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return month_;
    }

    int date() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return date_;
    }

    void reset(int new_month) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(new_month >= 1);
                BOOST_CONTRACT_ASSERT(new_month <= 12);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(month() == new_month);
            })
        ;

        month_ = new_month;
    }

private:
    static int days_in(int month) {
        int result;
        auto c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(month >= 1);
                BOOST_CONTRACT_ASSERT(month <= 12);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= 1);
                BOOST_CONTRACT_ASSERT(result <= 31);
            })
        ;

        return 31; // For simplicity, assume all months have 31 days.
    }

    int month_, date_;
};

int main() {
    calendar cal;
    BOOST_TEST_EQ(cal.date(), 31);
    BOOST_TEST_EQ(cal.month(), 1);

    cal.reset(8); // Set month 
    BOOST_TEST_EQ(cal.month(), 8);

    return boost::report_errors();
}
//]

