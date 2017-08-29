/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <iostream>

// Specification //

template<typename T>
class number DBC_INHERIT_OBJECT(number<T>) {
public:
    explicit number(const T& value = T()): value_(value)
    DBC_CONSTRUCTOR( (public) (template)(number)( (const T&)(value) ), {
    }, {
        DBC_ASSERT(self.now.value_ == value.now, "value set");
    }, {})

    // Operator body can be split from contract specification but using
    // valid macro token for function name and DBC_OPERATOR_BODY() instead of
    // DBC_BODY() -- when using macro APIs.
    T operator/(const T& denumerator) const
    DBC_MEM_FUN( (public) (T) (template)(number) 
            (operator_div)( (const T&)(denumerator) ) (const), {
        DBC_ASSERT(denumerator != 0, "denumerator not zero");
    }, {
        DBC_ASSERT(result * denumerator.now == self.now.value_, "divided");
    }, ;)

    // LIMITATION: This operator has no return type so its body must be 
    // implemented here together with its contract specification -- when using 
    // macro APIs.
    operator T() const
    DBC_MEM_FUN( (public) (T) (template)(number)
            (operator_T)() (const), {
    }, {
        DBC_ASSERT(result == self.now.value_, "returning value");
    }, { 
        return value_; 
    })

private:
    T value_;

    DBC_INVARIANT(number, {})
};

// Implementation //

template<typename T>
T number<T>::DBC_OPERATOR_BODY(operator/, operator_div)(
        const T& denumerator) const { 
    return value_ / denumerator; 
}

// Program //

int main() {
    number<int> i(+20);

    number<int> d1(i / -10);
    std::cout << d1 << std::endl;

    number<int> d2(i / 0); // Will violate operator/() precondition.

    return 0;
};

