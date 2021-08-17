/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parse.y"
     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 25 Jul 19   */

/* Copyright (c) 2019 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09; 02 Aug 12 */
/* 30 Jul 13 */

/*
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.

; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; You should have received a copy of the GNU General Public License
; along with this program; if not, see <http://www.gnu.org/licenses/>.
  */


/* NOTE:   Copy your lexan.l lexical analyzer to this directory.      */

       /* To use:
                     make pars1y              has 1 shift/reduce conflict
                     pars1y                   execute the parser
                     i:=j .
                     ^D                       control-D to end input

                     pars1y                   execute the parser
                     begin i:=j; if i+j then x:=a+b*c else x:=a*b+c; k:=i end.
                     ^D

                     pars1y                   execute the parser
                     if x+y then if y+z then i:=j else k:=2.
                     ^D

           You may copy pars1.y to be parse.y and extend it for your
           assignment.  Then use   make parser   as above.
        */

        /* Yacc reports 1 shift/reduce conflict, due to the ELSE part of
           the IF statement, but Yacc's default resolves it in the right way.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"
#include "pprint.h"
#include "codegen.h"

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN
int //yydebug=0;

TOKEN parseresult;


#line 136 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING = 259,
    NUMBER = 260,
    PLUS = 261,
    MINUS = 262,
    TIMES = 263,
    DIVIDE = 264,
    ASSIGN = 265,
    EQ = 266,
    NE = 267,
    LT = 268,
    LE = 269,
    GE = 270,
    GT = 271,
    POINT = 272,
    DOT = 273,
    AND = 274,
    OR = 275,
    NOT = 276,
    DIV = 277,
    MOD = 278,
    IN = 279,
    COMMA = 280,
    SEMICOLON = 281,
    COLON = 282,
    LPAREN = 283,
    RPAREN = 284,
    LBRACKET = 285,
    RBRACKET = 286,
    DOTDOT = 287,
    ARRAY = 288,
    BEGINBEGIN = 289,
    CASE = 290,
    CONST = 291,
    DO = 292,
    DOWNTO = 293,
    ELSE = 294,
    END = 295,
    FILEFILE = 296,
    FOR = 297,
    FUNCTION = 298,
    GOTO = 299,
    IF = 300,
    LABEL = 301,
    NIL = 302,
    OF = 303,
    PACKED = 304,
    PROCEDURE = 305,
    PROGRAM = 306,
    RECORD = 307,
    REPEAT = 308,
    SET = 309,
    THEN = 310,
    TO = 311,
    TYPE = 312,
    UNTIL = 313,
    VAR = 314,
    WHILE = 315,
    WITH = 316
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING 259
#define NUMBER 260
#define PLUS 261
#define MINUS 262
#define TIMES 263
#define DIVIDE 264
#define ASSIGN 265
#define EQ 266
#define NE 267
#define LT 268
#define LE 269
#define GE 270
#define GT 271
#define POINT 272
#define DOT 273
#define AND 274
#define OR 275
#define NOT 276
#define DIV 277
#define MOD 278
#define IN 279
#define COMMA 280
#define SEMICOLON 281
#define COLON 282
#define LPAREN 283
#define RPAREN 284
#define LBRACKET 285
#define RBRACKET 286
#define DOTDOT 287
#define ARRAY 288
#define BEGINBEGIN 289
#define CASE 290
#define CONST 291
#define DO 292
#define DOWNTO 293
#define ELSE 294
#define END 295
#define FILEFILE 296
#define FOR 297
#define FUNCTION 298
#define GOTO 299
#define IF 300
#define LABEL 301
#define NIL 302
#define OF 303
#define PACKED 304
#define PROCEDURE 305
#define PROGRAM 306
#define RECORD 307
#define REPEAT 308
#define SET 309
#define THEN 310
#define TO 311
#define TYPE 312
#define UNTIL 313
#define VAR 314
#define WHILE 315
#define WITH 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   366

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

#define YYUNDEFTOK  2
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    85,    85,    90,    91,    93,    94,    95,    98,    99,
     101,   102,   104,   108,   109,   111,   112,   114,   116,   117,
     118,   119,   121,   123,   124,   126,   128,   130,   132,   133,
     137,   138,   140,   141,   143,   146,   147,   149,   151,   153,
     154,   156,   157,   161,   162,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   174,   176,   178,   179,   180,   181,
     183,   184,   186,   188,   189,   191,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   215,   216,   217,   219,   220,
     221,   222,   223,   224,   226,   227,   228,   229,   231,   233,
     235,   237,   238
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "NUMBER", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "ASSIGN", "EQ", "NE", "LT", "LE", "GE", "GT",
  "POINT", "DOT", "AND", "OR", "NOT", "DIV", "MOD", "IN", "COMMA",
  "SEMICOLON", "COLON", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "DOTDOT", "ARRAY", "BEGINBEGIN", "CASE", "CONST", "DO", "DOWNTO", "ELSE",
  "END", "FILEFILE", "FOR", "FUNCTION", "GOTO", "IF", "LABEL", "NIL", "OF",
  "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "THEN",
  "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH", "$accept", "program",
  "lblock", "labellist", "label", "cblock", "constgroup", "constdef",
  "tblock", "typegroup", "typedef", "complextype", "record", "fieldspecs",
  "fieldgroup", "enum", "pointer", "idlist", "vblock", "varspecs",
  "vargroup", "type", "simpletype", "array", "subrangegroup", "subrange",
  "block", "statement", "labelstatement", "gotostatement", "statements",
  "endpart", "endif", "function", "arglist", "assignment", "expr", "term",
  "factor", "variable", "dotref", "pointref", "arrayref", "exprgroup", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316
};
# endif

#define YYPACT_NINF (-128)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -36,    19,    38,     1,  -128,    28,    22,    21,    28,    48,
    -128,    85,    95,    59,    89,    93,    28,    86,  -128,  -128,
    -128,  -128,    87,    91,    95,   111,   115,    23,    95,    23,
      18,  -128,  -128,  -128,  -128,    36,  -128,  -128,  -128,   105,
     -16,    97,  -128,    65,    39,   117,   -23,   100,   106,    98,
     108,  -128,    23,    95,    18,  -128,   -19,  -128,  -128,  -128,
      29,    23,  -128,  -128,   178,   127,  -128,    31,   110,    80,
     197,    95,  -128,  -128,    23,  -128,   138,    23,    23,  -128,
      59,  -128,    89,  -128,    78,  -128,    93,     7,  -128,    28,
     114,   302,  -128,  -128,    23,    23,  -128,   283,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    95,    29,    95,    23,
      95,    18,   342,  -128,   322,   116,   342,  -128,  -128,     7,
      28,   119,    28,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,    23,   229,   256,  -128,   127,
     127,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   107,  -128,  -128,
     342,  -128,  -128,    23,  -128,  -128,   121,    20,   112,   128,
     118,  -128,    95,    95,    95,  -128,  -128,  -128,  -128,   124,
     122,   132,  -128,    28,     7,  -128,  -128,  -128,   153,   113,
      20,  -128,  -128,  -128,     7,  -128,  -128
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,    29,     0,     0,     0,
      28,     0,     0,     0,     0,     0,     0,     0,     4,     9,
      14,    31,    94,     0,     0,     0,     0,     0,     0,     0,
       0,    52,    53,    51,    50,     0,    95,    96,    97,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     0,     0,     0,    94,     0,    55,    93,    92,
       0,     0,    91,    90,     0,    84,    87,    89,    57,     0,
       0,     0,    59,    43,     0,    99,     0,     0,     0,     8,
      11,     3,     0,     6,     0,    13,    16,     0,    30,    33,
       0,    64,    54,    44,     0,     0,    86,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    98,   102,     0,    12,    10,     5,     0,
       0,     0,     0,    17,    18,    19,    20,    21,    15,    37,
      36,    34,    35,    32,    62,     0,     0,     0,    88,    66,
      67,    69,    68,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    61,    85,    56,
      48,    49,    58,     0,   100,    27,     0,     0,     0,    24,
       0,    63,     0,     0,     0,    45,   101,    26,    42,     0,
       0,    40,    22,     0,     0,    47,    46,    60,     0,     0,
       0,    23,    25,    41,     0,    39,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,  -128,    77,  -128,   120,    82,  -128,   125,    74,
    -128,    83,  -128,   -29,  -128,  -128,  -128,    -5,   123,    79,
    -128,  -127,  -128,  -128,   -34,  -128,   129,    -3,  -128,  -128,
     -47,   -46,  -128,    -8,    25,   152,   -22,     4,   -48,   -11,
    -128,  -128,  -128,     9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    17,    43,    44,    18,    40,    41,    19,    46,
      47,   140,   134,   178,   179,   135,   136,    48,    20,    49,
      50,   141,   142,   137,   190,   191,    21,    68,    31,    32,
      69,    73,   185,    63,    90,    34,    91,    65,    66,    67,
      36,    37,    38,   125
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       7,    35,   175,    10,    33,    64,    92,    70,    93,    30,
     139,    12,    96,    35,    35,     1,    33,    35,    12,    94,
      33,    54,     3,   188,   129,   189,    22,    58,    59,     5,
      60,     6,    22,    58,    59,   130,    16,    95,     4,    97,
     131,    15,    35,    16,    71,    33,    74,     8,    75,    76,
       9,    61,   122,    75,    76,   124,   126,    61,    72,   132,
      35,    77,    39,    33,    82,    83,    77,   202,   121,   168,
      62,   169,   146,   147,    11,   172,    62,   206,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,    42,   129,    45,   170,    22,    12,
      23,    13,   149,   150,    51,    35,   130,    35,    33,    35,
      33,   131,    33,   167,    55,    52,    78,   171,    53,    12,
      57,    13,    15,    80,    16,   176,    86,   180,    84,    24,
     132,    14,    12,    87,    89,   117,   118,    25,   119,    26,
      27,   123,    15,   144,    16,   194,   184,   174,    28,   177,
     187,   124,   192,   199,   193,    29,   198,   200,   203,   128,
     138,   204,   127,    81,   201,    79,   205,   133,   143,    85,
     181,    35,    35,    35,    33,    33,    33,    56,    88,   195,
     196,   197,   186,     0,    98,    99,   100,   101,   180,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    98,    99,   100,   101,     0,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   116,   120,    98,    99,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    99,   100,   101,   182,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,    98,
      99,   100,   101,   183,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    98,    99,
     100,   101,   148,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   145,    98,    99,
     100,   101,     0,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   173,    98,    99,
     100,   101,     0,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115
};

static const yytype_int16 yycheck[] =
{
       5,    12,   129,     8,    12,    27,    53,    29,    54,    12,
       3,    34,    60,    24,    25,    51,    24,    28,    34,    38,
      28,    24,     3,     3,    17,     5,     3,     4,     5,    28,
       7,     3,     3,     4,     5,    28,    59,    56,     0,    61,
      33,    57,    53,    59,    26,    53,    10,    25,    17,    18,
      29,    28,    74,    17,    18,    77,    78,    28,    40,    52,
      71,    30,     3,    71,    25,    26,    30,   194,    71,   117,
      47,   118,    94,    95,    26,   121,    47,   204,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     5,    17,     3,   119,     3,    34,
       5,    36,    98,    99,    18,   116,    28,   118,   116,   120,
     118,    33,   120,   116,     3,    28,    11,   120,    27,    34,
       5,    36,    57,    26,    59,   130,    26,   132,    11,    34,
      52,    46,    34,    27,    26,     8,    26,    42,    58,    44,
      45,     3,    57,    29,    59,    27,    39,    31,    53,    30,
      29,   173,    40,    31,    26,    60,    32,    25,     5,    82,
      86,    48,    80,    43,   193,    40,   200,    84,    89,    46,
     145,   182,   183,   184,   182,   183,   184,    25,    49,   182,
     183,   184,   173,    -1,     6,     7,     8,     9,   193,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    37,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,     9,    37,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,
       7,     8,     9,    37,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     6,     7,
       8,     9,    29,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    63,     3,     0,    28,     3,    79,    25,    29,
      79,    26,    34,    36,    46,    57,    59,    64,    67,    70,
      80,    88,     3,     5,    34,    42,    44,    45,    53,    60,
      89,    90,    91,    95,    97,   101,   102,   103,   104,     3,
      68,    69,     5,    65,    66,     3,    71,    72,    79,    81,
      82,    18,    28,    27,    89,     3,    97,     5,     4,     5,
       7,    28,    47,    95,    98,    99,   100,   101,    89,    92,
      98,    26,    40,    93,    10,    17,    18,    30,    11,    70,
      26,    67,    25,    26,    11,    80,    26,    27,    88,    26,
      96,    98,    92,    93,    38,    56,   100,    98,     6,     7,
       8,     9,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    55,     8,    26,    58,
      37,    89,    98,     3,    98,   105,    98,    68,    65,    17,
      28,    33,    52,    73,    74,    77,    78,    85,    71,     3,
      73,    83,    84,    81,    29,    25,    98,    98,    29,    99,
      99,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    89,   100,    92,
      98,    89,    93,    25,    31,    83,    79,    30,    75,    76,
      79,    96,    37,    37,    39,    94,   105,    29,     3,     5,
      86,    87,    40,    26,    27,    89,    89,    89,    32,    31,
      25,    75,    83,     5,    48,    86,    83
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    67,    67,
      68,    68,    69,    70,    70,    71,    71,    72,    73,    73,
      73,    73,    74,    75,    75,    76,    77,    78,    79,    79,
      80,    80,    81,    81,    82,    83,    83,    84,    85,    86,
      86,    87,    87,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    90,    91,    92,    92,    93,    93,
      94,    94,    95,    96,    96,    97,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   102,   103,
     104,   105,   105
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     3,     1,     3,     2,     1,     3,     1,
       3,     2,     3,     3,     1,     3,     2,     3,     1,     1,
       1,     1,     3,     3,     1,     3,     3,     2,     3,     1,
       3,     1,     3,     2,     3,     1,     1,     1,     6,     3,
       1,     3,     1,     3,     3,     5,     6,     6,     4,     4,
       1,     1,     1,     1,     3,     2,     3,     1,     3,     1,
       2,     0,     4,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       4,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 86 "parse.y"
                                        { parseresult = makeprogram(yyvsp[-6], yyvsp[-4], yyvsp[-1]); }
#line 1659 "y.tab.c"
    break;

  case 3:
#line 90 "parse.y"
                                          { yyval = yyvsp[0]; }
#line 1665 "y.tab.c"
    break;

  case 5:
#line 93 "parse.y"
                                         { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1671 "y.tab.c"
    break;

  case 6:
#line 94 "parse.y"
                                { yyval = cons(yyvsp[-1], NULL); }
#line 1677 "y.tab.c"
    break;

  case 7:
#line 95 "parse.y"
                       { instlabel(yyvsp[0]); }
#line 1683 "y.tab.c"
    break;

  case 8:
#line 98 "parse.y"
                                        { yyval = yyvsp[0]; }
#line 1689 "y.tab.c"
    break;

  case 12:
#line 104 "parse.y"
                                   { instconst(yyvsp[-2], yyvsp[0]); }
#line 1695 "y.tab.c"
    break;

  case 13:
#line 108 "parse.y"
                                      { yyval = yyvsp[0]; }
#line 1701 "y.tab.c"
    break;

  case 17:
#line 114 "parse.y"
                                          { insttype(yyvsp[-2], yyvsp[0]); }
#line 1707 "y.tab.c"
    break;

  case 22:
#line 121 "parse.y"
                                   { yyval = instrec(yyvsp[-2], yyvsp[-1]); }
#line 1713 "y.tab.c"
    break;

  case 23:
#line 123 "parse.y"
                                                { yyval = nconc(yyvsp[-2], yyvsp[0]); }
#line 1719 "y.tab.c"
    break;

  case 24:
#line 124 "parse.y"
                           { yyval = yyvsp[0]; }
#line 1725 "y.tab.c"
    break;

  case 25:
#line 126 "parse.y"
                                  { instfields(yyvsp[-2], yyvsp[0]); yyval = yyvsp[-2]; }
#line 1731 "y.tab.c"
    break;

  case 26:
#line 128 "parse.y"
                                  { yyval = instenum(yyvsp[-1]); }
#line 1737 "y.tab.c"
    break;

  case 27:
#line 130 "parse.y"
                        { yyval = instpoint(yyvsp[-1], yyvsp[0]); }
#line 1743 "y.tab.c"
    break;

  case 28:
#line 132 "parse.y"
                                        { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1749 "y.tab.c"
    break;

  case 29:
#line 133 "parse.y"
                           { yyval = cons(yyvsp[0], NULL); }
#line 1755 "y.tab.c"
    break;

  case 30:
#line 137 "parse.y"
                                   { yyval = yyvsp[0]; }
#line 1761 "y.tab.c"
    break;

  case 34:
#line 143 "parse.y"
                                  { instvars(yyvsp[-2], yyvsp[0]); }
#line 1767 "y.tab.c"
    break;

  case 37:
#line 149 "parse.y"
                          { yyval = findtype(yyvsp[0]); }
#line 1773 "y.tab.c"
    break;

  case 38:
#line 151 "parse.y"
                                                              { yyval = instarray(yyvsp[-3], yyvsp[0]); }
#line 1779 "y.tab.c"
    break;

  case 39:
#line 153 "parse.y"
                                             { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1785 "y.tab.c"
    break;

  case 40:
#line 154 "parse.y"
                         { yyval = cons(yyvsp[0], NULL); }
#line 1791 "y.tab.c"
    break;

  case 41:
#line 156 "parse.y"
                                     { yyval = makesubranget(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1797 "y.tab.c"
    break;

  case 42:
#line 157 "parse.y"
                           { yyval = findtype(yyvsp[0]); }
#line 1803 "y.tab.c"
    break;

  case 43:
#line 161 "parse.y"
                                            { yyval = makeprogn(yyvsp[-2],cons(yyvsp[-1], yyvsp[0])); }
#line 1809 "y.tab.c"
    break;

  case 44:
#line 163 "parse.y"
                                       { yyval = makeprogn(yyvsp[-2],cons(yyvsp[-1], yyvsp[0])); }
#line 1815 "y.tab.c"
    break;

  case 45:
#line 164 "parse.y"
                                               { yyval = makeif(yyvsp[-4], yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 1821 "y.tab.c"
    break;

  case 46:
#line 165 "parse.y"
                                                     { yyval = makefor(1, yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1827 "y.tab.c"
    break;

  case 47:
#line 166 "parse.y"
                                                         { yyval = makefor(-1, yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1833 "y.tab.c"
    break;

  case 48:
#line 167 "parse.y"
                                             { yyval = makerepeat(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1839 "y.tab.c"
    break;

  case 49:
#line 168 "parse.y"
                                        { yyval = makewhile(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1845 "y.tab.c"
    break;

  case 52:
#line 171 "parse.y"
                               { yyval = makeprogn(makeop(PROGNOP), yyvsp[0]); }
#line 1851 "y.tab.c"
    break;

  case 54:
#line 174 "parse.y"
                                                             { yyval = dolabel(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1857 "y.tab.c"
    break;

  case 55:
#line 176 "parse.y"
                                                { yyval = dogoto(yyvsp[-1], yyvsp[0]); }
#line 1863 "y.tab.c"
    break;

  case 56:
#line 178 "parse.y"
                                                          { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1869 "y.tab.c"
    break;

  case 57:
#line 179 "parse.y"
                                               { yyval = cons(yyvsp[0], NULL); }
#line 1875 "y.tab.c"
    break;

  case 58:
#line 180 "parse.y"
                                               { yyval = cons(yyvsp[-1], yyvsp[0]); }
#line 1881 "y.tab.c"
    break;

  case 59:
#line 181 "parse.y"
                                               { yyval = NULL; }
#line 1887 "y.tab.c"
    break;

  case 60:
#line 183 "parse.y"
                                               { yyval = yyvsp[0]; }
#line 1893 "y.tab.c"
    break;

  case 61:
#line 184 "parse.y"
                                               { yyval = NULL; }
#line 1899 "y.tab.c"
    break;

  case 62:
#line 186 "parse.y"
                                                 {yyval = makefuncall(yyvsp[-2], yyvsp[-3], yyvsp[-1]); }
#line 1905 "y.tab.c"
    break;

  case 63:
#line 188 "parse.y"
                                               { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1911 "y.tab.c"
    break;

  case 64:
#line 189 "parse.y"
                     { yyval = cons(yyvsp[0], NULL); }
#line 1917 "y.tab.c"
    break;

  case 65:
#line 191 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1923 "y.tab.c"
    break;

  case 66:
#line 195 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1929 "y.tab.c"
    break;

  case 67:
#line 196 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1935 "y.tab.c"
    break;

  case 68:
#line 197 "parse.y"
                                                   { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1941 "y.tab.c"
    break;

  case 69:
#line 198 "parse.y"
                                                  { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1947 "y.tab.c"
    break;

  case 70:
#line 199 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1953 "y.tab.c"
    break;

  case 71:
#line 200 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1959 "y.tab.c"
    break;

  case 72:
#line 201 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1965 "y.tab.c"
    break;

  case 73:
#line 202 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1971 "y.tab.c"
    break;

  case 74:
#line 203 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1977 "y.tab.c"
    break;

  case 75:
#line 204 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1983 "y.tab.c"
    break;

  case 76:
#line 205 "parse.y"
                                                  { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1989 "y.tab.c"
    break;

  case 77:
#line 206 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1995 "y.tab.c"
    break;

  case 78:
#line 207 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2001 "y.tab.c"
    break;

  case 79:
#line 208 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2007 "y.tab.c"
    break;

  case 80:
#line 209 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2013 "y.tab.c"
    break;

  case 81:
#line 210 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2019 "y.tab.c"
    break;

  case 82:
#line 211 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2025 "y.tab.c"
    break;

  case 83:
#line 212 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2031 "y.tab.c"
    break;

  case 85:
#line 215 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2037 "y.tab.c"
    break;

  case 86:
#line 216 "parse.y"
                                               { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 2043 "y.tab.c"
    break;

  case 88:
#line 219 "parse.y"
                                               { yyval = yyvsp[-1]; }
#line 2049 "y.tab.c"
    break;

  case 91:
#line 222 "parse.y"
                                               { yyval = makenil(yyvsp[0]); }
#line 2055 "y.tab.c"
    break;

  case 94:
#line 226 "parse.y"
                                               { yyval = findid(yyvsp[0]); }
#line 2061 "y.tab.c"
    break;

  case 98:
#line 231 "parse.y"
                                             { yyval = reducedot(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2067 "y.tab.c"
    break;

  case 99:
#line 233 "parse.y"
                                             { yyval = dopoint(yyvsp[-1], yyvsp[0]); }
#line 2073 "y.tab.c"
    break;

  case 100:
#line 235 "parse.y"
                                                     { yyval = arrayref(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2079 "y.tab.c"
    break;

  case 101:
#line 237 "parse.y"
                                             { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 2085 "y.tab.c"
    break;

  case 102:
#line 238 "parse.y"
                                             { yyval = cons(yyvsp[0], NULL); }
#line 2091 "y.tab.c"
    break;


#line 2095 "y.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 239 "parse.y"


/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG        0             /* set bits here for debugging, 0 = off  */
#define DB_CONS       1             /* bit to trace cons */
#define DB_BINOP      2             /* bit to trace binop */
#define DB_MAKEIF     4             /* bit to trace makeif */
#define DB_MAKEPROGN  8             /* bit to trace makeprogn */
#define DB_PARSERES  16             /* bit to trace parseresult */
#define DB_MAKEFOR   32             /* bit to trace makefor */
#define DB_FINDID   64             /* bit to trace findid */

 int labelnumber = 0;  /* sequential counter for internal label numbers */
 int userlabels[50];

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

