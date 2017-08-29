/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

/** @file
 * Precond attempts to access self, must fail compilation.
 */

#include <dbc.hpp>

// Specification //

template<typename T>
class positive DBC_INHERIT_OBJECT(positive<T>) {
public:
    // Method (1): Constr spec and impl in .hpp (w/ and w/out DBC).
    explicit positive(const T& value = T()): value_ptr_(new T())
    DBC_CONSTRUCTOR( (public) (template)(positive)( (const T&)(value) ), {
        DBC_ASSERT(value > 0, "positive");
        DBC_ASSERT(self.value_ptr_, "value exists"); // Must fail.
    }, {
        DBC_ASSERT(*self.now.value_ptr_ == value.now, "value set");
    }, {
        *value_ptr_ = value;
    })

private:
    T* value_ptr_;

    DBC_INVARIANT(positive, {
        DBC_ASSERT(self.value_ptr_, "value exists");
        DBC_ASSERT(*self.value_ptr_ > 0, "positive");
    })
};

// Program //

int main() {
    positive<int>(-10);

    return 0;
};

