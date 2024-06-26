/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_NUM = 258,
     T_ID = 259,
     T_STRING = 260,
     T_INT = 261,
     T_VOID = 262,
     T_IF = 263,
     T_ELSE = 264,
     T_WHILE = 265,
     T_RETURN = 266,
     T_READ = 267,
     T_WRITE = 268,
     T_LE = 269,
     T_LT = 270,
     T_GE = 271,
     T_GT = 272,
     T_EQ = 273,
     T_NE = 274,
     T_BREAK = 275,
     T_CONTINUE = 276
   };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_ID 259
#define T_STRING 260
#define T_INT 261
#define T_VOID 262
#define T_IF 263
#define T_ELSE 264
#define T_WHILE 265
#define T_RETURN 266
#define T_READ 267
#define T_WRITE 268
#define T_LE 269
#define T_LT 270
#define T_GE 271
#define T_GT 272
#define T_EQ 273
#define T_NE 274
#define T_BREAK 275
#define T_CONTINUE 276




/* Copy the first part of user declarations.  */
#line 1 "lab6.y"

/*
	Author: Abdur Razzak
	Date: March 27, 2024
	Lab: Lab 6
	Modifications:
		Added semantic actions in every production.
		SYMBOL table checking are skipped for this lab.
		next property is used to connect same level nodes and print with same indentation
		the yacc file is taken from LAB 5
		Only 3 address are used in each node: s1, s2 and next
		Corrected the indectation in call sequence
		All tokens starts with T_ and node types are A_
		next is only 5 required time used.
		Var_LIST are all s1 connected
		All the PT() called are from inside case:statement
		As a grad student, prototyping is supported, also break and continue statement.
		A_EXPR node is only defiend now, all the other cases are written inside
		May be tomorrow and all of the expression are 

		Input: This file will take tokens as input
		Output: Will apply Grammer based on token sequence
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "ast.h"

ASTnode *PROGRAM;
// prototying yylex to get ride of compilation waring
int yylex();

// mydebug and linecount are declared in lex file and the yacc file is 
// just using them, therefore, they are declared as extern
extern int mydebug;
extern int linecount;


// when error occurs, it prints the line number
void yyerror (char *s)  /* Called by yyparse on error */
{
  printf ("Error: %s, In line: %d\n", s, linecount);
}




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 54 "lab6.y"
{
	int value;
	char * string;
	ASTnode *node;
	enum AST_MY_DATA_TYPE d_type;
	enum AST_OPERATORS operators;
}
/* Line 193 of yacc.c.  */
#line 195 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 208 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    28,    23,     2,
      33,    34,    26,    24,    32,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
       2,    37,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,    22,    36,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    18,    20,
      25,    29,    36,    38,    40,    47,    54,    56,    58,    60,
      64,    69,    72,    77,    80,    81,    84,    85,    87,    89,
      91,    93,    95,    97,    99,   101,   103,   106,   108,   114,
     122,   128,   131,   135,   139,   143,   147,   152,   154,   159,
     161,   163,   167,   169,   171,   173,   175,   177,   179,   181,
     185,   187,   189,   191,   195,   197,   199,   201,   205,   207,
     209,   211,   214,   219,   221,   222,   224,   228,   231
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    41,    -1,    41,    40,    -1,
      45,    -1,    42,    -1,    44,    43,    29,    -1,     4,    -1,
       4,    30,     3,    31,    -1,     4,    32,    43,    -1,     4,
      30,     3,    31,    32,    43,    -1,     6,    -1,     7,    -1,
      44,     4,    33,    46,    34,    49,    -1,    44,     4,    33,
      46,    34,    29,    -1,     7,    -1,    47,    -1,    48,    -1,
      48,    32,    47,    -1,    44,     4,    30,    31,    -1,    44,
       4,    -1,    35,    50,    51,    36,    -1,    42,    50,    -1,
      -1,    52,    51,    -1,    -1,    53,    -1,    49,    -1,    54,
      -1,    55,    -1,    59,    -1,    56,    -1,    57,    -1,    58,
      -1,    72,    -1,    61,    29,    -1,    29,    -1,     8,    33,
      61,    34,    52,    -1,     8,    33,    61,    34,    52,     9,
      52,    -1,    10,    33,    61,    34,    52,    -1,    11,    29,
      -1,    11,    61,    29,    -1,    12,    60,    29,    -1,    13,
      61,    29,    -1,    13,     5,    29,    -1,    60,    37,    62,
      29,    -1,     4,    -1,     4,    30,    61,    31,    -1,    62,
      -1,    64,    -1,    64,    63,    62,    -1,    14,    -1,    15,
      -1,    17,    -1,    16,    -1,    18,    -1,    19,    -1,    66,
      -1,    64,    65,    66,    -1,    24,    -1,    25,    -1,    68,
      -1,    66,    67,    68,    -1,    26,    -1,    27,    -1,    28,
      -1,    33,    61,    34,    -1,     3,    -1,    60,    -1,    69,
      -1,    25,    68,    -1,     4,    33,    70,    34,    -1,    71,
      -1,    -1,    61,    -1,    61,    32,    71,    -1,    20,    29,
      -1,    21,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   108,   108,   119,   120,   130,   131,   140,   157,   162,
     168,   174,   187,   188,   194,   202,   213,   214,   220,   221,
     233,   240,   253,   266,   271,   280,   285,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   307,   313,   321,   329,
     346,   358,   362,   372,   383,   388,   400,   412,   417,   428,
     436,   437,   450,   451,   452,   453,   454,   455,   463,   465,
     476,   477,   484,   485,   496,   497,   498,   505,   506,   511,
     512,   513,   525,   535,   536,   544,   549,   561,   565
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_NUM", "T_ID", "T_STRING", "T_INT",
  "T_VOID", "T_IF", "T_ELSE", "T_WHILE", "T_RETURN", "T_READ", "T_WRITE",
  "T_LE", "T_LT", "T_GE", "T_GT", "T_EQ", "T_NE", "T_BREAK", "T_CONTINUE",
  "'|'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "';'", "'['", "']'",
  "','", "'('", "')'", "'{'", "'}'", "'='", "$accept", "Program",
  "Declaration_List", "Declaration", "Var_Declaration", "Var_List",
  "Type_Specifier", "Fun_Declaration", "Params", "Param_List", "Param",
  "Compound_Stmt", "Local_Declarations", "Statement_List", "Statement",
  "Expression_Stmt", "Selection_Stmt", "Iteration_Stmt", "Return_Stmt",
  "Read_Stmt", "Write_Stmt", "Assignment_Stmt", "Var", "Expression",
  "Simple_Expression", "Relop", "Additive_Expression", "Addop", "Term",
  "Multop", "Factor", "Call", "Args", "Arg_List", "Break_Continue_Stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   124,    38,    43,    45,    42,    47,    37,    59,
      91,    93,    44,    40,    41,   123,   125,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    42,    43,    43,
      43,    43,    44,    44,    45,    45,    46,    46,    47,    47,
      48,    48,    49,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    54,    54,
      55,    56,    56,    57,    58,    58,    59,    60,    60,    61,
      62,    62,    63,    63,    63,    63,    63,    63,    64,    64,
      65,    65,    66,    66,    67,    67,    67,    68,    68,    68,
      68,    68,    69,    70,    70,    71,    71,    72,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     4,
       3,     6,     1,     1,     6,     6,     1,     1,     1,     3,
       4,     2,     4,     2,     0,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     5,     7,
       5,     2,     3,     3,     3,     3,     4,     1,     4,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     2,     4,     1,     0,     1,     3,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,     0,     2,     3,     6,     0,     5,     1,
       4,     8,     0,     0,     0,     0,     7,     0,     8,    10,
      13,     0,     0,    17,    18,     9,    21,     0,     0,     0,
       0,    15,    24,    14,    19,    11,    20,    24,     0,    26,
      23,    68,    47,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,    28,     0,    26,    27,    29,    30,    32,
      33,    34,    31,    69,     0,    49,    50,    58,    62,    70,
      35,     0,    74,     0,     0,    41,    69,     0,    47,     0,
       0,     0,    77,    78,    71,     0,    22,    25,     0,    36,
      52,    53,    55,    54,    56,    57,    60,    61,     0,     0,
      64,    65,    66,     0,     0,    75,     0,    73,     0,     0,
      42,    43,    45,    44,    67,     0,    51,    59,    63,    48,
       0,    72,     0,     0,    46,    76,    38,    40,     0,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,     7,     8,    22,    23,
      24,    53,    39,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    76,    64,    65,    98,    66,    99,    67,   103,
      68,    69,   106,   107,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const yytype_int8 yypact[] =
{
      72,   -73,   -73,     9,   -73,    72,   -73,    16,   -73,   -73,
     -73,    41,   -16,    69,    34,    74,   -73,    51,    45,   -73,
      52,    81,    53,   -73,    56,    58,    61,    35,    72,    34,
      62,   -73,    72,   -73,   -73,   -73,   -73,    72,    34,    11,
     -73,   -73,    12,    59,    63,     8,    90,     1,    66,    68,
      14,   -73,    14,   -73,    64,    11,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,    65,    70,   -73,    44,    39,   -73,   -73,
     -73,    14,    14,    14,    14,   -73,   -73,    75,    71,    76,
      77,    78,   -73,   -73,   -73,    79,   -73,   -73,    14,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,    14,    14,
     -73,   -73,   -73,    14,    67,    80,    82,   -73,    83,    84,
     -73,   -73,   -73,   -73,   -73,    85,   -73,    39,   -73,   -73,
      14,   -73,    11,    11,   -73,   -73,    94,   -73,    11,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,   103,   -73,    17,    -4,    20,   -73,   -73,    87,
     -73,    92,    73,    54,   -72,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -39,   -44,   -45,   -73,   -73,   -73,    21,   -73,
     -48,   -73,   -73,    -9,   -73
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -17
static const yytype_int16 yytable[] =
{
      63,    77,    84,    81,    41,    42,    80,    79,    85,     9,
      19,    41,    42,    16,    41,    42,    63,    41,    42,    43,
      11,    44,    45,    46,    47,    35,    50,   104,   105,   108,
     109,    48,    49,    50,    52,    21,    50,    75,    18,    50,
      51,    52,    71,   115,    52,    72,    32,    52,    21,    37,
     126,   127,    38,   116,    37,   118,   129,    38,    90,    91,
      92,    93,    94,    95,    31,   100,   101,   102,    96,    97,
      32,    13,    17,    14,    15,    13,   105,    14,     1,     2,
       1,    20,    25,    63,    63,    26,   -16,    27,    28,    63,
      29,    30,    73,    36,    78,    82,    74,    83,   119,    89,
      86,    71,    88,   128,   110,   111,   112,   113,    10,    87,
      40,   125,   120,   114,   124,    34,   121,   122,   123,    33,
     117
};

static const yytype_uint8 yycheck[] =
{
      39,    45,    50,    47,     3,     4,     5,    46,    52,     0,
      14,     3,     4,    29,     3,     4,    55,     3,     4,     8,
       4,    10,    11,    12,    13,    29,    25,    71,    72,    73,
      74,    20,    21,    25,    33,    15,    25,    29,     4,    25,
      29,    33,    30,    88,    33,    33,    35,    33,    28,    32,
     122,   123,    32,    98,    37,   103,   128,    37,    14,    15,
      16,    17,    18,    19,    29,    26,    27,    28,    24,    25,
      35,    30,     3,    32,    33,    30,   120,    32,     6,     7,
       6,     7,    31,   122,   123,     4,    34,    34,    32,   128,
      32,    30,    33,    31,     4,    29,    33,    29,    31,    29,
      36,    30,    37,     9,    29,    29,    29,    29,     5,    55,
      37,   120,    32,    34,    29,    28,    34,    34,    34,    27,
      99
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    39,    40,    41,    42,    44,    45,     0,
      40,     4,    43,    30,    32,    33,    29,     3,     4,    43,
       7,    44,    46,    47,    48,    31,     4,    34,    32,    32,
      30,    29,    35,    49,    47,    43,    31,    42,    44,    50,
      50,     3,     4,     8,    10,    11,    12,    13,    20,    21,
      25,    29,    33,    49,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    64,    66,    68,    69,
      72,    30,    33,    33,    33,    29,    60,    61,     4,    60,
       5,    61,    29,    29,    68,    61,    36,    51,    37,    29,
      14,    15,    16,    17,    18,    19,    24,    25,    63,    65,
      26,    27,    28,    67,    61,    61,    70,    71,    61,    61,
      29,    29,    29,    29,    34,    62,    62,    66,    68,    31,
      32,    34,    34,    34,    29,    71,    52,    52,     9,    52
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 108 "lab6.y"
    {PROGRAM = (yyvsp[(1) - (1)].node);}
    break;

  case 3:
#line 119 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 4:
#line 120 "lab6.y"
    {
		(yyval.node) = (yyvsp[(1) - (2)].node);
		(yyval.node) -> next= (yyvsp[(2) - (2)].node);
	}
    break;

  case 5:
#line 130 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 6:
#line 131 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 7:
#line 141 "lab6.y"
    {
					// populate the s1 connected list with the defined type via $1;
					ASTnode *p = (yyvsp[(2) - (3)].node);
					while(p != NULL){
						p->my_data_type = (yyvsp[(1) - (3)].d_type);
						p = p->s1;
					}
					// pointing to the first pointer
					(yyval.node) = (yyvsp[(2) - (3)].node);
				}
    break;

  case 8:
#line 158 "lab6.y"
    { 
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (1)].string);
				}
    break;

  case 9:
