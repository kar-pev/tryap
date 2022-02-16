#ifndef TRYAP_GRAMMAR_H
#define TRYAP_GRAMMAR_H
#include <vector>
#include <map>

class Grammar {

    public:

        Grammar();

        void set_S (char);

        void add_N (char);

        void add_T (char);

        bool add_Rule (std::string, std::string);

        //checking if elem in vector
        bool check_elem (std::vector <char> &array, char symbol);

        //validating new rule
        bool new_Rule_Validation (std::string n, std::string rule);

    protected:
        // Not terminals
        std::vector <char> N;

        // Terminals
        std::vector <char> T;

        //Rules
        std::map <std::string, std::vector <std::string> > P;

        //Start terminal
        char S;

};


#endif //TRYAP_GRAMMAR_H
