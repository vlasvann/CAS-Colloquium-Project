#include "natural.h"

Natural::Natural() {}

Natural::Natural(const std::string&) {}

Natural::Natural(const int&) {}

Natural::Natural(const std::vector<int>&) {
	m_digits.push_back(0);
}

int Natural::COM_NN_D(const Natural&) const {
    return 0; // временная заглушка
}

bool Natural::NZER_N_B() const {
    return false; // временная заглушка
}

Natural Natural::ADD_1N_N() const {
    return Natural(); // временная заглушка
}

Natural Natural::ADD_NN_N(const Natural&) const {
    return Natural(); // временная заглушка
}

Natural Natural::SUB_NN_N(const Natural&) const {
    return Natural(); // временная заглушка
}

Natural Natural::MUL_ND_N(int) const {
    return Natural(); // временная заглушка
}

Natural Natural::MUL_Nk_N(int) const {
    return Natural(); // временная заглушка
}

Natural Natural::MUL_NN_N(const Natural&) const {
    return Natural(); // временная заглушка
}

Natural Natural::SUB_NDN_N(const Natural&, int) const {
    return Natural(); // временная заглушка
}

std::pair<int, int> Natural::DIV_NN_Dk(const Natural&) const {
    return std::make_pair(0, 0); // временная заглушка
}

Natural Natural::DIV_NN_N(const Natural&) const {
    return Natural(); // временная заглушка
}

Natural Natural::MOD_NN_N(const Natural&) const {
    return Natural(); // временная заглушка
}

Natural Natural::GCF_NN_N(const Natural&) const {
    return Natural(); // временная заглушка
}

Natural Natural::LCM_NN_N(const Natural&) const {
    return Natural(); // временная заглушка
}
