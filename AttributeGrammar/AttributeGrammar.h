#ifndef TRYAP_ATTRIBUTEGRAMMAR_H
#define TRYAP_ATTRIBUTEGRAMMAR_H

#include <map>
#include <string>
#include <set>
#include "../LLGrammar/LLGrammar.h"
#include "Tree.h"
#include "../Authomat/Authomat.h"

struct attrs { char action = '\0'; std::set <int> first_pos; std::set <int> last_pos; bool empty;};

struct vert { attrs attr; char val = '\0'; vert * left = nullptr; vert * right = nullptr; vert * parent = nullptr;};

struct connection { char sign; int from; int to;};

class AttributeGrammar : public LLGrammar{
    public:

        void build_tree( std::string expression );

        void build_followpos( vert * child );

        Authomat build_authomat( std::string expression );

    private:

        void dfs(std::vector < std::pair <char, int> > &der, int &i, vert * child, int & pos);

        vert * tree = nullptr;

        std::vector <std::pair <char, std::unordered_set <int> > > followpos;

        std::unordered_set <char> Sigma;

};


#endif //TRYAP_ATTRIBUTEGRAMMAR_H
