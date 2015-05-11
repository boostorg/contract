
#ifndef BOOST_CONTRACT_AUX_NONE_HPP_
#define BOOST_CONTRACT_AUX_NONE_HPP_

namespace boost { namespace contract { namespace aux {

struct none { // Tag for "no type".
    static none value; // Tag for "no value".

    // Must contain no functionality (so it cannot actually be used by mistake).
};

none none::value;

} } } // namespace

#endif // #include guard

