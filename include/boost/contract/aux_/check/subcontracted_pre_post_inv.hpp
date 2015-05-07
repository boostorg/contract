
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

// TODO: Double check that this lib header should only #include from core/*
// and aux_/*, while headers directly from contract/* should NOT be #included
// by other headers of this lib (so they remain 100% for user's #inclusion).
// Consider generating a Doxygen #include diagram...

#include <boost/contract/core/var.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/check/pre_post_inv.hpp>
#include <boost/contract/aux_/type_traits/bases.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>

namespace boost { namespace contract { namespace aux { namespace check {

template<
    class Class,
    class Intro = boost::contract::aux::none,
    typename Arg0 = boost::contract::aux::none
> class subcontracted_pre_post_inv :
    public boost::contract::aux::check::pre_post_inv<Class>,
    private boost::noncopyable // Avoid copying captured function arguments.
{
    // Base types as pointers because mpl::for_each will construct them.
    typedef typename boost::mpl::transform<
        typename boost::mpl::eval_if<boost::contract::aux::type_traits::
                has_bases<Class>,
            boost::contract::aux::type_traits::bases_of<Class>
        ,
            boost::mpl::identity<boost::mpl::vector<> >
        >::type,
        boost::add_pointer<boost::mpl::placeholders::_1>
    >::type base_ptrs;

public:
    explicit subcontracted_pre_post_inv(boost::contract::from const from,
        boost::contract::virtual_* const virt, Class* const obj, Arg0& arg0
    ) :
        boost::contract::aux::check::pre_post_inv<Class>(from, obj),
        virt_(virt),
        arg0_(arg0)
    { init(); }
    
    virtual ~subcontracted_pre_post_inv() { if(own_virt_) delete virt_; }
    
protected:
    void copy_subcontracted_oldof() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::virtual_::copy_oldof));
        // Old-of values always copied on stack for derived func being called.
    }
    
    void check_subcontracted_entry_inv() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::virtual_::check_entry_inv));
        this->check_entry_inv();
    }
    
    // Allow to throw on failure for relaxing subcontracted pre.
    void check_subcontracted_pre(bool const throw_on_failure = false) {
        try {
            boost::mpl::for_each<base_ptrs>(check_base_.action(
                    boost::contract::virtual_::check_pre));
            // Pre logic-or: Last check, error also throws.
            this->check_pre(throw_on_failure);
        } catch(boost::contract::aux::no_error const&) {
            // Pre logic-or: Stop at 1st no_error (thrown by callee).
        }
    }

    void check_subcontracted_exit_inv() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::virtual_::check_exit_inv));
        this->check_exit_inv();
    }

    void check_subcontracted_post() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::virtual_::check_post));
        std::clog << "post checking" << std::endl;
        check_base_.action(boost::contract::virtual_::check_this_post)(this->object());
        std::clog << "post checked" << std::endl;
        //this->check_post();
    }

    // Invariant: virt_ never null after init (so can always deref it here).
    boost::contract::virtual_& virtual_call() { return *virt_; }

private:
    void init() {
        if(virt_) own_virt_ = false;
        else {
            virt_ = new boost::contract::virtual_();
            own_virt_ = true;
        }
        check_base_.nest(this);
    }

    class check_base {
    public:
        explicit check_base() : nest_(0),
                action_(boost::contract::virtual_::user_call) {}

        void nest(subcontracted_pre_post_inv* n) { nest_ = n; }

        check_base& action(boost::contract::virtual_::action_enum const a) {
            action_ = a;
            return *this;
        }

        template<class Base>
        void operator()(Base*) {
            typedef boost::contract::var result_type;
            typedef boost::mpl::vector<Arg0 const&, boost::contract::virtual_*>
                    virtual_arg_types;
            //std::clog << "*** func: " <<
            //    typeid(result_type).name() << " " << 
            //    typeid(Base).name() << " " <<
            //    typeid(virtual_arg_types).name() <<
            //std::endl;

            call_base_function<Base, result_type, virtual_arg_types>(
                boost::mpl::bool_<
                    Intro::template has_member_function<
                        Base,
                        result_type,
                        virtual_arg_types,
                        boost::function_types::const_qualified
                    >::value
                >()
            );
        }

    private:
        template<class Base, typename ResultType, class VirtualArgTypes>
        void call_base_function(boost::mpl::false_ const&) {
            //std::clog << "*** base function not found" << std::endl;
        }
        template<class Base, typename ResultType, class VirtualArgTypes>
        void call_base_function(boost::mpl::true_ const&) {
            //std::clog << "*** base function found" << std::endl;
            
            typedef typename boost::mpl::push_front<
                typename boost::mpl::push_front<VirtualArgTypes, Base*>::type,
                ResultType
            >::type base_virtual_func_types;
            typedef typename boost::function_types::member_function_pointer<
                base_virtual_func_types,
                boost::function_types::const_qualified
            >::type base_virtual_func_ptr;

            base_virtual_func_ptr base_virtual_func = Intro::template
                    member_function_address<Base, base_virtual_func_ptr>();
            BOOST_CONTRACT_AUX_DEBUG(base_virtual_func);
            
            BOOST_CONTRACT_AUX_DEBUG(nest_);
            Base const* const base = nest_->object();
            BOOST_CONTRACT_AUX_DEBUG(base);
            
            boost::contract::virtual_::action_enum reset_action =
                    nest_->virtual_call().action_;
            nest_->virtual_call().action_ = action_;
            try {
                (base->*base_virtual_func)(nest_->arg0_, nest_->virt_);
            } catch(boost::contract::aux::no_error const&) {
                if(nest_->virtual_call().action_ ==
                        boost::contract::virtual_::check_pre) {
                    nest_->virtual_call().action_ = reset_action;
                    throw; // Pre logic-or: 1st no_err stops (throw to caller).
                }
            } catch(...) {
                if(nest_->virtual_call().action_ ==
                        boost::contract::virtual_::check_pre) {
                    // Pre logic-or: Ignore err, possibly checks up to caller.
                }
            }
            nest_->virtual_call().action_ = reset_action;
        }

        subcontracted_pre_post_inv* nest_;
        boost::contract::virtual_::action_enum action_;
    };

    bool own_virt_;
    boost::contract::virtual_* virt_;
    check_base check_base_;
    // TODO: Support 0-to-n args.
    Arg0& arg0_; // TODO: Should this be & or perfect fwd?
};

} } } } // namespace

#endif // #include guard

