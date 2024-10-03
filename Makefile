all: lex yacc eval

lex: 
	lex poly.l

yacc: 
	yacc -d poly.y

eval: 
	g++ y.tab.c  polyutils.cpp -o a.out

run:
	./a.out  input.txt

clean:
	rm -f lex.yy.c y.tab.c y.tab.h a.out
