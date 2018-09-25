%option c++ noyywrap

%%


ab  std::cout << "a";
[a-z][a-z]  std::cout << "b"; // priority goes from top to bottom


%%

// output now:
// abcde -> abe
// abcdef -> abb

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	lexer.yylex();
	//call the function
	//returns the symbols that you type
	return 0;
}