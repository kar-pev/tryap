#include <iostream>
#include <string>
#include "Grammar/Grammar.h"
#include "RegularGrammar/RegularGrammar.h"
#include "RegularExpression/RegularExpression.h"
#include "LLGrammar/LLGrammar.h"

int main() {

    LLGrammar llGrammar;

    llGrammar.add_N('A');

    llGrammar.add_N('B');

    llGrammar.add_T('a');

    llGrammar.add_T('b');

    llGrammar.add_Rule('A', "a");

    llGrammar.add_Rule('A', "e");

    llGrammar.build_first();

    return 0;
}
