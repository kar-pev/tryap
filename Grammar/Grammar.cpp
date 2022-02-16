#include <algorithm>
#include <iostream>
#include "Grammar.h"

Grammar::Grammar() {

}

void Grammar::set_S(char s) {
    Grammar::S = s;
}

void Grammar::add_N(char n) {
    Grammar::N.push_back(n);
}

void Grammar::add_T(char t) {
    Grammar::T.push_back(t);
}


bool Grammar::add_Rule(std::string n, std::string rule) {
    if (Grammar::new_Rule_Validation(n, rule)) {
        Grammar::P[n].push_back(rule);
    } else {
        return false;
    }

    return true;
}

bool Grammar::check_elem(std::vector<char> &array, char symbol) {
    for (char &i : array) {
        if (symbol == i) {
            return true;
        }
    }
    return false;
}


bool Grammar::new_Rule_Validation(std::string n, std::string rule) {
    for (char &i : n) {
        if (!check_elem(Grammar::N, i) && !check_elem(Grammar::T, i)) {
            return false;
        }
    }
    for (char &i : rule) {
        if (!check_elem(Grammar::N, i) && !check_elem(Grammar::T, i)) {
            return false;
        }
    }

    if (Grammar::P.find(n) != Grammar::P.end()) {
        if (std::find(Grammar::P[n].begin(), Grammar::P[n].end(), rule) == Grammar::P[n].end()) {
            return false;
        }
    }

    return true;
}