TOKEN makenil(TOKEN tok) {
  tok = makeintc(0);
  tok->basicdt = POINTER;
  tok->realval = 0;
  return tok;
}

/* mulint multiplies expression exp by integer n */
TOKEN mulint(TOKEN exp, int n) {
  TOKEN times = makeop(TIMESOP);
  times->operands = exp;
  times->operands->link = makeintc(n);
  return times;
}

/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
  /* dbugprinttok(arr);
  dbprsymbol(arr->symtype);
  dbprsymbol(arr->symtype->datatype); */
  TOKEN offset;
  if (subs->tokentype == NUMBERTOK) {
    offset = makeintc((subs->intval-arr->symtype->lowbound) * arr->symtype->datatype->size);
  } else {
    offset = makeplus(mulint(copytok(subs), arr->symtype->datatype->size),
        makeintc(-1*arr->symtype->lowbound*arr->symtype->datatype->size), NULL);
  }
  //printf("offset:%i\n", offset);
  tok = makearef(arr, offset, tokb);
  tok->basicdt = arr->symtype->datatype->basicdt; 
  tok->symtype = arr->symtype->datatype;
  if (subs->link != NULL) {
    return arrayref(tok, talloc(), subs->link, talloc());
  }
  return tok;
}
// assert( arr->symtype->kind == ARRAYSYM );

