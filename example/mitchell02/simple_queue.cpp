
#include <boost/contract.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

// Disable selected expensive assertion checks and old value copies.
#define O_1 0               // O(1): constant complexity (default).
#define O_N 1               // O(n): linear complexity.
#define COMPLEXITY_MAX O_1  // Max allowed complexity.

template<typename T>
class simple_queue
    #define BASES private boost::contract::constructor_precondition< \
            simple_queue<T> >
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        BOOST_CONTRACT_ASSERT(count() >= 0); // Non-negative count.
    }

    /* Creation */

    // Create empty queue.
    static void simple_queue_precondition(int const& _capacity) {
        BOOST_CONTRACT_ASSERT(_capacity > 0); // Positive capacity.
    }
    explicit simple_queue(int _capacity) :
        boost::contract::constructor_precondition<simple_queue>(
            boost::bind(&simple_queue::simple_queue_precondition,
                    boost::cref(_capacity)
            )
        )
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(capacity() == _capacity); // Capacity set.
                BOOST_CONTRACT_ASSERT(this->is_empty()); // Empty.
            })
        ;

        items_.reserve(_capacity);
    }

    // Destroy queue.
    virtual ~simple_queue() {
        auto c = boost::contract::destructor(this); // Check invariants.
    }

    /* Basic Queries */

    // Items in queue (in their order).
    // (Somewhat exposes implementation but allows to check more contracts.)
    std::vector<T> const& items() const {
        auto c = boost::contract::public_member(this); // Check invariants.

        return items_;
    }

    // Max number of items queue can hold.
    int capacity() const {
        auto c = boost::contract::public_member(this); // Check invariants.

        return items_.capacity();
    }

    /* Derived Queries */

    // Number of items.
    int count() const {
        int result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                // Return items count.
                BOOST_CONTRACT_ASSERT(result == int(items().size()));
            })
        ;

        return result = items_.size();
    }

    // Item at head.
    T const& head() const {
        boost::optional<T const&> result;
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!is_empty()); // Not empty.
            })
            .postcondition([&] {
                // Return item on top.
                BOOST_CONTRACT_ASSERT(*result == items().at(0));
            })
        ;

        return *(result = items_.at(0));
    }

    // If queue contains no item.
    bool is_empty() const {
        bool result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                // Consistent with count.
                BOOST_CONTRACT_ASSERT(result == (count() == 0));
            })
        ;

        return result = (items_.size() == 0);
    }

    // If queue as no room for another item.
    bool is_full() const {
        bool result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT( // Consistent with size and capacity.
                        result == (capacity() == int(items().size())));
            })
        ;

        return result = (items_.size() == items_.capacity());
    }

    /* Commands */

    // Remove head itme and shift all other items.
    void remove() {
        // Expensive all_equal postcond. and old_items copy might be skipped.
        boost::shared_ptr<std::vector<T> const> old_items;
        if(O_N <= COMPLEXITY_MAX) old_items = BOOST_CONTRACT_OLDOF(items());

        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!is_empty()); // Not empty.
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == *old_count - 1); // Count dec.
                if(O_N <= COMPLEXITY_MAX) {
                    all_equal(items(), *old_items, /* shifted = */ 1);
                }
            })
        ;
        
        items_.erase(items_.begin());
    }

    // Add item to tail.
    void put(T const& item) {
        // Expensive all_equal postcond. and old_items copy might be skipped.
        boost::shared_ptr<std::vector<T> const> old_items;
        if(O_N <= COMPLEXITY_MAX) old_items = BOOST_CONTRACT_OLDOF(items());

        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count() < capacity()); // Room for add.
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == *old_count + 1); // Count inc.
                // Second to last item.
                BOOST_CONTRACT_ASSERT(items().at(count() - 1) == item);
                if(O_N <= COMPLEXITY_MAX) all_equal(items(), *old_items);
            })
        ;
        
        items_.push_back(item);
    }

private:
    // Contract helper.
    static bool all_equal(std::vector<T> const& left,
            std::vector<T> const& right, unsigned offset = 0) {
        auto c = boost::contract::private_member()
            .precondition([&] {
                // Correct offset.
                BOOST_CONTRACT_ASSERT(right.size() == left.size() + offset);
            })
        ;

        for(unsigned i = offset; i < right.size(); ++i) {
            if(left.at(i - offset) != right.at(i)) return false;
        }
        return true;
    }

    std::vector<T> items_;
};

int main() {
    simple_queue<int> q(10);
    q.put(123);
    q.put(456);
    
    BOOST_TEST_EQ(q.capacity(), 10);
    BOOST_TEST_EQ(q.head(), 123);
    
    BOOST_TEST(!q.is_empty());
    BOOST_TEST(!q.is_full());

    std::vector<int> const& items = q.items();
    BOOST_TEST_EQ(items.at(0), 123);
    BOOST_TEST_EQ(items.at(1), 456);
    
    q.remove();
    BOOST_TEST_EQ(q.count(), 1);

    return boost::report_errors();
}

