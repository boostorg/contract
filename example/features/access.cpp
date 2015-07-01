
#include <boost/contract.hpp>
#include <vector>
#include <cstddef>

template<typename T>
class pushable {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(capacity() <= max_size());
    }

    virtual void push_back(T const& value, boost::contract::virtual_* v = 0)
            = 0;

    virtual std::size_t max_size() const = 0;
    virtual std::size_t capacity() const = 0;
};

template<typename T> // Contract for pure virtual function.
void pushable<T>::push_back(T const& value, boost::contract::virtual_* v) {
    auto old_capacity = BOOST_CONTRACT_OLDOF(v, capacity());
    auto c = boost::contract::public_function(v, this)
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(capacity() < max_size());
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
        })
    ;
}


//[access
template<typename T>
class vector
    #define BASES public pushable<T>
    : BASES
{
    // In private section:
    friend class boost::contract::access; // Friend `access` class so...

    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types; // ...private bases.
    #undef BASES

    void invariant() const { // ...private invariants (static and non).
        BOOST_CONTRACT_ASSERT(size() <= capacity());
    }

public:
    virtual void push_back(T const& value, boost::contract::virtual_* v = 0)
            /* override */ {
        auto old_size = BOOST_CONTRACT_OLDOF(v, size());
        auto c = boost::contract::public_function<override_push_back>(
                v, &vector::push_back, this, value)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
            })
        ;

        vect_.push_back(value);
    }

private:
    BOOST_CONTRACT_OVERRIDE(push_back) // Allowed even without friend `access`.
    std::vector<T> vect_;

    /* ... */
//]

public:
    // TODO: Write contracts for those too.
    std::size_t size() const { return vect_.size(); }
    std::size_t max_size() const { return vect_.max_size(); }
    std::size_t capacity() const { return vect_.capacity(); }
};
//]

