/***Code Generation of expressions using labelled trees*************/
The code implements the concept of register allocation and register spilling with using labelled for generating the loads and stores
Instructions with limited register is implemented in register__assign folder
1.An input file(text) with an  expression  statement  is validated by tree.l and parsed by expression.y
2.The labelled tree is constructed for the parse tree generated for the expression.
3.we generate the load and store instructions for evaluating the expression 


/**************HOW TO RUN *****************/  

->lex tree.l
->yacc -d tree.y 
->g++ lex.yy.c y.tab.c -lfl
->./a.out <in.txt


