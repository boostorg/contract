/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef THROWING_NUMBER_HPP_
#define THROWING_NUMBER_HPP_

#include <dbc.hpp>
#include <iostream>
#include <string>
#include <cassert>

// Specification //
    
bool destructor_called = false; // For testing only.

template<typename T>
class number DBC_INHERIT_OBJECT(number<T>) {
public:
    T* value_ptr; // Intentionally public so we can mess with it.
    
    explicit number(void): value_ptr(new T())
    DBC_CONSTRUCTOR( (public) (template)(number)( (void) ), {
    }, {
    }, {
        *value_ptr = 0;
        // No error, invariant will not be violated.
    })
    
    explicit number(const T& value): value_ptr(new T())
    DBC_CONSTRUCTOR( (public) (template)(number)( (const T&)(value) ), {
    }, {
    }, {
        *value_ptr = value;
        value_ptr = 0; // Error, will violate invariant.
    })
    
    explicit number(const std::string& s): value_ptr(new T()) { init(s); }

    virtual ~number(void)
    DBC_DESTRUCTOR( (public) (virtual) (template)(number)( (void) ), ;)

    const T& value(void) const
    DBC_MEM_FUN( (public) (const T&) (template)(number)
            (value)( (void) ) (const), {
    }, {
        DBC_ASSERT(result == *(self.now.value_ptr), "returning value");
    }, ;)

    const T& value(const T& new_value)
    DBC_MEM_FUN( (public) (const T&) (template)(number) 
            (value)( (const T&)(new_value) ), {
    }, {
    }, ;)

private:
    void init(const std::string& s)
    DBC_CONSTRUCTOR( (private) (template)(number)( (const std::string&)(s) ), {
    }, {
        // value_ptr can be safety deref. here because invariant checked it.
        DBC_ASSERT(T(s.now.size()) == *(self.now.value_ptr), 
                "value initialized");
    }, ;)

    DBC_INVARIANT(number, {
        DBC_ASSERT(self.value_ptr, "value exists");
    })
};

// Implementation //

template<typename T>
void number<T>::DBC_BODY(init)(const std::string& s) {
    *value_ptr = s.size(); 
    value_ptr = 0; // Error, will violate invariant.
}
    
template<typename T>
DBC_DESTRUCTOR_BODY(number<T>)() { 
    std::cout << ">>> Destructor body called" << std::endl;
    destructor_called = true;
    // Assert never exec if inv is violated (for test prog only).
    assert(value_ptr);
    delete value_ptr; 
}

template<typename T>
const T& number<T>::DBC_BODY(value)() const { return *value_ptr; }

template<typename T>
const T& number<T>::DBC_BODY(value)(const T& new_value) {
    *value_ptr = new_value;
    value_ptr = 0; // Error, will violate invariant.
    return new_value;
}

#endif // THROWING_NUMBER_HPP_