#line 163 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (4)].string);
					(yyval.node)->value = (yyvsp[(3) - (4)].value);
				}
    break;

  case 10:
#line 169 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (3)].string);
					(yyval.node)->s1 = (yyvsp[(3) - (3)].node);
				}
    break;

  case 11:
#line 175 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (6)].string);
					(yyval.node)->value = (yyvsp[(3) - (6)].value);
					(yyval.node)->s1 = (yyvsp[(6) - (6)].node);
				}
    break;

  case 12:
#line 187 "lab6.y"
    {(yyval.d_type) = A_INTTYPE;}
    break;

  case 13:
#line 188 "lab6.y"
    {(yyval.d_type) = A_VOIDTYPE;}
    break;

  case 14:
#line 195 "lab6.y"
    { 
					(yyval.node) = ASTCreateNode(A_FUNCTIONDEC);
					(yyval.node)->name = (yyvsp[(2) - (6)].string);
					(yyval.node)->s1 = (yyvsp[(4) - (6)].node);
					(yyval.node)->s2 = (yyvsp[(6) - (6)].node);
					(yyval.node)->my_data_type = (yyvsp[(1) - (6)].d_type);
				}
    break;

  case 15:
#line 203 "lab6.y"
    {// Grad Student function function prototyping case.
					(yyval.node) = ASTCreateNode(A_FUNCTION_PROTO);
					(yyval.node)->name = (yyvsp[(2) - (6)].string);
					(yyval.node)->s1 = (yyvsp[(4) - (6)].node);
					(yyval.node)->my_data_type = (yyvsp[(1) - (6)].d_type);
				}
    break;

  case 16:
#line 213 "lab6.y"
    {(yyval.node) = NULL;}
    break;

  case 17:
#line 214 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 18:
#line 220 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 19:
#line 222 "lab6.y"
    {
					(yyval.node) = (yyvsp[(1) - (3)].node);
					(yyval.node)->next = (yyvsp[(3) - (3)].node);
				}
    break;

  case 20:
#line 234 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_PARAMS);
					(yyval.node)->my_data_type = (yyvsp[(1) - (4)].d_type);
					(yyval.node)->name = (yyvsp[(2) - (4)].string);
					(yyval.node)->value = -1;
				}
    break;

  case 21:
#line 241 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_PARAMS);
					(yyval.node)->my_data_type = (yyvsp[(1) - (2)].d_type);
					(yyval.node)->name = (yyvsp[(2) - (2)].string);
				}
    break;

  case 22:
#line 254 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_COMPOUND);
					(yyval.node)->s1 = (yyvsp[(2) - (4)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (4)].node);					
				}
    break;

  case 23:
#line 267 "lab6.y"
    {
					(yyval.node) = (yyvsp[(1) - (2)].node);
					(yyval.node)->next = (yyvsp[(2) - (2)].node);
				}
    break;

  case 24:
#line 271 "lab6.y"
    {(yyval.node) = NULL;}
    break;

  case 25:
