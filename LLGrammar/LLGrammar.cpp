#include <algorithm>
#include <iostream>
#include "LLGrammar.h"

LLGrammar::LLGrammar() = default;

std::unordered_map < char, std::unordered_set<char> > LLGrammar::build_first() {
    std::cout << "start" << std::endl;
    for (char n : LLGrammar::N) {
        LLGrammar::first[n] = std::unordered_set <char> ();
        if (std::find(LLGrammar::P[n].begin(), LLGrammar::P[n].end(), "e") != LLGrammar::P[n].end()) {
            LLGrammar::first[n].insert('e');
        }
    }

    for (char t : LLGrammar::T) {
        LLGrammar::first[t] = {t};
    }

    bool Checker = true;

    int set_size;

    while (Checker) {

        Checker = false;

        for (auto rule : LLGrammar::P) {
            for (auto result : rule.second) {
                for (auto symbol : result) {

                    for (auto val : LLGrammar::first[symbol]) {

                        set_size = LLGrammar::first[rule.first].size();

                        LLGrammar::first[rule.first].insert(val);

                        if (set_size < LLGrammar::first[rule.first].size()) {
                            Checker = true;
                        }
                    }

                    if (std::find(LLGrammar::first[symbol].begin(), LLGrammar::first[symbol].end(), 'e') == LLGrammar::first[symbol].end()) {

                        break;

                    }
                }
            }
        }


        //iteration output
        for (auto it : LLGrammar::first) {
            std::cout << it.first << " : ";
            if (std::empty(it.second)) {
                std::cout << "empty";
            }
            for (auto item : it.second) {
                std::cout << item << ' ';
            }
            std::cout << std::endl;
        }

        std::cout << '\n' << "iteration" << '\n';

        //-----------------------

    }

}
