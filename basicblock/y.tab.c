/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "bb.y" /* yacc.c:339  */

	#include<bits/stdc++.h>
	#include"graph.h"
	using namespace std;
	int yylex();
	void yyerror(char *s);

	int tempC = 1;	int getTemp(){	return tempC++;	}
	int ins = 100;	int getIns(){	return ins++;	}
	string type="";
	int block=-1;
	void createGraph(map<int , vector<string> > basic_block, int graph_size)
	{
		map<int,vector<int> > graph;
		map<int , vector<string> >::iterator it;
		it = basic_block.begin();
		int curr;
		for(;;)
		{
			curr = it->first;
			vector <string>temp = basic_block[it->first];
			string t = temp[temp.size() -1];
			if(t.find("if")!=-1)
			{
				it++;
				if(it==basic_block.end())
				{
					break;
				}
				int next = it->first;
				graph[curr].push_back(next);				
				string n = t.substr(t.find("goto") + 5);
				stringstream tt(n);
				int x = 0;
				tt >> x;
				graph[curr].push_back(x);				
			}
			else if(t.find("goto")!= -1)
			{
				string n = t.substr(t.find("goto") + 5);
				stringstream tt(n);
				int x = 0;
				tt >> x;
				graph[curr].push_back(x);
				it++;
			}
			else
			{
				int next = it->first;
				it++;
				if(it==basic_block.end())
				{
					break;
				}
				graph[curr].push_back(next);
			}
			if(it==basic_block.end())
			{
				break;
			}
		}
		for(map<int , vector<int> > :: iterator it = graph.begin() ; it!=graph.end();it++)
		{
			cout<<" parent  : "<<it->first<<endl;
			cout<<"child :  "<<endl;
			for(int i = 0;i<it->second.size();i++)
			{
				cout<<it->second[i] << " ";
			}
			cout<<endl;
		}
	}
	void basicblock(set<int>leader , map<int,string>mp)
	{
		map<int , vector<string> > basic_block;
		set<int>::iterator it;
		it = leader.begin();
		int i = 0;
		int curr;
		while(true)
		{			
			curr = *it;
			it++;
			if(it == leader.end())
			{
				break;
			}
			int next = *it;
			while(curr<next)
			{
				basic_block[i].push_back(mp[curr]);
				curr++;
			}
			i++;
		}
		while(mp[curr]!="")
		{
			basic_block[i].push_back(mp[curr]);
				curr++;
		}
		map<int , vector<string> > :: iterator result;
		for(result = basic_block.begin();result!=basic_block.end();)
		{
			cout<<endl<<"B"<<result->first<<" : ";
			vector<string>temp = result->second;
			for(int i = 0;i<temp.size();i++)
			{
				cout<< "\t"<<temp[i]<<endl;
			}
			result++;
		}
		int graph_size = i+1;
		createGraph(basic_block , graph_size);
		createDAG(basic_block);
	}
	void genLeader(map<int,string> mp)	
	{
		bool first = false;
		set<int>leader;
		for(map<int,string>::iterator it = mp.begin();it!=mp.end();it++)
		{
			if(first == false)
			{
				leader.insert(it->first);
				first = true;
			}
			int pos = it->second.find("goto");
			if(pos!=-1)
			{
				string temp = it->second.substr(pos+5);
				stringstream s(temp);				
				int t = 0;
				s>>t;
				leader.insert(t);
				leader.insert(it->first+1);
			}
		}
		basicblock(leader,mp);
	}
	
	typedef struct Node{
		int ins;
		string type, name, code;
		vector<string> index;
		vector<int> nextList;
		vector<int> trueList, falseList;
	}node;

	node* makeNode(){
		ostringstream s;
		s<<"t"<<getTemp();
		node* temp = new Node();
		temp->code = s.str();
		return temp;
	}

	node* makeNode2(string x){
		node *temp=new node();
		temp->code=x;
		temp->name=x;
		return temp;
	}

	typedef struct NodeDec{
		string type, value;
		vector<string> index;
	}nodedec;

	nodedec* makeNodeDec(){
		nodedec* temp = new NodeDec();
		return temp;
	}

	map<int, map<string, nodedec *> > symboltable;
	map<int, string> instructions;

	void showBlock(){
		for(int i=0;i<=block;i++){
			for(map<string,nodedec*>::iterator it=symboltable[i].begin();it!=symboltable[i].end();it++){
				cout<<it->first<<" "<<it->second->value<<" "<<it->second->type<<" ";
				for(int k=0;k<it->second->index.size();k++){	cout<<it->second->index[k]<<" ";	}
				cout<<endl;
			}
		}
		symboltable.erase(symboltable.find(block));
		block--;
		cout<<endl<<endl<<endl;
	}

	void checkId(string name){
		for(map<string, nodedec*>::iterator it=symboltable[block].begin();it!=symboltable[block].end();it++){
			if(it->first==name){
				cout<<"Variable "<<name<<" already declared"<<endl;
				exit(0);
			}
		}
	}

	void checkDeclared(string name){
		for(int i=block;i>=0;i--){
			for(map<string,nodedec*>::iterator it=symboltable[i].begin();it!=symboltable[i].end();it++){
				if(it->first==name)	return;
			}
		}
		cout<<name<<" not declared"<<endl;
		exit(0);
	}

	string getType(string name){
		for(int i=block;i>=0;i--){
			for(map<string, nodedec*>::iterator it=symboltable[i].begin();it!=symboltable[i].end();it++){
				if(it->first==name){
					return it->second->type;
				}
			}
		}
		return "";
	}
	vector<string> getIndex(string name){
		for(int i=block;i>=0;i--){
			for(map<string, nodedec*>::iterator it=symboltable[i].begin();it!=symboltable[i].end();it++){
				if(it->first==name){
					return it->second->index;
				}
			}
		}
		vector<string> x;
		return x;
	}

	vector<int> mergeVectors(vector<int> a, vector<int> b){
		vector<int> res(a.begin(),a.end());
		for(int i=0;i<b.size();i++)	res.push_back(b[i]);
		return res;
	}

	void bp(vector<int> a,int num)
	{
		ostringstream ss;
		ss<<num;

		for(vector<int>::iterator it=a.begin();it!=a.end();it++){
			instructions[*it] = instructions[*it]+ss.str();
		}
	}


