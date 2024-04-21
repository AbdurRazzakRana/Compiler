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
#line 1 "lab9.y"

/*
	Author: Abdur Razzak
	Date: April 20, 2024
	Lab: Lab 9
	Modifications:
		Added Level counters
		implemented data type and sub data type
		added support for parameters type chekcing
		array can be sent as function parameter
		fucntion prototype is supported
		tid's are searched for prior occurances before inserting 		 

		Input: This file will take tokens as input
		Output: Will apply Grammer based on token sequence
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ast.h"
#include "symtable.h"

ASTnode *PROGRAM;
// prototying yylex to get ride of compilation waring
int yylex();

// mydebug and linecount are declared in lex file and the yacc file is 
// just using them, therefore, they are declared as extern
extern int mydebug;
extern int linecount;

int LEVEL = 0;  // global context variable to know how depth we are
int OFFSET = 0; // global variable to accumulate required runtime space
int GOFFSET = 0; // global variable to accumulate global variable offset
int maxoffset = 0;  // the largest offset needed of the current function

// when error occurs, it prints the line number
void yyerror (char *s)  /* Called by yyparse on error */
{
  printf ("YACC PARSE ERROR: %s on line number %d\n", s, linecount);
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
#line 53 "lab9.y"
{
	int value;
	char * string;
	ASTnode *node;
	enum AST_MY_DATA_TYPE d_type;
	enum AST_OPERATORS operators;
}
/* Line 193 of yacc.c.  */
#line 194 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 207 "y.tab.c"

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   134

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  133

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
      25,    29,    36,    38,    40,    43,    46,    47,    54,    56,
      58,    60,    64,    69,    72,    73,    79,    82,    83,    86,
      87,    89,    91,    93,    95,    97,    99,   101,   103,   105,
     108,   110,   116,   124,   130,   133,   137,   141,   145,   149,
     154,   156,   161,   163,   165,   169,   171,   173,   175,   177,
     179,   181,   183,   187,   189,   191,   193,   197,   199,   201,
     203,   207,   209,   211,   213,   216,   221,   223,   224,   226,
     230,   233
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    41,    -1,    41,    40,    -1,
      45,    -1,    42,    -1,    44,    43,    29,    -1,     4,    -1,
       4,    30,     3,    31,    -1,     4,    32,    43,    -1,     4,
      30,     3,    31,    32,    43,    -1,     6,    -1,     7,    -1,
      46,    51,    -1,    46,    29,    -1,    -1,    44,     4,    47,
      33,    48,    34,    -1,     7,    -1,    49,    -1,    50,    -1,
      50,    32,    49,    -1,    44,     4,    30,    31,    -1,    44,
       4,    -1,    -1,    35,    52,    53,    54,    36,    -1,    42,
      53,    -1,    -1,    55,    54,    -1,    -1,    56,    -1,    51,
      -1,    57,    -1,    58,    -1,    62,    -1,    59,    -1,    60,
      -1,    61,    -1,    75,    -1,    64,    29,    -1,    29,    -1,
       8,    33,    64,    34,    55,    -1,     8,    33,    64,    34,
      55,     9,    55,    -1,    10,    33,    64,    34,    55,    -1,
      11,    29,    -1,    11,    64,    29,    -1,    12,    63,    29,
      -1,    13,    64,    29,    -1,    13,     5,    29,    -1,    63,
      37,    65,    29,    -1,     4,    -1,     4,    30,    64,    31,
      -1,    65,    -1,    67,    -1,    67,    66,    65,    -1,    14,
      -1,    15,    -1,    17,    -1,    16,    -1,    18,    -1,    19,
      -1,    69,    -1,    67,    68,    69,    -1,    24,    -1,    25,
      -1,    71,    -1,    69,    70,    71,    -1,    26,    -1,    27,
      -1,    28,    -1,    33,    64,    34,    -1,     3,    -1,    63,
      -1,    72,    -1,    25,    71,    -1,     4,    33,    73,    34,
      -1,    74,    -1,    -1,    64,    -1,    64,    32,    74,    -1,
      20,    29,    -1,    21,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   118,   119,   129,   130,   139,   174,   179,
     185,   191,   204,   205,   212,   226,   245,   244,   275,   276,
     282,   283,   295,   315,   341,   341,   364,   369,   378,   383,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   405,
     411,   419,   427,   444,   456,   460,   470,   481,   486,   498,
     522,   543,   582,   590,   591,   615,   616,   617,   618,   619,
     620,   628,   629,   652,   653,   660,   661,   684,   685,   686,
     693,   694,   700,   701,   702,   718,   758,   759,   767,   780,
     800,   804
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
  "Type_Specifier", "Fun_Declaration", "Grad_Fun_Common_Part", "@1",
  "Params", "Param_List", "Param", "Compound_Stmt", "@2",
  "Local_Declarations", "Statement_List", "Statement", "Expression_Stmt",
  "Selection_Stmt", "Iteration_Stmt", "Return_Stmt", "Read_Stmt",
  "Write_Stmt", "Assignment_Stmt", "Var", "Expression",
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
      43,    43,    44,    44,    45,    45,    47,    46,    48,    48,
      49,    49,    50,    50,    52,    51,    53,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    59,    59,    60,    61,    61,    62,
      63,    63,    64,    65,    65,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    70,
      71,    71,    71,    71,    71,    72,    73,    73,    74,    74,
      75,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     4,
       3,     6,     1,     1,     2,     2,     0,     6,     1,     1,
       1,     3,     4,     2,     0,     5,     2,     0,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     5,     7,     5,     2,     3,     3,     3,     3,     4,
       1,     4,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     2,     4,     1,     0,     1,     3,
       2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,     0,     2,     3,     6,     0,     5,     0,
       1,     4,     8,     0,    15,    24,    14,     0,     0,     0,
       7,    27,     0,     8,    10,     0,    27,     0,    29,     9,
      13,     0,     0,    19,    20,    26,    71,    50,     0,     0,
       0,     0,     0,     0,     0,     0,    40,     0,    31,     0,
      29,    30,    32,    33,    35,    36,    37,    34,    72,     0,
      52,    53,    61,    65,    73,    38,     0,    23,    17,     0,
       0,    77,     0,     0,    44,    72,     0,    50,     0,     0,
       0,    80,    81,    74,     0,    25,    28,     0,    39,    55,
      56,    58,    57,    59,    60,    63,    64,     0,     0,    67,
      68,    69,     0,    11,     0,    21,     0,    78,     0,    76,
       0,     0,    45,    46,    48,    47,    70,     0,    54,    62,
      66,    22,    51,     0,    75,     0,     0,    49,    79,    41,
      43,     0,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    13,     7,     8,     9,    19,
      32,    33,    34,    48,    21,    28,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    75,    59,    60,    97,    61,
      98,    62,   102,    63,    64,   108,   109,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int8 yypact[] =
{
      14,   -81,   -81,    30,   -81,    14,   -81,    42,   -81,   -23,
     -81,   -81,    46,    22,   -81,   -81,   -81,    51,    63,    25,
     -81,    14,    43,    17,   -81,    36,    14,    63,    15,    41,
      49,    82,    53,   -81,    56,   -81,   -81,   -19,    57,    58,
      12,    85,    52,    64,    65,    35,   -81,    35,   -81,    59,
      15,   -81,   -81,   -81,   -81,   -81,   -81,   -81,    55,    67,
     -81,    47,    54,   -81,   -81,   -81,    63,    69,   -81,    14,
      35,    35,    35,    35,   -81,   -81,    71,    72,    75,    76,
      77,   -81,   -81,   -81,    73,   -81,   -81,    35,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,    35,    35,   -81,
     -81,   -81,    35,   -81,    70,   -81,    78,    79,    74,   -81,
      80,    81,   -81,   -81,   -81,   -81,   -81,    83,   -81,    54,
     -81,   -81,   -81,    35,   -81,    15,    15,   -81,   -81,   101,
     -81,    15,   -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   108,   -81,     3,   -14,   -16,   -81,   -81,   -81,
     -81,    48,   -81,   107,   -81,    92,    84,   -56,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -28,   -39,   -80,   -81,   -81,
     -81,    21,   -81,   -43,   -81,   -81,    -3,   -81
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -19
static const yytype_int16 yytable[] =
{
      58,    76,    83,    80,    24,    27,    14,   117,    84,    31,
      27,    70,    15,    78,    71,    36,    37,   118,    36,    37,
       1,     2,    58,    38,    26,    39,    40,    41,    42,    26,
      10,   106,   107,   110,   111,    43,    44,    45,    36,    37,
      45,    74,     1,    30,    46,    47,    12,    17,    47,    18,
      15,    20,   103,    31,    22,    36,    37,    79,    25,   120,
      45,    89,    90,    91,    92,    93,    94,    23,    47,   129,
     130,    95,    96,    66,    29,   132,    17,    45,    18,   -16,
      99,   100,   101,   -18,   107,    47,    67,    68,    69,    77,
      72,    73,    87,    81,    82,    85,    88,    58,    58,   104,
     112,   121,    70,    58,   113,   114,   115,   116,   124,   122,
     131,   123,   127,    11,   125,   126,    16,   105,    35,   119,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
      28,    40,    45,    42,    18,    21,    29,    87,    47,    25,
      26,    30,    35,    41,    33,     3,     4,    97,     3,     4,
       6,     7,    50,     8,    21,    10,    11,    12,    13,    26,
       0,    70,    71,    72,    73,    20,    21,    25,     3,     4,
      25,    29,     6,     7,    29,    33,     4,    30,    33,    32,
      35,    29,    66,    69,     3,     3,     4,     5,    33,   102,
      25,    14,    15,    16,    17,    18,    19,     4,    33,   125,
     126,    24,    25,    32,    31,   131,    30,    25,    32,    33,
      26,    27,    28,    34,   123,    33,     4,    34,    32,     4,
      33,    33,    37,    29,    29,    36,    29,   125,   126,    30,
      29,    31,    30,   131,    29,    29,    29,    34,    34,    31,
       9,    32,    29,     5,    34,    34,     9,    69,    26,    98,
     123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    39,    40,    41,    42,    44,    45,    46,
       0,    40,     4,    43,    29,    35,    51,    30,    32,    47,
      29,    52,     3,     4,    43,    33,    42,    44,    53,    31,
       7,    44,    48,    49,    50,    53,     3,     4,     8,    10,
      11,    12,    13,    20,    21,    25,    29,    33,    51,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    67,    69,    71,    72,    75,    32,     4,    34,    32,
      30,    33,    33,    33,    29,    63,    64,     4,    63,     5,
      64,    29,    29,    71,    64,    36,    54,    37,    29,    14,
      15,    16,    17,    18,    19,    24,    25,    66,    68,    26,
      27,    28,    70,    43,    30,    49,    64,    64,    73,    74,
      64,    64,    29,    29,    29,    29,    34,    65,    65,    69,
      71,    31,    31,    32,    34,    34,    34,    29,    74,    55,
      55,     9,    55
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
#line 107 "lab9.y"
    {PROGRAM = (yyvsp[(1) - (1)].node);}
    break;

  case 3:
#line 118 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 4:
#line 119 "lab9.y"
    {
		(yyval.node) = (yyvsp[(1) - (2)].node);
		(yyval.node) -> next= (yyvsp[(2) - (2)].node);
	}
    break;

  case 5:
#line 129 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 6:
#line 130 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 7:
#line 140 "lab9.y"
    {
					// populate the s1 connected list with the defined type via $1;
					ASTnode *p = (yyvsp[(2) - (3)].node);
					while(p != NULL){
						p->my_data_type = (yyvsp[(1) - (3)].d_type);
						// check if varaible in the list if its already declared at same level
						if (Search(p->name, LEVEL, 0) != NULL) {
							// symbol already defined, should barf
							yyerror(p->name);
							yyerror("Symbol already defined");
							exit(1);
						}
						// symbol not declared at LEVEL
						if(p->value == 0) { // if its an integer
							p->symbol = Insert(p->name, p->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // sub type will be scalar
							OFFSET = OFFSET + 1; // 1 size added for the offset
						}
						else { // for the array
							p->symbol = Insert(p->name, p->my_data_type, SYM_ARRAY, LEVEL, p->value, OFFSET); // sub type is array
							OFFSET = OFFSET + p->value; // size of the array will be added in offset
						}

						p = p->s1;
					}
					// pointing to the first pointer
					(yyval.node) = (yyvsp[(2) - (3)].node);
				}
    break;

  case 8:
#line 175 "lab9.y"
    { 
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (1)].string);
				}
    break;

  case 9:
#line 180 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (4)].string);
					(yyval.node)->value = (yyvsp[(3) - (4)].value);
				}
    break;

  case 10:
#line 186 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (3)].string);
					(yyval.node)->s1 = (yyvsp[(3) - (3)].node);
				}
    break;

  case 11:
