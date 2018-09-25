%option c++ noyywrap

%%

%%

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	return 0;
}