#include "RegularGrammar.h"
#include <map>
#include <iostream>


RegularGrammar::RegularGrammar() {

    RegularGrammar::P = {{'S', std::vector <std::string> {"~Q", "(~V)V", "e"}},
                         {'Q', std::vector <std::string> {"V", "|S"}},
                         {'V', std::vector <std::string> {"*S", "S", "|S"}}};

}


std::pair<char, std::string> RegularGrammar::get_rule(int a, int b) {
    return std::make_pair(RegularGrammar::N[a - 1], RegularGrammar::P[RegularGrammar::N[a - 1]][b - 1]);
}

