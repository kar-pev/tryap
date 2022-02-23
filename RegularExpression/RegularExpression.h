#ifndef TRYAP_REGULAREXPRESSION_H
#define TRYAP_REGULAREXPRESSION_H


#include <string>

class RegularExpression {
    public:

        friend std::istream& operator >> (std::istream &in, RegularExpression &regularExpression);

        void set_expression(std::string);

        std::string get_expression();

    private:
        // Expression
        std::string value;
};


#endif //TRYAP_REGULAREXPRESSION_H