#line 314 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TYPE = 258,
    ID = 259,
    VAL = 260,
    AND = 261,
    OR = 262,
    NOT = 263,
    LT = 264,
    GT = 265,
    EQQ = 266,
    LTE = 267,
    GTE = 268,
    PL = 269,
    MI = 270,
    MUL = 271,
    DIV = 272,
    OP = 273,
    CL = 274,
    OCB = 275,
    CCB = 276,
    OSB = 277,
    CSB = 278,
    EQ = 279,
    COMMA = 280,
    SEMICOLON = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    TRUE = 285,
    FALSE = 286,
    NTE = 287
  };
#endif
/* Tokens.  */
#define TYPE 258
#define ID 259
#define VAL 260
#define AND 261
#define OR 262
#define NOT 263
#define LT 264
#define GT 265
#define EQQ 266
#define LTE 267
#define GTE 268
#define PL 269
#define MI 270
#define MUL 271
#define DIV 272
#define OP 273
#define CL 274
#define OCB 275
#define CCB 276
#define OSB 277
#define CSB 278
#define EQ 279
#define COMMA 280
#define SEMICOLON 281
#define IF 282
#define ELSE 283
#define WHILE 284
#define TRUE 285
#define FALSE 286
#define NTE 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 250 "bb.y" /* yacc.c:355  */

	char * str;
	struct Node * nn;
	struct NodeDec * nd;

#line 424 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 441 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   132

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   264,   264,   271,   271,   277,   278,   279,   280,   281,
     283,   288,   291,   293,   299,   307,   317,   317,   319,   327,
     335,   343,   352,   353,   355,   362,   364,   365,   371,   384,
     400,   402,   403,   404,   405,   407,   408,   409,   410,   412,
     413,   417,   420,   421,   423,   425,   427,   433,   439,   444,
     449,   456,   457,   459,   460,   461,   462,   463,   464
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "ID", "VAL", "AND", "OR", "NOT",
  "LT", "GT", "EQQ", "LTE", "GTE", "PL", "MI", "MUL", "DIV", "OP", "CL",
  "OCB", "CCB", "OSB", "CSB", "EQ", "COMMA", "SEMICOLON", "IF", "ELSE",
  "WHILE", "TRUE", "FALSE", "NTE", "$accept", "start", "ST", "$@1", "st",
  "I", "IE", "W", "D", "$@2", "VARIABLES", "HMM", "ARR", "A", "L", "R",
  "E", "T", "F", "M", "N", "BOOLEAN", "RELOP", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

