%option c++ noyywrap

%%

^(([02468]|[1-9])*[02468],)*([02468]|[1-9])*[02468]$ {
	std::cout << "accepted: " << YYText() << std::endl; 
}

%%

int main()
{
	yyFlexLexer lexer(&std::cin, &std::cout);
	//create an instance of the lexer that uses std cin and out for io
	lexer.yylex(); 
	//accept sentences that are composed of even numbers and commas
	//the sentences are series of even numbers separated by commas
	//with at least one even number
	//examples: 
	//18
	//2,4
	//0,12,66,78	
	//shouldn't accept
	//2,3,4
	//2,44,
	return 0;
}