#ifndef TRYAP_AUTHOMAT_H
#define TRYAP_AUTHOMAT_H

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include "../TinyXml/tinyxml2.h"


class Authomat {

    public:

        void print_authomat(std::string type);
        void add_Q(int condition);
        void add_Sigma(char sign);
        void set_Sigma(std::unordered_set <char> & alphabet);
        void set_q(int condition);
        void add_Delta(char sign, int from, int to);
        void add_F(int condition);

    private:
        //conditions
        std::vector <int> Q = {};
        //alphabet
        std::unordered_set <char> Sigma;
        //first condition
        int q;
        //transitions
        std::vector < std::tuple <char, int, int> > Delta;
        //final conditions
        std::vector <int> F;

};


#endif //TRYAP_AUTHOMAT_H
