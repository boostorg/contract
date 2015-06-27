
//[override_overload
class a
    #define BASES public b
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void f(int x, boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_f>(
                v, &a::f, this, x);
        /* ... */
    }
    
    void f(double x, boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_f>(
                v, &a::f, this, x);
        /* ... */
    }

private:
    BOOST_CONTRACT_OVERRIDE(f)
};
//]

