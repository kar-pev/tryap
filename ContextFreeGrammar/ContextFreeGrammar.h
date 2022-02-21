#ifndef TRYAP_CONTEXTFREEGRAMMAR_H
#define TRYAP_CONTEXTFREEGRAMMAR_H

#include "../Grammar/Grammar.h"


class ContextFreeGrammar : protected Grammar {

    bool add_Rule(char n, std::string);

    protected:
        //Rules
        std::map <char, std::vector <std::string> >P;
};


#endif //TRYAP_CONTEXTFREEGRAMMAR_H
