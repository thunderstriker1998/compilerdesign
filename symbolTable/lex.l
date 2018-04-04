%{
	#include"y.tab.h"	
	int yywrap();
%}

%%
[ \t\n]+	{return 0;}
"int"	{yylval.string = strdup(yytext);return INT;}
[a-zA-Z_][a-zA_Z0-9_]	{yylval.string = strdup(yytext);return var;}
[,]	{yylval.string = strdup(yytext);return comma;}
[;]	{yylval.string = strdup(yytext);return semi_colon;}
%%
int yywrap(void)
{
	return 1;
}
