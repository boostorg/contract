
#include <boost/contract.hpp>
#include <iostream>
#include <cstring>
#include <cassert>

//[throw_on_failure_cstring
struct too_large_error {};

template<std::size_t MaxSize>
class cstring
    #define BASES private boost::contract::constructor_precondition<cstring< \
            MaxSize> >
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    /* implicit */ cstring(char const* chars) :
        boost::contract::constructor_precondition<cstring>([&] {
            BOOST_CONTRACT_ASSERT(chars); // Throw `assertion_failure`.
            // Or, throw user-defined exception.
            if(std::strlen(chars) > MaxSize) throw too_large_error();
        })
    {

        /* ... */
//]
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == std::strlen(chars));
            })
        ;

        size_ = std::strlen(chars);
        for(std::size_t i = 0; i < size_; ++i) chars_[i] = chars[i];
        chars_[size_] = '\0';
    }

    ~cstring() {
        // Check invariants.
        boost::contract::guard c = boost::contract::destructor(this);
    }
    
    std::size_t size() const {
        // Check invariants.
        boost::contract::guard c = boost::contract::public_function(this);
        return size_;
    }
    
    void invariant() const {
        if(size() > MaxSize) throw too_large_error(); // Throw user-defined ex.
        BOOST_CONTRACT_ASSERT(chars_); // Or, throw `assertion_failure`.
        BOOST_CONTRACT_ASSERT(chars_[size()] == '\0');
    }

private:
    char chars_[MaxSize + 1];
    std::size_t size_;
};

//[throw_on_failure_handler
void throwing_handler(boost::contract::from context) {
    if(context == boost::contract::from_destructor) {
        // Ignore exception because destructors should never throw.
        std::clog << "destructor contract failed (ignored)" << std::endl;
    } else throw; // Re-throw (assertion_failure, too_large_error, etc.).
}

int main() {
    boost::contract::set_failure(&throwing_handler);

    /* ... */
//]

    {
        cstring<3> s("abc");
        assert(s.size() == 3);
    }

    try {
        char* c = 0;
        cstring<3> s(c);
        assert(false);
    } catch(boost::contract::assertion_failure const& error) { // OK (expected).
        std::clog << "ignored: " << error.what() << std::endl;
    } catch(...) { assert(false); }
    
    try {
        cstring<3> s("abcd");
        assert(false);
    } catch(too_large_error const&) {} // OK (expected).
    catch(...) { assert(false); }

    return 0;
}

