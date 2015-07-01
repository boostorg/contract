
//[mitchell02_customer_manager
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>
#include <map>
#include <utility>

// Basic customer information.
struct customer_info {
    typedef std::string identifier;
    
    identifier id;

    explicit customer_info(identifier const& _id) :
            id(_id), name_(), address_(), birthday_() {}

private:
    std::string name_;
    std::string address_;
    std::string birthday_;

    friend class customer_manager;
};

// Manage customers.
class customer_manager {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(count() >= 0); // Non-negative count.
    }

    /* Creation */

    customer_manager() {
        auto c = boost::contract::constructor(this); // Check invariants.
    }

    virtual ~customer_manager() {
        auto c = boost::contract::destructor(this); // Check invariants.
    }

    /* Basic Queries */

    int count() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return customers_.size();
    }

    bool id_active(customer_info::identifier const& id) const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return customers_.find(id) != customers_.cend();
    }

    /* Derived Queries */

    std::string const& name_for(customer_info::identifier const& id) const {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(id_active(id)); // Active.
            })
        ;

        // Find != end because of preconditions (no defensive programming).
        return customers_.find(id)->second.name_;
    }

    /* Commands */

    void add(customer_info const& info) {
        auto old_count = BOOST_CONTRACT_OLDOF(count());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                // Not already active.
                BOOST_CONTRACT_ASSERT(!id_active(info.id));
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(count() == *old_count + 1); // Count inc.
                BOOST_CONTRACT_ASSERT(id_active(info.id)); // Activated.
            })
        ;

        customers_.insert(std::make_pair(info.id, customer(info)));
    }

    void set_name(
            customer_info::identifier const& id, std::string const& name) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(id_active(id)); // Already active.
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(name_for(id) == name); // Name set.
            })
        ;

        // Find != end because of precondition (no defensive programming).
        customers_.find(id)->second.name_ = name;
    }

private:
    class agent {}; // Customer agent.

    struct customer : customer_info {
        agent managing_agent;
        std::string last_contact;

        explicit customer(customer_info const& info) : customer_info(info),
                managing_agent(), last_contact() {}
    };

    std::map<customer_info::identifier, customer> customers_;
};

int main() {
    customer_manager m;
    
    customer_info const js("john_smith_123");
    m.add(js);
    m.set_name(js.id, "John Smith");
    BOOST_TEST_EQ(m.name_for(js.id), "John Smith");
    BOOST_TEST_EQ(m.count(), 1);
    BOOST_TEST(m.id_active(js.id));

    return boost::report_errors();
}
//]