#line 192 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_VARDEC);
					(yyval.node)->name = (yyvsp[(1) - (6)].string);
					(yyval.node)->value = (yyvsp[(3) - (6)].value);
					(yyval.node)->s1 = (yyvsp[(6) - (6)].node);
				}
    break;

  case 12:
#line 204 "lab9.y"
    {(yyval.d_type) = A_INTTYPE;}
    break;

  case 13:
#line 205 "lab9.y"
    {(yyval.d_type) = A_VOIDTYPE;}
    break;

  case 14:
#line 213 "lab9.y"
    { 
					// function declaration with compound statement
					(yyval.node) = ASTCreateNode(A_FUNCTIONDEC);
					(yyval.node)->my_data_type = (yyvsp[(1) - (2)].node)->my_data_type; // function type is from the declaration in function head part
					(yyval.node)->name = (yyvsp[(1) - (2)].node)->name; // name will be from head part described at Grad_Fun_Common_Part
					(yyval.node)->s1 = (yyvsp[(1) - (2)].node)->s1;
					(yyval.node)->s2 = (yyvsp[(2) - (2)].node);
					(yyval.node)->symbol = Search((yyvsp[(1) - (2)].node)->name, LEVEL, 0);
					(yyval.node)->symbol->offset = maxoffset;  // setting max offset as the offset for the function

					// During walkout from the function, set back the counters for global varaibles
					OFFSET = GOFFSET;
				}
    break;

  case 15:
