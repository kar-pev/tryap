#ifndef TRYAP_REGULARGRAMMAR_H
#define TRYAP_REGULARGRAMMAR_H

#include <map>
#include <string>
#include <vector>


class RegularGrammar {
    public:

    private:
        // Not terminals
        static std::vector <char> N;

        // Terminals
        static std::vector <char> T;

        //Rules
        std::map <std::string, std::string> P;

        //Start terminal
        static char S;
};


#endif //TRYAP_REGULARGRAMMAR_H
