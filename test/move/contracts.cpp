
// Test contracts for move operations.

#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>
#include <utility>

struct v : boost::contract::constructor_precondition<v> {
    void invariant() const {
        if(!moved()) {
            BOOST_CONTRACT_ASSERT(i_ < w_.size());
        }
    }

    v(std::vector<char> const& w, unsigned i) :
        boost::contract::constructor_precondition<v>([&] {
            BOOST_CONTRACT_ASSERT(i <= w.size());
        }),
        w_(w), i_(i), moved_(false)
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] { BOOST_CONTRACT_ASSERT(!moved()); })
        ;
    }

    ~v() {
        // Moved-from can be destroyed (so no pre !moved here).
        boost::contract::guard c = boost::contract::destructor(this);
    }

    v(v const& o) :
        boost::contract::constructor_precondition<v>(
            [&] { BOOST_CONTRACT_ASSERT(!o.moved()); }
        )
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] { BOOST_CONTRACT_ASSERT(!moved()); })
        ;
        copy(o);
    }

    v& operator=(v const& o) {
        // Moved-from can be (copy) assigned (so no pre !moved here).
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] { BOOST_CONTRACT_ASSERT(!o.moved()); })
            .postcondition([&] { BOOST_CONTRACT_ASSERT(!moved()); })
        ;
        copy(o);
        return *this;
    }

    v(v&& o) :
        boost::contract::constructor_precondition<v>(
            [&] { BOOST_CONTRACT_ASSERT(!o.moved()); }
        )
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(!moved());
                BOOST_CONTRACT_ASSERT(o.moved());
            })
        ;
        move(std::forward<v>(o));
    }

    v& operator=(v&& o) {
        // Moved-from can be (move) assigned (so no pre !moved here).
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] { BOOST_CONTRACT_ASSERT(!o.moved()); })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(!moved());
                BOOST_CONTRACT_ASSERT(o.moved());
            })
        ;
        move(std::forward<v>(o));
        return *this;
    }

    char at() const {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] { BOOST_CONTRACT_ASSERT(!moved()); })
        ;
        return w_.at(i_);
    }

    bool moved() const {
        boost::contract::guard c = boost::contract::public_function(this);
        return moved_;
    }

private:
    void copy(v const& o) {
        w_ = o.w_;
        i_ = o.i_;
        moved_ = false;
    }

    void move(v&& o) {
        w_ = std::move(o.w_);
        i_ = std::move(o.i_);
        moved_ = false;
        o.moved_ = true; // Mark moved-from object.
    }

    std::vector<char> w_;
    unsigned i_;
    bool moved_;
};

int main() {
    struct err {};
    boost::contract::set_precondition_failure(
            [] (boost::contract::from) { throw err(); });

    {
        v x = {{'a', 'b', 'c', 'd'}, 2};
        BOOST_TEST_EQ(x.at(), 'c');

        v y1 = x; // Test copy constructor.
        BOOST_TEST_EQ(y1.at(), 'c');
        BOOST_TEST_EQ(x.at(), 'c');

        v y2 = {{'a'}, 0};
        y2 = x; // Test copy assignment.
        BOOST_TEST_EQ(y2.at(), 'c');
        BOOST_TEST_EQ(x.at(), 'c');

        v z1 = std::move(x); // Test move constructor.
        BOOST_TEST_EQ(z1.at(), 'c');
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            try { x.at(); BOOST_TEST(false); }
            catch(err const&) {} // Test !moved() pre failed.
            catch(...) { BOOST_TEST(false); }
        #endif

        x = y1; // Test moved-from can be copy assigned.
        BOOST_TEST_EQ(x.at(), 'c');
        BOOST_TEST_EQ(y1.at(), 'c');

        v z2 = {{'a'}, 0};
        z2 = std::move(x); // Test move assignment.
        BOOST_TEST_EQ(z2.at(), 'c');
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            try { x.at(); BOOST_TEST(false); }
            catch(err const&) {} // Test !moved() pre failed.
            catch(...) { BOOST_TEST(false); }
        #endif

        x = std::move(y2); // Test moved-from can be move assigned.
        BOOST_TEST_EQ(x.at(), 'c');
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            try { y2.at(); BOOST_TEST(false); }
            catch(err const&) {} // Test !moved() pre failed.
            catch(...) { BOOST_TEST(false); }
        #endif
    } // Test moved-from (y2) can be destroyed.

    return boost::report_errors();
}

