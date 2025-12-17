/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "test.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);

/* AST 節點類型 */
typedef enum {
    AST_NUM, AST_BOOL, AST_VAR, AST_OP, AST_IF, AST_FUN, AST_CALL
} ASTType;

/* AST 節點 */
typedef struct ASTNode {
    ASTType type;
    union {
        int num;
        int bool_val;
        char *var;
        struct {
            char *op;
            struct ASTNode **args;
            int arg_count;
        } op;
        struct {
            struct ASTNode *cond;
            struct ASTNode *then_exp;
            struct ASTNode *else_exp;
        } if_node;
        struct {
            char **params;
            int param_count;
            struct ASTNode *body;
        } fun;
        struct {
            struct ASTNode *func;
            struct ASTNode **args;
            int arg_count;
        } call;
    } data;
} ASTNode;

/* 運行時值 */
typedef struct Value {
    enum { VAL_NUM, VAL_BOOL, VAL_FUNC } type;
    union {
        int num;
        int bool_val;
        struct {
            char **params;
            int param_count;
            ASTNode *body;
            struct Env *closure;
        } func;
    } data;
} Value;

/* 環境 */
typedef struct Env {
    char *name;
    Value *value;
    struct Env *next;
} Env;

Env *global_env = NULL;

/* 函式宣告 */
ASTNode* make_num(int n);
ASTNode* make_bool(int b);
ASTNode* make_var(char *name);
ASTNode* make_op(char *op, ASTNode **args, int count);
ASTNode* make_if(ASTNode *cond, ASTNode *then_exp, ASTNode *else_exp);
ASTNode* make_fun(char **params, int count, ASTNode *body);
ASTNode* make_call(ASTNode *func, ASTNode **args, int count);
Value* eval(ASTNode *ast, Env *env);
void define_var(Env **env, char *name, Value *val);
Value* lookup_var(Env *env, char *name);


#line 147 "test.tab.c" /* yacc.c:339  */

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
   by #include "test.tab.h".  */
#ifndef YY_YY_TEST_TAB_H_INCLUDED
# define YY_YY_TEST_TAB_H_INCLUDED
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
    NUMBER = 258,
    BOOL_VAL = 259,
    ID = 260,
    PRINT_NUM = 261,
    PRINT_BOOL = 262,
    MOD = 263,
    AND = 264,
    OR = 265,
    NOT = 266,
    DEFINE = 267,
    FUN = 268,
    IF = 269
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 82 "test.y" /* yacc.c:355  */

    int num_val;
    int bool_val;
    char *string;
    struct ASTNode *ast;
    struct {
        struct ASTNode **items;
        int count;
    } ast_list;
    struct {
        char **items;
        int count;
    } str_list;

#line 217 "test.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TEST_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 232 "test.tab.c" /* yacc.c:358  */

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
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  103

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   269

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
      15,    16,    19,    17,     2,    18,     2,    20,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      22,    23,    21,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   116,   117,   120,   124,   125,   128,   134,
     142,   145,   148,   151,   152,   153,   154,   155,   158,   158,
     158,   158,   158,   159,   159,   159,   162,   167,   175,   180,
     188,   196,   204,   212,   217,   217,   217,   220,   225,   230,
     237,   258,   263,   264,   270,   275,   282,   285,   290,   295,
     299,   306,   311
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "BOOL_VAL", "ID", "PRINT_NUM",
  "PRINT_BOOL", "MOD", "AND", "OR", "NOT", "DEFINE", "FUN", "IF", "'('",
  "')'", "'+'", "'-'", "'*'", "'/'", "'>'", "'<'", "'='", "$accept",
  "PROGRAM", "STMTS", "STMT", "PRINT_STMT", "EXP", "NUM_OP", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "MODULUS", "GREATER", "SMALLER", "EQUAL",
  "LOGICAL_OP", "AND_OP", "OR_OP", "NOT_OP", "DEF_STMT", "FUN_EXP",
  "FUN_IDS", "IDS", "FUN_CALL", "IF_EXP", "PARAMS", "EXPS", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    40,    41,    43,    45,    42,
      47,    62,    60,    61
};
# endif

