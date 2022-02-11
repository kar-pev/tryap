#ifndef TRYAP_REGULARGRAMMAR_H
#define TRYAP_REGULARGRAMMAR_H

#include <map>
#include <string>
#include <vector>
#include <utility>


class RegularGrammar {
    public:

        RegularGrammar();

        std::pair <char, std::string> get_rule(int a, int b);

    private:
        // Not terminals
        const std::vector <char> N {'S', 'Q', 'V'};

        // Terminals
        const std::vector <char> T {'a', 'b'};

        //Rules
        static std::map <char, std::vector <std::string> >P;

        //Start terminal
        const char S = 'S';
};


#endif //TRYAP_REGULARGRAMMAR_H
