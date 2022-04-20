#include <algorithm>
#include <iostream>
#include "LLGrammar.h"


void LLGrammar::build_first() {
    for (char n: this->N) {
        LLGrammar::first[n] = std::unordered_set<char>();
        if (std::find(LLGrammar::P.at(n).begin(), LLGrammar::P.at(n).end(), "e") != LLGrammar::P.at(n).end()) {
            LLGrammar::first[n].insert('e');
        }
        std::cout << "start" << std::endl;

    }

    for (char t: LLGrammar::T) {
        LLGrammar::first[t] = {t};
    }

    LLGrammar::first['e'] = {'e'};

    bool Checker = true;

    int set_size;

    while (Checker) {

        Checker = false;

        for (auto rule: LLGrammar::P) {
            for (auto result: rule.second) {
                for (auto symbol: result) {

                    for (auto val: LLGrammar::first[symbol]) {

                        set_size = LLGrammar::first[rule.first].size();

                        LLGrammar::first[rule.first].insert(val);

                        if (set_size < LLGrammar::first[rule.first].size()) {
                            Checker = true;
                        }
                    }

                    if (std::find(LLGrammar::first[symbol].begin(), LLGrammar::first[symbol].end(), 'e') ==
                        LLGrammar::first[symbol].end()) {

                        break;

                    }
                }
            }
        }


        //iteration output
        for (auto it: LLGrammar::first) {
            std::cout << it.first << " : ";
            if (std::empty(it.second)) {
                std::cout << "empty";
            }
            for (auto item: it.second) {
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

    for (char n: LLGrammar::N) {
        LLGrammar::follow[n] = std::unordered_set<char>();
    }

    LLGrammar::follow[LLGrammar::S].insert('$');

    for (auto term: LLGrammar::P) {

        for (auto rule: term.second) {

            LLGrammar::rule_category(rule);

        }

    }

    //checking output----------------------------------------
    for (auto it: LLGrammar::follow) {
        std::cout << it.first << " : ";
        if (std::empty(it.second)) {
            std::cout << "empty";
        }
        for (auto item: it.second) {
            std::cout << item << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << '\n' << "iteration" << '\n';

    //-------------------------------------

    bool checker = true;

    while (checker) {

        checker = false;

        for (auto term: LLGrammar::P) {

            for (auto rule: term.second) {

                if (LLGrammar::follow_update(term.first, rule)) {

                    checker = true;

                }

            }

        }

        //------------------------------------
        for (auto it: LLGrammar::follow) {
            std::cout << it.first << " : ";
            if (std::empty(it.second)) {
                std::cout << "empty";
            }
            for (auto item: it.second) {
                std::cout << item << ' ';
            }
            std::cout << std::endl;
        }

        std::cout << '\n' << "iteration" << '\n';

        //-------------------------------------

    }

    LLGrammar::follow_exists = true;

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

    for (char i: part) {

        for (char elem: LLGrammar::first[i]) {

            if (elem != 'e' && mode == 0) {

                if (std::find(LLGrammar::follow[B].begin(), LLGrammar::follow[B].end(), elem) ==
                    LLGrammar::follow[B].end()) {

                    LLGrammar::follow[B].insert(elem);

                    added = true;

                }

            } else if (mode == 0 && elem == 'e') {

                checker = true;

            } else if (mode == 1 && elem == 'e') {

                for (auto item: LLGrammar::follow[A]) {

                    if (std::find(LLGrammar::follow[B].begin(), LLGrammar::follow[B].end(), item) ==
                        LLGrammar::follow[B].end()) {

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


bool LLGrammar::follow_update(char A, std::string rule) {

    int rule_length = rule.size();

    bool added = false;

    for (int i = 0; i < rule_length; i++) {

        if (LLGrammar::check_elem(LLGrammar::N, rule[i])) {

            if (i < rule_length - 1) {

                if (string_first(rule[i], rule.substr(i + 1, rule_length - i), 1, A)) {

                    added = true;

                }

            } else {

                for (auto item: LLGrammar::follow[A]) {

                    if (std::find(LLGrammar::follow[rule[i]].begin(), LLGrammar::follow[rule[i]].end(), item) ==
                        LLGrammar::follow[rule[i]].end()) {

                        LLGrammar::follow[rule[i]].insert(item);

                        added = true;

                    }

                }

            }

        }

    }

    return added;

}

bool LLGrammar::build_analyzer() {

    if (!LLGrammar::follow_exists) {

        LLGrammar::build_follow();

    }

    for (auto noterm: LLGrammar::N) {

        for (auto term: LLGrammar::T) {

            LLGrammar::LLanalyzer[noterm][term].first = 0;

        }

        LLGrammar::LLanalyzer[noterm]['$'].first = 0;

    }

    int counter = 1;

    int rule_number = 0;

    for ( auto rule : LLGrammar::P ) {

        for ( auto result : rule.second ) {

            std::cout << '\n' << counter << '\n';

            for ( auto lit : result ) {

                for ( auto item : LLGrammar::first[lit]) {

                    if (item != 'e') {

                        std::cout << "from first : " << rule.first << ' ' << item << ' ' << LLGrammar::LLanalyzer[rule.first][item].first << '\n';

                        if (LLGrammar::LLanalyzer[rule.first][item].first == 0) {
                            LLGrammar::LLanalyzer[rule.first][item].first = counter;
                            LLGrammar::LLanalyzer[rule.first][item].second = rule_number;
                        } else {
                            return false;
                        }

                    } else {

                        for ( auto elem : LLGrammar::follow[rule.first]) {

                            std::cout << "from follow : "<< rule.first << ' ' << elem << ' ' << LLGrammar::LLanalyzer[rule.first][elem].first << '\n';


                            if (LLGrammar::LLanalyzer[rule.first][elem].first == 0) {
                                LLGrammar::LLanalyzer[rule.first][elem].first = counter;
                                LLGrammar::LLanalyzer[rule.first][elem].second = rule_number;
                            } else {
                                return false;
                            }

                        }

                    }

                }

                if (std::find(LLGrammar::first[lit].begin(), LLGrammar::first[lit].end(), 'e') == LLGrammar::first[lit].end()) {

                    break;

                }



            }

            counter++;

            rule_number++;

        }

        rule_number = 0;

    }

    int cnt = 1;

    for (auto item : LLGrammar::P) {

        for (auto rule : item.second) {

            std::cout << cnt << " : " << item.first << " -> " << rule << '\n';

            cnt++;

        }

    }

    for (auto n : LLGrammar::LLanalyzer) {

        std::cout << "  ";

        for (auto t : n.second) {

            std::cout << t.first << ' ';

        }

        std::cout << std::endl;

        break;

    }

    for (auto n : LLGrammar::LLanalyzer) {

        std::cout << n.first;

        for (auto t : n.second) {

            std::cout << ' ' << t.second.first;

        }

        std::cout << '\n';

    }

    LLGrammar::analyzer_exists = true;

    return true;

}

std::vector < std::pair <char, int> > LLGrammar::derivation(std::string input) {

    if (!LLGrammar::analyzer_exists){
        LLGrammar::build_analyzer();
    }

    input += '$';

    std::stack < char > cur_stack;

    cur_stack.push('$'); cur_stack.push(LLGrammar::S);

    std::vector < std::pair <char, int> > result;

    char first_elem;

    std::string::iterator ptr = input.begin();

    while (ptr != input.end()) {

        first_elem = cur_stack.top();

        /*std::cout << *ptr << '\n';

        std::cout << first_elem << '\n';

        for (auto item : result) {
            std::cout << item.first << item.second << ' ';
        }

        std::cout << std::endl;*/

        if (first_elem == '$' && *ptr != '$') {
            std::cout << first_elem << ' ' << *ptr << "this is not regular expression" << '\n';
            return std::vector < std::pair <char, int> > (0);
        }

        if (*ptr == 'e') {
            ptr++;
            continue;
        }

        std::pair <int, int> needed_rule;

        try {

            needed_rule = LLGrammar::LLanalyzer[first_elem].at(*ptr);


            if (needed_rule.first == 0) {
                std::cout << "this is not regular expression, no rule" << '\n';
                return std::vector < std::pair <char, int> > (0);
            }

            result.push_back(std::make_pair(first_elem, needed_rule.second));

            cur_stack.pop();

            for ( auto it = LLGrammar::P.at(first_elem)[needed_rule.second].end() - 1; it != LLGrammar::P.at(first_elem)[needed_rule.second].begin() - 1; it--) {
                cur_stack.push(*it);
            }

            //I'll change this later. Rules shouldn't have ~
            while (ptr != input.end()) {

                if (cur_stack.top() == *ptr) {
                    ptr++;
                    cur_stack.pop();
                } else if (cur_stack.top() == 'e') {
                    cur_stack.pop();
                } else {
                    break;
                }

            }


        } catch(std::out_of_range){
            std::cout << "this is not regular expression, fail" << '\n';
            return(std::vector < std::pair <char, int> > (0));
        }

    }

    std::cout << '\n' << "deduction : ";

    for (auto item : result) {
        std::cout << item.first << item.second << ' ';
    }

    std::cout << '\n';

    return result;

}



