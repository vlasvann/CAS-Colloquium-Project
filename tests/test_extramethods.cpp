#include <cassert>
#include <iostream>
#include <stdexcept>
#include "extraMethods.h"


void test_TRANS_BIN_ZN_Z()
{
	ExtraMethods methods;
	 
	std::cout << "Test TRANS_BIN_ZN_Z: ";

	assert(methods.TRANS_BIN_ZN_Z(Integer("8"), Natural("8")).toString() == "00001000");

	assert(methods.TRANS_BIN_ZN_Z(Integer("100"), Natural("8")).toString() == "01100100");

	assert(methods.TRANS_BIN_ZN_Z(Integer("0"), Natural("8")).toString() == "00000000");

	assert(methods.TRANS_BIN_ZN_Z(Integer("-0"), Natural("8")).toString() == "00000000");

	assert(methods.TRANS_BIN_ZN_Z(Integer("-8"), Natural("8")).toString() == "11111000");

	assert(methods.TRANS_BIN_ZN_Z(Integer("-289"), Natural("10")).toString() == "1011011111");

	try
	{
		methods.TRANS_BIN_ZN_Z(Integer("8"), Natural("4"));
		std::cout << "failed TRANS_BIN_ZN_Z(Integer('8'), Natural('4')";
		assert(false);
	}
	catch (std::invalid_argument& e)
	{
		assert(true);
	}

	std::cout << "PASSED.\n";
}


void test_TRANS_DECFAC_Z_Z()
{
	ExtraMethods methods;

	std::cout << "Test TRANS_DECFAC_Z_Z: ";

	assert(methods.TRANS_DECFAC_Z_Z(Integer("5")).toString() == "21");

	assert(methods.TRANS_DECFAC_Z_Z(Integer("0")).toString() == "0");

	assert(methods.TRANS_DECFAC_Z_Z(Integer("719")).toString() == "54321");

	assert(methods.TRANS_DECFAC_Z_Z(Integer("-719")).toString() == "-54321");

	assert(methods.TRANS_DECFAC_Z_Z(Integer("-0")).toString() == "0");

	assert(methods.TRANS_DECFAC_Z_Z(Integer("-7")).toString() == "-101");

	std::cout << "PASSED.\n";
}


void test_TRANS_FACDEC_Z_Z()
{
	ExtraMethods methods;

	std::cout << "Test TRANS_FACDEC_Z_Z: ";

	assert(methods.TRANS_FACDEC_Z_Z(Integer("21")).toString() == "5");

	assert(methods.TRANS_FACDEC_Z_Z(Integer("0")).toString() == "0");

	assert(methods.TRANS_FACDEC_Z_Z(Integer("54321")).toString() == "719");

	assert(methods.TRANS_FACDEC_Z_Z(Integer("-54321")).toString() == "-719");

	assert(methods.TRANS_FACDEC_Z_Z(Integer("-1021")).toString() == "-29");

	assert(methods.TRANS_FACDEC_Z_Z(Integer("-0")).toString() == "0");

	std::cout << "PASSED.\n";
}


void test_FINDOUT_LUCKYNUMBER_N_B()
{
	ExtraMethods methods;

	std::cout << "Test FINDOUT_LUCKYNUMBER_N_B: ";

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("19")) == true);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("7")) == true);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("13")) == true);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("100000")) == true);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("78999")) == true);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("314159")) == true);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("0")) == false);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("4")) == false);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("11")) == false);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("1234")) == false);

	assert(methods.FINDOUT_LUCKYNUMBER_N_B(Natural("11111")) == false);

	std::cout << "PASSED.\n";
}


void test_EXP_ZN_Z()
{
	ExtraMethods methods;

	std::cout << "Test EXP_ZN_Z: ";

	assert(methods.EXP_ZN_Z(Integer("2"), Natural("3")).toString() == "8");

	assert(methods.EXP_ZN_Z(Integer("12"), Natural("8")).toString() == "429981696");

	assert(methods.EXP_ZN_Z(Integer("47"), Natural("4")).toString() == "4879681");

	assert(methods.EXP_ZN_Z(Integer("1024"), Natural("5")).toString() == "1125899906842624");

	assert(methods.EXP_ZN_Z(Integer("999"), Natural("0")).toString() == "1");

	assert(methods.EXP_ZN_Z(Integer("-12"), Natural("5")).toString() == "-248832");

	assert(methods.EXP_ZN_Z(Integer("-47"), Natural("3")).toString() == "-103823");	

	assert(methods.EXP_ZN_Z(Integer("-1024"), Natural("6")).toString() == "1152921504606846976");

	assert(methods.EXP_ZN_Z(Integer("-256"), Natural("0")).toString() == "1");

	assert(methods.EXP_ZN_Z(Integer("-2"), Natural("32")).toString() == "4294967296");

	std::cout << "PASSED.\n";
}


void test_TRANS_PQ_STRNN_STR()
{
	ExtraMethods methods;

	std::cout << "Test TRANS_PQ_STRNN_STR: ";

	assert(methods.TRANS_PQ_STRNN_STR({ "22D5", 0 }, Natural("16"), Natural("10")) == "8917");
	
	assert(methods.TRANS_PQ_STRNN_STR({ "22D5", 1 }, Natural("16"), Natural("10")) == "-8917");

	assert(methods.TRANS_PQ_STRNN_STR({ "1011", 0 }, Natural("2"), Natural("16")) == "B");

	assert(methods.TRANS_PQ_STRNN_STR({ "123", 0 }, Natural("4"), Natural("16")) == "1B");

	assert(methods.TRANS_PQ_STRNN_STR({ "ZYZ", 0 }, Natural("36"), Natural("10")) == "46619");

	assert(methods.TRANS_PQ_STRNN_STR({ "FF", 0 }, Natural("16"), Natural("2")) == "11111111");

	assert(methods.TRANS_PQ_STRNN_STR({ "HELLO", 1 }, Natural("36"), Natural("10")) == "-29234652");

	assert(methods.TRANS_PQ_STRNN_STR({ "36", 1 }, Natural("10"), Natural("36")) == "-10");

	assert(methods.TRANS_PQ_STRNN_STR({ "35", 0 }, Natural("10"), Natural("36")) == "Z");

	assert(methods.TRANS_PQ_STRNN_STR({ "0", 0 }, Natural("3"), Natural("27")) == "0");

	assert(methods.TRANS_PQ_STRNN_STR({ "1000", 0 }, Natural("10"), Natural("36")) == "RS");

	assert(methods.TRANS_PQ_STRNN_STR({ "ETULETI", 0 }, Natural("36"), Natural("13")) == "3075807A59");

	std::cout << "PASSED.\n";
}


int main() 
{
	test_TRANS_BIN_ZN_Z();
	test_TRANS_DECFAC_Z_Z();
	test_TRANS_FACDEC_Z_Z();
	test_FINDOUT_LUCKYNUMBER_N_B();
	test_EXP_ZN_Z();
	test_TRANS_PQ_STRNN_STR();
	std::cout << "ALL TESTS PASSED SUCCESSFULLY.\n";
	return 0;
}