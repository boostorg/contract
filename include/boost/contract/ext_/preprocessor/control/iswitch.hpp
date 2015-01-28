
#ifndef BOOST_CONTRACT_EXT_PP_ISWITCH_HPP_
#define BOOST_CONTRACT_EXT_PP_ISWITCH_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "iswitch-generate.py".

#include <boost/preprocessor/limits.hpp>
#if BOOST_PP_LIMIT_TUPLE != 64
#   error "code generation used incorrect BOOST_PP_LIMIT_TUPLE"
#endif

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

// Usage:
//  ISWITCH-n(cond, case1, op1, ..., case-n, op-n, default_, data)
//
// Parameters (for each i in [1, n]):
// * Parameter `data` must be a pp-tuple `(x, y, ...)` that can be used as
// argument list for the op-i macros `op-i data` expands to `op-i(x, y, ...)`.
// * Parameter `cond` must be a pp-tuple `(a, b, ...)` that can be used as
// argument list for case-i macros `case-i cond` expands to `case-i(a, b, ...)`.
// * All case-i macros must expand `case-i cond` to 0 or 1.
//
// Result:
// * Let k be the first index in [1, n] for which `case-k cond` expands to 1
// then ISWITCH-n expands to `op-k data` and all `case-i cond` for i in
// (k, n] are not evaluated. Therefore, it is possible to put last case-i macros
// expensive to evaluate (or even incorrect to evaluate unless previous case
// macros expand 0, similar to C++ short-circuit optimizations).
// * ISWITHC-n expands to `default_ data` iff `case-i data` expands to 0 for
// all i in [1, n].
//
// Notes:
// * There is also a variadics version of this macro that determines n
// automatically (but to avoid a couple of extra macro expansions, it is best
// to not use the variadics version when n is known a priori).

/* ISWITCH (variadics) */

#include <boost/preprocessor/config/config.hpp>
#if BOOST_PP_VARIADICS
#   include <boost/preprocessor/facilities/overload.hpp>
#   define BOOST_CONTRACT_EXT_PP_ISWITCH(...) \
        BOOST_PP_EXPAND( \
            BOOST_PP_OVERLOAD(BOOST_CONTRACT_EXT_PP_ISWITCH_, __VA_ARGS__) \
            (__VA_ARGS__) \
        )
#endif

