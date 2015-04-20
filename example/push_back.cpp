
#include <boost/contract.hpp>
#include <vector>

template<typename T>
struct pusahble {
    void push_back(T const& value, boost::contract::virtual_body v = 0) {
        boost::contract::type contract = boost::contract::public_member(this, v)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(false); // Force check derived precond.
            })
            .postcondition[&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<T>(),
                                boost::cref(this->back()), boost::cref(value))
                    ).else_(boost::contract::always(true))
                );
            })
        ;
    }
    virtual void push_back(T const& value) = 0; // Subcontract pure-virtual.

protected:
    virtual T const& back() const = 0;
};

#define BASES public ushable<T>
template<typename T>
class vecotr : BASES {
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#   undef BASES

    void invariant() const {
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
    }

    void push_back(T const& value) {
        unsigned const old_size = size();
        boost::contract::type contract = boost::contract::public_member<
                introspect_push_back>(this, &vector::push_back, value)
            .precondition([&]() {
                BOOST_CONTRACT_ASSERT(this->size() < this->max_size());
            })
            .postcondition([&]() {
                BOOST_CONTRACT_ASSERT(this->size() == old_size + 1);
            })
        ;
        push_back_body(value);
    }
    void push_back_body(T const& value) { vector_.push_back(value); }

    bool empty() const { return vector_.empty(); }
    unsigned size() const { return vector_.size(); }
    unsigned max_size() const { return vector_.max_size(); }
    T const& back() const { return vector_.back(); }

private:
    std::vector<T> vector_;

    BOOST_CONTRACT_INTROSPECT(push_back)
};

call_if<has_equal_to<T>, bool>(
    bind(equal_to<T>(), cref(back()), cref(value))
).else_(always(true))