#line 281 "lab6.y"
    {
					(yyval.node) = (yyvsp[(1) - (2)].node);
					(yyval.node)->next = (yyvsp[(2) - (2)].node);
				}
    break;

  case 26:
#line 285 "lab6.y"
    {(yyval.node) = NULL;}
    break;

  case 27:
#line 292 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 28:
#line 293 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 29:
#line 294 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 30:
#line 295 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 31:
#line 296 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 32:
#line 297 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 33:
#line 298 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 34:
#line 299 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 35:
#line 300 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 36:
#line 308 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_EXPR_STAT);
					(yyval.node)->s1 = (yyvsp[(1) - (2)].node);
				}
    break;

  case 37:
#line 313 "lab6.y"
    {(yyval.node) = ASTCreateNode(A_EXPR_STAT);}
    break;

  case 38:
#line 322 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_IF); 
					(yyval.node)->s1 = (yyvsp[(3) - (5)].node);

					(yyval.node)->s2 = ASTCreateNode(A_IFBODY);
					(yyval.node)->s2->s1 = (yyvsp[(5) - (5)].node);
				}
    break;

  case 39:
#line 330 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_IF);    
					(yyval.node)->s1 = (yyvsp[(3) - (7)].node);	// setting expression to the first child of IF Condition

					(yyval.node)->s2 = ASTCreateNode(A_IFBODY);
					(yyval.node)->s2->s1 = (yyvsp[(5) - (7)].node);
					(yyval.node)->s2->s2 = (yyvsp[(7) - (7)].node);				// else statment is set ot first child of else body
				}
    break;

  case 40:
#line 347 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_WHILE_STAT);
					(yyval.node)->s1 = (yyvsp[(3) - (5)].node);
					(yyval.node)->s2 = (yyvsp[(5) - (5)].node);
				}
    break;

  case 41:
#line 359 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_RETURN_STAT);
				}
    break;

  case 42:
#line 363 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_RETURN_STAT);
					(yyval.node)->s1 = (yyvsp[(2) - (3)].node);
				}
    break;

  case 43:
#line 373 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_READ);
					(yyval.node)->s1 = (yyvsp[(2) - (3)].node);
				}
    break;

  case 44:
#line 384 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_WRITE);
					(yyval.node)->s1 = (yyvsp[(2) - (3)].node);
				}
    break;

  case 45:
#line 389 "lab6.y"
    {	
					(yyval.node) = ASTCreateNode(A_WRITE);
					(yyval.node)->name = (yyvsp[(2) - (3)].string);
				}
    break;

  case 46:
#line 401 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_ASSGN_STAT);
					(yyval.node)->s1 = (yyvsp[(1) - (4)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (4)].node);
				}
    break;

  case 47:
#line 413 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_VARUSE);
					(yyval.node)->name = (yyvsp[(1) - (1)].string);
				}
    break;

  case 48:
#line 418 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_VARUSE);
					(yyval.node)->name = (yyvsp[(1) - (4)].string);
					(yyval.node)->s1 = (yyvsp[(3) - (4)].node);
					(yyval.node)->value = -1;
				}
    break;

  case 49:
#line 428 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 50:
#line 436 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 51:
#line 438 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (3)].node);
					(yyval.node)->operator = (yyvsp[(2) - (3)].operators);
				}
    break;

  case 52:
#line 450 "lab6.y"
    {(yyval.operators) = A_LESSEQUAL;}
    break;

  case 53:
#line 451 "lab6.y"
    {(yyval.operators) = A_LESSTHAN;}
    break;

  case 54:
#line 452 "lab6.y"
    {(yyval.operators) = A_GREATERTHAN;}
    break;

  case 55:
#line 453 "lab6.y"
    {(yyval.operators) = A_GREATEREQUAL;}
    break;

  case 56:
#line 454 "lab6.y"
    {(yyval.operators) = A_EQUAL;}
    break;

  case 57:
#line 455 "lab6.y"
    {(yyval.operators) = A_NOTEQUAL;}
    break;

  case 58:
#line 464 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 59:
#line 466 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (3)].node);
					(yyval.node)->operator = (yyvsp[(2) - (3)].operators);
				}
    break;

  case 60:
#line 476 "lab6.y"
    {(yyval.operators) = A_PLUS;}
    break;

  case 61:
#line 477 "lab6.y"
    {(yyval.operators) = A_MINUS;}
    break;

  case 62:
#line 484 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 63:
#line 486 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (3)].node);
					(yyval.node)->operator = (yyvsp[(2) - (3)].operators);
				}
    break;

  case 64:
#line 496 "lab6.y"
    {(yyval.operators) = A_TIMES;}
    break;

  case 65:
#line 497 "lab6.y"
    {(yyval.operators) = A_DEVIDE;}
    break;

  case 66:
#line 498 "lab6.y"
    {(yyval.operators) = A_MOD;}
    break;

  case 67:
#line 505 "lab6.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);}
    break;

  case 68:
#line 507 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_NUM);
					(yyval.node)->value = (yyvsp[(1) - (1)].value);
				}
    break;

  case 69:
#line 511 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 70:
#line 512 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 71:
#line 514 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(2) - (2)].node);
					(yyval.node)->operator = A_UNIRY_MINUS;
				}
    break;

  case 72:
#line 526 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_FUNC_CALL);
					(yyval.node)->name = (yyvsp[(1) - (4)].string);
					(yyval.node)->s1 = (yyvsp[(3) - (4)].node);
				}
    break;

  case 73:
#line 535 "lab6.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 74:
#line 536 "lab6.y"
    {(yyval.node) = NULL;}
    break;

  case 75:
#line 545 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_ARG);
					(yyval.node)->s1 = (yyvsp[(1) - (1)].node);
				}
    break;

  case 76:
#line 550 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_ARG);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->next = (yyvsp[(3) - (3)].node);
				}
    break;

  case 77:
#line 562 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_BREAK);
				}
    break;

  case 78:
#line 566 "lab6.y"
    {
					(yyval.node) = ASTCreateNode(A_CONTINUE);
				}
    break;


/* Line 1267 of yacc.c.  */
#line 2048 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 570 "lab6.y"
	/* end of rules, start of program */

int main()
{ 
	yyparse();
	printf("\nFinished Parsing\n\n\n");
	ASTprint(0, PROGRAM);
}