#define YYPACT_NINF -14

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-14)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     120,   -14,   -14,   -14,     2,     3,   120,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   133,   133,
     133,   133,   133,   133,    -1,   -13,   133,    -8,   133,   133,
     133,   133,   133,   133,   133,   -14,   -14,   -14,    88,    67,
      11,    15,   133,   -14,    91,    94,    19,   133,    35,   133,
     133,    97,   133,   111,   133,   133,   133,   114,   117,   -14,
     -14,   -14,   -14,    21,   -14,   -14,   -14,   -14,    28,   -14,
     -14,    40,    31,   133,   -14,    33,   -14,    34,    37,    42,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,    53,   -14,   -14,
     -14,   -14,   -14
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    11,    10,    12,     0,     0,     2,     3,     7,     5,
      13,    18,    19,    20,    21,    22,    23,    24,    25,    14,
      34,    35,    36,     6,    15,    16,    17,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,     1,     4,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
      50,     8,     9,     0,    37,    52,    38,    39,     0,    44,
      43,     0,     0,     0,    26,     0,    28,     0,     0,     0,
      33,    46,    30,    40,    45,    42,    41,     0,    27,    29,
      31,    32,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -14,   -14,   -14,    12,   -14,     0,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
      -3,   -14,   -14,   -14,   -14,    25,    -6
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    53,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    59,    81,    25,    26,    48,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       9,    45,    58,    46,    57,    35,     9,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    47,    38,
      39,    40,    41,    42,    43,    44,    55,    71,    50,    51,
      52,    72,    61,    56,    63,    77,    60,    92,    67,    62,
      79,    64,    65,    66,    93,    94,    45,    96,    70,    98,
      99,    80,    73,   100,    75,    75,    95,    78,   101,    82,
      83,    75,    85,    75,    87,    88,    89,    75,    70,   102,
      68,     0,    27,     0,     0,    30,    31,    32,    33,     0,
      35,    36,    37,    97,    38,    39,    40,    41,    42,    43,
      44,     1,     2,     3,     1,     2,     3,     1,     2,     3,
       1,     2,     3,    49,    69,     0,    49,    74,     0,    49,
      76,     0,    49,    84,     1,     2,     3,     1,     2,     3,
       1,     2,     3,     1,     2,     3,    49,    86,     0,    49,
      90,     0,    49,    91,     0,     4,     1,     2,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49
};

static const yytype_int8 yycheck[] =
{
       0,     4,    15,     0,     5,    13,     6,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     6,    17,
      18,    19,    20,    21,    22,    23,    32,    16,    28,    29,
      30,    16,    38,    33,    40,    16,    36,    16,    44,    39,
       5,    41,    42,    43,    16,     5,    49,    16,    48,    16,
      16,    16,    52,    16,    54,    55,    16,    57,    16,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    16,
      45,    -1,     5,    -1,    -1,     8,     9,    10,    11,    -1,
      13,    14,    15,    83,    17,    18,    19,    20,    21,    22,
      23,     3,     4,     5,     3,     4,     5,     3,     4,     5,
       3,     4,     5,    15,    16,    -1,    15,    16,    -1,    15,
      16,    -1,    15,    16,     3,     4,     5,     3,     4,     5,
       3,     4,     5,     3,     4,     5,    15,    16,    -1,    15,
      16,    -1,    15,    16,    -1,    15,     3,     4,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    15,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    47,    48,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    17,    18,
      19,    20,    21,    22,    23,    44,     0,    27,    49,    15,
      29,    29,    29,    29,    50,    50,    29,     5,    15,    45,
      29,    50,    29,    50,    29,    29,    29,    50,    49,    16,
      29,    16,    16,    29,    16,    29,    16,    16,    29,     5,
      16,    46,    29,    29,    16,    29,    16,    29,    29,    29,
      16,    16,    16,    16,     5,    16,    16,    29,    16,    16,
      16,    16,    16
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    24,    25,    26,    26,    27,    27,    27,    28,    28,
      29,    29,    29,    29,    29,    29,    29,    29,    30,    30,
      30,    30,    30,    30,    30,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    39,    39,    40,    41,    42,
      43,    44,    45,    45,    46,    46,    47,    47,    48,    49,
      49,    50,    50
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     5,     4,     5,
       5,     5,     5,     4,     1,     1,     1,     4,     4,     4,
       5,     5,     3,     2,     1,     2,     4,     4,     6,     0,
       2,     1,     2
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
        case 5:
#line 120 "test.y" /* yacc.c:1646  */
    { 
        /* 表達式求值但不輸出 - 這是正確的行為 */
        /* 如果要看結果，必須使用 print-num 或 print-bool */
    }
#line 1385 "test.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 128 "test.y" /* yacc.c:1646  */
    {
        Value *v = eval((yyvsp[-1].ast), global_env);
        if (v->type == VAL_NUM) {
            printf("%d\n", v->data.num);
        }
    }
#line 1396 "test.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 134 "test.y" /* yacc.c:1646  */
    {
        Value *v = eval((yyvsp[-1].ast), global_env);
        if (v->type == VAL_BOOL) {
            printf("%s\n", v->data.bool_val ? "#t" : "#f");
        }
    }
#line 1407 "test.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 142 "test.y" /* yacc.c:1646  */
    { 
        (yyval.ast) = make_bool((yyvsp[0].bool_val));
    }
#line 1415 "test.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 145 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_num((yyvsp[0].num_val));
    }
