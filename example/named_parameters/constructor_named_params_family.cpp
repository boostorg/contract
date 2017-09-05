
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>
#include <vector>

namespace family {

struct person
{
    std::string name;
    int age;
    double weight;

    template< typename Name, typename Age, typename Weight >
    person ( Name the_name, Age the_age, Weight the_weight ) 
        : name(the_name), age(the_age), weight(the_weight)
    {}

    person& operator= ( person const& right )
    {
        name = right.name; age = right.age; weight = right.weight;
        return *this;
    }
};

} // namespace

//[constructor_named_params_family
namespace family {

CONTRACT_PARAMETER(name)
CONTRACT_PARAMETER(age)
CONTRACT_PARAMETER(relatives)
CONTRACT_PARAMETER(weight)

CONTRACT_CLASS(
    struct (member) extends( public person )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_CONSTRUCTOR(
        public (member) (
                in auto name,
                in out auto age, //default 32,
                deduce out (std::vector<person>) relatives,
                deduce in requires(
                    boost::is_convertible<boost::mpl::_, double>
                ) weight //, default(75.0)
            ) // Preconditions, body, etc access arguments as usual...
            precondition( std::string(name) != "", age >= 0, weight >= 0.0 )
            postcondition(
                auto old_relatives_size = CONTRACT_OLDOF relatives.size(),
                relatives.size() == old_relatives_size + 1
            )
            initialize( // ... but initializers must use the `..._ARG` macro.
                person(CONTRACT_CONSTRUCTOR_ARG(name),
                        CONTRACT_CONSTRUCTOR_ARG(age),
                        CONTRACT_CONSTRUCTOR_ARG(weight)),
                family_(CONTRACT_CONSTRUCTOR_ARG(relatives))
            )
    ) {
        relatives.push_back(*this);
    }

    private: std::vector<person>& family_;
};

} // namespace
//]

int main ( void )
{
    //[constructor_named_params_family_call
    std::vector<family::person> r;/*
    family::member m1(family::name_ = "Mary", family::relatives_ = r);
    //]
    BOOST_TEST(m1.name == "Mary");
    BOOST_TEST(r.size() == 1);

    family::member m2(family::relatives_ = r, family::name_ = "Mike");
    BOOST_TEST(m2.name == "Mike");
    BOOST_TEST(r.size() == 2);
*/
    int a = 23;/*
    family::member m3(family::relatives_ = r, family::name_ = "Lisa",
            family::age_ = a);
    BOOST_TEST(m3.name == "Lisa");
    BOOST_TEST(m3.age == a);
    BOOST_TEST(r.size() == 3);

    family::member m4(family::relatives_ = r, family::weight_ = 65.0,
            family::name_ = "John");
    BOOST_TEST(m4.name == "John");
    BOOST_TEST(int(m4.weight) == 65);
    BOOST_TEST(r.size() == 4);
    */
    family::member m5(family::age_ = a, family::relatives_ = r,
            family::weight_ = 65.0, family::name_ = "July");
//    BOOST_TEST(m5.name == "July");
//    BOOST_TEST(int(m5.weight) == 65);
//    BOOST_TEST(r.size() == 5);
/*
    family::member m6("Paul", a, r, 65.0);
    BOOST_TEST(m6.name == "Paul");
    BOOST_TEST(m6.age == a);
    BOOST_TEST(int(m6.weight) == 65);
    BOOST_TEST(r.size() == 6);*/
    return boost::report_errors();
}
//]

