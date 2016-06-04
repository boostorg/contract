
// Test scoped mutex locks before contracts (no need to also test ctors, etc.).

#include "../detail/oteststream.hpp"
#include <boost/contract.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

struct b : private boost::contract::constructor_precondition<b> {
    static void static_invariant() { out << "b::static_inv" << std::endl; }
    void invariant() const { out << "b::inv" << std::endl; }
    
    b() : boost::contract::constructor_precondition<b>(
            [&] { out << "b::ctor::pre" << std::endl; }) {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::constructor(this)
            .old([&] { out << "b::ctor::old" << std::endl; })
            .postcondition([&] { out << "b::ctor::post" << std::endl; })
        ;
        out << "b::ctor::body" << std::endl;
    }

    virtual ~b() {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] { out << "b::dtor::old" << std::endl; })
            .postcondition([&] { out << "b::dtor::post" << std::endl; })
        ;
        out << "b::dtor::body" << std::endl;
    }

    virtual void f(boost::contract::virtual_* v = 0) const {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] { out << "b::f::pre" << std::endl; })
            .old([&] { out << "b::f::old" << std::endl; })
            .postcondition([&] { out << "b::f::post" << std::endl; })
        ;
        out << "b::f::body" << std::endl;
    }
    
    virtual void g(boost::contract::virtual_* v = 0) const {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] { out << "b::g::pre" << std::endl; })
            .old([&] { out << "b::g::old" << std::endl; })
            .postcondition([&] { out << "b::g::post" << std::endl; })
        ;
        out << "b::g::body" << std::endl;
    }

private:
    mutable boost::mutex mutex_;
};

struct a
    #define BASES private boost::contract::constructor_precondition<a>, public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }

    a() : boost::contract::constructor_precondition<a>(
            [&] { out << "a::ctor::pre" << std::endl; }) {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::constructor(this)
            .old([&] { out << "a::ctor::old" << std::endl; })
            .postcondition([&] { out << "a::ctor::post" << std::endl; })
        ;
        out << "a::ctor::body" << std::endl;
    }
    
    ~a() {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] { out << "a::dtor::old" << std::endl; })
            .postcondition([&] { out << "a::dtor::post" << std::endl; })
        ;
        out << "a::dtor::body" << std::endl;
    }
    
    void f(boost::contract::virtual_* v = 0) const /* override */ {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, &a::f, this)
            .precondition([&] { out << "a::f::pre" << std::endl; })
            .old([&] { out << "a::f::old" << std::endl; })
            .postcondition([&] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
    }
    BOOST_CONTRACT_OVERRIDE(f)
    
    void g(boost::contract::virtual_* v = 0) const /* override */ {
        boost::mutex::scoped_lock lock(mutex_);
        boost::contract::guard c = boost::contract::public_function<override_g>(
                v, &a::g, this)
            .precondition([&] { out << "a::g::pre" << std::endl; })
            .old([&] { out << "a::g::old" << std::endl; })
            .postcondition([&] { out << "a::g::post" << std::endl; })
        ;
        out << "a::g::body" << std::endl;
    }
    BOOST_CONTRACT_OVERRIDE(g)

private:
    mutable boost::mutex mutex_;
};

int main() {
    // Unfortunately, I cannot compile Boost.Thread on Cygwin with GCC and
    // CLang... I get linker errors even if I use `threadapi=pthread` and add
    // `<library>/boost/thread//boost_thread` to the Jamfile.
#ifdef BOOST_MSVC
    {
        a aa;
        boost::thread tf([&aa] { aa.f(); });
        boost::thread tg([&aa] { aa.g(); });
        tf.join();
        tg.join();
    }

    std::ostringstream ok; ok // Mutexes also guarantee order of text in `out`.
        // Test constructor.
        
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
        #endif

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::ctor::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::ctor::post" << std::endl
        #endif
        
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::ctor::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::ctor::post" << std::endl
        #endif

        // Test public functions.

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "b::f::pre" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "b::g::pre" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::g::old" << std::endl
            << "a::g::old" << std::endl
        #endif
        << "a::g::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::g::old" << std::endl
            << "b::g::post" << std::endl
            << "a::g::post" << std::endl
        #endif

        // Test destructor.

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::dtor::old" << std::endl
        #endif
        << "a::dtor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::dtor::post" << std::endl
        #endif

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::dtor::old" << std::endl
        #endif
        << "b::dtor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::dtor::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
#endif
    return boost::report_errors();
}

