
#include <boost/contract.hpp>

//[static
template<class C>
class make {
public:
    static void static_invariant() { // Static class invariants.
        BOOST_CONTRACT_ASSERT(instances() >= 0);
    }

    static int instances() {
        auto c = boost::contract::public_function<make>(); // Check invariants.
        return instances_; // Function body.
    }

    make() : obj_() {
        auto old_instances = BOOST_CONTRACT_OLDOF(instances());
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_OLDOF(instances() == *old_instances + 1);
            })
        ;

        ++instances_;
    }

    ~make() {
        auto old_instances = BOOST_CONTRACT_OLDOF(instances());
        auto c = boost::contract::destructor(this)
            .postcondition([&] { // (An example of destructor postconditions.)
                BOOST_CONTRACT_OLDOF(instances() == *old_instances - 1);
            })
        ;

        --instances_;
    }
    
    /* ... */

private:
    C obj_;
    static int instances_;
};

template<class C>
int make<C>::instances_ = 0;
//]

