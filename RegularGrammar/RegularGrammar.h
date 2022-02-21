#ifndef TRYAP_REGULARGRAMMAR_H
#define TRYAP_REGULARGRAMMAR_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include "../ContextFreeGrammar/ContextFreeGrammar.h"


class RegularGrammar : protected ContextFreeGrammar{
    public:

        RegularGrammar();

        std::pair <char, std::string> get_rule(int a, int b);

};


#endif //TRYAP_REGULARGRAMMAR_H
