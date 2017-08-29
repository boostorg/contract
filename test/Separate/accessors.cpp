/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <string>

class scoped_recursive_lock { // A dummy implementation...
public:
    scoped_recursive_lock() { std::cout << "Locked" << std::endl; }
    ~scoped_recursive_lock() { std::cout << "Unlocked" << std::endl; }
};

template<typename C> class separate; // Forward declaration for friendship.

/**
 * @tparam V Member variable type. This type must have copy constructor (for
 *  both read and write functions).
 */
template<class D, class C, typename V>
class varctor {
    friend class separate<D>; // Only = and V() public, constr via friendship.
public:
    /** Write member variable. */
    V operator=(const V& value) {
        scoped_recursive_lock l;
        return ((*obj_).*var_) = value; // Requires V copy constr.
    }

    /** Read member variable. */
    operator V() {
        scoped_recursive_lock l;
        return (*obj_).*var_; // Requires V copy constr.
    }

private:
    varctor(boost::shared_ptr<C> obj, V C::* var): obj_(obj), var_(var) {}
    varctor(const varctor& o): obj_(o.obj_), var_(o.var_) {}
    
    varctor& operator=(const varctor&); // No copy operator.

    boost::shared_ptr<C> obj_;
    V C::* var_;
};

template<class D, typename R, class C>
class functor0 {
    friend class separate<D>; // Only opeator() public, constr via friendship.
public:
    R operator()() {
        scoped_recursive_lock l;
        return ((*obj_).*fun_)();
    }

private:
    functor0(boost::shared_ptr<C> obj, R (C::* fun)()):
            obj_(obj), fun_(fun) {}
    functor0(const functor0& o): obj_(o.obj_), fun_(o.fun_) {}

    functor0& operator=(const functor0&); // No copy operator.

    boost::shared_ptr<C> obj_;
    R (C::* fun_)();
};

template<class D, typename R, class C, typename A0>
class functor1 {
    friend class separate<D>; // Only opeator() public, constr via friendship.
public:
    R operator()(A0 arg0) {
        scoped_recursive_lock l;
        return ((*obj_).*fun_)(arg0);
    }
    R operator()(/* default A0 */) {
        scoped_recursive_lock l;
        return ((*obj_).*fun_)();
    }
private:
    functor1(boost::shared_ptr<C> obj, R (C::* fun)(A0)):
            obj_(obj), fun_(fun) {}
    functor1(const functor1& o): obj_(o.obj_), fun_(o.fun_) {}

    functor1& operator=(const functor1&); // No copy operator.

    boost::shared_ptr<C> obj_;
    R (C::* fun_)(A0);
};

template<class C>
class separate {
public:
    // Copyable.

    separate(): obj_(new C()) {} // If used, C must have copy constr.
    
    // Shall this instead be constr only with separate(C* ptr) like
    // boost::shared_ptr? That way, separate<> will not actually constr C...
    // and it might be problematic for CORBA or similar...
    template<typename A0>
    separate(A0 arg0): obj_(new C(arg0)) {} // Same constr as C.

//    /** Access member variable from class C. */
//    template<typename V>
//    varctor<C, C, V> operator->*(V C::* var)
//        { return varctor<C, C, V>(obj_, var); }
    
    /** Access member variables. */
    template<typename V, class B>
    varctor<C, B, V> operator->*(V B::* var)
        { return varctor<C, B, V>(obj_, var); }
    
//    /** Access member function from class C. */
//    template<typename R, typename A0>
//    functor1<C, R, C, A0> operator->*(R (C::* func)(A0))
//        { return functor1<C, R, C, A0>(obj_, func); }
    
    /** Access member functions. */
    template<typename R, class B, typename A0>
    functor1<C, R, B, A0> operator->*(R (B::* func)(A0))
        { return functor1<C, R, B, A0>(obj_, func); }
    
    template<typename R, class B>
    functor0<C, R, B> operator->*(R (B::* func)())
        { return functor0<C, R, B>(obj_, func); }
    
private:
    boost::shared_ptr<C> obj_;
};


class B {
public:
    std::string b1;
    
    B(): b1("bbb") {}
    
    std::string g1(const std::string& i) { return b1 + "<base>" + i; }
};

class C: public B {
public:
    std::string a1;

    C(const std::string& a): a1(a) {}

    std::string f0() { return a1; }
    std::string f1(const std::string& i) { return a1 + i; }
    
    // Optional arguments are not supported via mem ptr and functors.
    // Overloading can be used to obtain the same effect (the 2nd definition
    // below makes i optional). However, mem ptr and functor require huggly
    // stati_cast to resolve type selection ambiugities manually -- static_cast
    // will result in compiler error if not function declared, other casting
    // will result in runtime segfault, ONLY USE STATIC CASTING!!!
    std::string opt(const std::string& i) { return a1 + i; }
    std::string opt() { return a1 + "<optional>"; }
};

int main() {
    C c("abc");
    C* p = &c;
    p->*&C::a1 = "xyz";
    std::cout << "a1 = " << p->*&C::a1 << std::endl;
    std::string pi = (p->*&C::f1)("uvw");
    std::cout << "f1(\"uvw\") = " << pi << std::endl;
    
    std::cout << "Similarly but accessed via separate<>:" << std::endl;
    
    separate<C> s("abc");
    s->*&C::a1 = "xyz";
    std::cout << "a1 = " << (s->*&C::a1).operator std::string() << std::endl;
    std::cout << "f0 = " << (s->*&C::f0)() << std::endl;
    std::string s1 = (s->*&C::f1)("uvw");
    std::cout << "f1 = " << s1 << std::endl;
    // Accesing inherited members.
    s->*&C::b1 = "<base>xyz";
    std::cout << "b1 = " << std::string(s->*&C::b1) << std::endl;
    std::string bi = (s->*&C::g1)("uvw");
    std::cout << "g1 = " << bi << std::endl;
    // Optional arguments.
    std::cout << "opt(\"zzz\") = " << (s->*static_cast
            <std::string (C::*)(const std::string&)>(&C::opt))("zzz") 
            << std::endl;
    std::cout << "opt() = " << (s->*static_cast
            <std::string (C::*)()>(&C::opt))() 
            << std::endl;
    
    return 0;
}

