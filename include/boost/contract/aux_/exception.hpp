
#ifndef BOOST_CONTRACT_AUX_EXCEPTION_HPP_
#define BOOST_CONTRACT_AUX_EXCEPTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <string>

namespace boost { namespace contract { namespace aux {

class no_error {}; // Must have no bases (just a tag type to signal no error).

} } } // namespace

#endif // #include guard