/* ISWITCH1 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH1(cond, case1, op1, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        op1 \
    , \
        default_ \
    ) data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH_5 BOOST_CONTRACT_EXT_PP_ISWITCH1

/* ISWITCH2 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH2_YES_(cond, case1, op1, case2, op2, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH2_NO_(cond, case1, op1, case2, op2, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH1(cond, case2, op2, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH2(cond, case1, op1, case2, op2, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH2_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH2_NO_ \
    )(cond, case1, op1, case2, op2, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_7 BOOST_CONTRACT_EXT_PP_ISWITCH2

/* ISWITCH3 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH3_YES_(cond, case1, op1, case2, op2, case3, op3, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH3_NO_(cond, case1, op1, case2, op2, case3, op3, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH2(cond, case2, op2, case3, op3, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH3(cond, case1, op1, case2, op2, case3, op3, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH3_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH3_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_9 BOOST_CONTRACT_EXT_PP_ISWITCH3

/* ISWITCH4 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH4_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH4_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH3(cond, case2, op2, case3, op3, case4, op4, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH4(cond, case1, op1, case2, op2, case3, op3, case4, op4, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH4_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH4_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_11 BOOST_CONTRACT_EXT_PP_ISWITCH4

/* ISWITCH5 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH5_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH5_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH4(cond, case2, op2, case3, op3, case4, op4, case5, op5, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH5(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH5_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH5_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_13 BOOST_CONTRACT_EXT_PP_ISWITCH5

/* ISWITCH6 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH6_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH6_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH5(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH6(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH6_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH6_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_15 BOOST_CONTRACT_EXT_PP_ISWITCH6

/* ISWITCH7 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH7_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH7_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH6(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH7(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH7_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH7_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_17 BOOST_CONTRACT_EXT_PP_ISWITCH7

/* ISWITCH8 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH8_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH8_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH7(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH8(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH8_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH8_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_19 BOOST_CONTRACT_EXT_PP_ISWITCH8

/* ISWITCH9 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH9_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH9_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH8(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH9(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH9_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH9_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_21 BOOST_CONTRACT_EXT_PP_ISWITCH9

/* ISWITCH10 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH10_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH10_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH9(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH10(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH10_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH10_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_23 BOOST_CONTRACT_EXT_PP_ISWITCH10

/* ISWITCH11 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH11_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH11_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH10(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH11(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH11_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH11_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_25 BOOST_CONTRACT_EXT_PP_ISWITCH11

/* ISWITCH12 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH12_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH12_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH11(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH12(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH12_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH12_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_27 BOOST_CONTRACT_EXT_PP_ISWITCH12

/* ISWITCH13 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH13_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH13_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH12(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH13(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH13_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH13_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_29 BOOST_CONTRACT_EXT_PP_ISWITCH13

/* ISWITCH14 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH14_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH14_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH13(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH14(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH14_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH14_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_31 BOOST_CONTRACT_EXT_PP_ISWITCH14

/* ISWITCH15 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH15_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH15_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH14(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH15(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH15_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH15_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_33 BOOST_CONTRACT_EXT_PP_ISWITCH15

/* ISWITCH16 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH16_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH16_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH15(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH16(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH16_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH16_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_35 BOOST_CONTRACT_EXT_PP_ISWITCH16

/* ISWITCH17 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH17_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH17_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH16(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH17(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH17_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH17_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_37 BOOST_CONTRACT_EXT_PP_ISWITCH17

/* ISWITCH18 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH18_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH18_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH17(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH18(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH18_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH18_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_39 BOOST_CONTRACT_EXT_PP_ISWITCH18

/* ISWITCH19 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH19_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH19_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH18(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH19(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH19_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH19_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_41 BOOST_CONTRACT_EXT_PP_ISWITCH19

/* ISWITCH20 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH20_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH20_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH19(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH20(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH20_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH20_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_43 BOOST_CONTRACT_EXT_PP_ISWITCH20

/* ISWITCH21 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH21_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH21_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH20(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH21(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH21_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH21_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_45 BOOST_CONTRACT_EXT_PP_ISWITCH21

/* ISWITCH22 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH22_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH22_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH21(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH22(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH22_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH22_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_47 BOOST_CONTRACT_EXT_PP_ISWITCH22

/* ISWITCH23 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH23_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH23_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH22(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH23(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH23_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH23_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_49 BOOST_CONTRACT_EXT_PP_ISWITCH23

/* ISWITCH24 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH24_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH24_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH23(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH24(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH24_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH24_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_51 BOOST_CONTRACT_EXT_PP_ISWITCH24

/* ISWITCH25 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH25_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH25_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH24(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH25(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH25_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH25_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_53 BOOST_CONTRACT_EXT_PP_ISWITCH25

/* ISWITCH26 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH26_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH26_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH25(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH26(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH26_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH26_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_55 BOOST_CONTRACT_EXT_PP_ISWITCH26

/* ISWITCH27 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH27_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH27_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH26(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH27(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH27_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH27_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_57 BOOST_CONTRACT_EXT_PP_ISWITCH27

/* ISWITCH28 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH28_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH28_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH27(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH28(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH28_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH28_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_59 BOOST_CONTRACT_EXT_PP_ISWITCH28

/* ISWITCH29 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH29_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH29_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH28(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH29(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH29_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH29_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_61 BOOST_CONTRACT_EXT_PP_ISWITCH29

/* ISWITCH30 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH30_YES_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, case30, op30, default_, data) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH30_NO_(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, case30, op30, default_, data) \
    BOOST_CONTRACT_EXT_PP_ISWITCH29(cond, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, case30, op30, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH30(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, case30, op30, default_, data) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(case1 cond, \
        BOOST_CONTRACT_EXT_PP_ISWITCH30_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_ISWITCH30_NO_ \
    )(cond, case1, op1, case2, op2, case3, op3, case4, op4, case5, op5, case6, op6, case7, op7, case8, op8, case9, op9, case10, op10, case11, op11, case12, op12, case13, op13, case14, op14, case15, op15, case16, op16, case17, op17, case18, op18, case19, op19, case20, op20, case21, op21, case22, op22, case23, op23, case24, op24, case25, op25, case26, op26, case27, op27, case28, op28, case29, op29, case30, op30, default_, data))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_63 BOOST_CONTRACT_EXT_PP_ISWITCH30

#endif // #include guard

