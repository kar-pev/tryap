#ifndef TRYAP_LLGRAMMAR_H
#define TRYAP_LLGRAMMAR_H

#include "../ContextFreeGrammar/ContextFreeGrammar.h"

#include <unordered_map>
#include <unordered_set>


class LLGrammar : public ContextFreeGrammar{

    public:

        LLGrammar();

        void build_first();

        void build_follow();

        bool rule_category(std::string rule);

        bool string_first(char B, std::string part, int mode, char A);

        bool follow_update(char A, std::string rule);

    private:

        std::unordered_map < char, std::unordered_set<char> > first;

        std::unordered_map < char, std::unordered_set<char> > follow;

        std::unordered_map < char, std::unordered_set<char> > LLanalisator;

        bool first_exists = false;

};


#endif //TRYAP_LLGRAMMAR_H