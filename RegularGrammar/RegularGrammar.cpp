#include "RegularGrammar.h"
#include <map>
#include <iostream>


RegularGrammar::RegularGrammar() {

    RegularGrammar::N = {'S', 'Q'};

    RegularGrammar::T = {'~', '*', '|', '(', ')'};

    RegularGrammar::S = 'S';

    RegularGrammar::P = {{'S', std::vector <std::string> {"~Q", "(~Q)Q", "e"}},
                         {'Q', std::vector <std::string> {"*S", "S", "|S"}}};


}


std::pair<char, std::string> RegularGrammar::get_rule(int a, int b) {
    return std::make_pair(RegularGrammar::N[a - 1], RegularGrammar::P[RegularGrammar::N[a - 1]][b - 1]);
}

