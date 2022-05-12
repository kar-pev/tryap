#include "Authomat.h"

void Authomat::print_authomat(std::string type) {
    if (type == "xml") {
        tinyxml2::XMLDocument result;
        result.LoadFile("result.xml");


    } else {
        std::cout << "Q : ";
        for (auto it: this->Q) {
            std::cout << it << ' ';
        }
        std::cout << '\n' << "Sigma : ";
        for (auto it: this->Sigma) {
            std::cout << it << ' ';
        }
        std::cout << '\n' << "q : " << this->q << '\n';
        std::cout << "Delta :\n";
        for (auto it: this->Delta) {
            std::cout << std::get<1>(it) << " -> " << std::get<0>(it) << " -> " << std::get<2>(it) << '\n';
        }
        std::cout << "F : ";
        for (auto it: this->F) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
    }
}

void Authomat::add_Q(int condition) {
    Authomat::Q.push_back(condition);
}

void Authomat::add_Sigma(char sign) {
    Authomat::Sigma.insert(sign);
}

void Authomat::set_q(int condition) {
    Authomat::q = condition;
}

void Authomat::add_Delta(char sign, int from, int to) {
    Authomat::Delta.emplace_back(sign, from, to);
}

void Authomat::add_F(int condition) {
    Authomat::F.emplace_back(condition);
}

void Authomat::set_Sigma(std::unordered_set<char> &alphabet) {
    Authomat::Sigma = alphabet;
}
