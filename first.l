%option c++ noyywrap

%%


10\.0\.0\.[0-255] std::cout << "Found an IP address! :)" << std::endl; // 0-255 is taken as [0-2]|[5]|[5]

%%

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	lexer.yylex(); 
	
	return 0;
}