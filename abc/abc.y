%baseclass-preinclude <iostream>
%lsp-needed

%token A
%token B
%token C

%union {
    int length;
}

%type<length> aseq;
%type<length> bseq;
%type<length> cseq;

%%

start :
    aseq bseq cseq
    {
        if($1 == $2 && $2 == $3) {
            std::cout << "The sequence is valid, the length is: " << $1 << std::endl;
        } else {
            std::cout << "The sequence is invalid." << std::endl;
        }
    }
;

aseq :
    A
    { $$ = 1; }
|
    aseq A
    { $$ = $1 + 1; }
;

bseq :
    B
    { $$ = 1; }
|
    bseq B
    { $$ = $1 + 1; }
;

cseq :
    C
    { $$ = 1; }
|
    cseq C
    { $$ = $1 + 1; }
;