#define YYPACT_NINF -77

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-77)))

#define YYTABLE_NINF -36

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      15,   -77,    19,   -13,   -77,     9,   -77,    -6,   -77,   -77,
     -77,   -77,   -77,    95,    17,    20,    20,    60,    29,   -77,
       7,    20,    20,    11,   -77,    28,   -77,    20,    20,    64,
      48,    85,   -77,    31,   106,    60,    60,   -77,   -77,   100,
      -4,    60,   -77,    45,    62,    43,    69,    80,    57,   -77,
      68,    20,    20,   -77,    20,    20,   -77,   116,    84,    39,
     -77,   -77,   -77,   -77,   -77,   -77,    20,   -77,   -77,   -77,
      42,   -77,    15,   -77,   -77,    65,   120,    17,   -77,   -77,
      57,    85,    85,   -77,   -77,   -77,   106,    60,    60,    15,
     -77,   -77,    11,   -77,   -77,   101,   -77,   116,   116,    79,
      15,   -77,    17,   -77,   -77,   -77,   -77,   -77,    15,   -77
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    16,     0,     0,    44,     0,     2,     0,     7,     8,
       9,     5,     6,     0,     0,     0,     0,     0,     0,     1,
       3,     0,     0,    25,    17,    40,    41,     0,     0,    31,
       0,    34,    38,     0,    30,     0,     0,    51,    52,     0,
       0,     0,    11,    44,     0,     0,     0,     0,    39,    43,
       0,     0,     0,    28,     0,     0,    27,    48,     0,     0,
      53,    54,    57,    55,    56,    58,     0,    44,    44,    44,
       0,     4,     3,    29,    26,     0,     0,     0,    20,    42,
      35,    32,    33,    36,    37,    49,    50,     0,     0,     3,
      44,    10,    25,    22,    23,     0,    18,    47,    46,    13,
       3,    24,     0,    21,    45,    15,    19,    44,     3,    14
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -16,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -76,   -77,    26,   -77,     0,   108,     1,    77,   -15,   -37,
     -77,   -28,   -77
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,    43,     8,     9,    10,    11,    14,
      24,    95,    47,    12,    29,    33,    39,    31,    32,    18,
     107,    40,    66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      13,    96,    67,    68,    42,    17,    72,    57,    59,    19,
       1,     2,    49,    70,    20,    69,    30,    34,     1,     2,
      13,    23,    44,    34,    25,    26,   106,    48,   -12,    50,
      87,    88,    89,    46,     3,    27,     4,    58,    28,    83,
      84,    15,     3,    16,     4,    67,    68,    41,    67,    68,
      15,    80,    80,   100,    48,    48,    91,    56,    85,    97,
      98,    90,    51,    52,    25,    26,    71,    86,    35,    74,
     108,    53,    13,    99,    75,    27,    51,    52,    36,    21,
     -35,   -35,    51,    52,   105,    73,    21,    79,    92,    13,
      37,    38,   109,    60,    61,    62,    63,    64,    51,    52,
      13,    54,    55,    79,    76,    77,    78,   104,    13,    60,
      61,    62,    63,    64,    51,    52,    65,    21,   101,    22,
      51,    52,    67,    68,    93,    94,   102,   103,    81,    82,
      45,     0,    65
};

