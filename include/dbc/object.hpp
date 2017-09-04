
#ifndef DBC_OBJECT_HPP_
#define DBC_OBJECT_HPP_

#ifndef DBC

#define DBC_INHERIT_OBJECT(class_type)
#define DBC_TRAILING_OBJECT(class_type)

#else // DBC

#include "detail/threading/sync.hpp"

#define DBC_INHERIT_OBJECT(class_type) : private ::dbc::object< class_type >
#define DBC_TRAILING_OBJECT(class_type) , private ::dbc::object< class_type >

namespace dbc {

/**
 * This is a template on class type C so no common base class is introduced.
 */
template<class C>
class object {
public:
    /** 
     * True iff *this object* is checking a contract. The name contains 
     * "object" to better differentiate the role of this flag compared to the 
     * role of the dbc::globally_checking_contract_ flag.
     * dbc_ prefix not to clash with C's names, _ postfix to reserve it. 
     * Mutable so contract can access it via self (of const class_type&).
     */
    mutable sync_<bool, false> dbc_object_checking_contract_;
    
    // Don't decl these constr explicit (they must also support possible 
    // implicit type conversions of user's class, if any).

    /* no explicit */ object(): dbc_object_checking_contract_(false) {}

    /* no explicit */ object(const object& other): 
            dbc_object_checking_contract_(other.dbc_object_checking_contract_) 
            {}

    const object& operator=(const object& other) {
        dbc_object_checking_contract_ = dbc_object_checking_contract_ || 
                other.dbc_object_checking_contract_;
        return *this;
    }

    virtual ~object() {}
};

} // namespace dbc

#endif // DBC

#endif // DBC_OBJECT_HPP_

