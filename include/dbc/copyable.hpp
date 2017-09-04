
#ifndef DBC_COPYABLE_HPP_
#define DBC_COPYABLE_HPP_

#ifndef DBC

#define DBC_COPYABLE(type) (type)

#else // DBC

// Prefix must match symbol postfix of DBC_PP_BASE_dbc_copyable_ macro name.
#define DBC_COPYABLE(type) (dbc_copyable_)(type)

namespace dbc {

/** Tag specified type as copyable. */
template<typename T> struct copyable { typedef T type; };

} // namespace dbc

#endif // DBC

#endif // DBC_COPYABLE_HPP_

