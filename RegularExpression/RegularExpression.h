#ifndef TRYAP_REGULAREXPRESSION_H
#define TRYAP_REGULAREXPRESSION_H


#include <string>

class RegularExpression {
    public:
        void set_expression(std::string);
        std::string get_expression();
    private:
        // Expression
        std::string value;
};


#endif //TRYAP_REGULAREXPRESSION_H
