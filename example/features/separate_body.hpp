
#include <boost/contract.hpp>

//[separate_body_hpp
template<typename T, std::size_t MaxSize>
class array
    : private boost::contract::constructor_precondition<unique_identifiers>
{
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() <= MaxSize);
    }

    explicit array(std::size_t count) :
        boost::contract::constructor_precondition<unique_identifiers>([&] {
            BOOST_CONTRACT_ASSERT(count <= MaxSize)
        }),
        values_(new T[MaxSize]) // But must member initializations here.
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
            })
        ;
        constructor_body(count);
    }

    virtual ~array() {
        auto c = boost::contract::destructor(this); // Check invariants.
        destructor_body();
    }

    std::size_t size() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return size_body();
    }

    void push_back(T const& value) {
        auto old_size = BOOST_CONTRACT_OLDOF(v, size());
        auto c = boost::contract::public_function(v, this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < MaxSize);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
            })
        ;
        push_back_body();
    }
    
private:
    // Contracts in class declaration (above), but body implementations are not.
    void construtor_body(std::size_t count);
    void destructor_body();
    std::size_t size_body() const;
    void push_back_body(T const& value);

    T* values_;
    std::size_t size_;
};
//]

