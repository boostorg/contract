
//[mitchell02_stack
#include <boost/contract.hpp>
#include <boost/optional.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

template<typename T>
class stack {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(count() >= 0); // Non-negative count.
    }

    /* Creation */

    // Create empty stack.
    stack() {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == 0); // Empty.
            })
        ;
    }

    // Destroy stack.
    virtual ~stack() {
        auto c = boost::contract::destructor(this); // Check invariants.
    }

    /* Basic Queries */

    // Number of items.
    int count() const {
        auto c = boost::contract::public_function(this); // Check invariants.

        return items_.size();
    }

    // Item at index in [1, count()] (as in Eiffel).
    T const& item_at(int index) const {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index > 0); // Positive index.
                BOOST_CONTRACT_ASSERT(index <= count()); // Index within count.
            })
        ;

        return items_[index - 1];
    }

    /* Derived Queries */

    // If no items.
    bool is_empty() const {
        bool result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                // Consistent with count.
                BOOST_CONTRACT_ASSERT(result == (count() == 0));
            })
        ;

        return result = (count() == 0);
    }

    // Top item.
    T const& item() const {
        boost::optional<T const&> result; // Avoid extra construction of T.
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count() > 0); // Not empty.
            })
            .postcondition([&] {
                // Item on top.
                BOOST_CONTRACT_ASSERT(*result == item_at(count()));
            })
        ;

        return *(result = item_at(count()));
    }

    /* Commands */

    // Push item to the top.
    void put(T const& new_item) {
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == *old_count + 1); // Count inc.
                BOOST_CONTRACT_ASSERT(item() == new_item); // Item set.
            })
        ;

        items_.push_back(new_item);
    }

    // Pop top item.
    void remove() {
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count() > 0); // Not empty.
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == *old_count - 1); // Count dec.
            })
        ;

        items_.pop_back();
    }

private:
    std::vector<T> items_;
};

int main() {
    stack<int> s;
    BOOST_TEST_EQ(s.count(), 0);

    s.put(123);
    BOOST_TEST_EQ(s.item(), 123);

    s.remove();
    BOOST_TEST(s.is_empty());

    return boost::report_errors();
}
//]

