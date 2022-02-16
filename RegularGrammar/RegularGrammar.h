#ifndef TRYAP_REGULARGRAMMAR_H
#define TRYAP_REGULARGRAMMAR_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include "../Grammar/Grammar.h"


class RegularGrammar : Grammar{
    public:

        RegularGrammar();

        std::pair <char, std::string> get_rule(int a, int b);

    private:

        //Rules
        std::map <char, std::vector <std::string> >P;

};


#endif //TRYAP_REGULARGRAMMAR_H