/* dopoint handles a ^ operator.  john^ becomes (^ john) with type record
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
  tok->tokentype = OPERATOR;
  tok->whichval = POINTEROP;
  tok->operands = var;
  tok->symtype = var->symtype->datatype->datatype;
  return tok;
}
//     assert( var->symtype->kind == POINTERSYM );
//     assert( var->symtype->datatype->kind == TYPESYM );

/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field) {
  SYMBOL i = var->symtype->datatype;
  while (i != NULL) {
    //printf("ASD: %s %s\n\n", i->namestring, field->stringval);
    if (strcmp(i->namestring, field->stringval) == 0) {
      //printf("A: %s %i\n", field->stringval, i->offset);
      field->tokentype = NUMBERTOK;
      field->basicdt = INTEGER;
      field->intval = i->offset;
      break;
    }
    i = i->link;
  }
  TOKEN tok = makearef(var, field, dot);
  tok->basicdt = i->datatype->basicdt; 
  tok->symtype = i->datatype;
  //printf("A: %i\n", i->datatype->basicdt);
  return tok; 
}
// assert( var->symtype->kind == RECORDSYM );

/* makearef makes an array reference operation.
   off is be an integer constant token
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok) {
  if (var->tokentype == OPERATOR && var->whichval == AREFOP) {
    if (var->operands->link->tokentype == NUMBERTOK && off->tokentype == NUMBERTOK) {
      var->operands->link->intval += off->intval;
    } else if (off->tokentype == NUMBERTOK){
      var->operands->link->operands->link->intval += off->intval;
    } else {
      var->operands->link = makeplus(var->operands->link, off, tok);
    }
    return var;
  } else {
    tok->tokentype = OPERATOR;
    tok->whichval = AREFOP;
    tok->operands = var;
    tok->operands->link = off;
    return tok;
  }
}

/* dogoto is the action for a goto statement.
   tok is a (now) unused token that is recycled. */
