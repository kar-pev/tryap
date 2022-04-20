#ifndef TRYAP_AUTHOMAT_H
#define TRYAP_AUTHOMAT_H

#include <vector>
#include <unordered_map>


class Authomat {

    public:

        //conditions
        std::vector <int> Q;
        //alphabet
        std::vector <char> Sigma;
        //first condition
        int q;
        //transitions
        std::unordered_map <char, std::pair<int, int> > Delta;
        //final conditions
        std::vector <int> F;

};


#endif //TRYAP_AUTHOMAT_H
