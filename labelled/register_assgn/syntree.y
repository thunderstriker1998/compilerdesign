%{
	#include<bits/stdc++.h>
	using namespace std;
	int yylex();	
	void yyerror(char *s);
	map<string,string> op;
	int r=2;

	void initMap(map<string,string>& op)
	{
		op["+"]="ADD";
		op["-"]="SUB";
		op["*"]="MUL";
		op["/"]="DIV";
	}
	typedef struct node
	{
		struct node *left,*right;
		int label;
		bool done;
		string val;
	}NODE;

	NODE* makeNode(string val, NODE* left , NODE* right)
	{
		NODE *temp=new NODE();
		temp->val=val;
		temp->left=left;
		temp->right=right;
		return temp;
	}

	void assign_label(NODE *root)
	{
		if(root)
		{
			assign_label(root->right);
			assign_label(root->left);
			if(!root->left && !root->right)
				root->label=1;
			else
			{
				if(root->left->label == root->right->label)
					root->label = root->left->label+1;
				else
					root->label = max(root->left->label, root->right->label);
			}
		}
	}

	void gen(NODE *root, int base)
	{
		if(root)
		{
			if(!root->right && !root->left)
			{
				printf("LD R%d, %s\n",base,(root->val).c_str());
			}
			else
			{
				if(root->label > r)
				{
					if(root->right->label>root->left->label)
					{
						gen(root->right,1);
						printf("ST t%d, R%d\n", root->label, r);
						if(root->left->label>=r)
						{
							gen(root->left,1);
						}
						else
						{
							gen(root->left,r-root->left->label);
						}
						printf("LD R%d, t%d\n", r-1, root->label);
						printf("%s R%d, R%d, R%d\n",(op[root->val]).c_str(), r, r, r-1);

					}
					else
					{
						gen(root->left,1);
						printf("ST t%d R%d\n", root->label, r);
						if(root->right->label>=r)
						{
							gen(root->right,1);
						}
						else 
						{
							gen(root->right,r-root->right->label);
						}
						printf("LD R%d, t%d\n", r-1, root->label);
						printf("%s R%d, R%d, R%d\n",(op[root->val]).c_str(), r, r-1, r);
					}
				}
				else
				{
					if(root->right->label == root->left->label)
					{
						gen(root->right,base+1);
						gen(root->left,base);
						printf("%s R%d, R%d, R%d\n",(op[root->val]).c_str(), base+root->label-1, base+root->label-2, base+root->label-1);
					}
					else if(root->right->label>root->left->label)
					{
						int m = min(root->left->label,root->right->label);
						gen(root->right,base);
						gen(root->left,base);
						printf("%s R%d, R%d, R%d\n",(op[root->val]).c_str(), base+root->label-1, base+m-1, base+root->label-1);
					}
					else
					{
						int m = min(root->left->label,root->right->label);
						gen(root->left,base);
						gen(root->right,base);
						printf("%s R%d, R%d, R%d\n",(op[root->val]).c_str(), base+root->label-1, base+m-1, base+root->label-1);
					}
				}
			}
		}
	}

	void postOrder(NODE* root)
	{
		if(root)
		{
			postOrder(root->left);
			postOrder(root->right);
			cout<<root->val<<" "<<root->label<<endl;
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
s : e 
	{
		$$=$1;
		assign_label($$);
		initMap(op);
		gen($$,1);
		//postOrder($$);
		cout<<endl;
	}
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