static const yytype_int8 yycheck[] =
{
       0,    77,     6,     7,    20,    18,    43,    35,    36,     0,
       3,     4,    27,    41,    20,    19,    15,    16,     3,     4,
      20,     4,    21,    22,     4,     5,   102,    27,    21,    28,
      67,    68,    69,    22,    27,    15,    29,    36,    18,    54,
      55,    22,    27,    24,    29,     6,     7,    18,     6,     7,
      22,    51,    52,    90,    54,    55,    72,    26,    19,    87,
      88,    19,    14,    15,     4,     5,    21,    66,     8,    26,
     107,    23,    72,    89,     5,    15,    14,    15,    18,    22,
      16,    17,    14,    15,   100,    23,    22,    19,    23,    89,
      30,    31,   108,     9,    10,    11,    12,    13,    14,    15,
     100,    16,    17,    19,    24,    25,    26,    28,   108,     9,
      10,    11,    12,    13,    14,    15,    32,    22,    92,    24,
      14,    15,     6,     7,     4,     5,    25,    26,    51,    52,
      22,    -1,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    27,    29,    34,    35,    36,    38,    39,
      40,    41,    46,    47,    42,    22,    24,    18,    52,     0,
      20,    22,    24,     4,    43,     4,     5,    15,    18,    47,
      49,    50,    51,    48,    49,     8,    18,    30,    31,    49,
      54,    18,    35,    37,    49,    48,    22,    45,    47,    51,
      49,    14,    15,    23,    16,    17,    26,    54,    49,    54,
       9,    10,    11,    12,    13,    32,    55,     6,     7,    19,
      54,    21,    52,    23,    26,     5,    24,    25,    26,    19,
      47,    50,    50,    51,    51,    19,    49,    52,    52,    52,
      19,    35,    23,     4,     5,    44,    43,    54,    54,    35,
      52,    45,    25,    26,    28,    35,    43,    53,    52,    35
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    36,    35,    35,    35,    35,    35,    35,
      37,    37,    37,    38,    39,    40,    42,    41,    43,    43,
      43,    43,    44,    44,    45,    45,    46,    46,    47,    47,
      48,    49,    49,    49,    49,    50,    50,    50,    50,    51,
      51,    51,    51,    51,    52,    53,    54,    54,    54,    54,
      54,    54,    54,    55,    55,    55,    55,    55,    55
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     4,     1,     1,     1,     1,     1,
       3,     1,     0,     6,    10,     7,     0,     3,     4,     6,
       3,     5,     1,     1,     4,     0,     4,     4,     4,     4,
       1,     1,     3,     3,     1,     1,     3,     3,     1,     1,
       1,     1,     3,     2,     0,     0,     4,     4,     2,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 264 "bb.y" /* yacc.c:1646  */
    {
			for(map<int, string>::iterator it=instructions.begin();it!=instructions.end();it++){
				cout<<it->first<<" "<<it->second<<endl;
			}
			genLeader(instructions);
		}
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 271 "bb.y" /* yacc.c:1646  */
    {block++;}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 271 "bb.y" /* yacc.c:1646  */
    {
			//showBlock();
			(yyval.nn)=new node();
			(yyval.nn)->nextList=(yyvsp[-1].nn)->nextList;
			block--;
		}
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 277 "bb.y" /* yacc.c:1646  */
    {type="";(yyval.nn)=new node();(yyval.nn)->nextList=(yyvsp[0].nn)->nextList;}
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 278 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->nextList=(yyvsp[0].nn)->nextList;}
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 279 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->nextList=(yyvsp[0].nn)->nextList;}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 280 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->nextList=(yyvsp[0].nn)->nextList;}
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 281 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->nextList=(yyvsp[0].nn)->nextList;}
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 283 "bb.y" /* yacc.c:1646  */
    {
			(yyval.nn)=new node();
			bp((yyvsp[-2].nn)->nextList,(yyvsp[-1].nn)->ins);
			(yyval.nn)->nextList=(yyvsp[0].nn)->nextList;
		}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 288 "bb.y" /* yacc.c:1646  */
    {
			(yyval.nn)->nextList=(yyvsp[0].nn)->nextList;
		}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 291 "bb.y" /* yacc.c:1646  */
    {}
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 293 "bb.y" /* yacc.c:1646  */
    {
		(yyval.nn)=new node();
		bp((yyvsp[-3].nn)->trueList,(yyvsp[-1].nn)->ins);
		(yyval.nn)->nextList=mergeVectors((yyvsp[-3].nn)->falseList,(yyvsp[0].nn)->nextList);
	}
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 299 "bb.y" /* yacc.c:1646  */
    {
				(yyval.nn)=new node();
				bp((yyvsp[-7].nn)->trueList,(yyvsp[-5].nn)->ins);
				bp((yyvsp[-7].nn)->falseList,(yyvsp[-1].nn)->ins);
				(yyval.nn)->nextList=mergeVectors((yyvsp[-4].nn)->nextList,(yyvsp[-2].nn)->nextList);
				(yyval.nn)->nextList=mergeVectors((yyval.nn)->nextList,(yyvsp[0].nn)->nextList);
			}
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 307 "bb.y" /* yacc.c:1646  */
    {
				(yyval.nn)=new node();
				bp((yyvsp[-3].nn)->trueList,(yyvsp[-1].nn)->ins);
				bp((yyvsp[0].nn)->nextList,(yyvsp[-5].nn)->ins);
				ostringstream ss;
				ss<<(yyvsp[-5].nn)->ins;
				instructions[getIns()]="goto "+ss.str();
				(yyval.nn)->nextList=(yyvsp[-3].nn)->falseList;
		}
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 317 "bb.y" /* yacc.c:1646  */
    {type=(yyvsp[0].str);}
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 317 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();}
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 319 "bb.y" /* yacc.c:1646  */
    {
					checkId((yyvsp[-3].str));
					(yyval.nd) = makeNodeDec();
					(yyval.nd)->type = type;
					(yyval.nd)->value="";
					(yyval.nd)->index = (yyvsp[-2].nd)->index;
					symboltable[block][(yyvsp[-3].str)]=(yyval.nd);
				}
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 327 "bb.y" /* yacc.c:1646  */
    {
					checkId((yyvsp[-5].str));
					(yyval.nd) = makeNodeDec();
					(yyval.nd)->type = type;
					(yyval.nd)->value=(yyvsp[-2].str);
					(yyval.nd)->index = (yyvsp[-4].nd)->index;
					symboltable[block][(yyvsp[-5].str)]=(yyval.nd);
				}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 335 "bb.y" /* yacc.c:1646  */
    {
					checkId((yyvsp[-2].str));
					(yyval.nd) = makeNodeDec();
					(yyval.nd)->type = type;
					(yyval.nd)->value="";
					(yyval.nd)->index = (yyvsp[-1].nd)->index;
					symboltable[block][(yyvsp[-2].str)]=(yyval.nd);
				}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 343 "bb.y" /* yacc.c:1646  */
    {
					checkId((yyvsp[-4].str));
					(yyval.nd) = makeNodeDec();
					(yyval.nd)->type = type;
					(yyval.nd)->value=(yyvsp[-1].str);
					(yyval.nd)->index = (yyvsp[-3].nd)->index;
					symboltable[block][(yyvsp[-4].str)]=(yyval.nd);
				}
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 352 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 1773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 353 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 355 "bb.y" /* yacc.c:1646  */
    {
				(yyval.nd)=makeNodeDec();
				(yyval.nd)->index.push_back((yyvsp[-2].str));
				for(int i=0;i<(yyvsp[0].nd)->index.size();i++)	{
					(yyval.nd)->index.push_back((yyvsp[0].nd)->index[i]);
				}
			}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 362 "bb.y" /* yacc.c:1646  */
    {(yyval.nd)=makeNodeDec();}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 364 "bb.y" /* yacc.c:1646  */
    {instructions[getIns()]=(yyvsp[-3].nn)->name+"["+(yyvsp[-3].nn)->code+"]= "+(yyvsp[-1].nn)->code;}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 365 "bb.y" /* yacc.c:1646  */
    {
			checkDeclared((yyvsp[-3].str));
			instructions[getIns()]=(string)(yyvsp[-3].str)+" = "+(yyvsp[-1].nn)->code;
	  		(yyval.nn)=new Node();
		}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 371 "bb.y" /* yacc.c:1646  */
    {
			(yyval.nn)=makeNode();
			(yyval.nn)->name=(yyvsp[-3].str);
			checkDeclared((yyvsp[-3].str));
			(yyval.nn)->type=getType((yyvsp[-3].str));
			(yyval.nn)->index=getIndex((yyvsp[-3].str));
			int w;
			if((yyval.nn)->type=="int" || (yyval.nn)->type=="float"){w=4;}else{w=1;}
			for(int i=1;i<(yyval.nn)->index.size();i++){	stringstream geek((yyval.nn)->index[i]); int x=0; geek>>x; w*=x;	}
			ostringstream ss;
			ss<<w;
			instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[-1].nn)->code+" * "+ss.str();
		}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 384 "bb.y" /* yacc.c:1646  */
    {
			Node * myTemp=makeNode();
 			(yyval.nn)=makeNode();
 			(yyval.nn)->name=(yyvsp[-3].nn)->name;
 			(yyval.nn)->type=(yyvsp[-3].nn)->type;
 			(yyval.nn)->index=(yyvsp[-3].nn)->index;
 			(yyval.nn)->index.erase((yyval.nn)->index.begin());
 			int w;
			if((yyval.nn)->type=="int" || (yyval.nn)->type=="float"){w=4;}else{w=1;}
			for(int i=1;i<(yyval.nn)->index.size();i++){	stringstream geek((yyval.nn)->index[i]); int x=0; geek>>x; w*=x;	}
			ostringstream ss;
			ss<<w;
 			instructions[getIns()]=myTemp->code + " = "+(yyvsp[-1].nn)->code +" * "+ss.str();
 			instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[-3].nn)->code+ " + " + myTemp->code;
		}
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 400 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=(yyvsp[0].nn);}
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 402 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[0].nn)->name+"["+(yyvsp[0].nn)->code+"]";}
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 403 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[-2].nn)->code+" + "+(yyvsp[0].nn)->code;}
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 404 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[-2].nn)->code+" - "+(yyvsp[0].nn)->code;}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 405 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=(yyvsp[0].nn);}
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 407 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[0].nn)->name+"["+(yyvsp[0].nn)->code+"]";}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 408 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[-2].nn)->code+" * "+(yyvsp[0].nn)->code;}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 409 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[-2].nn)->code+" / "+(yyvsp[0].nn)->code;}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 410 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=(yyvsp[0].nn);}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 412 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = "+(yyvsp[0].nn)->name+"["+(yyvsp[0].nn)->code+"]";}
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 413 "bb.y" /* yacc.c:1646  */
    {
			checkDeclared((yyvsp[0].str));
			(yyval.nn)=makeNode2((yyvsp[0].str));
		}
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 417 "bb.y" /* yacc.c:1646  */
    {
			(yyval.nn)=makeNode2((yyvsp[0].str));
		}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 420 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=(yyvsp[-1].nn);}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 421 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=makeNode();instructions[getIns()]=(yyval.nn)->code+" = - "+(yyvsp[0].nn)->code;}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 423 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->ins=ins;}
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 425 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->nextList.push_back(getIns());instructions[(yyval.nn)->nextList.back()]="goto ";}
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 427 "bb.y" /* yacc.c:1646  */
    {
					(yyval.nn)=new node();
					bp((yyvsp[-3].nn)->falseList,(yyvsp[-1].nn)->ins);
					(yyval.nn)->trueList=mergeVectors((yyvsp[-3].nn)->trueList,(yyvsp[0].nn)->trueList);
					(yyval.nn)->falseList=(yyvsp[0].nn)->falseList;
				}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 433 "bb.y" /* yacc.c:1646  */
    {
					(yyval.nn)=new node();
	 				bp((yyvsp[-3].nn)->trueList,(yyvsp[-1].nn)->ins);
	 				(yyval.nn)->trueList=(yyvsp[0].nn)->trueList;
	 				(yyval.nn)->falseList=mergeVectors((yyvsp[-3].nn)->falseList,(yyvsp[0].nn)->falseList);
				}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 439 "bb.y" /* yacc.c:1646  */
    {
					(yyval.nn)=new node();
					(yyval.nn)->trueList=(yyvsp[0].nn)->falseList;
					(yyval.nn)->falseList=(yyvsp[0].nn)->trueList;
				}
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 444 "bb.y" /* yacc.c:1646  */
    {
					(yyval.nn)=new node();
					(yyval.nn)->trueList=(yyvsp[-1].nn)->trueList;
					(yyval.nn)->falseList=(yyvsp[-1].nn)->falseList;
				}
#line 1994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 449 "bb.y" /* yacc.c:1646  */
    {
					(yyval.nn)=new node();
					(yyval.nn)->trueList.push_back(getIns());
					instructions[(yyval.nn)->trueList.back()]="if "+(yyvsp[-2].nn)->code+" "+(yyvsp[-1].str)+" "+(yyvsp[0].nn)->code+" goto ";
					(yyval.nn)->falseList.push_back(getIns());
					instructions[(yyval.nn)->falseList.back()]="goto ";
				}
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 456 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->trueList.push_back(getIns());instructions[(yyval.nn)->trueList.back()]="goto ";}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 457 "bb.y" /* yacc.c:1646  */
    {(yyval.nn)=new node();(yyval.nn)->falseList.push_back(getIns());instructions[(yyval.nn)->falseList.back()]="goto ";}
#line 2018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 459 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 2024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 460 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 461 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 462 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 463 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 464 "bb.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str);}
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2058 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 466 "bb.y" /* yacc.c:1906  */


void yyerror(char* s)
{
	cout<<s<<endl;
}
int yywrap(){	return 1;	}
int main()
{
	yyparse();
}
