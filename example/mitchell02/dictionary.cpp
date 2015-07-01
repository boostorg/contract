
//[mitchell02_dictionary
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <utility>
#include <map>

template<typename K, typename T>
class dictionary {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(count() >= 0); // Non-negative count.
    }

    /* Creation */

    // Create empty dictionary.
    dictionary() {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == 0); // Empty.
            })
        ;
    }

    // Destroy dictionary.
    ~dictionary() {
        auto c = boost::contract::destructor(this); // Check invariants.
    }

    /* Basic Queries */

    // Number of key entries.
    int count() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return items_.size();
    }

    // Has entry for key?
    bool has(K const& key) const {
        bool result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                // Empty has no key.
                if(count() == 0) BOOST_CONTRACT_ASSERT(!result);
            })
        ;

        return result = (items_.find(key) != items_.end());
    }

    // Value for a given key.
    T const& value_for(K const& key) const {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(has(key)); // Has key.
            })
        ;

        // Find != end because of precondition (no defensive programming).
        return items_.find(key)->second;
    }

    /* Commands */

    // Add value of a given key.
    void put(K const& key, T const& value) {
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!has(key)); // Has not key already.
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == *old_count + 1); // Count inc.
                BOOST_CONTRACT_ASSERT(has(key)); // Has key.
                // Value set for key.
                BOOST_CONTRACT_ASSERT(value_for(key) == value);
            })
        ;

        items_.insert(std::make_pair(key, value));
    }

    // Remove value for given key.
    void remove(K const& key) {
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(has(key)); // Has key.
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == *old_count - 1); // Count dec.
                BOOST_CONTRACT_ASSERT(!has(key)); // Has not key.
            })
        ;

        items_.erase(key);
    }

private:
    std::map<K, T> items_;
};

int main() {
    std::string const js = "John Smith";

    dictionary<std::string, int> ages;
    BOOST_TEST(!ages.has(js));

    ages.put(js, 23);
    BOOST_TEST_EQ(ages.value_for(js), 23);

    ages.remove(js);
    BOOST_TEST_EQ(ages.count(), 0);
    
    return boost::report_errors();
}
//]

