#include <cassert>
#include <iostream>
#include <stdexcept>
#include "integer.h"

void test_constructor_default() {
    Integer zero;
    assert(zero.ABS_Z_N().NZER_N_B() == true);
    assert(zero.POZ_Z_D() == 0);
}

void test_constructor_from_natural() {
    Natural nat("123");
    Integer num(nat);
    assert(num.ABS_Z_N().COM_NN_D(nat) == 0);
    assert(num.POZ_Z_D() == 1);
}

void test_constructor_with_sign() {
    Natural nat("456");
    Integer positive(nat, 0);
    Integer negative(nat, 1);
    
    assert(positive.ABS_Z_N().COM_NN_D(nat) == 0);
    assert(positive.POZ_Z_D() == 1);
    
    assert(negative.ABS_Z_N().COM_NN_D(nat) == 0);
    assert(negative.POZ_Z_D() == -1);
}

void test_constructor_from_string() {
    Integer positive("123");
    Integer negative("-456");
    Integer zero1("");
    Integer zero2("0");
    
    assert(positive.POZ_Z_D() == 1);
    assert(negative.POZ_Z_D() == -1);
    assert(zero1.POZ_Z_D() == 0);
    assert(zero2.POZ_Z_D() == 0);
}

void test_ABS_Z_N() {
    Natural nat("789");
    Integer positive(nat, 0);
    Integer negative(nat, 1);
    
    assert(positive.ABS_Z_N().COM_NN_D(nat) == 0);
    assert(negative.ABS_Z_N().COM_NN_D(nat) == 0);
}

void test_POZ_Z_D() {
    Integer zero;
    Integer positive("123");
    Integer negative("-456");
    
    assert(zero.POZ_Z_D() == 0);
    assert(positive.POZ_Z_D() == 1);
    assert(negative.POZ_Z_D() == -1);
}

void test_MUL_ZM_Z() {
    Integer positive("123");
    Integer negative("-456");
    Integer zero;
    
    Integer pos_to_neg = positive.MUL_ZM_Z();
    Integer neg_to_pos = negative.MUL_ZM_Z();
    Integer zero_inverted = zero.MUL_ZM_Z();
    
    assert(pos_to_neg.POZ_Z_D() == -1);
    assert(neg_to_pos.POZ_Z_D() == 1);
    assert(zero_inverted.POZ_Z_D() == 0);
}

void test_TRANS_N_Z() {
    Natural nat("999");
    Integer integer_obj;
    Integer result = integer_obj.TRANS_N_Z(nat);
    
    assert(result.POZ_Z_D() == 1);
    assert(result.ABS_Z_N().COM_NN_D(nat) == 0);
}

void test_TRANS_Z_N() {
    Integer positive("123");
    Integer zero;

    Natural pos_nat = positive.TRANS_Z_N();
    assert(pos_nat.COM_NN_D(Natural("123")) == 0);
    
    bool zero_exception_thrown = false;
    try {
        zero.TRANS_Z_N();
    } catch (const std::invalid_argument&) {
        zero_exception_thrown = true;
    }
    assert(zero_exception_thrown);

}

void test_ADD_ZZ_Z() {
    Integer a("100");
    Integer b("50");
    Integer result1 = a.ADD_ZZ_Z(b);
    assert(result1.POZ_Z_D() == 1);
    
    Integer c("-100");
    Integer d("-50");
    Integer result2 = c.ADD_ZZ_Z(d);
    assert(result2.POZ_Z_D() == -1);
    
    Integer e("100");
    Integer f("-50");
    Integer result3 = e.ADD_ZZ_Z(f);
    assert(result3.POZ_Z_D() == 1);
    
    Integer g("50");
    Integer h("-100");
    Integer result4 = g.ADD_ZZ_Z(h);
    assert(result4.POZ_Z_D() == -1);
    
    Integer zero;
    Integer result5 = a.ADD_ZZ_Z(zero);
    assert(result5.ABS_Z_N().COM_NN_D(a.ABS_Z_N()) == 0);
}

void test_SUB_ZZ_Z() {
    Integer a("100");
    Integer b("50");
    Integer result1 = a.SUB_ZZ_Z(b);
    assert(result1.POZ_Z_D() == 1);
    
    Integer c("-100");
    Integer d("-50");
    Integer result2 = c.SUB_ZZ_Z(d);
    assert(result2.POZ_Z_D() == -1);
}

