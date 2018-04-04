# compilerdesign
Implementation of  compiler design concepts in lex,yacc(Dragon Book)
* folder ifelse -> if a given "if" statement doesnt have a corresponding "else", add an empty "else{}" statement.
* folder loops -> convert the given "for" and "dowhile" loop to "while" loop such that its semantic meaning is maintained.
* folder threeaddr_backpatching-> for a given boolean expression, create the true list, false list etc.
* folder labelled -> given an arithmetic expression ,generate its corresponding assembly code for any value for required register and available number of registers.
* folder dag_opt_all ->it generates dag for a given block of statements and removes copy propagation, constant folding and common sub expression and generates optimized three address statements for that block.
* folder symbol table -> given a set of declaration statements, it generates its symbol table.
* folder syntax tree -> creates a syntax tree for an arithmetic expression.
* folder threeaddr_array -> creates three address statements for expressions invloving array reference.
* folder threeaddr_all -> creates three address statements for any kind of c statements(including array reference of any dimension).