#line 227 "lab9.y"
    {// Grad Student function prototyping case.
					(yyval.node) = ASTCreateNode(A_FUNCTION_PROTO);
					(yyval.node)->my_data_type = (yyvsp[(1) - (2)].node)->my_data_type;  //function type is described at Grad_Fun_Common_Part
					(yyval.node)->name = (yyvsp[(1) - (2)].node)->name; // same as previous
					(yyval.node)->s1 = (yyvsp[(1) - (2)].node)->s1;

					(yyval.node)->symbol = Search((yyvsp[(1) - (2)].node)->name, LEVEL, 0);
					(yyval.node)->symbol->offset = maxoffset;  // setting max offset as the offset for the function

					// Even though we are not going into the function for prototyping case
					OFFSET = GOFFSET;
				}
    break;

  case 16:
#line 245 "lab9.y"
    {
					if (Search((yyvsp[(2) - (2)].string), LEVEL, 0) != NULL) { // check if the function has been defined before
						yyerror((yyvsp[(2) - (2)].string));  // T_ID has alredy been used, should barf
						yyerror("function name already in use");
						exit(1);
					}

					// not in sym table, should be inserted
					Insert((yyvsp[(2) - (2)].string), (yyvsp[(1) - (2)].d_type), SYM_FUNCTION, LEVEL, 0, 0);

					// At the time of walkin to the function resettting counters
					/*while chekcing assignment testcases, setting offset = 0 will match the outputs
					however, while matching with ~scooper/lab7 output, offset needs to be set 2
					In class, Prof. Cooper clarified that setting 0 or 2 to the offset, both works */
					GOFFSET = OFFSET;
					OFFSET = 2;
					maxoffset = OFFSET;
				}
    break;

  case 17:
#line 264 "lab9.y"
    {
					Search((yyvsp[(2) - (6)].string), LEVEL, 0) -> fparms = (yyvsp[(5) - (6)].node);  // setting pointer to the function parameters 

					(yyval.node) = ASTCreateNode(A_FUNCTION_COMMON); // setting up name, type and s1 for both prototype and func dec
					(yyval.node)->my_data_type = (yyvsp[(1) - (6)].d_type);
					(yyval.node)->name = (yyvsp[(2) - (6)].string);
					(yyval.node)->s1 = (yyvsp[(5) - (6)].node);
				}
    break;

  case 18:
#line 275 "lab9.y"
    {(yyval.node) = NULL;}
    break;

  case 19:
#line 276 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 20:
#line 282 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 21:
#line 284 "lab9.y"
    {
					(yyval.node) = (yyvsp[(1) - (3)].node);
					(yyval.node)->next = (yyvsp[(3) - (3)].node);
				}
    break;

  case 22:
#line 296 "lab9.y"
    {
					// check if name is already used
					// level+1 because varaibles in parameters will be used as child level inside function
					if (Search((yyvsp[(2) - (4)].string), LEVEL+1, 0) != NULL){
						// name already in the symbol table, can not have 2 varaibles with same name, barf
						yyerror((yyvsp[(2) - (4)].string));
						yyerror("Parameter already used");
						exit(1);
					}
					// varaible is not used before, creating node
					(yyval.node) = ASTCreateNode(A_PARAMS);
					(yyval.node)->my_data_type = (yyvsp[(1) - (4)].d_type);
					(yyval.node)->name = (yyvsp[(2) - (4)].string);
					(yyval.node)->value = -1;

					// inserting the node into symbol table
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyval.node)->my_data_type, SYM_ARRAY, LEVEL+1, 1, OFFSET); // level +1 because they are at child level
					OFFSET = OFFSET + 1; // offset increased for insertion
				}
    break;

  case 23:
#line 316 "lab9.y"
    {
					// check if name is already used
					// level+1 because varaibles in parameters will be used as child level inside function
					if (Search((yyvsp[(2) - (2)].string), LEVEL+1, 0) != NULL){
						// name already in the symbol table, can not have 2 varaibles with same name, barf
						yyerror((yyvsp[(2) - (2)].string));
						yyerror("Parameter already used");
						exit(1);
					}
					// varaible is not used before, creating node
					(yyval.node) = ASTCreateNode(A_PARAMS);
					(yyval.node)->my_data_type = (yyvsp[(1) - (2)].d_type);
					(yyval.node)->name = (yyvsp[(2) - (2)].string);
					
					// inserting the node into symbol table
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyval.node)->my_data_type, SYM_SCALAR, LEVEL+1, 1, OFFSET); // ids are in child level; level + 1
					OFFSET = OFFSET + 1; // one up for the insertion
				}
    break;

  case 24:
#line 341 "lab9.y"
    {LEVEL++;}
    break;

  case 25:
#line 342 "lab9.y"
    {
					// Before walkin to the function, level +1
					(yyval.node) = ASTCreateNode(A_COMPOUND);
					(yyval.node)->s1 = (yyvsp[(3) - (5)].node);
					(yyval.node)->s2 = (yyvsp[(4) - (5)].node);
					Display();
					// setting the maxoffset to the higher counter
					if (OFFSET > maxoffset)
						maxoffset = OFFSET;
					// we don't need the offset that are deleted
					OFFSET -= Delete(LEVEL);

					// at the time of walk out from the function, level -1 
					LEVEL--;
				}
    break;

  case 26:
#line 365 "lab9.y"
    {
					(yyval.node) = (yyvsp[(1) - (2)].node);
					(yyval.node)->next = (yyvsp[(2) - (2)].node);
				}
    break;

  case 27:
#line 369 "lab9.y"
    {(yyval.node) = NULL;}
    break;

  case 28:
#line 379 "lab9.y"
    {
					(yyval.node) = (yyvsp[(1) - (2)].node);
					(yyval.node)->next = (yyvsp[(2) - (2)].node);
				}
    break;

  case 29:
#line 383 "lab9.y"
    {(yyval.node) = NULL;}
    break;

  case 30:
#line 390 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 31:
#line 391 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 32:
#line 392 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 33:
#line 393 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 34:
#line 394 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 35:
#line 395 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 36:
#line 396 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 37:
#line 397 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 38:
#line 398 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 39:
#line 406 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_EXPR_STAT);
					(yyval.node)->s1 = (yyvsp[(1) - (2)].node);
				}
    break;

  case 40:
#line 411 "lab9.y"
    {(yyval.node) = ASTCreateNode(A_EXPR_STAT);}
    break;

  case 41:
#line 420 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_IF); 
					(yyval.node)->s1 = (yyvsp[(3) - (5)].node);

					(yyval.node)->s2 = ASTCreateNode(A_IFBODY);
					(yyval.node)->s2->s1 = (yyvsp[(5) - (5)].node);
				}
    break;

  case 42:
#line 428 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_IF);    
					(yyval.node)->s1 = (yyvsp[(3) - (7)].node);	// setting expression to the first child of IF Condition

					(yyval.node)->s2 = ASTCreateNode(A_IFBODY);
					(yyval.node)->s2->s1 = (yyvsp[(5) - (7)].node);
					(yyval.node)->s2->s2 = (yyvsp[(7) - (7)].node);				// else statment is set ot first child of else body
				}
    break;

  case 43:
#line 445 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_WHILE_STAT);
					(yyval.node)->s1 = (yyvsp[(3) - (5)].node);
					(yyval.node)->s2 = (yyvsp[(5) - (5)].node);
				}
    break;

  case 44:
#line 457 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_RETURN_STAT);
				}
    break;

  case 45:
#line 461 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_RETURN_STAT);
					(yyval.node)->s1 = (yyvsp[(2) - (3)].node);
				}
    break;

  case 46:
#line 471 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_READ);
					(yyval.node)->s1 = (yyvsp[(2) - (3)].node);
				}
    break;

  case 47:
#line 482 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_WRITE);
					(yyval.node)->s1 = (yyvsp[(2) - (3)].node);
				}
    break;

  case 48:
#line 487 "lab9.y"
    {	
					(yyval.node) = ASTCreateNode(A_WRITE);
					(yyval.node)->name = (yyvsp[(2) - (3)].string);
				}
    break;

  case 49:
#line 499 "lab9.y"
    {

					if((yyvsp[(1) - (4)].node)->my_data_type != (yyvsp[(3) - (4)].node)->my_data_type){
						// type is not the same
						printf("%s type: %d\n", (yyvsp[(1) - (4)].node)->name, (yyvsp[(1) - (4)].node)->my_data_type);
						printf("%s type: %d\n", (yyvsp[(3) - (4)].node)->name, (yyvsp[(3) - (4)].node)->my_data_type);
						yyerror("Type Mismatch");
						exit(1);
					}
					(yyval.node) = ASTCreateNode(A_ASSGN_STAT);
					(yyval.node)->s1 = (yyvsp[(1) - (4)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (4)].node);

					(yyval.node)->name = CreateTemp(); // creating temporary register to hold the operation
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[(1) - (4)].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register
					OFFSET = OFFSET + 1; // one up for the insertion
				}
    break;

  case 50:
#line 523 "lab9.y"
    {
					struct SymbTab *p = Search ((yyvsp[(1) - (1)].string), LEVEL, 	1);
					if (p == NULL) {
						// reference variable is trying to used but not in sym table
						yyerror((yyvsp[(1) - (1)].string));
						yyerror("symbol used but not defined");
						exit(1);
					}
				// sub tuype can be array or scalar both, only barf for function type
					if(p->SubType == SYM_FUNCTION){
						// reference variable to a non scaler variable
						yyerror((yyvsp[(1) - (1)].string));
						yyerror("symbol must be either SCALAR or ARRAY");
						exit(1);
					}
					(yyval.node) = ASTCreateNode(A_VARUSE);
					(yyval.node)->name = (yyvsp[(1) - (1)].string);
					(yyval.node)->my_data_type = p->Declared_Type; // data type is declared at the begining; y[2] shold be int
					(yyval.node)->symbol = p;
				}
    break;

  case 51:
#line 544 "lab9.y"
    {
					struct SymbTab *p = Search ((yyvsp[(1) - (4)].string), LEVEL,	1);
					if (p == NULL) {
						// reference variable is trying to used but not in sym table
						yyerror((yyvsp[(1) - (4)].string));
						yyerror("symbol used but not defined");
						exit(1);
					}

					if(p->SubType != SYM_ARRAY){
						// reference variable to an non array variable
						yyerror((yyvsp[(1) - (4)].string));
						yyerror("symbol must be a ARRAY");
						exit(1);
					}

					// p should be array here

					(yyval.node) = ASTCreateNode(A_VARUSE);
					(yyval.node)->name = (yyvsp[(1) - (4)].string);
					(yyval.node)->s1 = (yyvsp[(3) - (4)].node);
					(yyval.node)->value = -1; // -1 to call the Expression in ast.c
					(yyval.node)->symbol = p;
					(yyval.node)->my_data_type = p->Declared_Type;
					
					// for the Grad case: f(int x){}    f(y[0])
					// though y is array, but the output y[0] type has to be integer and scaller.
					// if we change the $$->symbol->SubType to SCALAR, it chnages entire array type in the symbol table
					// because of the pointer.
					// hence to support this scenairo, careated a copy and changed the subtype into the coppied instance
					(yyval.node)->symbol = (struct SymbTab*)malloc(sizeof(struct SymbTab));
					*((yyval.node)->symbol) = *p;
					(yyval.node)->symbol->SubType = SYM_SCALAR;
				}
    break;

  case 52:
#line 582 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 53:
#line 590 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 54:
#line 592 "lab9.y"
    {
					if((yyvsp[(1) - (3)].node)->my_data_type != (yyvsp[(3) - (3)].node)->my_data_type){
						// type is not the same
						yyerror("Type Mismatch");
						exit(1);
					}

					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (3)].node);
					(yyval.node)->operator = (yyvsp[(2) - (3)].operators);
					(yyval.node)->my_data_type = (yyvsp[(1) - (3)].node)->my_data_type;
					
					(yyval.node)->name = CreateTemp(); // to hold the relop operation, using a register
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[(1) - (3)].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register 
					OFFSET = OFFSET + 1;
				}
    break;

  case 55:
#line 615 "lab9.y"
    {(yyval.operators) = A_LESSEQUAL;}
    break;

  case 56:
#line 616 "lab9.y"
    {(yyval.operators) = A_LESSTHAN;}
    break;

  case 57:
#line 617 "lab9.y"
    {(yyval.operators) = A_GREATERTHAN;}
    break;

  case 58:
#line 618 "lab9.y"
    {(yyval.operators) = A_GREATEREQUAL;}
    break;

  case 59:
#line 619 "lab9.y"
    {(yyval.operators) = A_EQUAL;}
    break;

  case 60:
#line 620 "lab9.y"
    {(yyval.operators) = A_NOTEQUAL;}
    break;

  case 61:
#line 628 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 62:
#line 630 "lab9.y"
    {
					// checking both of the operands are in same type
					if((yyvsp[(1) - (3)].node)->my_data_type != (yyvsp[(3) - (3)].node)->my_data_type){
						// type is not the same
						yyerror("Type Mismatch");
						exit(1);
					}
					// type is same, we can do the operation
					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (3)].node);
					(yyval.node)->operator = (yyvsp[(2) - (3)].operators);
					(yyval.node)->my_data_type = (yyvsp[(1) - (3)].node)->my_data_type;

					(yyval.node)->name = CreateTemp(); // using register to hold the add operation
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[(1) - (3)].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register
					OFFSET = OFFSET + 1;
				}
    break;

  case 63:
#line 652 "lab9.y"
    {(yyval.operators) = A_PLUS;}
    break;

  case 64:
#line 653 "lab9.y"
    {(yyval.operators) = A_MINUS;}
    break;

  case 65:
#line 660 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 66:
#line 662 "lab9.y"
    {
					// checking both of the operands are in same type
					if((yyvsp[(1) - (3)].node)->my_data_type != (yyvsp[(3) - (3)].node)->my_data_type){
						// type is not the same
						yyerror("Type Mismatch");
						exit(1);
					}
					// we can do the operation
					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->s2 = (yyvsp[(3) - (3)].node);
					(yyval.node)->operator = (yyvsp[(2) - (3)].operators);
					(yyval.node)->my_data_type = (yyvsp[(1) - (3)].node)->my_data_type;

					(yyval.node)->name = CreateTemp(); // using register to hold the result
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[(1) - (3)].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register
					OFFSET = OFFSET + 1;
				}
    break;

  case 67:
#line 684 "lab9.y"
    {(yyval.operators) = A_TIMES;}
    break;

  case 68:
#line 685 "lab9.y"
    {(yyval.operators) = A_DEVIDE;}
    break;

  case 69:
#line 686 "lab9.y"
    {(yyval.operators) = A_MOD;}
    break;

  case 70:
#line 693 "lab9.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);}
    break;

  case 71:
#line 695 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_NUM);
					(yyval.node)->value = (yyvsp[(1) - (1)].value);
					(yyval.node)->my_data_type = A_INTTYPE; // number returns int
				}
    break;

  case 72:
#line 700 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 73:
#line 701 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 74:
#line 703 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->s1 = (yyvsp[(2) - (2)].node);
					(yyval.node)->operator = A_UNIRY_MINUS;

					(yyval.node)->name = CreateTemp(); // unary minus operation in register
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[(2) - (2)].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
					OFFSET = OFFSET + 1;
				}
    break;

  case 75:
#line 719 "lab9.y"
    {  // check is the function is in the symbol table
					struct SymbTab *p = Search((yyvsp[(1) - (4)].string), 0, 0);
					if(p == NULL){
						// symbol not found in table, can not call a function without declaring, barf
						yyerror((yyvsp[(1) - (4)].string));
						yyerror("function name not defined");
						exit(1);
					}
					// name is  found in the table and its a function

					// check calling name is funciton type or not
					if (p->SubType != SYM_FUNCTION) {
						// symbol not defined as a function, barf
						yyerror((yyvsp[(1) - (4)].string));
						yyerror("is not defined as a function");
						exit(1);
					}

					// check to see that the formal and actual parameters are
					// same length and type
					if(check_params((yyvsp[(3) - (4)].node), p->fparms) == 0){
						// length and type did not match, should barf;
						yyerror((yyvsp[(1) - (4)].string));
						yyerror("Actual and Formals do not match");
						exit(1);
					}
					// name found in the list, it defined as function and 
					// params are same type and length as well
					// creating node for function call
					(yyval.node) = ASTCreateNode(A_FUNC_CALL);
					(yyval.node)->name = (yyvsp[(1) - (4)].string);
					(yyval.node)->my_data_type = p->Declared_Type;
					(yyval.node)->s1 = (yyvsp[(3) - (4)].node);
					(yyval.node)->symbol = p;
				}
    break;

  case 76:
#line 758 "lab9.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 77:
#line 759 "lab9.y"
    {(yyval.node) = NULL;}
    break;

  case 78:
#line 768 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_ARG);
					(yyval.node)->s1 = (yyvsp[(1) - (1)].node);
					(yyval.node)->my_data_type = (yyvsp[(1) - (1)].node)->my_data_type;
					
					(yyval.node)->name = CreateTemp();
					// insert with subtype
					// if subtype does not have such as T_NUM, insert scaler
					enum SYMBOL_SUBTYPE subType = (yyvsp[(1) - (1)].node)->symbol != NULL ? (yyvsp[(1) - (1)].node)->symbol->SubType : SYM_SCALAR;
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[(1) - (1)].node)->my_data_type, subType, LEVEL, 1, OFFSET); // final sub type will be whatever got from the expression
					OFFSET = OFFSET + 1;
				}
    break;

  case 79:
#line 781 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_ARG);
					(yyval.node)->s1 = (yyvsp[(1) - (3)].node);
					(yyval.node)->next = (yyvsp[(3) - (3)].node);
					(yyval.node)->my_data_type = (yyvsp[(1) - (3)].node)->my_data_type;

					(yyval.node)->name = CreateTemp();
					// insert with subtype
					// if subtype does not have such as T_NUM, insert scaler
					enum SYMBOL_SUBTYPE subType = (yyvsp[(1) - (3)].node)->symbol != NULL ? (yyvsp[(1) - (3)].node)->symbol->SubType : SYM_SCALAR;
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[(1) - (3)].node)->my_data_type, subType, LEVEL, 1, OFFSET);// final sub type is form the expression 
					OFFSET = OFFSET + 1;
				}
    break;

  case 80:
#line 801 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_BREAK);
				}
    break;

  case 81:
#line 805 "lab9.y"
    {
					(yyval.node) = ASTCreateNode(A_CONTINUE);
				}
    break;


/* Line 1267 of yacc.c.  */
#line 2303 "y.tab.c"
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


#line 809 "lab9.y"
	/* end of rules, start of program */

int main()
{ 
	yyparse();
	printf("\nFinished Parsing\n\n\n");

	Display();  // show global varaible functions
	printf("\n\nAST PRINT\n\n");
	ASTprint(0, PROGRAM);
}
