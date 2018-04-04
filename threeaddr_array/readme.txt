/***Converting an array expression into its three address code*************/
1.An input file(text) with array expression  statement  is validated by expression.l and parsed by expression.y
2.The grammar produces  the three address code and stores in code element of the NODE structure .3.
We get a three address code as we parse the expression  


/**************HOW TO RUN *****************/  

->lex for.l
->yacc -d expression.y 
->g++ lex.yy.c expression.tab.c -lfl
->./a.out <in.txt


