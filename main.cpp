#include <iostream>
#include <string>
#include "Grammar/Grammar.h"
#include "RegularGrammar/RegularGrammar.h"
#include "RegularExpression/RegularExpression.h"
#include "LLGrammar/LLGrammar.h"

int main() {

    RegularGrammar regularGrammar;

    RegularExpression expression;

    std::cin >> expression;

    //fix e* and e on first place(no finish conditions)
    //multiple * problem

    //try answer about ~~*, probably followpos ||| fixed
    //fix authomats with e

    regularGrammar.build_tree( expression.get_expression() );

    return 0;

}
