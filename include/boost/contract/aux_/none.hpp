
#ifndef BOOST_CONTRACT_AUX_NONE_HPP_
#define BOOST_CONTRACT_AUX_NONE_HPP_

namespace boost { namespace contract { namespace aux {

class none { // Tag for "no type".
public:
    static none value; // Tag for "no value".

    // Allow default constructor and copy operations.
    
    // Must contain no other member (so it cannot be used by mistake).
};

none none::value;

// TODO: Remove, for testing only...
#include <iostream>
std::ostream& operator<<(std::ostream& out, none const&) {
    return out << "<none>";
}

} } } // namespace

#endif // #include guard

