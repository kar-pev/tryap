#ifndef TRYAP_REGULARGRAMMAR_H
#define TRYAP_REGULARGRAMMAR_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include "../AttributeGrammar/AttributeGrammar.h"
#include "../Authomat/Authomat.h"



class RegularGrammar : public AttributeGrammar {
    public:

        RegularGrammar();

        std::pair <char, std::string> get_rule(int a, int b);


    private:



};


#endif //TRYAP_REGULARGRAMMAR_H
