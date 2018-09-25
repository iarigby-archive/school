%option c++ noyywrap

%%


ab		std::cout << "a";
[a-z][a-z]+	std::cout << "b"; // priority goes from top to bottom


%%

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	lexer.yylex();
	//call the function
	// output now:
	// it only ouputs a single b on 2+ letters (other than ab)
	// in case of abc the second rule is matched (because of rule 2 from lecture)

	return 0;
}