#line 1423 "test.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 148 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_var((yyvsp[0].string));
    }
#line 1431 "test.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 162 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_op("+", (yyvsp[-1].ast_list).items, (yyvsp[-1].ast_list).count);
    }
#line 1439 "test.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "test.y" /* yacc.c:1646  */
    {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = (yyvsp[-2].ast);
        args[1] = (yyvsp[-1].ast);
        (yyval.ast) = make_op("-", args, 2);
    }
#line 1450 "test.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 175 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_op("*", (yyvsp[-1].ast_list).items, (yyvsp[-1].ast_list).count);
    }
#line 1458 "test.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 180 "test.y" /* yacc.c:1646  */
    {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = (yyvsp[-2].ast);
        args[1] = (yyvsp[-1].ast);
        (yyval.ast) = make_op("/", args, 2);
    }
#line 1469 "test.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 188 "test.y" /* yacc.c:1646  */
    {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = (yyvsp[-2].ast);
        args[1] = (yyvsp[-1].ast);
        (yyval.ast) = make_op("mod", args, 2);
    }
#line 1480 "test.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 196 "test.y" /* yacc.c:1646  */
    {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = (yyvsp[-2].ast);
        args[1] = (yyvsp[-1].ast);
        (yyval.ast) = make_op(">", args, 2);
    }
#line 1491 "test.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 204 "test.y" /* yacc.c:1646  */
    {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = (yyvsp[-2].ast);
        args[1] = (yyvsp[-1].ast);
        (yyval.ast) = make_op("<", args, 2);
    }
#line 1502 "test.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 212 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_op("=", (yyvsp[-1].ast_list).items, (yyvsp[-1].ast_list).count);
    }
#line 1510 "test.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 220 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_op("and", (yyvsp[-1].ast_list).items, (yyvsp[-1].ast_list).count);
    }
#line 1518 "test.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 225 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_op("or", (yyvsp[-1].ast_list).items, (yyvsp[-1].ast_list).count);
    }
#line 1526 "test.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 230 "test.y" /* yacc.c:1646  */
    {
        ASTNode **args = malloc(sizeof(ASTNode*));
        args[0] = (yyvsp[-1].ast);
        (yyval.ast) = make_op("not", args, 1);
    }
#line 1536 "test.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 237 "test.y" /* yacc.c:1646  */
    {
        /* 先建立一個佔位符，讓遞迴函式可以引用自己 */
        Value *placeholder = malloc(sizeof(Value));
        placeholder->type = VAL_NUM;  /* 暫時的型別 */
        placeholder->data.num = 0;
        
        /* 先加入環境 */
        Env *new_env = malloc(sizeof(Env));
        new_env->name = strdup((yyvsp[-2].string));
        new_env->value = placeholder;
        new_env->next = global_env;
        global_env = new_env;
        
        /* 現在求值，這樣函式體就能找到這個名字 */
        Value *val = eval((yyvsp[-1].ast), global_env);
        
        /* 更新值 */
        new_env->value = val;
    }
#line 1560 "test.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 258 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_fun((yyvsp[-2].str_list).items, (yyvsp[-2].str_list).count, (yyvsp[-1].ast));
    }
#line 1568 "test.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 263 "test.y" /* yacc.c:1646  */
    { (yyval.str_list) = (yyvsp[-1].str_list); }
#line 1574 "test.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 264 "test.y" /* yacc.c:1646  */
    { 
        (yyval.str_list).items = NULL; 
        (yyval.str_list).count = 0; 
    }
