
#include <dbc.hpp>

template<typename T>
class number DBC_INHERIT_OBJECT(number<T>) {
public:
    number(const T& value = T()): value_ptr_(new T()) { init(value); }

    virtual ~number()
    DBC_DESTRUCTOR( (public) (virtual) (template)(number)(), ; )

    T get() const
    DBC_MEM_FUN( (public) (T) (template)(number) (get)() (const), {
    }, {
        DBC_ASSERT(result == *(self.now.value_ptr_), "returning value");
    }, ; )

    double operator/(const double& den) const
    DBC_MEM_FUN( (public) (double) (template)(number) 
            (operator_div)( (const double&)(den) ) (const), {
        DBC_ASSERT(den != 0, "non-zero denumerator");
    }, {
        DBC_ASSERT((result * den.now) == self.now.get(), "returning division");
    }, ; )

private:
    void init(const T& value)
    DBC_CONSTRUCTOR( (private) (template)(number)( (const T&)(value) ), {
    }, {
        DBC_ASSERT(self.now.get() == value.now, "value set");
    }, ; )
    
    T* value_ptr_;

    DBC_INVARIANT(number<T>, {
        DBC_ASSERT(self.value_ptr_, "value exists");
    })
};

// Implementation //

template<typename T>
void number<T>::DBC_BODY(init)(const T& value) { *value_ptr_ = value; }

template<typename T>
DBC_DESTRUCTOR_BODY(number<T>)() { delete value_ptr_; }

template<typename T>
T number<T>::DBC_BODY(get)() const { return *value_ptr_; }

template<typename T>
double number<T>::DBC_OPERATOR_BODY(operator/, operator_div)(
        const double& den) const { 
    return get() / den; 
}

