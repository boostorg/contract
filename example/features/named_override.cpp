
//[named_override
class a
    #define BASES public b
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void _f(boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_underscore_f>(
                v, &a::_f, this)
            /* ... */
        ;
    }
    BOOST_CONTRACT_NAMED_OVERRIDE(override_underscore_f, _f) // Explicit name.
};
//]


