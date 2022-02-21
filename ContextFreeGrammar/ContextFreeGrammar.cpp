#include "ContextFreeGrammar.h"

bool ContextFreeGrammar::add_Rule(char n, std::string rule) {
    std::string left_part = reinterpret_cast<const char *>(n);
    if (ContextFreeGrammar::new_Rule_Validation(left_part, rule)) {
        ContextFreeGrammar::P[n].push_back(rule);
    } else {
        return false;
    }

    return true;
}




