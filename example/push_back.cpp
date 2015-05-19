
#include <boost/contract.hpp>
#include <vector>

template<typename T>
struct pusahble {
    virtual void push_back(T const& value,
            boost::contract::virtual_* v = 0) = 0 {
        boost::contract::var c = boost::contract::public_member(v, this)
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
protected:
    virtual T const& back() const = 0;
};

template<typename T>
class vector
    #define BASES public ushable<T>
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
    }

    virtual void push_back(T const& value, boost::contract::virtual_* v = 0) {
        boost::shared_ptr<unsigned const> old_size =
                BOOST_CONTRACT_OLDOF(v, size());
        boost::contract::type contract = boost::contract::public_member<
                introspect_push_back>(v, this, value)
            .precondition([&]() {
                BOOST_CONTRACT_ASSERT(this->size() < this->max_size());
            })
            .postcondition([&]() {
                BOOST_CONTRACT_ASSERT(this->size() == old_size + 1);
            })
        ;
        vector_.push_back(value);
    }
    BOOST_CONTRACT_INTROSPECT(push_back)

    bool empty() const { return vector_.empty(); }
    unsigned size() const { return vector_.size(); }
    unsigned max_size() const { return vector_.max_size(); }
    T const& back() const { return vector_.back(); }

private:
    std::vector<T> vector_;
};

void my_sqrt(double& x) { // My square root (with contracts).
    boost::shared_ptr<double const> old_x = BOOST_CONTRACT_OLDOF(x);
    boost::contract::scoped contract = boost::contract::free_function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(x >= 0);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x * x == old_x);
        })
    ;
    x = std::sqrt(x); // C++ square root (without contracts).
}