void test_MUL_ZZ_Z() {
    Integer a("5");
    Integer b("3");
    Integer result1 = a.MUL_ZZ_Z(b);
    assert(result1.POZ_Z_D() == 1);
    
    Integer c("-4");
    Integer d("-2");
    Integer result2 = c.MUL_ZZ_Z(d);
    assert(result2.POZ_Z_D() == 1);
    
    Integer e("6");
    Integer f("-3");
    Integer result3 = e.MUL_ZZ_Z(f);
    assert(result3.POZ_Z_D() == -1);
    
    Integer g("-7");
    Integer h("2");
    Integer result4 = g.MUL_ZZ_Z(h);
    assert(result4.POZ_Z_D() == -1);
    
    Integer zero;
    Integer i("10");
    Integer result5 = i.MUL_ZZ_Z(zero);
    assert(result5.POZ_Z_D() == 0);
    
    Integer result6 = zero.MUL_ZZ_Z(i);
    assert(result6.POZ_Z_D() == 0);
}



void test_DIV_ZZ_Z() {
    Integer a("10");
    Integer b("2");
    Integer result1 = a.DIV_ZZ_Z(b);
    assert(result1.POZ_Z_D() == 1);
    
    Integer c("-8");
    Integer d("-4");
    Integer result2 = c.DIV_ZZ_Z(d);
    assert(result2.POZ_Z_D() == 1);
    
    Integer e("15");
    Integer f("-3");
    Integer result3 = e.DIV_ZZ_Z(f);
    assert(result3.POZ_Z_D() == -1);
    
    Integer g("-12");
    Integer h("4");
    Integer result4 = g.DIV_ZZ_Z(h);
    assert(result4.POZ_Z_D() == -1);
    
    Integer i("3");
    Integer j("5");
    Integer result5 = i.DIV_ZZ_Z(j);
    assert(result5.POZ_Z_D() == 0);
    
    Integer k("-2");
    Integer l("5");
    Integer result6 = k.DIV_ZZ_Z(l);
    assert(result6.POZ_Z_D() == -1);
    
    Integer m("10");
    Integer zero;
    bool exception_thrown = false;
    try {
        m.DIV_ZZ_Z(zero);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    
    Integer result7 = zero.DIV_ZZ_Z(m);
    assert(result7.POZ_Z_D() == 0);
}

void test_MOD_ZZ_Z() {
    Integer a("10");
    Integer b("2");
    Integer result1 = a.MOD_ZZ_Z(b);
    assert(result1.POZ_Z_D() == 0);
    
    Integer c("10");
    Integer d("3");
    Integer result2 = c.MOD_ZZ_Z(d);
    assert(result2.POZ_Z_D() == 1);
    
    Integer e("-10");
    Integer f("3");
    Integer result3 = e.MOD_ZZ_Z(f);
    
    Integer g("10");
    Integer zero;
    bool exception_thrown = false;
    try {
        g.MOD_ZZ_Z(zero);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    
    Integer result4 = zero.MOD_ZZ_Z(g);
    assert(result4.POZ_Z_D() == 0);
}

void test_integrated_operations() {
    Integer a("15");
    Integer b("3");
    Integer product = a.MUL_ZZ_Z(b);
    Integer quotient = product.DIV_ZZ_Z(b);
    assert(quotient.ABS_Z_N().COM_NN_D(a.ABS_Z_N()) == 0);
    assert(quotient.POZ_Z_D() == a.POZ_Z_D());
    
    Integer c("17");
    Integer d("5");
    Integer div_result = c.DIV_ZZ_Z(d);
    Integer mod_result = c.MOD_ZZ_Z(d);
    Integer reconstructed = div_result.MUL_ZZ_Z(d).ADD_ZZ_Z(mod_result);
    assert(reconstructed.ABS_Z_N().COM_NN_D(c.ABS_Z_N()) == 0);
    assert(reconstructed.POZ_Z_D() == c.POZ_Z_D());
}

int main() {
    test_constructor_default();
    test_constructor_from_natural();
    test_constructor_with_sign();
    test_constructor_from_string();
    test_ABS_Z_N();
    test_POZ_Z_D();
    test_MUL_ZM_Z();
    test_TRANS_N_Z();
    test_TRANS_Z_N();
    test_ADD_ZZ_Z();
    test_SUB_ZZ_Z();
    test_MUL_ZZ_Z();
    test_DIV_ZZ_Z();
    test_MOD_ZZ_Z();
    test_integrated_operations();
    
    return 0;
}
