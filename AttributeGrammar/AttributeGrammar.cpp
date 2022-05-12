#include "AttributeGrammar.h"

#include <iostream>

#include <unordered_set>
#include <set>
#include <queue>

void set_attrs(char action, std::set <int> first_pos, std::set <int> last_pos, bool empty, vert * vertex) {
    vertex->attr.action = action;
    vertex->attr.first_pos = first_pos;
    vertex->attr.last_pos = last_pos;
    vertex->attr.empty = empty;
}


struct connection connection(char sign, int from, int to) {
    struct connection connect{};
    connect.sign = sign;
    connect.from = from;
    connect.to = to;
    return connect;
}


//build of deduction tree
void AttributeGrammar::dfs(std::vector < std::pair <char, int> > &der, int &rule_number, vert * child, int & pos) {

    if (AttributeGrammar::check_elem(AttributeGrammar::T, child->val)) {
        if (child->val == 'e' && child->parent->attr.action == '.') {
            if (child->parent->parent != nullptr) {
                if (child->parent->parent->left == child->parent) {
                    child->parent->parent->left = child->parent->left;
                    child->parent->left->parent = child->parent->parent;
                } else {
                    child->parent->parent->right = child->parent->left;
                    child->parent->left->parent = child->parent->parent;
                }
            } else {
                return;
            }
//            child->parent->attr.action = '\0';
            child->parent->attr.first_pos.insert(pos);
            child->parent->attr.last_pos.insert(pos);
            child->parent->attr.empty = false;
        } else {
            child->attr.first_pos.insert(pos);
            child->attr.last_pos.insert(pos);
            if (child->val == 'e') {
                child->attr.empty = true;
            } else {
                child->attr.empty = false;
            }
            AttributeGrammar::Sigma.insert(child->val);
            AttributeGrammar::followpos.emplace_back(child->val, std::unordered_set <int> ());
            pos++;
        }
        return;
    }

    std::string cur_rule = AttributeGrammar::P[der[rule_number].first][der[rule_number].second];

    rule_number++;
    if (cur_rule.size() == 5) {
        child->attr.action = '.';

        child->left = new vert();
        child->right = new vert();
        child->left->parent = child;
        child->right->parent = child;
        child->left->attr.action = '.';

        child->left->left = new vert();
        child->left->right = new vert();
        child->left->left->parent = child->left;
        child->left->right->parent = child->left;
        child->left->left->val = cur_rule[1];
        child->left->right->val = cur_rule[2];
        child->right->val = cur_rule[4];

        dfs(der, rule_number, child->left->left, pos);
        dfs(der, rule_number, child->left->right, pos);
        dfs(der, rule_number, child->right, pos);
    } else if (cur_rule.size() == 2) {
        child->left = new vert();
        child->right = new vert();
        child->left->parent = child;
        child->right->parent = child;

        child->left->val = cur_rule[0];
        child->right->val = cur_rule[1];

        if (cur_rule == "|S") {
            child->parent->attr.action = '|';
            child->parent->val = '\0';
            child->val = 'S';
            dfs(der, rule_number, child, pos);
        }

        //if for ~Q rule, where ~ equals to every letter
        if (cur_rule[1] == 'Q') {
            child->attr.action = '.';
            child->val = '\0';
            dfs(der, rule_number, child->left, pos);
            dfs(der, rule_number, child->right, pos);
        }

        if (cur_rule == "*S") {
            child->parent->left->parent = new vert();
            child->parent->left->parent->left = child->parent->left;
            child->parent->left->parent->right = nullptr;
            child->parent->left->parent->parent = child->parent;
            child->parent->left = child->parent->left->parent;
            child->parent->left->val = '\0';
            child->parent->left->attr.action = '*';
            child->val = 'S';
            child->attr.action = '.';
            dfs(der, rule_number, child, pos);
        }

    } else {
        if (child->parent != nullptr) {
            if (child->parent->left == child) {
                child->parent->left = new vert();
                child->parent->left->parent = child->parent;
                child->parent->left->val = cur_rule[0];
                dfs(der, rule_number, child->parent->left, pos);
            } else {
                child->parent->right = new vert();
                child->parent->right->parent = child->parent;
                child->parent->right->val = cur_rule[0];
                dfs(der, rule_number, child->parent->right, pos);
            }
        } else {
            child->left = new vert();
            child->left->val = cur_rule[0];
            child->left->parent = child;
            dfs(der, rule_number, child->left, pos);
        }
    }
}

