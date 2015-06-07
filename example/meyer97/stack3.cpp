
#include "stack4.hpp"
#include <boost/contract.hpp>
#include <boost/optional.hpp>
#include <boost/detail/lightweight_test.hpp>

// Dispenser LIFO with max capacity using error codes.
template<typename T>
class stack3 {
public:
    void invariant() const {
        if(!error()) {
            BOOST_CONTRACT_ASSERT(count() >= 0); // Count non-negative.
            BOOST_CONTRACT_ASSERT(count() <= capacity()); // Count bounded.
            // Empty if no item.
            BOOST_CONTRACT_ASSERT(empty() == (count() == 0));
        }
    }

    enum error_code {
        no_error = 0,
        overflow_error,
        underflow_error,
        size_error
    };

    /* Initialization */

    // Create stack for max of n items, if n < 0 set error (no preconditions).
    explicit stack3(int n, T const& default_value = T()) :
            stack_(0), error_(no_error) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                // Error if impossible.
                BOOST_CONTRACT_ASSERT((n < 0) == (error() == size_error));
                // No error if possible.
                BOOST_CONTRACT_ASSERT((n >= 0) == !error());
                // Created if no error.
                if(!error()) BOOST_CONTRACT_ASSERT(capacity() == n);
            })
        ;

        if(n >= 0) stack_ = stack4<T>(n);
        else error_ = size_error;
    }

    /* Access */

    // Max number of stack items.
    int capacity() const {
        auto c = boost::contract::public_member(this); // Check invariants.

        return stack_.capacity();
    }

    // Number of stack items.
    int count() const {
        auto c = boost::contract::public_member(this); // Check invariants.

        return stack_.count();
    }

    // Top item if present, otherwise none and set error (no preconditions).
    boost::optional<T const&> item() const {
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT( // Error if impossible.
                        this->empty() == (error() == underflow_error));
                // No error if possible.
                BOOST_CONTRACT_ASSERT(!empty() == !error());
            })
        ;

        if(!empty()) {
            error_ = no_error;
            return boost::optional<T const&>(stack_.item());
        } else {
            error_ = underflow_error;
            return boost::optional<T const&>();
        }
    }

    /* Status Report */

    // Error indicator set by various operations.
    error_code error() const {
        auto c = boost::contract::public_member(this); // Check invariants.

        return error_;
    }

    bool empty() const {
        auto c = boost::contract::public_member(this); // Check invariants.

        return stack_.empty();
    }

    bool full() const {
        auto c = boost::contract::public_member(this); // Check invariants.
        
        return stack_.full();
    }

    /* Item Change */

    // Add x to top if capacity allows, otherwise set error (no preconditions).
    void put(T const& x) {
        auto old_full = BOOST_CONTRACT_OLDOF(full());
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                // Error if impossible.
                BOOST_CONTRACT_ASSERT(*old_full == (error() == overflow_error));
                // No error if possible.
                BOOST_CONTRACT_ASSERT(!*old_full == !error());
                if(!error()) { // If no error...
                    BOOST_CONTRACT_ASSERT(!empty()); // ...not empty.
                    BOOST_CONTRACT_ASSERT(*item() == x); // ...added to top.
                    // ...one more.
                    BOOST_CONTRACT_ASSERT(count() == *old_count + 1);
                }
            })
        ;

        if(full()) error_ = overflow_error;
        else {
            stack_.put(x);
            error_ = no_error;
        }
    }

    // Remove top item if possible, otherwise set error (no preconditions).
    void remove() {
        auto old_empty = BOOST_CONTRACT_OLDOF(empty());
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                // Error if impossible.
                BOOST_CONTRACT_ASSERT(*old_empty == (error() ==
                        underflow_error));
                // No error if possible.
                BOOST_CONTRACT_ASSERT(!*old_empty == !error());
                if(!error()) { // If no error...
                    BOOST_CONTRACT_ASSERT(!full()); // ...not full.
                    // ...one less.
                    BOOST_CONTRACT_ASSERT(count() == *old_count - 1);
                }
            })
        ;

        if(empty()) error_ = underflow_error;
        else {
            stack_.remove();
            error_ = no_error;
        }
    }

private:
    stack4<T> stack_;
    mutable error_code error_;
};

int main() {
    stack3<int> s(3);
    BOOST_TEST_EQ(s.capacity(), 3);
    BOOST_TEST_EQ(s.count(), 0);
    BOOST_TEST(s.empty());
    BOOST_TEST(!s.full());

    s.put(123);
    BOOST_TEST(!s.empty());
    BOOST_TEST(!s.full());
    BOOST_TEST_EQ(*s.item(), 123);
    
    s.remove();
    BOOST_TEST(s.empty());
    BOOST_TEST(!s.full());

    return boost::report_errors();
}

