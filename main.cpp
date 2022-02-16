#include <iostream>
#include <string>
#include "Grammar/Grammar.h"

int main() {
    std::string input;
    std::cin >> input;

    bool check;
    Grammar grammar;

    grammar.add_T('a');
    grammar.add_T('b');
    grammar.add_N('S');



    check = grammar.add_Rule("S", "abS");

    if (check) {
        std::cout << "Rule added successfully" << std::endl;
    } else {
        std::cout << "Task failed" << std::endl;
    }

    return 0;
}