TOKEN dogoto(TOKEN tok, TOKEN labeltok) {
  int i;
  int labelnum = -1;
  for(i = 0; i < 50; i++) {
    if (userlabels[i] == labeltok->intval) {
      labelnum = i;
    }
  }
  if (labelnum != -1) {
    tok->tokentype = OPERATOR;
    tok->whichval = GOTOOP;
    tok->operands = makeintc(labelnum);
  }
  return tok;
}

/* dolabel is the action for a label of the form   <number>: <statement>
   tok is a (now) unused token that is recycled. */
TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement) {
  int i;
  int labelnum = -1;
  for(i = 0; i < 50; i++) {
    if (userlabels[i] == labeltok->intval) {
      labelnum = i;
    }
  }
  if (labelnum != -1) {
    tok->tokentype = OPERATOR;
    tok->whichval = LABELOP;
    tok->operands = makeintc(labelnum);
    tok->link = statement;
  }
  return tok;
}

/* makewhile makes structures for a while statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement) {
  tok->tokentype = OPERATOR;
  tok->whichval = PROGNOP;
  TOKEN label = makelabel();
  tokb->tokentype = OPERATOR;
  tokb->whichval = PROGNOP;
  tokb->operands = statement;
  statement->link = makegoto(label->operands->intval);
  TOKEN _if = makeif(makeop(IFOP), expr, tokb, NULL);
  label->link = _if;
  tok->operands = label;
  return tok;
}

/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok) {
  SYMBOL sym = symalloc();
  if (bounds->link == NULL) {
    sym->kind = ARRAYSYM;
    sym->datatype = typetok->symtype;
    sym->size = (bounds->symtype->highbound - bounds->symtype->lowbound + 1)*sym->datatype->size;
    sym->lowbound = bounds->symtype->lowbound;
    sym->highbound = bounds->symtype->highbound;
  } else {
    sym->kind = ARRAYSYM;
    sym->datatype = instarray(bounds->link, typetok)->symtype;
    sym->size = (bounds->symtype->highbound - bounds->symtype->lowbound + 1)*sym->datatype->size;
    sym->lowbound = bounds->symtype->lowbound;
    sym->highbound = bounds->symtype->highbound;
  }
  typetok->symtype = sym;
  return typetok;
}
//     assert(bounds->symtype->kind == SUBRANGE );

/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high) {
  SYMBOL sym = symalloc();
  sym->kind = SUBRANGE;
  sym->size = basicsizes[INTEGER];
  sym->basicdt = INTEGER;
  sym->lowbound = low;
  sym->highbound = high;
  tok->symtype = sym;
  return tok;
}

TOKEN makesubranget(TOKEN tok, TOKEN low, TOKEN high) {
  return makesubrange(tok, low->intval, high->intval);
}

/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist) {
  int low = 0;
  int high = 0;
  while (idlist != NULL) {
    instconst(idlist, makeintc(high));
    if (idlist->link == NULL)
      break;
    else {
      high++;
      idlist = idlist->link;
    }
  }
  return makesubrange(idlist, low, high);
}

/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void  insttype(TOKEN typename, TOKEN typetok) {
  SYMBOL sym = searchins(typename->stringval);
  sym->kind = TYPESYM;
  sym->datatype = typetok->symtype;
  sym->size = typetok->symtype->size;
  sym->basicdt = typetok->symtype->basicdt;
  // printf("%s: size: %i  kind: %i", typename->stringval, sym->size, sym->kind);
}

/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {
  SYMBOL sym = symalloc();
  sym->kind = POINTERSYM;
  sym->datatype = typename->symtype;
  sym->size = basicsizes[POINTER];
  sym->basicdt = POINTER;
  tok->symtype = sym;
  return tok;
}

/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok) {
  SYMBOL rec = makesym(rectok->stringval);
  int next = 0;
  rec->kind = RECORDSYM;
  rec->datatype = NULL;
  SYMBOL prevsym = NULL;
  while (argstok != NULL) {
    //printf("%s\n", argstok->stringval);
    SYMBOL typesym = argstok->symtype;
    int align = alignsize(typesym);
    SYMBOL sym = makesym(argstok->stringval);
    if (rec->datatype == NULL) {
      rec->datatype = sym;
    }
    sym->datatype = typesym;
    sym->offset = wordaddress(next, align);
    sym->size = typesym->size;
    next = sym->offset + sym->size;
    rec->size = next;
    sym->link = NULL;
    if (prevsym != NULL) {
      prevsym->link = sym;
    }
    prevsym = sym;
    argstok = argstok->link;
  }
  rec->size = wordaddress(rec->size, 16);
  //printf("%s: size: %i  datatype: %s", rec->namestring, rec->size, rec->datatype->namestring);
  rectok->symtype = rec;
  return rectok;
}


/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok) {
  TOKEN id = idlist;
  while(id != NULL) {
    id->symtype = typetok->symtype;
    id = id->link;
  }
  return idlist;
}

/* instlabel installs a user label into the label table */
void  instlabel (TOKEN num) {
  userlabels[labelnumber++] = num->intval;
}

