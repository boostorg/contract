
#ifndef DBC_SYNC_HPP_
#define DBC_SYNC_HPP_

namespace dbc {

template<typename T, T DEFAULT>
class sync_ {
public:
    sync_(const T& value = DEFAULT): value_(value) {}

    /** @todo[LC] If DBC_THREADING, sync this operation with a mutex declared
     * mutable in this class' state. */
     
    const T& operator=(const T& value) { return value_ = value; }

    operator T() const { return value_; }

private:
    T value_;
};

} // namespace dbc

#endif // DBC_SYNC_HPP_

