#include <cassert>
#include <iostream>
#include "../src/polynomial.h"

using namespace std;

void test_default_constructor()
{
    Polynomial p;
    assert(p.toString() == "0");
}

void test_constructor_with_rational()
{
    unordered_map<int, Rational> coeffs = {
        {0, Rational(Integer(1), Natural(1))},
        {2, Rational(Integer(3), Natural(1))}
    };

    Polynomial p(coeffs);
    assert(p.DEG_P_N().toString() == "2");
    assert(p.LED_P_Q().toString() == "3/1");
}

void test_constructor_with_integer()
{
    unordered_map<int, Integer> coeffs = {
        {0, Integer(1)},
        {3, Integer(5)}
    };

    Polynomial p(coeffs);
    assert(p.DEG_P_N().toString() == "3");
    assert(p.LED_P_Q().toString() == "5/1");
}

void test_add()
{
    // p1 = 13x^3 + 2x + 1, p2 = 4x^2 + x + 3, expected = 13x^3 + 4x^2 + 3x + 4
    Polynomial p1({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(2), Natural(1))}, {3, Rational(Integer(13), Natural(1))} });
    Polynomial p2({ {0, Rational(Integer(3), Natural(1))}, {1, Rational(Integer(1), Natural(1))}, {2, Rational(Integer(4), Natural(1))} });
    Polynomial res = p1 + p2;
    Polynomial expected({ {0, Rational(Integer(4), Natural(1))}, {1, Rational(Integer(3), Natural(1))}, {2, Rational(Integer(4), Natural(1))}, {3, Rational(Integer(13), Natural(1))} });
    assert(res.toString() == expected.toString());
}

void test_sub()
{
    // p1 = 12x^3 + 2x + 1, p2 = 2x^5 + 3, expected = -2x^5 + 12x^3 + 2x - 2
    Polynomial p1({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(2), Natural(1))}, {3, Rational(Integer(12), Natural(1))} });
    Polynomial p2({ {0, Rational(Integer(3), Natural(1))}, {5, Rational(Integer(2), Natural(1))} });
    Polynomial res = p1 - p2;
    Polynomial expected({ {0, Rational(Integer(2, 1), Natural(1))}, {1, Rational(Integer(2), Natural(1))}, {3, Rational(Integer(12), Natural(1))}, {5, Rational(Integer(2,1), Natural(1))} });
    assert(res.toString() == expected.toString());
}

void test_mul_by_rational()
{
    // p = 2x + 1, expected = 6x + 3
    Polynomial p({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(2), Natural(1))} });
    Rational factor(Integer(3), Natural(1));
    Polynomial res = p.MUL_PQ_P(factor);

    Polynomial expected({ {0, Rational(Integer(3), Natural(1))}, {1, Rational(Integer(6), Natural(1))} });
    assert(res.toString() == expected.toString());
}

void test_mul_by_xk()
{
    // p = 2x + 1, k = 2, expected = 2x^3 + x^2
    Polynomial p({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(2), Natural(1))} });
    Polynomial res = p.MUL_Pxk_P(Natural(2));

    Polynomial expected({ {2, Rational(Integer(1), Natural(1))}, {3, Rational(Integer(2), Natural(1))} });
    assert(res.toString() == expected.toString());
}

void test_led_deg()
{
    // p = 7x^3 + 3x^2
    Polynomial p({ {3, Rational(Integer(7), Natural(1))}, {2, Rational(Integer(3), Natural(1))} });
    assert(p.LED_P_Q().toString() == "7/1");
    assert(p.DEG_P_N().toString() == "3");
}

void test_mul_pp_p()
{
    // p1 = x + 1, p2 = x + 2, expected = x^2 + 3x + 2
    Polynomial p1({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(1), Natural(1))} });
    Polynomial p2({ {0, Rational(Integer(2), Natural(1))}, {1, Rational(Integer(1), Natural(1))} });
    Polynomial res = p1 * p2;
    Polynomial expected({
        {0, Rational(Integer(2), Natural(1))},
        {1, Rational(Integer(3), Natural(1))},
        {2, Rational(Integer(1), Natural(1))}
        });
    assert(res.toString() == expected.toString());
}

void test_div_pp_p()
{
    // p1 = x^2 + 2x + 1, p2 = x + 1, expected = x + 1
    Polynomial p1({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(2), Natural(1))}, {2, Rational(Integer(1), Natural(1))} });
    Polynomial p2({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(1), Natural(1))} });
    Polynomial res = p1 / p2;

    Polynomial expected({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(1), Natural(1))} });
    assert(res.toString() == expected.toString());
}

void test_mod_pp_p()
{
    // p1 = x^2 + 2x + 3, p2 = x + 1, expected = 2
    Polynomial p1({ {0, Rational(Integer(3), Natural(1))}, {1, Rational(Integer(2), Natural(1))}, {2, Rational(Integer(1), Natural(1))} });
    Polynomial p2({ {0, Rational(Integer(1), Natural(1))}, {1, Rational(Integer(1), Natural(1))} });
    Polynomial res = p1 % p2;

    Polynomial expected({ {0, Rational(Integer(2), Natural(1))} });
    assert(res.toString() == expected.toString());
}

