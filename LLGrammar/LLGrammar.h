#ifndef TRYAP_LLGRAMMAR_H
#define TRYAP_LLGRAMMAR_H

#include "../ContextFreeGrammar/ContextFreeGrammar.h"

#include <unordered_map>
#include <unordered_set>


class LLGrammar : public ContextFreeGrammar{

    public:

        LLGrammar();

        std::unordered_map < char /*literal*/, std::unordered_set<char> /*first for literal*/ > build_first();

    private:

        std::unordered_map < char, std::unordered_set<char> > first;

        std::unordered_map < char, std::unordered_set<char> > follow;

        std::unordered_map < char, std::unordered_set<char> > LLanalisator;

};


#endif //TRYAP_LLGRAMMAR_H