#include "RegularExpression.h"


void RegularExpression::set_expression(std::string exp) {
    RegularExpression::value = exp;
}

std::string RegularExpression::get_expression() {
    return RegularExpression::value;
}

std::istream &operator>>(std::istream &in, RegularExpression &regularExpression) {
    in >> regularExpression.value;
    return in;
}

