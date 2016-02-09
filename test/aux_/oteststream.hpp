
#ifndef BOOST_CONTRACT_TEST_AUX_OTESTSTREAM_HPP_
#define BOOST_CONTRACT_TEST_AUX_OTESTSTREAM_HPP_

#include <boost/iostreams/tee.hpp>
#include <boost/iostreams/stream.hpp>
#include <string>
#include <sstream>
#include <iostream>

// Convenience to declare test string functions across shared libs.
#define BOOST_CONTRACT_TEST_AUX_OTESTSTREAM_STR_DECL(declspec, func) \
    std::string declspec func(); \
    void declspec func(std::string const& text);

#define BOOST_CONTRACT_TEST_AUX_OTESTSTREAM_STR_DEF(func) \
    namespace boost { namespace contract { namespace test { namespace aux { \
            namespace oteststream_ { \
        std::string func; \
    } } } } } \
    \
    std::string func() { \
        return boost::contract::test::aux::oteststream_::func; \
    } \
    \
    void func(std::string const& text) { \
        if(text == "") boost::contract::test::aux::oteststream_::func = ""; \
        else { \
            boost::contract::test::aux::oteststream_::func = \
                    boost::contract::test::aux::oteststream_::func + text; \
            std::clog << text; \
            std::clog.flush(); \
        } \
    }

namespace boost { namespace contract { namespace test { namespace aux {

namespace oteststream_ {
    struct oss_base { // Wrap oss data member for proper initialization order.
    protected:
        std::ostringstream oss_;
    };
}

// Print to clog plus build internal string (using ostringstream) for checking.
struct oteststream :
    private oteststream_::oss_base,
    public boost::iostreams::stream<boost::iostreams::tee_device<std::ostream,
            std::ostringstream> >
{
    oteststream() :
        oteststream_::oss_base(),
        boost::iostreams::stream<boost::iostreams::tee_device<
                std::ostream, std::ostringstream> >(
            boost::iostreams::tee_device<std::ostream, std::ostringstream>(
                    std::clog, oss_)
        )
    {}

    std::string str() const { return oss_.str(); }
    void str(std::string const& s) { oss_.str(s); }

    bool eq(std::string const& s) { return eq(str(), s); }
    
    // Also display mismatching characters.
    static bool eq(std::string const& r, std::string const& s) {
        std::string::size_type i = 0;
        for(; i < r.size() && i < s.size(); ++i) if(r[i] != s[i]) break;
        if(i < r.size() || i < s.size()) {
            std::cout << std::endl;
            std::cout <<
                "Error: Following strings differ at position " << i <<
                ", because '" << r[i] << "' != '" << s[i] << "':" << std::endl
            ;
            std::cout << std::endl;
            std::cout
                << r.substr(0, i)
                << "(((" << r[i] << ")))"
                << r.substr(std::min(i + 1, r.size()), r.size())
                << std::endl
            ;
            std::cout << std::endl;
            std::cout
                << s.substr(0, i)
                << "(((" << s[i] << ")))"
                << s.substr(std::min(i + 1, s.size()), s.size())
                << std::endl
            ;
            std::cout << std::endl;
            return false;
        }
        return true;
    }
};

} } } } // namespace

#endif // #include guard

