%option noyywrap c++ yylineno

%{
#include <iostream>
#include <stdlib.h>
void print(std::string type, std::string text) {
	std::cout << type << "\t\t" << text << std::endl;
}
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

	/* ignored */
[ \t\n]	
#.*
 
	/* keywords */ 

program 	print("keyword", YYText());
begin		print("keyword", YYText());
end			print("keyword", YYText());
integer		print("keyword", YYText());
boolean 	print("keyword", YYText());
not 		print("keyword", YYText());
skip 		print("keyword", YYText());
if 			print("keyword", YYText());
then 		print("keyword", YYText());
else 		print("keyword", YYText());
endif 		print("keyword", YYText());
while 		print("keyword", YYText());
do 			print("keyword", YYText());
done 		print("keyword", YYText());
read 		print("keyword", YYText());
write 		print("keyword", YYText());

	/* operators */
or			print("binary", YYText());
and			print("binary", YYText());
=			print("binary", YYText());
\<			print("binary", YYText());
\>			print("binary", YYText());
\+			print("binary", YYText());
\-			print("binary", YYText());
\*			print("binary", YYText());
div			print("binary", YYText());
mod			print("binary", YYText());

	/* literals */
true        print("bool literal ", YYText());
false		print("bool literal ", YYText());
[0-9]+		print("int literal ", YYText());


	/* identifiers */

[a-z][a-zA-Z0-9_]* 	std::cout << "identifier: \t" << YYText() << std::endl;

	/* other */
\(			std::cout << "found \t\t" << YYText() << std::endl;
\)			std::cout << "found \t\t" << YYText() << std::endl;
;			std::cout << "found \t\t" << YYText() << std::endl;
:=			std::cout << "found \t\t" << YYText() << std::endl;
. {
    std::cerr << "*** Line " << lineno() << ": Lexical error for " << YYText() << std::endl;
    //exit(1);
}


%%


