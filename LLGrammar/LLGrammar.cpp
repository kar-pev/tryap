#include <algorithm>
#include <iostream>
#include "LLGrammar.h"

LLGrammar::LLGrammar() = default;

void LLGrammar::build_first() {
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

    LLGrammar::first_exists = true;

}

void LLGrammar::build_follow() {

    if (!LLGrammar::first_exists) {

        LLGrammar::build_first();

    }

    for (char n : LLGrammar::N) {
        LLGrammar::follow[n] = std::unordered_set <char> ();
    }

    LLGrammar::follow[LLGrammar::S].insert('$');

    for (auto term : LLGrammar::P) {

        for (auto rule : term.second) {

            LLGrammar::rule_category(rule);

        }

    }

    //checking output----------------------------------------
    for (auto it : LLGrammar::follow) {
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

    //-------------------------------------

    bool checker  = true;

    while (checker) {

        checker = false;

        for (auto term : LLGrammar::P) {

            for (auto rule : term.second) {

                if(LLGrammar::follow_update(term.first, rule)) {

                    checker = true;

                }

            }

        }

        //------------------------------------
        for (auto it : LLGrammar::follow) {
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

        //-------------------------------------

    }

}


bool LLGrammar::rule_category(std::string rule) {

    int rule_length = rule.size();

    bool added = false;

    for (int i = 0; i < rule_length; i++) {

        if (LLGrammar::check_elem(LLGrammar::N, rule[i])) {

            if (i < rule_length - 1) {

                if (string_first(rule[i], rule.substr(i + 1, rule_length - i), 0, 'A')) {

                    added = true;

                }

            }

        }

    }

    return added;

}


bool LLGrammar::string_first(char B, std::string part, int mode, char A) {

    bool checker = false;

    bool added = false;

    for ( char i : part ) {

        for ( char elem : LLGrammar::first[i] ) {

            if (elem != 'e' && mode == 0) {

                if (std::find(LLGrammar::follow[B].begin(), LLGrammar::follow[B].end(), elem) == LLGrammar::follow[B].end()) {

                    LLGrammar::follow[B].insert(elem);

                    checker = true;

                    added = true;

                }

            } else if (mode == 0 && elem == 'e') {

                checker = true;

            } else if (mode == 1 && elem == 'e') {

                for ( auto item : LLGrammar::follow[A]) {

                    if (std::find(LLGrammar::follow[B].begin(), LLGrammar::follow[B].end(), item) == LLGrammar::follow[B].end()) {

                        LLGrammar::follow[B].insert(item);

                        checker = true;

                        added = true;

                    }

                }

            }

        }

        if (!checker) {

            break;

        }

        checker = false;

    }

    return added;

}


bool LLGrammar::follow_update( char A, std::string rule) {

    int rule_length = rule.size();

    bool added = false;

    for (int i = 0; i < rule_length; i++) {

        if (LLGrammar::check_elem(LLGrammar::N, rule[i])) {

            if (i < rule_length - 1) {

                if (string_first(rule[i], rule.substr(i + 1, rule_length - i), 1, A)) {

                    added = true;

                }

            } else {

                for ( auto item : LLGrammar::follow[A]) {

                    if (std::find(LLGrammar::follow[rule[i]].begin(), LLGrammar::follow[rule[i]].end(), item) == LLGrammar::follow[rule[i]].end()) {

                        LLGrammar::follow[rule[i]].insert(item);

                        added = true;

                    }

                }

            }

        }

    }

    return added;

}



