/***Converting For statement ( C construct) to while statement using lex and yacc*************/
1.An input file(text) with FOR  statement  is validated by for.l and parsed by for.y
2.The grammar in for.y converts a for statement  to an equivalent while statement (in C construct)


/**************HOW TO RUN *****************/  

->lex for.l
->yacc -d for.y 
->g++ lex.yy.c for.tab.c -lfl
->./a.out <in.txt


