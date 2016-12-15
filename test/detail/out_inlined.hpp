
#ifndef BOOST_CONTRACT_TEST_OUT_INLINED_HPP_
#define BOOST_CONTRACT_TEST_OUT_INLINED_HPP_

#include "out.hpp"
#include <iostream>

namespace boost { namespace contract { namespace test { namespace detail {

namespace out_ {
    std::string out;
}

std::string out() { return out_::out; }

void out(std::string const& text) {
    if(text == "") out_::out = "";
    else {
        out_::out = out_::out + text;
        std::clog << text;
        std::clog.flush();
    }
}

} } } }

#endif // #include guard