void tree_print(vert * v){
    if (v->val != '\0'){
        std::cout << v->val << '\n';
    } else {
        std::cout << v->attr.action << '\n';
    }
    /*std::cout << "first_pos: ";
    for (auto it : v->attr.first_pos) {
        std::cout << it << ' ';
    }
    std::cout << "\nlast_pos: ";
    for (auto it : v->attr.last_pos) {
        std::cout << it << ' ';
    }
    std::cout << "\nempty: " << v->attr.empty << '\n';
    if (v->val == '~' || v->val == 'e') {
        return;
    }*/

    if (v->left) {
        tree_print(v->left);
    }
    if (v->right) {
        tree_print(v->right);
    }

}

//helpful main function for tree building
void AttributeGrammar::build_tree( std::string expression ) {

    std::vector < std::pair <char, int> > der = derivation(expression);

    AttributeGrammar::tree = new(vert);
    AttributeGrammar::tree->val = AttributeGrammar::S;
    AttributeGrammar::tree->parent = nullptr;
    set_attrs('.', {}, {}, false, AttributeGrammar::tree);

    int rule_number = 0, pos = 0;

    AttributeGrammar::dfs(der, rule_number, AttributeGrammar::tree, pos);

    AttributeGrammar::build_followpos(AttributeGrammar::tree);

    if (AttributeGrammar::tree->attr.empty) {
        AttributeGrammar::tree->attr.first_pos.insert(-1);
    }

    for (auto i : AttributeGrammar::tree->attr.last_pos) {
            followpos[i].second.insert(-1);
    }




    AttributeGrammar::followpos.emplace_back('#', std::unordered_set<int> ());

    tree_print(AttributeGrammar::tree);

    for (auto it : AttributeGrammar::followpos) {
        std::cout << it.first << ": ";
        for (auto j : it.second) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }


    AttributeGrammar::build_authomat(expression);

}

void AttributeGrammar::build_followpos( vert * child ) {

    if (child->left == nullptr && child->right == nullptr) {
        return;
    }
    if (child->left != nullptr) {
        AttributeGrammar::build_followpos( child->left );
    }
    if (child->right != nullptr) {
        AttributeGrammar::build_followpos( child->right );
    }

    if (child->attr.action == '.') {
        if (child->left->attr.empty && child->right->attr.empty) {
            child->attr.first_pos.insert(child->left->attr.first_pos.begin(), child->left->attr.first_pos.end());
            child->attr.first_pos.insert(child->right->attr.first_pos.begin(), child->right->attr.first_pos.end());
            child->attr.last_pos.insert(child->left->attr.last_pos.begin(), child->left->attr.last_pos.end());
            child->attr.last_pos.insert(child->right->attr.last_pos.begin(), child->right->attr.last_pos.end());
            child->attr.empty = true;
        }
        if (child->left->attr.empty && !child->right->attr.empty) {
            child->attr.first_pos.insert(child->left->attr.first_pos.begin(), child->left->attr.first_pos.end());
            child->attr.first_pos.insert(child->right->attr.first_pos.begin(), child->right->attr.first_pos.end());
            child->attr.last_pos.insert(child->right->attr.last_pos.begin(), child->right->attr.last_pos.end());
            child->attr.empty = false;
        }
        if (!child->left->attr.empty && child->right->attr.empty) {
            child->attr.first_pos.insert(child->left->attr.first_pos.begin(), child->left->attr.first_pos.end());
            child->attr.last_pos.insert(child->left->attr.last_pos.begin(), child->left->attr.last_pos.end());
            child->attr.last_pos.insert(child->right->attr.last_pos.begin(), child->right->attr.last_pos.end());
            child->attr.empty = false;
        }
        if (!child->left->attr.empty && !child->right->attr.empty) {
            child->attr.first_pos.insert(child->left->attr.first_pos.begin(), child->left->attr.first_pos.end());
            child->attr.last_pos.insert(child->right->attr.last_pos.begin(), child->right->attr.last_pos.end());
            child->attr.empty = false;
        }

        for (auto i : child->left->attr.last_pos) {
            for (auto j : child->right->attr.first_pos) {
                followpos[i].second.insert(j);
            }
        }
    }
    if (child->attr.action == '|') {
        child->attr.first_pos.insert(child->left->attr.first_pos.begin(), child->left->attr.first_pos.end());
        child->attr.first_pos.insert(child->right->attr.first_pos.begin(), child->right->attr.first_pos.end());
        child->attr.last_pos.insert(child->left->attr.last_pos.begin(), child->left->attr.last_pos.end());
        child->attr.last_pos.insert(child->right->attr.last_pos.begin(), child->right->attr.last_pos.end());
        child->attr.empty = child->left->attr.empty || child->right->attr.empty;
    }
    if (child->attr.action == '*') {
        child->attr.first_pos.insert(child->left->attr.first_pos.begin(), child->left->attr.first_pos.end());
        child->attr.last_pos.insert(child->left->attr.last_pos.begin(), child->left->attr.last_pos.end());
        child->attr.empty = true;

        for (auto i : child->left->attr.last_pos) {
            for (auto j : child->left->attr.first_pos) {
                followpos[i].second.insert(j);
            }
        }
    }
}

