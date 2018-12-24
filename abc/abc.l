%option noyywrap c++ yylineno

%{
#include "Parserbase.h"
%}

%%

a           return Parser::A;
b           return Parser::B;
c           return Parser::C;
.           {
                std::cerr << lineno() << ": Lexical error." << std::endl;
                exit(1);
            }
