
#ifndef BOOST_CONTRACT_AUX_FUNCTION_KEY_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_KEY_HPP_

namespace boost { namespace contract { namespace aux {

enum function_key {
    public_member,
    protected_member,
    private_member,
    constructor,
    destructor,
    free_function
};

} } } // namespace

#endif // #include guard

