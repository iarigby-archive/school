%option c++ noyywrap

%%


ab  std::cout << "a";
[a-z][a-z]  std::cout << "b"; // priority goes from top to bottom


%%

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	lexer.yylex();
	//call the function
	// output now:
	// abcde -> abe
	// abcdef -> abb

	return 0;
}