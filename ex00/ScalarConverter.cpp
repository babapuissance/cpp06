#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cmath>

static bool pseudo_lit(std::string s){
    return s=="nan"||s=="+inf"||s=="-inf"||s=="nanf"||s=="+inff"||s=="-inff";
}

static void printPseudo(std::string s){
    std::cout<<"char: impossible\nint: impossible\n";
    if (s == "nanf" || s == "+inff" || s == "-inff"){
        std::cout<<"float: "<<s<<"\ndouble: "<<s.substr(0,s.size()-1)<<"\n";
    } else {
        std::cout<<"float: "<<s<<"f\ndouble: "<<s<<"\n";
    }
}

static bool isChar(std::string s){
    return s.size()==1 && !isdigit(s[0]);
}

// & get a copy so we can't modify
//i code ascii / f float / d double
void ScalarConverter::convert(std::string const &s){
    if (pseudo_lit(s)) return printPseudo(s);

    char c; int i; float f; double d;

    if (isChar(s)){
        c = s[0]; i = c; f = c; d = c;
    }//float

    else if (s[s.size() - 1] == 'f'){
        f = std::strtof(s.c_str(), NULL);
        c = static_cast<char>(f);
        i = static_cast<int>(f);
        d = static_cast<double>(f);
    }
    //double
    else if (s.find('.') != std::string::npos){
        d = std::strtod(s.c_str(), NULL);
        c = static_cast<char>(d);
        i = static_cast<int>(d);
        f = static_cast<float>(d);
    }
    else{
        i = std::atoi(s.c_str());
        c = static_cast<char>(i);
        f = static_cast<float>(i);
        d = static_cast<double>(i);
    }

    // char
    if (!std::isprint(c)) std::cout<<"char: Non displayable\n";
    else std::cout<<"char: '"<<c<<"'\n";

    // int
    std::cout<<"int: "<<i<<"\n";

    // float
    std::cout<<"float: "<<f;
    if (f==(int)f) std::cout<<".0";
    std::cout<<"f\n";

    // double
    std::cout<<"double: "<<d;
    if (d==(int)d) std::cout<<".0";
    std::cout<<"\n";
}
