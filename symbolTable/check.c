#include<stdio.h>
#include "table.h" 
int main()
{
	int i = 0;
	initialize();
	insert(0,"hello");
	insert(0,"he");
	insert(0,"hel");
	for(i=0;i<5;i++)
	{
		struct symbolTable*temp = head[i].tuple;
		while(temp)
		{
			printf("%s\n",temp->name);
			temp = temp->next;
		}
	}
}
