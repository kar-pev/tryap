#include <iostream>
#include <string>
#include "Grammar/Grammar.h"
#include "RegularGrammar/RegularGrammar.h"
#include "RegularExpression/RegularExpression.h"
#include "LLGrammar/LLGrammar.h"

int main() {

    RegularGrammar regularGrammar;

    RegularExpression expression;

    /*std::cin >> expression;*/

    //e|~ is not re, need to be fixed
    expression.set_expression("(~)*(~|~~*)");

    regularGrammar.build_tree( expression.get_expression() );

    return 0;

}
