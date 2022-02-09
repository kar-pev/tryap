#include <iostream>
#include <string>
#include "RegularExpression.h"

int main() {
    RegularExpression expression;
    std::string input;
    std::cin >> input;

    expression.set_expression(input);

    std::cout << expression.get_expression();

    return 0;
}
