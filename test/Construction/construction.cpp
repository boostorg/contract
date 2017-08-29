/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <iostream>
#include <string>

// Specification //

template<typename T>
class number DBC_INHERIT_OBJECT(number<T>) {
public:
    // Method (1): Constr spec and impl in .hpp (w/ and w/out DBC).
    explicit number(const T& value = T()): value_ptr_(new T())
    DBC_CONSTRUCTOR( (public) (template)(number)( (const T&)(value) ), {
        DBC_ASSERT(true, "constructor precondition");
    }, {
        DBC_ASSERT(true, "constructor postondition");
    }, {
        *value_ptr_ = value;
    })
    
    // Method (2): To split spec and impl must use init().
    // Contract and construcotr real implementation specified by init(). Actual
    // constructor has trivial implementation that simply calls init() but base
    // initializers (if any) must be specified by the constructor 
    // implementation (this trivial constructor implementation is simple and 
    // small enough that could be defined directly in the .hpp but it could be 
    // put in the .cpp as well -- it is mainly a matter of taste.)
    // This private init() mechanism is commonly used also to implement 
    // delegating construction in C++. To avoid initialization problems: 
    // (a) init() must be private, (b) init() must be called only by the class 
    // constructor and not by any other member function. If C++ supported 
    // delegating constructor, DBC++ could have avoided the init() 
    // complication...
    explicit number(const std::string& s): value_ptr_(new T()) { init(s); }

    virtual ~number(void)
    DBC_DESTRUCTOR( (public) (virtual) (template)(number)( (void) ), ;)

    const T& value(void) const
    DBC_MEM_FUN( (public) (const T&) (template)(number)
            (value)( (void) ) (const), {
    }, {
        DBC_ASSERT(result == *(self.now.value_ptr_), "returning value");
    }, ;)

private:
    void init(const std::string& s)
    DBC_CONSTRUCTOR( (private) (template)(number)( (const std::string&)(s) ), {
        DBC_ASSERT(true, "init precondition");
    }, {
        // value_ptr_ can be safety deref. here because invariant checked it.
        DBC_ASSERT(T(s.now.size()) == *(self.now.value_ptr_), 
                "value initialized");
    }, ;)

    T* value_ptr_;

    DBC_INVARIANT(number, {
        DBC_ASSERT(self.value_ptr_, "value exists");
    })
};

// Implementation //

template<typename T>
void number<T>::DBC_BODY(init)(const std::string& s)
    { *value_ptr_ = s.size(); }
    
template<typename T>
DBC_DESTRUCTOR_BODY(number<T>)() { delete value_ptr_; }

template<typename T>
const T& number<T>::DBC_BODY(value)() const { return *value_ptr_; }

// Program //

int main() {
    std::cout << number<int>(10).value() << std::endl;
    std::cout << number<int>("abc").value() << std::endl;

    return 0;
};

