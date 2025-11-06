#include "Natural.h"
#include <iostream>
#include <cassert>

void testCOM_NN_D() {
    std::cout << "Testing COM_NN_D..." << std::endl;
    
    Natural n1("123");
    Natural n2("45");
    Natural n3("123");
    Natural n4("1234");
    Natural zero("0");
    
    assert(n1.COM_NN_D(n2) == 1);  // 123 > 45
    assert(n2.COM_NN_D(n1) == -1);  // 45 < 123
    assert(n1.COM_NN_D(n3) == 0);  // 123 == 123
    assert(n4.COM_NN_D(n1) == 1);  // 1234 > 123
    assert(zero.COM_NN_D(zero) == 0); // 0 == 0
    
    std::cout << "COM_NN_D tests passed!" << std::endl;
}

void testNZER_N_B() {
    std::cout << "Testing NZER_N_B..." << std::endl;
    
    Natural zero("0");
    Natural one("1");
    Natural large("12345");
    
    assert(zero.NZER_N_B() == false);  
    assert(one.NZER_N_B() == true);     
    assert(large.NZER_N_B() == true);  
    
    std::cout << "NZER_N_B tests passed!" << std::endl;
}

void testADD_1N_N() {
    std::cout << "Testing ADD_1N_N..." << std::endl;
    
    Natural zero("0");
    Natural nine("9");
    Natural ten("10");
    Natural n99("99");
    Natural n129("129");
    
    assert(zero.ADD_1N_N().toString() == "1");        // 0 + 1 = 1
    assert(nine.ADD_1N_N().toString() == "10");       // 9 + 1 = 10
    assert(ten.ADD_1N_N().toString() == "11");        // 10 + 1 = 11
    assert(n99.ADD_1N_N().toString() == "100");       // 99 + 1 = 100
    assert(n129.ADD_1N_N().toString() == "130");      // 129 + 1 = 130
    
    std::cout << "ADD_1N_N tests passed!" << std::endl;
}

void testADD_NN_N() {
    std::cout << "Testing ADD_NN_N..." << std::endl;
    
    Natural n1("123");
    Natural n2("45");
    Natural n3("999");
    Natural n4("1");
    Natural zero("0");
    
    assert(n1.ADD_NN_N(n2).toString() == "168");      // 123 + 45 = 168
    assert(n2.ADD_NN_N(n1).toString() == "168");      // 45 + 123 = 168
    assert(n3.ADD_NN_N(n4).toString() == "1000");     // 999 + 1 = 1000
    assert(zero.ADD_NN_N(n1).toString() == "123");    // 0 + 123 = 123
    assert(n1.ADD_NN_N(zero).toString() == "123");    // 123 + 0 = 123
    
    std::cout << "ADD_NN_N tests passed!" << std::endl;
}

void testSUB_NN_N() {
    std::cout << "Testing SUB_NN_N..." << std::endl;
    
    Natural n1("123");
    Natural n2("45");
    Natural n3("100");
    Natural n4("1");
    Natural n5("50");
    
    assert(n1.SUB_NN_N(n2).toString() == "78");       // 123 - 45 = 78
    assert(n3.SUB_NN_N(n4).toString() == "99");       // 100 - 1 = 99
    assert(n5.SUB_NN_N(n5).toString() == "0");        // 50 - 50 = 0
    
    try {
        n2.SUB_NN_N(n1);   
        assert(false);  
    } catch (const std::exception&) {
        
    }
    
    std::cout << "SUB_NN_N tests passed!" << std::endl;
}

void testMUL_ND_N() {
    std::cout << "Testing MUL_ND_N..." << std::endl;
    
    Natural n1("123");
    Natural n2("9");
    Natural zero("0");
    
    assert(n1.MUL_ND_N(4).toString() == "492");       // 123 × 4 = 492
    assert(n2.MUL_ND_N(9).toString() == "81");        // 9 × 9 = 81
    assert(n1.MUL_ND_N(0).toString() == "0");         // 123 × 0 = 0
    assert(zero.MUL_ND_N(5).toString() == "0");       // 0 × 5 = 0
    
    try {
        n1.MUL_ND_N(10);  
        assert(false);
    } catch (const std::exception&) {
        
    }
    
    std::cout << "MUL_ND_N tests passed!" << std::endl;
}

void testMUL_Nk_N() {
    std::cout << "Testing MUL_Nk_N..." << std::endl;
    
    Natural n1("123");
    Natural n2("7");
    Natural zero("0");
    
    assert(n1.MUL_Nk_N(2).toString() == "12300");     // 123 × 100 = 12300
    assert(n2.MUL_Nk_N(3).toString() == "7000");      // 7 × 1000 = 7000
    assert(n1.MUL_Nk_N(0).toString() == "123");       // 123 × 1 = 123
    assert(zero.MUL_Nk_N(5).toString() == "0");       // 0 × 100000 = 0
    
    std::cout << "MUL_Nk_N tests passed!" << std::endl;
}

void testMUL_NN_N() {
    std::cout << "Testing MUL_NN_N..." << std::endl;
    
    Natural n1("12");
    Natural n2("34");
    Natural n3("999");
    Natural n4("1");
    Natural zero("0");
    
    assert(n1.MUL_NN_N(n2).toString() == "408");      // 12 × 34 = 408
    assert(n3.MUL_NN_N(n4).toString() == "999");      // 999 × 1 = 999
    assert(zero.MUL_NN_N(n1).toString() == "0");      // 0 × 12 = 0
    assert(n1.MUL_NN_N(zero).toString() == "0");      // 12 × 0 = 0
    
    std::cout << "MUL_NN_N tests passed!" << std::endl;
}

