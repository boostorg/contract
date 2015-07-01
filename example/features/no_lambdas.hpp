
#include <boost/contract.hpp>

//[no_lambdas_hpp
template<typename T, std::size_t MaxSize>
class array
    : private boost::contract::constructor_precondition<array<T, MaxSize> >
{
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() <= MaxSize);
    }
    static void static_invariant() const {
        BOOST_CONTRACT_ASSERT(instances() >= 0);
    }

    explicit array(std::size_t count);
        static void constructor_precondition(std::size_t const& count) {
            BOOST_CONTRACT_ASSERT(count <= MaxSize)
        }
        static void constructor_old(
                boost::shared_ptr<int const>& old_instances) {
            old_instances = BOOST_CONTRACT_OLDOF(instances());
        }
        void constructor_postcondition(std::size_t const& count,
                boost::shared_ptr<int const> old_instances) const {
            BOOST_CONTRACT_ASSERT(size() == count);
            BOOST_CONTRACT_ASSERT(instances() == *old_instances + 1);
        }

    virtual ~array();
        void destructor_old(
                boost::shared_ptr<int const>& old_instances) const {
            old_instances = BOOST_CONTRACT_OLDOF(instances());
        }
        static void destructor_postcondition(
                boost::shared_ptr<int const> old_instances) {
            BOOST_CONTRACT_ASSERT(instances() == *old_instances - 1);
        }

    void push_back(T const& value);
        void push_back_precondition(T const& value) const {
            BOOST_CONTRACT_ASSERT(size() < MaxSize);
        }
        void push_back_old(boost::shared_ptr<std::size_t const>& old_size)
                const {
            old_size = BOOST_CONTRACT_OLDOF(size());
        }
        void push_back_postcondition(T const& value,
                boost::shared_ptr<std::size_t const> old_size) const {
            BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
        }
    
    std::size_t size() const; // Check invariants.

    static int instances(); // Check invariants.

private:
    T* values_;
    std::size_t size_;
    static int instances_;
};
//]

