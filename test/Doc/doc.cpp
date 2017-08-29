
#include <dbc.hpp>
#include <iostream>

namespace util {

/** 
 * Example of template documentation with namespace and more than 1 template 
 * argument.
 * @tparam From Source type.
 * @tparam To Destination type.
 */
template<typename From, typename To>
class converter DBC_INHERIT_OBJECT(DBC_MPARAM(2, (converter<From, To>))) {
public:
    /**
     * Convert specified value to integer.
     * @param[in] from The value to convert.
     * @return Converted value.
     */
    To convert(const From& from)
    DBC_MEM_FUN( (public) (To) (template)(converter)
            (convert)( (const From&)(from) ), {
        DBC_ASSERT(true, "convert precondition");
    }, {
        DBC_ASSERT(true, "convert postcondition");
    }, {
        return To(from);
    })

private:
    // Here, class type must spell full namespace for Doxygen to work.
    DBC_INVARIANT(DBC_MPARAM(2, (util::converter<From, To>)), {
        DBC_ASSERT(true, "converter invariant");
    })
};

} // namespace util

/** Example fo class documentation (no template, no namespace). */
class display DBC_INHERIT_OBJECT(display) {
public:
    /**
     * Print specified integer on stdout and terminate with a new line.
     * @param[in] i Integer to print.
     */
    void print(const int& i) const
    DBC_MEM_FUN( (public) (void) (display) 
            (print)( (const int&)(i) ) (const), {
        DBC_ASSERT(true, "print precondition");
    }, {
        DBC_ASSERT(true, "print postcondition");
    },{
        std::cout << i << std::endl;
    })

private:
    // Don't use global namespace prefix "::display", it will confuse Doxygen.
    DBC_INVARIANT(display, {
        DBC_ASSERT(true, "display invariant");
    })
};

int main() {
    util::converter<double, int> c;
    display d;
    d.print(c.convert(3.2));

    return 0;
}

