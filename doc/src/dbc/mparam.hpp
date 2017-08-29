/**
 * @file
 * Header to include only facility to support commas in macro parameters.
 */

/**
 * This macro is used to pass macro parameters containing commas.
 * The C++ preprocessor only recognize the <c>()</c> parenthesis. Other
 * parenthesis like <c><></c> for templates, <c>{}</c> for code blocks,
 * <c>[]</c> for indexing, etc are @e not recognized by the preprocessor so 
 * they do not wrap their expressions when used within macro parameters. This 
 * macro can be used to overcome this limitation.
 * 
 * For example, say that you have to pass to @c DBC_INHERIT_OBJECT() a class 
 * type which is a template with two arguments. The following will @e not work:
 * @code
 *  #include <dbc.hpp>
 *  
 *  template<typename K, typename T>
 *  class C DBC_INHERIT_OBJECT(C<K, T>) { ... }; // No, two macro parameters.
 * @endcode
 * The issue is that the preprocessor does not recognize the @c <> parenthesis
 * so the macro parameter <c>C<K, T></c> is interpreted by the preprocessor as
 * two separate tokens <c>C<K</c> and <c>T></c> separated by the comma. In this
 * case the compiler will generate an error saying that you passed two
 * parameters to the @c DBC_INHERIT_OBJECT() macro that takes one parameter
 * instead. @n
 * Because the preprocessor recognizes the <c>()</c> parenthesis, it might be
 * tempted to overcome this issue simply by wrapping the macro parameter within
 * <c>()</c> parenthesis:
 * @code
 *  #include <dbc.hpp>
 *  
 *  template<typename K, typename T>
 *  class C DBC_INHERIT_OBJECT( (C<K, T>) ) { ... }; // No type, only as value.
 * @endcode
 * In this case one parameter <c>(C<K, T>)</c> (and not two) is passed to the
 * macro. However, because of the extra parenthesis <c>()</c> around the
 * parameter, this time the C++ compiler (and not the preprocessor) will error 
 * when evaluating this expression in a context where a type is expected (note 
 * that this is instead a sufficient approach is the macro parameter represents
 * a value and not a type, but unfortunately that is not the case for
 * @c DBC_INHERIT_OBJECT() for which the parameter represents a type). @n
 * We need a way to strip the extra parenthesis <c>()</c> after they have been
 * used to pass the parameter as a single parameter. This is done by this macro
 * using the extra information of how many preprocessor tokens are contained
 * within the parenthesis (two in this example). The following will work:
 * @code
 *  #include <dbc.hpp>
 *  
 *  template<typename K, typename T>
 *  class C DBC_INHERIT_OBJECT( DBC_MPARAM(2, (C<K, T>) ) ) { ... }; // OK.
 * @endcode
 * 
 * Similar considerations apply if commas are used within code block
 * parenthesis <c>{}</c>. Note that when calling functions from code blocks,
 * commas separating the function arguments are always wrapped by <c>()</c> so
 * there is no issue. However, is you are instantiating a template with more
 * than one parameter in a code block you will need to use this macro. For 
 * example:
 * @code
 *  #include <dbc.hpp>
 *  ...
 *      DBC_INVARIANT(C, {
 *          f(1, 2); // OK, as the comma wrapped within () because of fun call.
 *          std::map<int, float> m; // No, two macro parameters.
 *          ...
 *      })
 * @endcode
 * will @e not work as the code block parameter is interpreted by the
 * preprocessor are two separate tokens
 * <c>{ f(1, 2); sts::map<int</c> and <c>float> m; ... }</c>
 * because of the comma in the @c std::map template instantiation. This will
 * work:
 * @code
 *  #include <dbc.hpp>
 *  ...
 *      DBC_INVARIANT(C, DBC_MPARAM(2, ({ // OK.
 *          f(1, 2);
 *          std::map<int, float> m;
 *          ...
 *      })))
 * @endcode
 * Note, the extra parenthesis <c>()</c> wrapping the code block <c>{ ... }</c>
 * passed to @c DBC_MPARAM().
 * 
 * Similar considerations apply when using any other parenthesis different from
 * <c>()</c> within a macro parameter.
 * @note This limitation has to do simply with how the C++ preprocessor works
 *  and it is not introduced by this library. If new revisions of the C++
 *  standard were to support @e variadic macros [@ref Nel04], this limitation
 *  could be overcome in different ways and the need for the @c DBC_MPARAM()
 *  macro could be revisited.
 * 
 * @param[in] token_count The number of tokens contained in
 *  @a parenthesised_param as recognized by the preprocessor. This number
 *  cannot be negative and there is no need to use this macro with a count less
 *  than 2 (because the preprocessor can deal directly with no-token or a
 *  single-token macro parameters).
 * @param[in] parenthesised_param The tokens that should be threated as a
 *  single macro parameter wrapped within extra parenthesis <c>()</c>.
 * @return Pass the specified tokens as a single macro parameter.
 */
#define DBC_MPARAM(token_count, parenthesised_param)

