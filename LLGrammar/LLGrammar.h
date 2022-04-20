#ifndef TRYAP_LLGRAMMAR_H
#define TRYAP_LLGRAMMAR_H

#include "../ContextFreeGrammar/ContextFreeGrammar.h"

#include <unordered_map>
#include <unordered_set>
#include <stack>


class LLGrammar : public ContextFreeGrammar{

    public:

        void build_first();

        void build_follow();

        bool build_analyzer();

        std::vector < std::pair <char, int> > derivation( std::string input );

        bool rule_category(std::string rule);

        bool string_first(char B, std::string part, int mode, char A);

        bool follow_update(char A, std::string rule);

    private:

        std::unordered_map < char, std::unordered_set<char> > first;

        std::unordered_map < char, std::unordered_set<char> > follow;

        std::unordered_map < char, std::unordered_map<char, std::pair <int, int> > > LLanalyzer;

        bool first_exists = false;

        bool follow_exists = false;

        bool analyzer_exists = false;

};


#endif //TRYAP_LLGRAMMAR_H