#line 1583 "test.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 270 "test.y" /* yacc.c:1646  */
    {
        (yyval.str_list).items = malloc(sizeof(char*));
        (yyval.str_list).items[0] = (yyvsp[0].string);
        (yyval.str_list).count = 1;
    }
#line 1593 "test.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 275 "test.y" /* yacc.c:1646  */
    {
        (yyval.str_list).items = realloc((yyvsp[-1].str_list).items, sizeof(char*) * ((yyvsp[-1].str_list).count + 1));
        (yyval.str_list).items[(yyvsp[-1].str_list).count] = (yyvsp[0].string);
        (yyval.str_list).count = (yyvsp[-1].str_list).count + 1;
    }
#line 1603 "test.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 282 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_call((yyvsp[-2].ast), (yyvsp[-1].ast_list).items, (yyvsp[-1].ast_list).count);
    }
#line 1611 "test.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 285 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_call(make_var((yyvsp[-2].string)), (yyvsp[-1].ast_list).items, (yyvsp[-1].ast_list).count);
    }
#line 1619 "test.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 290 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast) = make_if((yyvsp[-3].ast), (yyvsp[-2].ast), (yyvsp[-1].ast));
    }
#line 1627 "test.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 295 "test.y" /* yacc.c:1646  */
    { 
        (yyval.ast_list).items = NULL; 
        (yyval.ast_list).count = 0; 
    }
#line 1636 "test.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 299 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast_list).items = realloc((yyvsp[-1].ast_list).items, sizeof(ASTNode*) * ((yyvsp[-1].ast_list).count + 1));
        (yyval.ast_list).items[(yyvsp[-1].ast_list).count] = (yyvsp[0].ast);
        (yyval.ast_list).count = (yyvsp[-1].ast_list).count + 1;
    }
#line 1646 "test.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 306 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast_list).items = malloc(sizeof(ASTNode*));
        (yyval.ast_list).items[0] = (yyvsp[0].ast);
        (yyval.ast_list).count = 1;
    }
#line 1656 "test.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 311 "test.y" /* yacc.c:1646  */
    {
        (yyval.ast_list).items = realloc((yyvsp[-1].ast_list).items, sizeof(ASTNode*) * ((yyvsp[-1].ast_list).count + 1));
        (yyval.ast_list).items[(yyvsp[-1].ast_list).count] = (yyvsp[0].ast);
        (yyval.ast_list).count = (yyvsp[-1].ast_list).count + 1;
    }
#line 1666 "test.tab.c" /* yacc.c:1646  */
    break;


#line 1670 "test.tab.c" /* yacc.c:1646  */
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
#line 318 "test.y" /* yacc.c:1906  */


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* AST 建構函式 */
ASTNode* make_num(int n) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_NUM;
    node->data.num = n;
    return node;
}

ASTNode* make_bool(int b) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_BOOL;
    node->data.bool_val = b;
    return node;
}

ASTNode* make_var(char *name) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_VAR;
    node->data.var = strdup(name);
    return node;
}

ASTNode* make_op(char *op, ASTNode **args, int count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_OP;
    node->data.op.op = strdup(op);
    node->data.op.args = args;
    node->data.op.arg_count = count;
    return node;
}

ASTNode* make_if(ASTNode *cond, ASTNode *then_exp, ASTNode *else_exp) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IF;
    node->data.if_node.cond = cond;
    node->data.if_node.then_exp = then_exp;
    node->data.if_node.else_exp = else_exp;
    return node;
}

ASTNode* make_fun(char **params, int count, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_FUN;
    node->data.fun.params = params;
    node->data.fun.param_count = count;
    node->data.fun.body = body;
    return node;
}

ASTNode* make_call(ASTNode *func, ASTNode **args, int count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_CALL;
    node->data.call.func = func;
    node->data.call.args = args;
    node->data.call.arg_count = count;
    return node;
}

/* 環境操作 */
void define_var(Env **env, char *name, Value *val) {
    Env *e = *env;
    while (e) {
        if (strcmp(e->name, name) == 0) {
            fprintf(stderr, "Error: Variable '%s' already defined\n", name);
            exit(1);
        }
        e = e->next;
    }
    
    Env *new_env = malloc(sizeof(Env));
    new_env->name = strdup(name);
    new_env->value = val;
    new_env->next = *env;
    *env = new_env;
}

