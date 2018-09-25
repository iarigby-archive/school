%option c++ noyywrap

%%

[a-z]

%%

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	lexer.yylex();
	//call the function
	//returns the symbols that you type
	return 0;
}