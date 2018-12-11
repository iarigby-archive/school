COMPILERNAME=while

all: $(COMPILERNAME)
	-

compiler: $(COMPILERNAME)
	-

clean:
	rm -rf $(COMPILERNAME) lex.yy.cc

lex.yy.cc: $(COMPILERNAME).l
	flex $(COMPILERNAME).l

$(COMPILERNAME): $(COMPILERNAME).cc lex.yy.cc
	g++ -o$(COMPILERNAME) $(COMPILERNAME).cc lex.yy.cc

