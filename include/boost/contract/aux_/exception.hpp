
#ifndef BOOST_CONTRACT_AUX_EXCEPTION_HPP_
#define BOOST_CONTRACT_AUX_EXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace boost { namespace contract { namespace aux {

struct no_error {};

struct assertion_failure {
    explicit assertion_failure ( char const* const what ) : what_(what) {}
    const char* what ( ) const { return what_; }
private:
    const char* const what_;
};

} } } // namespace

#endif // #include guard

