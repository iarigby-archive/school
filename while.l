%option noyywrap c++ yylineno

%{
#include <iostream>
#include <stdlib.h>
%}

%%

 /* Here come the regular expressions and the corresponding actions.
    For the moment, we produce an output line for each token found.

    For instance:
            begin   std::cout << "begin keyword" << std::endl;
            [0-9]+	std::cout << "number literal" << std::endl;

    Do not forget about keywords, literals, operators, separator symbols,
    comments and whitespaces!
 */

. {
    std::cerr << "Line " << lineno() << ": Lexical error." << std::endl;
    exit(1);
}

%%
