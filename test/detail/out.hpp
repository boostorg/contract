
#ifndef BOOST_CONTRACT_TEST_DETAIL_OUT_HPP_
#define BOOST_CONTRACT_TEST_DETAIL_OUT_HPP_

// To declare test string functions across shared libraries.

#include <string>

namespace boost { namespace contract { namespace test { namespace detail {

std::string BOOST_CONTRACT_TEST_DETAIL_OUT_DECLSPEC out();

void BOOST_CONTRACT_TEST_DETAIL_OUT_DECLSPEC out(std::string const& text);

} } } }

#endif // #include guard

