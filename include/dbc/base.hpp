
#ifndef DBC_BASE_HPP_
#define DBC_BASE_HPP_

#ifndef DBC

#define DBC_BASE(base_class_type) (base_class_type)

#else // DBC

// Prefix must match symbol postfix of DBC_PP_BASE_dbc_base_ macro name.
#define DBC_BASE(base_class_type) (dbc_base_)(base_class_type)

#endif // DBC

#endif // DBC_BASE_HPP_