void test_derivative()
{
    // p1 = 3x^3 + 2x^2 + 5, expected = 9x^2 + 4x
    Polynomial p({
        {3, Rational(Integer(3), Natural(1))},
        {2, Rational(Integer(2), Natural(1))},
        {0, Rational(Integer(5), Natural(1))}
        });

    Polynomial d = p.DER_P_P();

    Polynomial expected({
        {2, Rational(Integer(9), Natural(1))},
        {1, Rational(Integer(4), Natural(1))}
        });
    assert(d.toString() == expected.toString());
}

void test_gcf_pp_p()
{
    // p1 = x^2 + 3x + 2, p2 = x^2 + 2x + 1, expected = x + 1
    Polynomial p1({
        {0, Rational(Integer(2), Natural(1))},
        {1, Rational(Integer(3), Natural(1))},
        {2, Rational(Integer(1), Natural(1))}
        });


    Polynomial p2({
        {0, Rational(Integer(1), Natural(1))},
        {1, Rational(Integer(2), Natural(1))},
        {2, Rational(Integer(1), Natural(1))}
        });

    Polynomial g = p1.GCF_PP_P(p2);
    Polynomial expected({
        {0, Rational(Integer(1), Natural(1))},
        {1, Rational(Integer(1), Natural(1))}
        });

    assert(g.toString() == expected.toString());
}

void test_nmr_p_p()
{
    // p = x^3 - 3x + 2 = (x + 2)(x - 1)^2, expected = x^2 + x - 2 = (x + 2)(x - 1)
    Polynomial p({
        {3, Rational(Integer(1), Natural(1))},
        {1, Rational(Integer(3, 1), Natural(1))},
        {0, Rational(Integer(2), Natural(1))}
        });

    Polynomial nm = p.NMR_P_P();


    Polynomial expected({
        {2, Rational(Integer(1), Natural(1))},
        {1, Rational(Integer(1), Natural(1))},
        {0, Rational(Integer(2, 1), Natural(1))}
        });

    assert(nm.toString() == expected.toString());

}


void test_is_zero()
{
    Polynomial p;
    assert(p.isZero());
    Polynomial q({ {0, Rational(Integer(), Natural(1))} });
    assert(q.isZero());
}

void test_fac_p_q()
{

    Polynomial p({
        {2, Rational(Integer(2), Natural(3))},
        {1, Rational(Integer(4), Natural(5))},
        {0, Rational(Integer(6), Natural(15))}
        });

    Rational res = p.FAC_P_Q();

    Rational expected(Integer(2), Natural(15));

    assert(res.toString() == expected.toString());

}

void test_zero_branches()
{
    Polynomial zero;


    assert(zero.LED_P_Q().isZero());
    assert(zero.DER_P_P().toString() == "0");

    bool thrown = false;
    try { zero.FAC_P_Q(); }
    catch (const std::logic_error&) { thrown = true; }
    assert(thrown);


    Rational q(Integer(3), Natural(1));
    assert(zero.MUL_PQ_P(q).isZero());


    assert(zero.MUL_Pxk_P(5).toString() == "0");
}

void test_division_by_zero()
{
    Polynomial p({ {2, Rational(Integer(1), Natural(1))}, {0, Rational(Integer(1), Natural(1))} });
    Polynomial zero;

    bool thrown = false;
    try { p.DIV_PP_P(zero); }
    catch (const std::logic_error&) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { p.MOD_PP_P(zero); }
    catch (const std::logic_error&) { thrown = true; }
    assert(thrown);
}

void test_gcf_with_zero()
{
    Polynomial p({ {2, Rational(Integer(1), Natural(1))}, {0, Rational(Integer(1), Natural(1))} });
    Polynomial zero;

    Polynomial g = p.GCF_PP_P(zero);
    assert(g.toString() == p.toString());
}

void test_nmr_derivative_zero()
{
    Polynomial p1({ {0, Rational(Integer(5), Natural(1))} });
    bool thrown1 = false;

    try { p1.NMR_P_P(); }
    catch (const std::logic_error&) { thrown1 = true; }
    assert(thrown1);
    Polynomial p2({ {0, Rational(Integer(4), Natural(1))}, {1, Rational(Integer(5), Natural(1))}, {2, Rational(Integer(1), Natural(1))} });

    bool thrown2 = false;
    try { p2.NMR_P_P(); }
    catch (const std::logic_error&) { thrown2 = true; }
    assert(thrown2);

}

int main()
{
    test_default_constructor();
    test_constructor_with_rational();
    test_constructor_with_integer();
    test_fac_p_q();
    test_derivative();
    test_is_zero();
    test_mul_by_xk();
    test_led_deg();
    test_add();
    test_sub();
    test_mul_pp_p();
    test_div_pp_p();

    test_mod_pp_p();
    test_gcf_pp_p();
    test_nmr_p_p();
    test_zero_branches();
    test_division_by_zero();
    test_gcf_with_zero();
    test_nmr_derivative_zero();
    return 0;
}