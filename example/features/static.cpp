
#include <boost/contract.hpp>

//[static
template<class C>
class instance_counter {
public:
    static void static_invariant() { // Static class invariants.
        BOOST_CONTRACT_ASSERT(count() >= 0);
    }

    static int count() { // Static public function (check static invariants).
        auto c = boost::contract::public_function<instance_counter>();
        return count_; // Function body.
    }

    instance_counter() : obj_() {
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_OLDOF(count() == *old_count + 1);
            })
        ;

        ++count_;
    }

    ~instance_counter() {
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::destructor(this)
            .postcondition([&] { // (An example of destructor postconditions.)
                BOOST_CONTRACT_OLDOF(count() == *old_count - 1);
            })
        ;

        --count_;
    }
    
    /* ... */

private:
    C obj_;
    static int count_;
};

template<class C>
int instance_counter<C>::count_ = 0;
//]

