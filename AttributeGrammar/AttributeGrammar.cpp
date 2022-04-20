#include "AttributeGrammar.h"

#include <iostream>

#include <unordered_set>
#include <set>

void set_attrs(char action, std::unordered_set <int> first_pos, std::unordered_set <int> last_pos, bool empty, vert * vertex) {
    vertex->attr.action = action;
    vertex->attr.first_pos = first_pos;
    vertex->attr.last_pos = last_pos;
    vertex->attr.empty = empty;
}


//build of deduction tree
void AttributeGrammar::dfs(std::vector < std::pair <char, int> > &der, int &rule_number, vert * child, int & pos) {

    std::cout << der[rule_number].first << ' ' << der[rule_number].second << ' ' << child->val << '\n';

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
            child->attr.empty = false;
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

    build_followpos(AttributeGrammar::tree);

    for (auto i : AttributeGrammar::tree->left->attr.last_pos) {
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
        child->attr.empty = child->left->attr.empty && child->right->attr.empty;
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

    result_authomat.q = 0;

    AttributeGrammar::build_tree( expression );
    if (AttributeGrammar::tree->attr.empty) {
        AttributeGrammar::tree->attr.first_pos.insert(-1);
    }

    std::vector < std::unordered_set <int> > conditions;

    conditions.push_back(AttributeGrammar::tree->attr.first_pos);

    while (true) {



    }


        return Authomat();
}