/* nconc concatenates two token lists, destructively, by making the last link
   of lista point to listb.
   (nconc '(a b) '(c d e))  =  (a b c d e)  */
/* nconc is useful for putting together two fieldlist groups to
   make them into a single list in a record declaration. */
/* nconc should return lista, or listb if lista is NULL. */
TOKEN nconc(TOKEN lista, TOKEN listb) {
  TOKEN p = lista;
  if (p == NULL)
    return listb;
  while(p->link != NULL) {
    p = p->link;
  }
  p->link = listb;
  return lista;
}

TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item);
         dbugprinttok(list);
       };
    return item;
  }

  /* makefloat forces the item tok to be floating, by floating a constant
   or by inserting a FLOATOP operator */
TOKEN makefloat(TOKEN tok){
  if ((tok->symentry != NULL && tok->symentry->kind == CONSTSYM) || tok->tokentype == NUMBERTOK) {
    tok->tokentype = NUMBERTOK;
    tok->basicdt = REAL;
    tok->realval = (float)tok->intval;
    return tok;
  } else {
    TOKEN f = talloc();
    f->tokentype = OPERATOR;
    f->whichval = FLOATOP;
    f->operands = tok;
    return f;
  }
}

/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok){
  TOKEN f = talloc();
  f->tokentype = OPERATOR;
  f->whichval = FIXOP;
  f->operands = tok;
  return f;
}


TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { 
    const int TYPE_LATTICE[] = {0, 1, 2, 2, 0};\
    int left_type, right_type;
    if (op->whichval == ASSIGNOP) {
      if (lhs->tokentype == IDENTIFIERTOK) {
        left_type = findid(lhs)->symtype->basicdt;
      } else {
        left_type = lhs->basicdt;
      }
      if (rhs->tokentype == IDENTIFIERTOK) {
        right_type = findid(rhs)->symtype->basicdt;
      } else {
        right_type = rhs->basicdt;
      }
      if (TYPE_LATTICE[left_type] > TYPE_LATTICE[right_type]) {
        rhs = makefloat(rhs);
      } else if (TYPE_LATTICE[left_type] < TYPE_LATTICE[right_type]) {
        rhs = makefix(rhs);
      }
      op->basicdt = left_type;
    } else {
      if (lhs->tokentype == IDENTIFIERTOK) {
        left_type = findid(lhs)->symtype->basicdt;
      } else {
        left_type = lhs->basicdt;
      }
      if (rhs->tokentype == IDENTIFIERTOK) {
        right_type = findid(rhs)->symtype->basicdt;
      } else {
        right_type = rhs->basicdt;
      }
      /* dbugprinttok(op->operands);
      dbugprinttok(op->operands->link);
      printf("%i-%i", left_type, right_type); */
      int type = left_type;
      if (TYPE_LATTICE[left_type] > TYPE_LATTICE[right_type]) {
        rhs = makefloat(rhs);
      } else if (TYPE_LATTICE[left_type] < TYPE_LATTICE[right_type]) {
        lhs = makefloat(lhs);
        type = right_type;
      }
      if (op->whichval >= EQOP && op->whichval <= GTOP) {
        op->basicdt = BOOLETYPE;
      } else {
        op->basicdt = type;
      }
    }
    op->operands = lhs;          /* link operands to operator       */
    lhs->link = rhs;             /* link second operand to first    */
    rhs->link = NULL;            /* terminate operand list          */
    
    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    return op;
  }

