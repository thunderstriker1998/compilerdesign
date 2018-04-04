#include<bits/stdc++.h>
using namespace std;
//node consists of op1,op2 , operator
class dag
{
	public :
	string label;
	vector<string>name;
	vector<dag*>next;
};
bool isExist(string op)
{
	
}
vector<string> split(string s)
{
	vector<string>result;
	string temp = "";
	for(int i = 0;i<s.size();i++)
	{
		if(s[i] == ' ')
		{
			result.push_back(temp);
			temp = "";
		}
		else
		{
			temp = temp + s[i];
		}
	}
	if(temp!="")
	{
		result.push_back(temp);
	}
	return result;
}
bool dfs(dag*root , dag*op1 ,dag * op2 ,string op)
{
	map<dag * ,bool>visited;
	stack<dag *>s;
	s.push(root);
	
	while(!s.empty())
	{
		
		dag *temp = s.top();
		visited[temp] = true;
		s.pop();	
		if(temp!=NULL and temp->next.size()>0)
		{
			if(temp->label == op)
			{
				bool flag1 = false , flag2 = false;
				std::vector<dag*> :: iterator it;
				it = find(temp->next.begin(), temp->next.end() , op1);
				if(it!=temp->next.end())
				{
					flag1 = true;
				}
				it = find(temp->next.begin(), temp->next.end() , op2);
				if(it!=temp->next.end())
				{
					flag2 = true;
				}
				if(flag1 and flag2)
					return true;
			}
		
			for(int i=0;i<temp->next.size();i++)
			{				
				if(temp->next[i]!=NULL and visited[temp->next[i]] == false)
				{
					s.push(temp->next[i]);
				}
			}		
		}		
	}
	return false;
}
dag* search(dag *op1 , dag *op2 , vector<dag*> root, string op)
{
	vector<dag*>temp = root;
	for(int i=0;i<temp.size();i++)
	{
		if(dfs(temp[i] , op1 , op2 , op) )
		{
			return temp[i];
		}
	}
}
bool isoperator(string s)
{
	if(s == "+" || s == "-" || s == "*" || s == "/" || s == "%")
		return true;
	return false;
}
void printDAG(dag *root)
{
	stack<dag*>s;
	s.push(root);
	map<dag* , bool>visited;
	while(!s.empty())
	{
		dag *temp = s.top();
		s.pop();		
		if(temp!=NULL)
		{
			visited[temp] = true;
			if(isoperator(temp->label))
			{
				cout<<"op - > "<<temp->label<<endl;
				if(temp->name.size() > 0)
				{
					cout<<"contains \n";
					for(int i = 0;i<temp->name.size();i++)
					{
						cout<<temp->name[i]<<" ";					
					}
					cout<<endl;
				}
				if(temp->next.size() > 0)
				{					
					cout<<"child \n";
					for(int i=0;i<temp->next.size();i++)
					{
						if(temp->next[i]!=NULL and visited[temp->next[i]] == false)
							s.push(temp->next[i]);
						cout<<temp->next[i]->label<<" ";
					}
				}				
				cout<<endl;
			}
		}
	}
}
// creating DAG for given basic_block and its CFG
void createDAG(map<int , vector<string> > basic_block)	
{
	vector<dag *>	result;
	map<int , vector<string> >::iterator it;		
	for(it = basic_block.begin() ; it!= basic_block.end() ; it++)	
	{
		dag *g = NULL;
		vector<dag*>root;
		map<string , dag*>mp;
		for(int i=0;i<it->second.size();i++)
		{
			if(it->second[i].find("if") == -1 and it->second[i].find("goto") == -1 and it->second[i].find("[") == -1)
			{
				cout<<it->second[i]<<endl;
				vector<string>q = split(it->second[i]);

				if(q.size() == 5)
				{
					string op1 = q[2], op2 = q[4], op = q[3] , lhs = q[0];
					if(root.size() == 0)
					{
						dag * t1 = new dag;
						t1->label = op1;
						dag * t2 = new dag;
						t2->label = op2;
						dag * internal = new dag;
						mp[op1] = t1;
						mp[op2] = t2;
						internal->label = op;
						internal->next.push_back(t1);						
						internal->next.push_back(t2);
						internal->name.push_back(lhs);						
						root.push_back(internal);
						cout<<internal->next[0]->label<<" "<<internal->next[1]->label<<endl;
					}
					else
					{
						if(mp[op1] && mp[op2])
						{
							dag *getnode  = search(mp[op1] , mp[op2] , root , op  );
							if(getnode!=NULL)
							{
								getnode->name.push_back(lhs);
							}
							else
							{
								dag *internal = new dag;
								internal->label = op;
								internal->name.push_back(lhs);
								internal->next.push_back(mp[op1]);
								internal->next.push_back(mp[op2]);
								root.push_back(internal);
							}
						}
						else if(mp[op1])
						{
							dag *internal = new dag;
							internal->next.push_back(mp[op1]);
							internal->label = op;
							internal->name.push_back(lhs);
							dag *t = new dag;
							t->label = op2;
							mp[op2] = t;
							internal->next.push_back(t);
							root.push_back(internal);
						}
						else if (mp[op2])
						{
							dag *internal = new dag;
							internal->next.push_back(mp[op2]);
							internal->label = op;
							internal->name.push_back(lhs);
							dag *t = new dag;
							t->label = op1;
							mp[op1] = t;
							internal->next.push_back(t);
							root.push_back(internal);
						}
						else
						{
							dag * internal = new dag;
							dag *t1 = new dag;
							dag *t2 = new dag;
							t1->label = op1;
							t2->label = op2;
							internal->label = op;
							internal->next.push_back(t1);
							internal->next.push_back(t2);
							root.push_back(internal);
						}
					}
				}
				else if(q.size() == 3)
				{
					string op = q[1] , lhs = q[0] , op1 = q[2];
					if(mp[op1])
					{
						mp[op1]->name.push_back(lhs);					
					}
				}
			}
		}			
		for(int i=0;i<root.size();i++)
		{		
			if(root[i]!=NULL)	
			{
				//cout<<root[i]<<endl;
				printDAG(root[i]);	
			}
		}
	}
}
