%{
	#include<bits/stdc++.h>
	using namespace std;
	int yylex();	
	void yyerror(char *s);

	typedef struct node
	{
		struct node *left,*right;
		string val;int label;
	}NODE;

	NODE* makeNode(string val, NODE* left , NODE* right)
	{
		NODE *temp=new NODE();
		temp->val=val;
		temp->left=left;
		temp->right=right;
		return temp;
	}

	void postOrder(NODE* root)
	{
		if(root)
		{
			postOrder(root->left);
			postOrder(root->right);
			cout<<root->val<<" "<<root->label<<" " <<endl;
		}
	}

	void inOrder(NODE* root)
	{
		if(root)
		{
			inOrder(root->left);
			cout<<root->val<<" ";
			inOrder(root->right);
		}
	}

	void preOrder(NODE* root)
	{
		if(root)
		{
			cout<<root->val<<" ";
			preOrder(root->left);
			preOrder(root->right);
		}
	}
	void genlabel(NODE *root)
	{
	    if(root->left)
	        genlabel(root->left);
	    if(root->right)
	       genlabel(root->right);                        
	    if(!root->left&&!root->right)
	    {
	    root->label=1;
	    return;
	    }
	    
	    if(root->left->label==root->right->label)
	    {   root->label=root->left->label+1;
	            return;
	    } 
	    else
	    {   
	    root->label=max(root->left->label,root->right->label);
	    return;
	    }
	
	}
	void gencode(NODE* root,int b)
    { 
            if(!root->left&&!root->right)
             {
                    cout<<"LD R"<<b<<" "<<root->val<<endl;   return;
             }   
            if(root->left->label==root->right->label)     
            {
                gencode(root->right,b+1);
                gencode(root->left,b); 
                int r=root->right->label;
                int l=root->left->label;  
                cout<<root->val<< "R"<<b+r<<" "<< "R"<<b+l-1<<" " "R"<<b+r<<endl;
                 
                  return;     
            }
            else
            {   
                if(root->right->label>root->left->label)
                {
                gencode(root->right,b);
                gencode(root->left,b); 
                int r=root->right->label;
                int l=root->left->label;
                int m=min(l,r);  
                cout<<root->val<< "R"<<b+r-1<<" "<< "R"<<b+m-1<<" " "R"<<b+r-1<<endl; 
                }
                 else
                 {
                        gencode(root->left,b+1);
                gencode(root->right,b); 
                int r=root->right->label;
                int l=root->left->label; 
                int m=min(l,r); 
                cout<<root->val<< "R"<<b+l-1<<" "<< "R"<<b+m-1<<" " "R"<<b+l-1<<endl; 
                                 
                 } 
                     
                 return; 
            }
        	  
	}
%}

%token PL MI MUL DIV OP CL EQ ID VAL SC UNR POW

%union{
	typedef struct node NODE;
	char *str;
	NODE *node;
}

%type <node> s e t f g
%type <str> PL MI MUL DIV OP CL EQ ID VAL SC UNR POW

%%
s : e {$$=$1;genlabel($$);postOrder($$);cout<<endl;gencode($$,1);}
e : e PL t {$$=makeNode($2,$1,$3);} |
	 e MI t {$$=makeNode($2,$1,$3);} |
	  t {$$=$1;};
t : t MUL f {$$=makeNode($2,$1,$3);}|
	 t DIV f {$$=makeNode($2,$1,$3);}|
	  f {$$=$1;};
f : g POW f {$$=makeNode($2,$1,$3);} |
	 g {$$=$1;};
g : OP e CL {$$=$2;} |
	 ID{$$=makeNode($1,NULL,NULL);} |
	  VAL{$$=makeNode($1,NULL,NULL);} |
	   MI g{$$=makeNode($1,NULL,$2);} ;

%%

void yyerror(char *s)
{
	printf("%s\n",s);
}
int yywrap()
{
	return 1;
}
int main(void)
{
	yyparse();
}