TOKEN unaryop(TOKEN op, TOKEN lhs) {
  op->operands = lhs;
  op->basicdt = lhs->basicdt;
  return op;
}

TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;  /* Make it look like an operator   */
     tok->whichval = IFOP;
     if (elsepart != NULL) elsepart->link = NULL;
     thenpart->link = elsepart;
     exp->link = thenpart;
     tok->operands = exp;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

/* makeprogram makes the tree structures for the top-level program */
TOKEN makeprogram(TOKEN name, TOKEN args, TOKEN statements) {
    TOKEN p = makeprogn(makeop(PROGNOP), args);
    p->link = statements;
    name->link = p;
    TOKEN prog = makeop(PROGRAMOP);
    prog->operands = name;
    return prog;
}

TOKEN makeprogn(TOKEN tok, TOKEN statements)
  {  tok->tokentype = OPERATOR;
     tok->whichval = PROGNOP;
     tok->operands = statements;
     if (DEBUG & DB_MAKEPROGN)
       { printf("makeprogn\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
       };
     return tok;
   }

/* makeop makes a new operator token with operator number opnum.
   Example:  makeop(FLOATOP)  */
TOKEN makeop(int opnum) {
    TOKEN t = talloc();
    t->tokentype = OPERATOR;
    t->whichval = opnum;
    return t;
}
/* makeintc makes a new integer number token with num as its value */
TOKEN makeintc(int num) {
    TOKEN t = talloc();
    t->tokentype = NUMBERTOK;
    t->basicdt = INTEGER;
    t->intval = num;
    return t;
}
/* makelabel makes a new label, using labelnumber++ */
TOKEN makelabel() {
    TOKEN t = makeop(LABELOP);
    t->operands = makeintc(labelnumber++);
    return t;
}
/* makegoto makes a GOTO operator to go to the specified label.
   The label number is put into a number token. */
TOKEN makegoto(int label) {
    TOKEN t = makeop(GOTOOP);
    t->operands = makeintc(label);
    return t;
}
/* makeplus makes a + operator.
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makeplus(TOKEN lhs, TOKEN rhs, TOKEN tok) {
    if (tok == NULL) {
        tok = makeop(PLUSOP);
    } else {
        tok->tokentype = OPERATOR;
        tok->whichval = PLUSOP;
    }
    tok->operands = lhs;
    tok->operands->link = rhs;
    return tok;
}

/*typedef struct tokn {
  int    tokentype;  
  int    basicdt;  
  struct symtbr * symtype;
  struct symtbr * symentry;
  struct tokn * operands;
  struct tokn * link;
  union { char  tokenstring[16];  
          int   which;
          int   intnum;
          double realnum; } tokenval;
  } *TOKEN;
*/
/* copytok makes a new token that is a copy of origtok */
TOKEN copytok(TOKEN origtok) {
    TOKEN tok = talloc();
    tok->tokentype = origtok->tokentype;
    tok->basicdt = origtok->basicdt;
    tok->symtype = origtok->symtype;
    tok->symentry = origtok->symentry;
    tok->tokenval = origtok->tokenval;
    return tok;
}

/* makefor makes structures for a for statement.
   sign is 1 for normal loop, -1 for downto.
   asg is an assignment statement, e.g. (:= i 1)
   endexpr is the end expression
   tok, tokb and tokc are (now) unused tokens that are recycled. */
TOKEN makefor(int sign, TOKEN tok, TOKEN asg, TOKEN tokb, TOKEN endexpr,
              TOKEN tokc, TOKEN statement) {
    if (DEBUG & DB_MAKEFOR) {
      printf("for\n");
      dbugprinttok(tok);
      dbugprinttok(asg);
      dbugprinttok(tokb);
      dbugprinttok(endexpr);
      dbugprinttok(tokc);
      dbugprinttok(statement);
    }
    /* tok->tokentype = OPERATOR;
    tok->whichval = PROGNOP;
    tokb->tokentype = OPERATOR;
    tokb->whichval = LABELOP;
    TOKEN j = maketoken(NUMBERTOK, INTEGER);
    j->intval = labelnumber++;
    tokb->operands = j;
    tokc-> */
    tok->tokentype = OPERATOR;
    tok->whichval = PROGNOP;
    /* TOKEN label = maketoken(OPERATOR, LABELOP);
    TOKEN j = maketoken(NUMBERTOK, INTEGER);
    j->intval = labelnumber++; 
    label->operands = j; */
    TOKEN label = makelabel();
    TOKEN to = makeop(LEOP);
    TOKEN i = copytok(asg->operands);
    findid(i);
    i->link = endexpr;
    to->operands = i;
    TOKEN inc = makeop(ASSIGNOP);
    inc->basicdt = i->basicdt;
    TOKEN _i = copytok(asg->operands);
    findid(_i);
    /* TOKEN plus = maketoken(OPERATOR, PLUSOP); */
    TOKEN __i = copytok(asg->operands);
    findid(__i);
    TOKEN plus = makeplus(__i, makeintc(1), tokb);
    _i->link = plus;
    inc->operands = _i;
    /* TOKEN _goto = maketoken(OPERATOR, GOTOOP);
    _goto->operands = j; */
    TOKEN _goto = makegoto(label->operands->intval);
    statement->link = inc;
    statement->link->link = _goto;
    label->link = makeif(makeop(IFOP), to, makeprogn(tokc, statement), NULL);
    asg->link = label;
    tok->operands = asg;
    return tok;
}

/* makerepeat makes structures for a repeat statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {
    tok->tokentype = OPERATOR;
    tok->whichval = PROGNOP;
    TOKEN label = makelabel();
    tokb->tokentype = OPERATOR;
    tokb->whichval = PROGNOP;
    tokb->operands = statements;
    TOKEN noop = makeop(PROGNOP);
    TOKEN _if = makeif(makeop(IFOP), expr, noop, makegoto(label->operands->intval));
    tokb->link = _if;
    label->link = tokb;
    tok->operands = label;
    return tok;
}


/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {
    tok->tokentype = OPERATOR;
    tok->whichval = FUNCALLOP;
    if (strcmp(fn->stringval, "new") == 0) {
      TOKEN asg = makeop(ASSIGNOP);
      asg->operands = args;
      tok->operands = fn;
      tok->operands->link = makeintc(args->symtype->datatype->size);
      asg->operands->link = tok;
      return asg;
    }
    if (strcmp(fn->stringval, "write") == 0) {
      if (args->basicdt == INTEGER) {
        strcpy(fn->stringval, "writei");
      } else if (args->basicdt == REAL) {
        strcpy(fn->stringval, "writef");
      }
    }
    if (strcmp(fn->stringval, "writeln") == 0) {
      if (args->basicdt == INTEGER) {
        strcpy(fn->stringval, "writelni");
      } else if (args->basicdt == REAL) {
        strcpy(fn->stringval, "writelnf");
      }
    }
    tok->operands = fn;
    tok->operands->link = args;
    SYMBOL sym;
    sym = searchst(fn->stringval);
    tok->basicdt = sym->link->datatype->basicdt;
    return tok;
}

int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

/* install variables in symbol table */
void instvars(TOKEN idlist, TOKEN typetok)
  {  SYMBOL sym, typesym; int align;
     typesym = typetok->symtype;
     align = alignsize(typesym);
     while ( idlist != NULL )   /* for each id */
       {  sym = insertsym(idlist->stringval);
          sym->kind = VARSYM;
          sym->offset =     /* "next" */
              wordaddress(blockoffs[blocknumber],
                          align);
          sym->size = typesym->size;
          blockoffs[blocknumber] =   /* "next" */
                         sym->offset + sym->size;
          sym->datatype = typesym;
          sym->basicdt = typesym->basicdt;
          idlist = idlist->link;
        };
  }

/* install const variables in symbol table */
void instconst(TOKEN id, TOKEN val)
  {  SYMBOL sym; int align, _size;

      if (val->basicdt == INTEGER) {
        _size = 4;
      } else if (val->basicdt == REAL) {
        _size = 8;
      } else if (val->basicdt == BOOLETYPE) {
        _size = 1;
      } else {
        _size = 8;
      }
     align = _size;
     if ( id != NULL )   /* for each id */
       {  sym = insertsym(id->stringval);
          sym->kind = CONSTSYM;
          sym->size = _size;
          sym->basicdt = val->basicdt;
          if (val->basicdt == INTEGER) {
            sym->constval.intnum = val->intval;
          } else if (val->basicdt == REAL) {
            sym->constval.realnum = val->realval;
          }
        };
  }

TOKEN findid(TOKEN tok) { /* the ID token */
    if (DEBUG & DB_FINDID) {
      printf("findid\n");
      dbugprinttok(tok);
    }
  
    SYMBOL sym, typ;
    sym = searchst(tok->stringval);
    if (sym->kind == CONSTSYM) {

      tok->tokentype = NUMBERTOK;
      tok->symentry = sym;
      tok->basicdt = sym->basicdt;
      if (sym->basicdt == INTEGER) {
        tok->intval = sym->constval.intnum;
      } else if (sym->basicdt == REAL) {
        tok->realval = sym->constval.realnum;
      }
    }
    else {
      tok->symentry = sym;
      typ = sym->datatype;
      tok->symtype = typ;
      if ( typ->kind == BASICTYPE ||
          typ->kind == POINTERSYM)
      tok->basicdt = typ->basicdt;
    }
    return tok;
}


TOKEN findtype(TOKEN tok) { /* the type token */
    SYMBOL sym;
    sym = searchins(tok->stringval);
    if (sym->kind == TYPESYM) {
      tok->symtype = sym->datatype;
    }
    else {
      tok->symtype = sym;
      tok->basicdt = sym->basicdt;
    }
    return tok;
}

int main(void)          /*  */
  { int res;
    initsyms();
    res = yyparse();
    printst();       /* to shorten, change to:  printstlevel(1);  */
    printf("yyparse result = %8d\n", res);
    if (DEBUG & DB_PARSERES) dbugprinttok(parseresult);
    ppexpr(parseresult);           /* Pretty-print the result tree */
    /* uncomment following to call code generator. */
     
    exprCanonicalization(parseresult);gencode(parseresult, blockoffs[blocknumber], labelnumber);

  }