Value* lookup_var(Env *env, char *name) {
    while (env) {
        if (strcmp(env->name, name) == 0) {
            return env->value;
        }
        env = env->next;
    }
    fprintf(stderr, "Error: Undefined variable '%s'\n", name);
    exit(1);
}

/* 求值器 */
Value* eval(ASTNode *ast, Env *env) {
    Value *result;
    int i;
    
    if (!ast) return NULL;
    
    switch (ast->type) {
        case AST_NUM:
            result = malloc(sizeof(Value));
            result->type = VAL_NUM;
            result->data.num = ast->data.num;
            return result;
            
        case AST_BOOL:
            result = malloc(sizeof(Value));
            result->type = VAL_BOOL;
            result->data.bool_val = ast->data.bool_val;
            return result;
            
        case AST_VAR:
            return lookup_var(env, ast->data.var);
            
        case AST_OP: {
            char *op = ast->data.op.op;
            
            if (strcmp(op, "+") == 0) {
                int sum = 0;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_NUM) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    sum += v->data.num;
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = sum;
                return result;
            }
            else if (strcmp(op, "-") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = v1->data.num - v2->data.num;
                return result;
            }
            else if (strcmp(op, "*") == 0) {
                int prod = 1;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_NUM) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    prod *= v->data.num;
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = prod;
                return result;
            }
            else if (strcmp(op, "/") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = v1->data.num / v2->data.num;
                return result;
            }
            else if (strcmp(op, "mod") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = v1->data.num % v2->data.num;
                return result;
            }
            else if (strcmp(op, ">") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = v1->data.num > v2->data.num;
                return result;
            }
            else if (strcmp(op, "<") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = v1->data.num < v2->data.num;
                return result;
            }
            else if (strcmp(op, "=") == 0) {
                Value *first = eval(ast->data.op.args[0], env);
                if (first->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                int all_equal = 1;
                for (i = 1; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_NUM) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    if (v->data.num != first->data.num) {
                        all_equal = 0;
                        break;
                    }
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = all_equal;
                return result;
            }
            else if (strcmp(op, "and") == 0) {
                int res = 1;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_BOOL) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    if (!v->data.bool_val) {
                        res = 0;
                        break;
                    }
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = res;
                return result;
            }
            else if (strcmp(op, "or") == 0) {
                int res = 0;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_BOOL) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    if (v->data.bool_val) {
                        res = 1;
                        break;
                    }
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = res;
                return result;
            }
            else if (strcmp(op, "not") == 0) {
                Value *v = eval(ast->data.op.args[0], env);
                if (v->type != VAL_BOOL) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = !v->data.bool_val;
                return result;
            }
            break;
        }
        
        case AST_IF: {
            Value *cond = eval(ast->data.if_node.cond, env);
            if (cond->data.bool_val) {
                return eval(ast->data.if_node.then_exp, env);
            } else {
                return eval(ast->data.if_node.else_exp, env);
            }
        }
        
        case AST_FUN: {
            result = malloc(sizeof(Value));
            result->type = VAL_FUNC;
            result->data.func.params = ast->data.fun.params;
            result->data.func.param_count = ast->data.fun.param_count;
            result->data.func.body = ast->data.fun.body;
            result->data.func.closure = env;
            return result;
        }
        
        case AST_CALL: {
            Value *func = eval(ast->data.call.func, env);
            
            if (func->type != VAL_FUNC) {
                fprintf(stderr, "Error: Not a function\n");
                exit(1);
            }
            
            if (func->data.func.param_count != ast->data.call.arg_count) {
                fprintf(stderr, "Error: Parameter count mismatch\n");
                exit(1);
            }
            
            /* 建立新環境 */
            Env *new_env = func->data.func.closure;
            for (i = 0; i < func->data.func.param_count; i++) {
                Value *arg_val = eval(ast->data.call.args[i], env);
                Env *binding = malloc(sizeof(Env));
                binding->name = strdup(func->data.func.params[i]);
                binding->value = arg_val;
                binding->next = new_env;
                new_env = binding;
            }
            
            /* 在新環境中求值函式體 */
            return eval(func->data.func.body, new_env);
        }
    }
    
    return NULL;
}

int main(int argc, char **argv) {
    return yyparse();
}
