#include <iostream>
#include <string>
#include "Grammar/Grammar.h"
#include "RegularGrammar/RegularGrammar.h"
#include "RegularExpression/RegularExpression.h"
#include "LLGrammar/LLGrammar.h"

int main() {

/*    LLGrammar llGrammar;

    llGrammar.add_N('A');

    llGrammar.add_N('B');

    llGrammar.add_N('C');

    llGrammar.set_S('A');

    llGrammar.add_T('a');

    llGrammar.add_T('b');

    llGrammar.add_Rule('A', "aBb");

    llGrammar.add_Rule('A', "e");

    llGrammar.add_Rule('A', "CB");

    llGrammar.add_Rule('C', "e");

    llGrammar.add_Rule('B', "A");*/

    RegularGrammar regularGrammar;

    bool check;

    check = regularGrammar.build_analyzer();

    if (!check) std::cout << "error";

    regularGrammar.build_tree("~|~");

    return 0;
}
