// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_SYNC_HPP_
#define CONTRACT_AUX_SYNC_HPP_

namespace contract { namespace aux {

template<typename T, T DEFAULT>
class sync {
public:
    sync(T const& value = DEFAULT): value_(value) {}

    // If threading, this accessors must be syncronized...
    T const& operator=(T const& value) { return value_ = value; }
    operator T() const { return value_; }

private:
    T value_;
};

}} // namespace

#endif // #include guard

