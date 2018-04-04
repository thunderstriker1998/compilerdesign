/***MATCHING UNMATCHED IF USING LEX YACC*************/
1.An string with if-else statements is validated by if.l and parsed by if.y
2.The grammar in if.y appends an empty else block to an unmatched if statement


/**************HOW TO RUN *****************/  

->lex if.l
->yacc -d if.y 
->g++ lex.yy.c y.tab.c -lfl
->./a.out <in.txt