Authomat AttributeGrammar::build_authomat(std::string expression) {

    Authomat result_authomat;

    result_authomat.set_q(0);

    result_authomat.set_Sigma(AttributeGrammar::Sigma);

    //map of all conditions, that was already found
    std::map < std::set <int>, int > conditions;

    std::queue < std::pair < std::set <int>, struct connection > > to_do;

    //condition for start ones
    to_do.emplace(AttributeGrammar::tree->attr.first_pos, connection('e', -1, -1));

    std::cout << "done" << '\n';

    //map for conditions, that was found by algo for current_condition
    std::unordered_map <char, std::set <int> > new_conditions;

    int found, condition_number = 0;

    auto current_condition = to_do.front();

    //adding new conditions in conditions
    while (!to_do.empty()) {
        current_condition = to_do.front();
        to_do.pop();

        for (auto it : current_condition.first) {
            std::cout << it << ' ';
        }
        std::cout << '\n';

        try {
            //condition already exists
            found = conditions.at(current_condition.first);
            result_authomat.add_Delta(current_condition.second.sign, current_condition.second.from, found);
            continue;
        } catch (std::out_of_range) {
            //new condition
            conditions[current_condition.first] = condition_number;
            current_condition.second.to = condition_number;
            result_authomat.add_Q(condition_number);
            condition_number++;
            if (current_condition.second.from != -1) {
                result_authomat.add_Delta(current_condition.second.sign, current_condition.second.from, current_condition.second.to);
            }
            if (current_condition.first.find(-1) != current_condition.first.end()) {
                result_authomat.add_F(current_condition.second.to);
            }
        }

        //adding all possible conditions in new_conditions
        for (auto it : current_condition.first) {
            //trying to find if conditions with same transitional symbol exist
            if (it != -1) {
                if (new_conditions.find(AttributeGrammar::followpos[it].first) == new_conditions.end()) {
                    new_conditions[AttributeGrammar::followpos[it].first] = {};
                }

                for (auto symb: AttributeGrammar::followpos[it].second) {
                    new_conditions[AttributeGrammar::followpos[it].first].insert(symb);
                }
            }
        }

        for (auto it : new_conditions) {
            if (it.first != 'e') {
                to_do.push(std::make_pair(it.second, connection(it.first, current_condition.second.to, -1)));
            }
        }

        new_conditions.clear();

    }

    for (auto it : conditions) {
        std::cout << it.second << " : ";
        for (auto k : it.first) {
            std::cout << k << ' ';
        }
        std::cout << '\n';
    }

    result_authomat.print_authomat("");

    return result_authomat;
}



