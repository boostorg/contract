
#ifndef BOOST_CONTRACT_OLDOF_HPP_
#define BOOST_CONTRACT_OLDOF_HPP_

#include <boost/contract/virtual_body.hpp>
#include <boost/contract/config.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/config.hpp>

// IMPORTANT: Following old-of templates and macros ensure that:
//  1.  Old-value expressions are evaluated only once and only when old-of
//      should not be skipped.
//  2.  Old-values are copied only once (using old-value type copy constructor)
//      and only when old-of should not be skipped.
// Old-of are skipped if either postconditions are disabled all together (see
// also CONFIG_NO_POSTCONDITONS), or if virtual-body functions are called to
// not check postconditions (as controlled by the "v" extra parameter).

#if !BOOST_PP_VARIADICS

#define BOOST_CONTRACT_OLDOF BOOST_CONTRACT_ERROR_variadic_macros_required_by_BOOST_CONTRACT_OLDOF_otherwise_manually_program_old_values

#else

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_OLDOF(...) \
    BOOST_PP_CAT(BOOST_PP_OVERLOAD( /* CAT(... EMPTY()) workaround for MSVC */ \
BOOST_CONTRACT_ERROR_macro_BOOST_CONTRACT_OLDOF_invalid_number_of_arguments_, \
            __VA_ARGS__)(__VA_ARGS__), BOOST_PP_EMPTY())

/* PRIVATE */

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#   define BOOST_CONTRACT_OLDOF_TYPEOF_(value) /* nothing */
#else
#   include <boost/typeof/typeof.hpp>
#   define BOOST_CONTRACT_OLDOF_TYPEOF_(value) BOOST_TYPEOF(value)
#endif

// NOTE: Following are not local macros, do NOT #undef them. These macro names
// are use so all variadic macro argument numbers > 2 will generate appropriate
// ERROR symbols.

#define \
BOOST_CONTRACT_ERROR_macro_BOOST_CONTRACT_OLDOF_invalid_number_of_arguments_2( \
        v_opt, value) \
    (boost::contract::skip_oldof(v_opt) ? boost::contract::oldof< \
            BOOST_CONTRACT_OLDOF_TYPEOF_((value))>() : (value))

#define \
BOOST_CONTRACT_ERROR_macro_BOOST_CONTRACT_OLDOF_invalid_number_of_arguments_1( \
        value) \
BOOST_CONTRACT_ERROR_macro_BOOST_CONTRACT_OLDOF_invalid_number_of_arguments_2( \
            BOOST_PP_EMPTY(), value)

#endif // VARIADICS

/* CODE */

namespace boost { namespace contract {

template<typename T = boost::contract::aux::none> class oldof;

// Used on compilers that do not support auto decl./type-of to erase old-value
// type T (and later un-erase it via pointer cast in oldof template below).
template<>
class oldof<boost::contract::aux::none> {
public:
    oldof() : ptr_() {}

    template<typename T> // This make_shared calls T's copy ctor.
    oldof(T const& value) : ptr_(boost::make_shared<T>(value)) {}

private:
    boost::shared_ptr<void> ptr_;

    template<typename T> friend class oldof; // Within same template family.
};

template<typename T>
class oldof {
public:
    oldof() : ptr_() {}
    
    // This make_shared calls T's copy ctor.
    oldof(T const& value) : ptr_(boost::make_shared<T>(value)) {}

    // This casts the pointer (to un-erase the type), so no T copy here.
    oldof(oldof<boost::contract::aux::none> const& old) :
            ptr_(boost::static_pointer_cast<T>(old.ptr_)) {}

    // Add const because contracts should not modify old-values.

    typename boost::add_const<T>::type& operator*() const { return *ptr_; }

    typename boost::add_const<T>::type* const operator->() const {
        return ptr_.get();
    }

private:
    boost::shared_ptr<T> ptr_;
};

bool skip_oldof(boost::contract::virtual_body const v) {
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return true; // Never check post, so old-of never needed.
#else
    if(v.action == boost::contract::virtual_body::user_call ||
            v.action == boost::contract::virtual_body::check_post_only) {
        return false; // Checking post, so old-of needed.
    }
    return true; // Not checking post, so old-of not needed.
#endif
}

bool skip_oldof() {
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return true; // Never check post, so old-of never needed.
#else
    return false; // Contracts of virtual-body functions, always check post.
#endif
}

} } // namespace

#endif // #include guard

