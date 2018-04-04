flex syntree.l
bison syntree.y
g++ lex.yy.c syntree.tab.c -lfl
./a.out < in.txt