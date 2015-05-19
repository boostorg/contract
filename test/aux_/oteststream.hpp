
#ifndef BOOST_CONTRACT_AUX_TEST_OTESTSTREAM_HPP_
#define BOOST_CONTRACT_AUX_TEST_OTESTSTREAM_HPP_

#include <boost/iostreams/tee.hpp>
#include <boost/iostreams/stream.hpp>
#include <string>
#include <sstream>
#include <iostream>

namespace boost { namespace contract { namespace aux { namespace test {

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

    bool eq(std::string const& s) { // Also display mismatching characters.
        std::string r = str();
        std::string::size_type i = 0;
        for(; i < r.size() && i < s.size(); ++i) if(r[i] != s[i]) break;
        if(i < r.size() || i < s.size()) {
            std::cout << std::endl;
            std::cout <<
                "Error: Following strings differ at position " << i <<
                ", because '" << r[i] << "' != '" << s[i] << "':" << std::endl
            ;
            std::cout << std::endl;
            std::cout << r.substr(0, std::min(i + 1, r.size())) << std::endl;
            std::cout << std::endl;
            std::cout << s.substr(0, std::min(i + 1, s.size())) << std::endl;
            std::cout << std::endl;
            return false;
        }
        return true;
    }
};

} } } } // namespace

#endif // #include guard

