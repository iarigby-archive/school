%option c++ noyywrap

%%


10\.0\.0\.([0-9]|[1-9][0-9]) std::cout << "Found an IP address: " << YYText() << std::endl; 
%%

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	lexer.yylex(); 
	
	return 0;
}