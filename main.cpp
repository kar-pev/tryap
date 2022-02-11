#include <iostream>
#include <string>
#include "RegularExpression.h"
#include "RegularGrammar.h"

int main() {
    RegularExpression expression;
    RegularGrammar grammar;
    std::string input;
    std::cin >> input;

    expression.set_expression(input);

/*
    std::cout << expression.get_expression();
*/

    grammar.get_rule(1, 1);

    return 0;
}