void testSUB_NDN_N() {
    std::cout << "Testing SUB_NDN_N..." << std::endl;
    
    Natural n1("100");
    Natural n2("25");
    Natural n3("50");
    
    assert(n1.SUB_NDN_N(n2, 3).toString() == "25");   // 100 - (25×3) = 25
    assert(n3.SUB_NDN_N(n2, 2).toString() == "0");    // 50 - (25×2) = 0
    
    try {
        n3.SUB_NDN_N(n2, 3);  
    } catch (const std::exception&) {
        
    }
    
    std::cout << "SUB_NDN_N tests passed!" << std::endl;
}

void testDIV_NN_Dk() {
    std::cout << "Testing DIV_NN_Dk..." << std::endl;
    
    Natural n1("1234");
    Natural n2("23");
    Natural n3("456");
    Natural n4("78");
    Natural n5("150");
    
    auto result1 = n1.DIV_NN_Dk(n2);
    std::cout << "1234 / 23: digit=" << result1.first << ", k=" << result1.second << std::endl;
    assert(result1.first == 5 && result1.second == 1); 
    
    auto result2 = n3.DIV_NN_Dk(n4);
    std::cout << "456 / 78: digit=" << result2.first << ", k=" << result2.second << std::endl;
    assert(result2.first == 5 && result2.second == 0);  
    
    auto result3 = n3.DIV_NN_Dk(n5);
    std::cout << "456 / 150: digit=" << result3.first << ", k=" << result3.second << std::endl;
    assert(result3.first == 3 && result3.second == 0); 
    
    std::cout << "DIV_NN_Dk tests passed!" << std::endl;
}

void testDIV_NN_N() {
    std::cout << "Testing DIV_NN_N..." << std::endl;
    
    Natural n1("1234");
    Natural n2("23");
    Natural n3("100");
    Natural n4("7");
    Natural n5("50");
    Natural zero("0");
    
    assert(n1.DIV_NN_N(n2).toString() == "53");       // 1234 ÷ 23 = 53
    assert(n3.DIV_NN_N(n4).toString() == "14");       // 100 ÷ 7 = 14
    assert(n5.DIV_NN_N(n5).toString() == "1");        // 50 ÷ 50 = 1
    assert(n2.DIV_NN_N(n1).toString() == "0");        // 23 ÷ 1234 = 0
    
    try {
        n1.DIV_NN_N(zero);   
        assert(false);
    } catch (const std::exception&) {
        
    }
    
    std::cout << "DIV_NN_N tests passed!" << std::endl;
}

void testMOD_NN_N() {
    std::cout << "Testing MOD_NN_N..." << std::endl;
    
    Natural n1("1234");
    Natural n2("23");
    Natural n3("100");
    Natural n4("7");
    Natural n5("50");
    
    assert(n1.MOD_NN_N(n2).toString() == "15");       // 1234 % 23 = 15
    assert(n3.MOD_NN_N(n4).toString() == "2");        // 100 % 7 = 2
    assert(n5.MOD_NN_N(n5).toString() == "0");        // 50 % 50 = 0
    assert(n2.MOD_NN_N(n1).toString() == "23");       // 23 % 1234 = 23
    
    std::cout << "MOD_NN_N tests passed!" << std::endl;
}

void testGCF_NN_N() {
    std::cout << "Testing GCF_NN_N..." << std::endl;
    
    Natural n1("48");
    Natural n2("18");
    Natural n3("17");
    Natural n4("13");
    Natural n5("42");
    Natural zero("0");
    
    assert(n1.GCF_NN_N(n2).toString() == "6");        // GCD(48,18) = 6
    assert(n3.GCF_NN_N(n4).toString() == "1");        // GCD(17,13) = 1
    assert(n5.GCF_NN_N(n5).toString() == "42");       // GCD(42,42) = 42
    assert(n1.GCF_NN_N(zero).toString() == "48");     // GCD(48,0) = 48
    
    std::cout << "GCF_NN_N tests passed!" << std::endl;
}

void testLCM_NN_N() {
    std::cout << "Testing LCM_NN_N..." << std::endl;
    
    Natural n1("12");
    Natural n2("18");
    Natural n3("7");
    Natural n4("5");
    Natural n5("8");
    Natural zero("0");
    
    assert(n1.LCM_NN_N(n2).toString() == "36");       // LCM(12,18) = 36
    assert(n3.LCM_NN_N(n4).toString() == "35");       // LCM(7,5) = 35
    assert(n5.LCM_NN_N(n5).toString() == "8");        // LCM(8,8) = 8
    assert(n1.LCM_NN_N(zero).toString() == "0");      // LCM(12,0) = 0
    
    std::cout << "LCM_NN_N tests passed!" << std::endl;
}

void runAllTests() {
    std::cout << "Starting all tests...\n" << std::endl;
    
    testCOM_NN_D();
    testNZER_N_B();
    testADD_1N_N();
    testADD_NN_N();
    testSUB_NN_N();
    testMUL_ND_N();
    testMUL_Nk_N();
    testMUL_NN_N();
    testSUB_NDN_N();
    testDIV_NN_Dk();
    testDIV_NN_N();
    testMOD_NN_N();
    testGCF_NN_N();
    testLCM_NN_N();
    
    std::cout << "\nAll tests passed successfully!" << std::endl;
}

int main() {
    try {
        runAllTests();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
