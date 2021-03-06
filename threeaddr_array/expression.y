%{
#include <stdio.h>
#include <stdlib.h>
extern char *yytext;
void insert();
void code();
void codeminus();
void codeassign();
int top=0;
char str[100][30];
char i[2]="0";
char temp[100];
void last();
void last1();
void last2();
void last3();
int val=4;
%}
%token NUM ID 
%right "="
%left "+" "-"
%left "*" "/"
%right UMINUS

%%

S : H '=' E {codeassign();}
  | L {last2();} '=' E {codeassign();}
  ;
E : E '+' {insert();} E {last3();} 
  | H
  | L {last2();}
  ;
L : H '[' E ']' {last1();} 
  | L '[' E ']' {last();}
   
  ;
H : ID{insert();} ;
  
%%

#include "lex.yy.c"
int main()
{
  yyparse();
  return 0;
} 

void insert()
{
  strcpy(str[++top],yytext);
  //printf("%s \n",str[top]);
}
void last3()
{
   strcpy(temp,"t");
    strcat(temp,i);
    printf("%s = %s %s %s \n",temp,str[top-2],str[top-1],str[top]);
    top=top-2;
    strcpy(str[top],temp);
   i[0]++;
}
void code()
{
    strcpy(temp,"t");
    //char a=i+'0';
    strcat(temp,i);
    printf("%s = %s %s %s \n",temp,str[top-2],str[top-1],str[top]);
    top=top-2;
    strcpy(str[top],temp);
   i[0]++;
}
void last()
{
    strcpy(temp,"t");
    strcat(temp,i);
    printf("%s = %s * %d\n",temp,str[top],val);
   // val/=4;
    strcpy(str[top],temp);
    i[0]++;
    strcpy(temp,"t");
    strcat(temp,i);
    printf("%s = %s + %s\n",temp,str[top-1],str[top]);
    top=top-1;
    strcpy(str[top],temp);
    i[0]++;
}
void last1()
{
   strcpy(temp,"t");
    strcat(temp,i);
    printf("%s = %s * %d\n",temp,str[top],val);
   // val/=4;
    strcpy(str[top],temp);
    i[0]++; 
}
void last2()
{
  strcpy(temp,"t");
    strcat(temp,i);
    printf("%s = %s [ %s ] \n",temp,str[top-1],str[top]);
    top=top-1;
     strcpy(str[top],temp);
    i[0]++;
}
void codeminus()
{
   strcpy(temp,"t");
   //char b=i+'0';
    strcat(temp,i);
   printf("%s = -%s\n",temp,str[top]);
   top--;
   strcpy(str[top],temp);
   i[0]++;

}
void codeassign()
{
   printf("%s = %s\n",str[top-1],str[top]);
   top=top-2;
}


