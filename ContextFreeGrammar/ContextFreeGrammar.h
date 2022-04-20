#ifndef TRYAP_CONTEXTFREEGRAMMAR_H
#define TRYAP_CONTEXTFREEGRAMMAR_H

#include "../Grammar/Grammar.h"


class ContextFreeGrammar : public Grammar {

public:
    virtual bool add_Rule(char n, std::string rule);

protected:
    //Rules
    std::unordered_map <char, std::vector <std::string> > P;
};


#endif //TRYAP_CONTEXTFREEGRAMMAR_H
