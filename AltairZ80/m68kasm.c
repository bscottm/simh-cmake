/* A Bison parser, made by GNU Bison 3.5.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
#define YYBISON_VERSION "3.5.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "m68kasm.y.txt"

/* m68k_parse.c: line assembler for generic m68k_cpu
  
   Copyright (c) 2009-2010, Holger Veit

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   HOLGER VEIT BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   Except as contained in this notice, the name of Holger Veit et al shall not be
   used in advertising or otherwise to promote the sale, use or other dealings
   in this Software without prior written authorization from Holger Veit et al.

   04-Oct-09    HV      Initial version
   20-Sep-14    PS      Adapted for AltairZ80
   
   use "bison m68kasm.y -o m68kasm.c" to create m68kasm.c
*/

#include "sim_defs.h"
#include <ctype.h>
#include <string.h>

struct _ea {
	int ea;
	int cnt;
	t_value arg[10];
};
struct _rea {
	int reg;
	struct _ea ea;
};
struct _mask {
	int x;
	int d;
};
struct _brop {
	int opc;
	int len;
};

static int oplen;
const static int movemx[] = {   0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000,
                                0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080 };
const static int movemd[] = {   0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001,
                                0x8000, 0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200, 0x0100 };
static int yyrc;
static int yyerrc;
static int yylex(void);
static int _genop(t_value arg);
static int _genea(struct _ea arg);
static int _genbr(t_value arg,t_value,int);
static void yyerror(char* s);

#define YYDEBUG 1

#line 140 "m68kasm.c"

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
    A0 = 258,
    A1 = 259,
    A2 = 260,
    A3 = 261,
    A4 = 262,
    A5 = 263,
    A6 = 264,
    A7 = 265,
    D0 = 266,
    D1 = 267,
    D2 = 268,
    D3 = 269,
    D4 = 270,
    D5 = 271,
    D6 = 272,
    D7 = 273,
    CCR = 274,
    SR = 275,
    USP = 276,
    PC = 277,
    NUMBER = 278,
    ABCD = 279,
    ADD = 280,
    ADDA = 281,
    ADDI = 282,
    ADDQ = 283,
    ADDX = 284,
    AND = 285,
    ANDI = 286,
    OR = 287,
    ORI = 288,
    SBCD = 289,
    SUB = 290,
    SUBA = 291,
    SUBI = 292,
    SUBQ = 293,
    SUBX = 294,
    ASL = 295,
    ASR = 296,
    LSL = 297,
    LSR = 298,
    ROL = 299,
    ROR = 300,
    ROXL = 301,
    ROXR = 302,
    BCC = 303,
    BCS = 304,
    BEQ = 305,
    BGE = 306,
    BGT = 307,
    BHI = 308,
    BLE = 309,
    BLS = 310,
    BLT = 311,
    BMI = 312,
    BNE = 313,
    BPL = 314,
    BVC = 315,
    BVS = 316,
    BSR = 317,
    BRA = 318,
    BCLR = 319,
    BSET = 320,
    BCHG = 321,
    BTST = 322,
    CHK = 323,
    CMP = 324,
    CMPA = 325,
    CMPI = 326,
    CMPM = 327,
    EOR = 328,
    EORI = 329,
    EXG = 330,
    EXT = 331,
    DIVU = 332,
    DIVS = 333,
    MULU = 334,
    MULS = 335,
    DBCC = 336,
    DBCS = 337,
    DBEQ = 338,
    DBF = 339,
    DBGE = 340,
    DBGT = 341,
    DBHI = 342,
    DBLE = 343,
    DBLS = 344,
    DBLT = 345,
    DBMI = 346,
    DBNE = 347,
    DBPL = 348,
    DBT = 349,
    DBVC = 350,
    DBVS = 351,
    SCC = 352,
    SCS = 353,
    SEQ = 354,
    SF = 355,
    SGE = 356,
    SGT = 357,
    SHI = 358,
    SLE = 359,
    SLS = 360,
    SLT = 361,
    SMI = 362,
    SNE = 363,
    SPL = 364,
    ST = 365,
    SVC = 366,
    SVS = 367,
    ILLEGAL = 368,
    NOP = 369,
    RESET = 370,
    RTE = 371,
    RTR = 372,
    RTS = 373,
    TRAPV = 374,
    JMP = 375,
    JSR = 376,
    LEA = 377,
    LINK = 378,
    MOVE = 379,
    MOVEA = 380,
    MOVEM = 381,
    MOVEP = 382,
    MOVEQ = 383,
    CLR = 384,
    NEG = 385,
    NEGX = 386,
    NBCD = 387,
    NOT = 388,
    PEA = 389,
    STOP = 390,
    TAS = 391,
    SWAP = 392,
    TRAP = 393,
    TST = 394,
    UNLK = 395,
    PREDEC = 396,
    POSTINC = 397,
    BSIZE = 398,
    WSIZE = 399,
    LSIZE = 400,
    SSIZE = 401
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 71 "m68kasm.y.txt"

	int rc;
	int reg;
	int wl;
	int opc;
	struct _ea ea;
	t_value num;
	struct _rea rea;
	struct _mask mask;
	struct _brop brop;

#line 348 "m68kasm.c"

};
typedef union YYSTYPE YYSTYPE;
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  266
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   928

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  153
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  276
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  462

#define YYUNDEFTOK  2
#define YYMAXUTOK   401


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   147,     2,     2,     2,     2,
     151,   152,     2,     2,   148,   150,     2,   149,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   112,   112,   113,   114,   116,   117,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   160,   161,   164,   165,   166,   167,   171,
     172,   173,   174,   178,   179,   180,   184,   185,   186,   190,
     191,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   249,
     250,   251,   252,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   282,   283,   284,   285,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   308,   309,   310,   311,
     312,   313,   314,   318,   319,   320,   323,   324,   327,   328,
     331,   334,   337,   338,   339,   340,   341,   342,   343,   344,
     347,   348,   349,   350,   351,   352,   353,   354,   357,   360,
     361,   364,   365,   366,   369,   370,   371,   374,   375,   378,
     379,   382,   383,   384,   386,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   391,   391,   391,   391,   391,
     391,   391,   391,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   393,   393,   394,   394,   394,   394,   394,
     394,   394,   395,   395,   396,   396,   396,   396,   396,   396,
     397,   397,   397,   397,   397,   398,   398,   398,   398,   398,
     401,   403,   405,   407,   409,   411,   413,   415,   418,   420,
     423,   424,   426,   428,   431,   435,   436
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "A0", "A1", "A2", "A3", "A4", "A5", "A6",
  "A7", "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "CCR", "SR", "USP",
  "PC", "NUMBER", "ABCD", "ADD", "ADDA", "ADDI", "ADDQ", "ADDX", "AND",
  "ANDI", "OR", "ORI", "SBCD", "SUB", "SUBA", "SUBI", "SUBQ", "SUBX",
  "ASL", "ASR", "LSL", "LSR", "ROL", "ROR", "ROXL", "ROXR", "BCC", "BCS",
  "BEQ", "BGE", "BGT", "BHI", "BLE", "BLS", "BLT", "BMI", "BNE", "BPL",
  "BVC", "BVS", "BSR", "BRA", "BCLR", "BSET", "BCHG", "BTST", "CHK", "CMP",
  "CMPA", "CMPI", "CMPM", "EOR", "EORI", "EXG", "EXT", "DIVU", "DIVS",
  "MULU", "MULS", "DBCC", "DBCS", "DBEQ", "DBF", "DBGE", "DBGT", "DBHI",
  "DBLE", "DBLS", "DBLT", "DBMI", "DBNE", "DBPL", "DBT", "DBVC", "DBVS",
  "SCC", "SCS", "SEQ", "SF", "SGE", "SGT", "SHI", "SLE", "SLS", "SLT",
  "SMI", "SNE", "SPL", "ST", "SVC", "SVS", "ILLEGAL", "NOP", "RESET",
  "RTE", "RTR", "RTS", "TRAPV", "JMP", "JSR", "LEA", "LINK", "MOVE",
  "MOVEA", "MOVEM", "MOVEP", "MOVEQ", "CLR", "NEG", "NEGX", "NBCD", "NOT",
  "PEA", "STOP", "TAS", "SWAP", "TRAP", "TST", "UNLK", "PREDEC", "POSTINC",
  "BSIZE", "WSIZE", "LSIZE", "SSIZE", "'#'", "','", "'/'", "'-'", "'('",
  "')'", "$accept", "stmt", "arop", "bcdop", "dualop", "immop", "immop2",
  "qop", "shftop", "brop", "btop", "monop", "mdop", "dbop", "direct",
  "jop", "shftarg", "bcdarg", "dualarg", "areg", "dreg", "szs", "szwl",
  "szbwl", "szmv", "szm", "reglist", "regs", "eama", "eaa", "ead", "eaall",
  "eada", "eadas", "eac", "eacai", "eacad", "ea0", "ea1", "ea2", "ea3",
  "ea4", "ea5", "ea6", "ea70", "ea72", "ea73", "ea74", "easr", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,    35,    44,    47,
      45,    40,    41
};
# endif

#define YYPACT_NINF (-343)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     675,  -343,  -126,  -343,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -343,  -126,  -343,  -126,  -126,  -126,   456,   456,   456,
     456,   456,   456,   456,   456,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,  -343,  -343,  -343,  -343,   477,  -126,  -107,  -126,  -126,
    -126,  -126,   626,  -107,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,   -20,
     642,   141,  -105,  -107,  -107,  -137,  -126,  -126,  -126,  -343,
    -126,  -343,   -82,  -343,   646,   -80,  -126,   642,    72,  -107,
     557,    18,   -72,   -65,   -50,  -343,    78,    31,    76,   477,
     646,  -343,   -20,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,   642,    85,   203,
    -343,   236,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,   236,  -343,   236,  -343,   236,  -343,   236,
    -343,   236,  -343,   236,  -343,   236,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,   -37,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,    18,  -343,  -343,    18,  -343,   -42,
     646,  -343,   -36,   -35,   646,   203,   -32,  -343,  -343,  -343,
    -343,  -343,  -343,   -29,   -27,   -19,  -343,  -343,  -343,   -13,
      18,  -343,  -343,    76,   538,    41,    92,  -343,  -343,  -343,
    -343,   100,  -343,   113,  -343,  -343,  -343,    18,  -343,   -10,
      -9,  -343,    -8,    -7,   119,   120,   129,  -343,   131,     8,
     581,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,    15,
      16,  -343,    19,  -343,  -143,  -138,   149,  -343,    25,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,   646,  -343,    27,  -343,
      29,   642,    32,    33,   626,   626,  -343,    22,   642,    37,
      76,   642,   155,    39,    40,    35,    36,    43,    45,    47,
    -343,  -343,  -343,  -343,  -343,   166,    51,    54,    57,  -343,
    -343,    66,   646,    77,   515,   646,    71,    73,    74,    83,
      76,   -84,   646,   197,  -343,   605,  -107,  -343,  -343,    84,
     646,  -343,   646,   642,    93,   -42,    76,  -343,  -343,  -343,
    -343,  -343,   211,  -343,  -343,  -343,   546,   642,   642,   646,
    -135,   626,   626,    90,    88,   646,   646,   642,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
      76,   546,   515,    76,  -343,   642,  -343,  -343,   -68,   -67,
    -343,   646,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,   581,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,   642,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,   626,  -343,   626,  -343,  -343,    91,
    -107,  -107,  -107,  -107,   104,   106,   107,   109,  -343,  -343,
    -343,  -343
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    45,     0,    43,     0,     0,     0,     0,     0,     0,
       0,    47,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   110,   111,   109,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   136,   139,   138,   140,   141,
     142,   154,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   155,   152,   153,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     156,   157,   158,   159,   160,   161,   162,   163,   164,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   114,
       0,   165,     0,   134,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     0,     0,     0,     0,
       0,    24,     0,   191,   192,   193,    49,    53,    59,    46,
      50,    56,    51,    58,    52,    55,    60,    48,   172,   173,
     174,   175,   176,   177,   178,   179,   271,     0,     0,     0,
     261,     0,    61,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,     0,    63,     0,    65,     0,    67,     0,
      69,     0,    71,     0,    73,     0,    75,   188,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   180,   181,   182,   183,   184,   185,
     186,   187,   260,     0,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,     0,   189,   190,     0,    54,     0,
       0,    57,     0,     0,     0,     0,     0,   244,   245,   246,
     247,   248,   249,     0,     0,     0,   194,   195,   196,     0,
       0,   197,   198,     0,     0,     0,     0,   113,   115,   116,
     117,     0,    40,     0,   135,    42,     1,     0,     2,     0,
       0,     3,     0,     0,     0,     0,     0,     8,     0,     0,
       0,    12,   235,   236,   237,   238,   239,   240,   241,     0,
       0,    25,     0,   274,     0,     0,     0,    62,     0,    64,
      66,    68,    70,    72,    74,    76,     0,   234,     0,   233,
       0,     0,     0,     0,     0,     0,    23,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   202,     0,   199,     0,
     250,   251,   252,   253,   254,     0,     0,     0,     0,    38,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   264,     0,   269,   263,   262,     0,
       0,    11,     0,     0,     0,     0,     0,    20,    21,    22,
      19,    26,     0,    29,    30,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   169,
     170,   215,   216,   217,   218,   219,   220,   221,   222,   171,
       0,     0,     0,     0,     9,     0,    14,    17,     0,     0,
     268,     0,   166,    13,    15,    16,    18,    27,   275,   276,
     242,    28,   243,    32,   203,   204,     0,    33,   255,   256,
     257,   258,   259,   200,    34,     0,    35,    36,    37,    39,
       4,     6,     5,    10,     0,   270,     0,   265,   167,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   273,   272,
     267,   266
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,   248,  -343,  -343,   -39,
     -51,   811,   -53,   812,  -343,  -343,  -276,  -343,   559,  -162,
     115,  -150,  -120,  -159,   128,  -343,  -343,   -34,  -342,   -25,
     108,   137,   -30,    38,    69,    26,    28,   -33,  -343
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   297,   268,   271,   160,
     212,   188,   227,   136,   250,   253,   327,   328,   307,   390,
     213,   308,   420,   421,   236,   329,   427,   282,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   422
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     234,   233,   392,   156,   357,   355,   157,   187,   281,   356,
     256,   214,   223,   232,   358,   218,   426,   133,   134,   135,
     215,   148,   149,   150,   151,   152,   153,   154,   155,   204,
     205,   206,   207,   208,   209,   210,   211,   225,   226,   251,
     252,   156,   204,   205,   206,   207,   208,   209,   210,   211,
     254,   255,   204,   205,   206,   207,   208,   209,   210,   211,
     392,   243,   249,   262,   405,   261,   267,   263,   356,   238,
     272,   221,   266,   222,   237,   274,   279,   310,   265,   290,
     444,   446,   275,   219,   445,   447,   269,   204,   205,   206,
     207,   208,   209,   210,   211,   214,   223,   276,   286,   218,
     323,   277,   238,   283,   215,   433,   434,   237,   293,   311,
     298,   306,   314,   315,   220,   338,   318,   341,   292,   319,
     295,   320,   298,   339,   298,   241,   298,   242,   298,   321,
     298,   235,   298,   324,   298,   322,   340,   239,   342,   343,
     344,   345,   346,   347,   148,   149,   150,   151,   152,   153,
     154,   155,   348,   216,   349,   221,   350,   222,   241,   157,
     242,   244,   245,   352,   353,   158,   287,   219,   240,   159,
     239,   354,   359,   360,   358,   362,   375,   363,   278,   313,
     365,   366,   217,   316,   372,   378,   379,   376,   377,   383,
     309,   380,   335,   309,   381,   382,   317,   288,   220,   384,
     373,   240,   385,   326,   336,   386,   148,   149,   150,   151,
     152,   153,   154,   155,   387,   325,   309,   157,   157,   400,
     407,   401,   402,   286,   332,   337,   294,   280,   283,   330,
     404,   403,   411,   309,   417,   357,   284,   216,   435,   335,
     442,   295,   441,   447,   289,     0,   416,   204,   205,   206,
     207,   208,   209,   210,   211,   361,   458,   270,   459,   460,
     291,   461,     0,   368,   370,   285,   217,     0,     0,     0,
       0,     0,   364,     0,     0,   367,   369,     0,     0,   371,
     440,     0,   374,   443,   246,   247,   248,     0,     0,     0,
     286,   287,   333,     0,   399,   283,     0,     0,     0,     0,
       0,   406,     0,   410,     0,     0,     0,     0,   388,   412,
     391,   413,     0,     0,   396,     0,   409,     0,     0,   393,
     286,     0,   288,   334,   414,   283,     0,     0,   425,     0,
     326,   326,     0,     0,   437,   438,   286,   312,   423,   424,
       0,   283,   325,   325,     0,     0,   286,     0,   439,     0,
     430,   283,     0,     0,   436,   428,     0,     0,   287,     0,
     448,   284,   331,     0,     0,     0,   409,     0,   391,     0,
     286,   286,   396,   286,     0,   283,   283,   393,   283,     0,
       0,     0,   397,   296,     0,     0,     0,   317,   287,   288,
     285,     0,     0,   451,     0,   453,   449,   454,   455,   456,
     457,     0,     0,     0,   287,   450,     0,   452,     0,     0,
       0,     0,     0,   398,   287,     0,     0,     0,   431,   288,
       0,   299,     0,   300,     0,   301,     0,   302,   284,   303,
       0,   304,     0,   305,     0,   288,     0,     0,   287,   287,
     397,   287,     0,     0,     0,   288,     0,     0,     0,   432,
       0,     0,   394,     0,     0,     0,     0,   285,   284,   148,
     149,   150,   151,   152,   153,   154,   155,     0,     0,   288,
     288,   398,   288,   415,   284,     0,     0,     0,     0,   156,
     389,   395,     0,     0,   284,     0,     0,   285,   204,   205,
     206,   207,   208,   209,   210,   211,     0,     0,     0,     0,
     156,     0,     0,   285,     0,     0,     0,     0,   284,   284,
     394,   284,     0,   285,     0,     0,     0,   429,   148,   149,
     150,   151,   152,   153,   154,   155,   204,   205,   206,   207,
     208,   209,   210,   211,     0,     0,     0,   285,   285,   395,
     285,   148,   149,   150,   151,   152,   153,   154,   155,   204,
     205,   206,   207,   208,   209,   210,   211,   204,   205,   206,
     207,   208,   209,   210,   211,   418,   419,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   162,   174,   176,   178,
     180,   182,   184,   186,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,     0,   157,     0,   133,
     134,   135,     0,   158,   351,     0,     0,   159,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,   157,     0,
       0,     0,     0,     0,   158,     0,     0,   408,   159,   148,
     149,   150,   151,   152,   153,   154,   155,   204,   205,   206,
     207,   208,   209,   210,   211,   148,   149,   150,   151,   152,
     153,   154,   155,     0,     0,     0,   157,   204,   205,   206,
     207,   208,   209,   210,   211,     0,   280,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     273,     0,     0,     0,     0,     0,     0,   157,     0,   280,
       0,     0,     0,     0,     0,     0,     0,   280,   157,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   137,   138,   139,   140,
     141,   142,   143,     0,   144,     0,   145,   146,   147,   161,
     173,   175,   177,   179,   181,   183,   185,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,     0,     0,     0,     0,     0,     0,   224,     0,
     228,   229,   230,   231,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   257,   258,
     259,     0,   260,     0,     0,     0,     0,     0,   264
};

static const yytype_int16 yycheck[] =
{
      53,    52,   344,    23,   142,   148,   141,   146,   128,   152,
     147,    45,    45,    52,   152,    45,   151,   143,   144,   145,
      45,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,   144,   145,   144,
     145,    23,    11,    12,    13,    14,    15,    16,    17,    18,
     103,   104,    11,    12,    13,    14,    15,    16,    17,    18,
     402,   100,   101,   114,   148,   147,   119,   147,   152,    99,
     121,    45,     0,    45,    99,   147,   127,   227,   117,   130,
     148,   148,   147,    45,   152,   152,   120,    11,    12,    13,
      14,    15,    16,    17,    18,   129,   129,   147,   128,   129,
     250,    23,   132,   128,   129,   381,   382,   132,    23,   151,
     161,   148,   148,   148,    45,    23,   148,   267,   157,   148,
     159,   148,   173,    23,   175,    99,   177,    99,   179,   148,
     181,   151,   183,   253,   185,   148,    23,    99,   148,   148,
     148,   148,    23,    23,     3,     4,     5,     6,     7,     8,
       9,    10,    23,    45,    23,   129,   148,   129,   132,   141,
     132,    20,    21,   148,   148,   147,   128,   129,    99,   151,
     132,   152,    23,   148,   152,   148,    21,   148,   147,   230,
     148,   148,    45,   234,   147,   150,   150,   148,   148,    23,
     224,   148,   151,   227,   149,   148,   235,   128,   129,   148,
     320,   132,   148,   254,   255,   148,     3,     4,     5,     6,
       7,     8,     9,    10,   148,   254,   250,   141,   141,   148,
      23,   148,   148,   253,   254,   255,    23,   151,   253,   254,
     350,   148,   148,   267,    23,   142,   128,   129,   148,   151,
     402,   280,   401,   152,   129,    -1,   366,    11,    12,    13,
      14,    15,    16,    17,    18,   306,   152,   120,   152,   152,
     132,   152,    -1,   314,   315,   128,   129,    -1,    -1,    -1,
      -1,    -1,   311,    -1,    -1,   314,   315,    -1,    -1,   318,
     400,    -1,   321,   403,   143,   144,   145,    -1,    -1,    -1,
     320,   253,   254,    -1,   345,   320,    -1,    -1,    -1,    -1,
      -1,   352,    -1,   356,    -1,    -1,    -1,    -1,   342,   360,
     344,   362,    -1,    -1,   344,    -1,   355,    -1,    -1,   344,
     350,    -1,   253,   254,   363,   350,    -1,    -1,   379,    -1,
     381,   382,    -1,    -1,   385,   386,   366,   229,   377,   378,
      -1,   366,   381,   382,    -1,    -1,   376,    -1,   387,    -1,
     380,   376,    -1,    -1,   384,   380,    -1,    -1,   320,    -1,
     411,   253,   254,    -1,    -1,    -1,   405,    -1,   402,    -1,
     400,   401,   402,   403,    -1,   400,   401,   402,   403,    -1,
      -1,    -1,   344,   147,    -1,    -1,    -1,   426,   350,   320,
     253,    -1,    -1,   444,    -1,   446,   435,   450,   451,   452,
     453,    -1,    -1,    -1,   366,   444,    -1,   446,    -1,    -1,
      -1,    -1,    -1,   344,   376,    -1,    -1,    -1,   380,   350,
      -1,   173,    -1,   175,    -1,   177,    -1,   179,   320,   181,
      -1,   183,    -1,   185,    -1,   366,    -1,    -1,   400,   401,
     402,   403,    -1,    -1,    -1,   376,    -1,    -1,    -1,   380,
      -1,    -1,   344,    -1,    -1,    -1,    -1,   320,   350,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,   400,
     401,   402,   403,   365,   366,    -1,    -1,    -1,    -1,    23,
     343,   344,    -1,    -1,   376,    -1,    -1,   350,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      23,    -1,    -1,   366,    -1,    -1,    -1,    -1,   400,   401,
     402,   403,    -1,   376,    -1,    -1,    -1,   380,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,   400,   401,   402,
     403,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    17,    18,    19,    20,
      21,    22,    23,    24,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,   141,    -1,   143,
     144,   145,    -1,   147,    23,    -1,    -1,   151,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,   141,    -1,
      -1,    -1,    -1,    -1,   147,    -1,    -1,    22,   151,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,   141,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,   151,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,   151,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,   141,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     4,     5,     6,     7,
       8,     9,    10,    -1,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   143,   144,   145,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,     3,     4,
       5,     6,     7,     8,     9,    10,    23,   141,   147,   151,
     172,   176,   181,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   176,   181,   176,   181,   176,   181,   176,
     181,   176,   181,   176,   181,   176,   181,   146,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,    11,    12,    13,    14,    15,    16,
      17,    18,   173,   183,   190,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   176,   144,   145,   175,   176,   176,
     176,   176,   172,   173,   175,   151,   187,   192,   195,   196,
     197,   198,   199,   172,    20,    21,   143,   144,   145,   172,
     177,   144,   145,   178,   175,   175,   147,   176,   176,   176,
     176,   147,   173,   147,   176,   172,     0,   175,   170,   190,
     194,   171,   173,   181,   147,   147,   147,    23,   147,   173,
     151,   185,   190,   192,   193,   194,   195,   196,   197,   183,
     173,   187,   172,    23,    23,   172,   147,   169,   173,   169,
     169,   169,   169,   169,   169,   169,   148,   181,   184,   190,
     184,   151,   193,   173,   148,   148,   173,   172,   148,   148,
     148,   148,   148,   184,   185,   172,   173,   179,   180,   188,
     192,   193,   195,   196,   197,   151,   173,   195,    23,    23,
      23,   184,   148,   148,   148,   148,    23,    23,    23,    23,
     148,    23,   148,   148,   152,   148,   152,   142,   152,    23,
     148,   173,   148,   148,   172,   148,   148,   172,   173,   172,
     173,   172,   147,   185,   172,    21,   148,   148,   150,   150,
     148,   149,   148,    23,   148,   148,   148,   148,   190,   194,
     182,   190,   191,   192,   193,   194,   195,   196,   197,   173,
     148,   148,   148,   148,   185,   148,   173,    23,    22,   172,
     175,   148,   173,   173,   172,   193,   185,    23,    19,    20,
     185,   186,   201,   172,   172,   173,   151,   189,   192,   194,
     195,   196,   197,   179,   179,   148,   195,   173,   173,   172,
     185,   186,   182,   185,   148,   152,   148,   152,   173,   172,
     172,   173,   172,   173,   175,   175,   175,   175,   152,   152,
     152,   152
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   153,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   155,   155,   156,   156,   156,   156,   157,
     157,   157,   157,   158,   158,   158,   159,   159,   159,   160,
     160,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   163,
     163,   163,   163,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   165,   165,   165,   165,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   167,   167,   167,   167,
     167,   167,   167,   168,   168,   168,   169,   169,   170,   170,
     171,   171,   172,   172,   172,   172,   172,   172,   172,   172,
     173,   173,   173,   173,   173,   173,   173,   173,   174,   175,
     175,   176,   176,   176,   177,   177,   177,   178,   178,   179,
     179,   180,   180,   180,   180,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   182,   182,   182,   182,   182,
     182,   182,   182,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   184,   184,   185,   185,   185,   185,   185,
     185,   185,   186,   186,   187,   187,   187,   187,   187,   187,
     188,   188,   188,   188,   188,   189,   189,   189,   189,   189,
     190,   191,   192,   193,   194,   195,   196,   196,   197,   197,
     198,   198,   199,   199,   200,   201,   201
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     5,     5,     5,     1,     2,     4,
       5,     4,     2,     5,     4,     5,     5,     4,     5,     4,
       4,     4,     4,     3,     1,     2,     4,     5,     5,     4,
       4,     4,     5,     5,     5,     5,     5,     5,     3,     5,
       2,     3,     2,     1,     1,     1,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     3,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     3,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     2,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     5,     8,     8,     4,     3,
       5,     1,     8,     8,     2,     1,     1
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
                       yystos[yyssp[yyi + 1 - yynrhs]],
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
      int yyn = yypact[*yyssp];
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
#line 112 "m68kasm.y.txt"
                     { _genop((yyvsp[-1].opc) | (yyvsp[0].opc)); yyrc = -1; }
#line 1971 "m68kasm.c"
    break;

  case 3:
#line 113 "m68kasm.y.txt"
                       { _genop((yyvsp[-1].opc) | (yyvsp[0].rea).reg | (yyvsp[0].rea).ea.ea); yyrc = _genea((yyvsp[0].rea).ea) -1; }
#line 1977 "m68kasm.c"
    break;

  case 4:
#line 114 "m68kasm.y.txt"
                              { _genop((yyvsp[-4].opc) | (yyvsp[0].ea).ea); if (oplen==0) { _genop((yyvsp[-2].num) & 0xff); yyrc = _genea((yyvsp[0].ea)) - 3; }
		else if (oplen==1) { _genop((yyvsp[-2].num)); yyrc = _genea((yyvsp[0].ea)) - 3; } else { _genop((yyvsp[-2].num)>>16); _genop((yyvsp[-2].num) & 0xffff); yyrc = _genea((yyvsp[0].ea))-5; } }
#line 1984 "m68kasm.c"
    break;

  case 5:
#line 116 "m68kasm.y.txt"
                           { _genop((yyvsp[-4].opc) | (((yyvsp[-2].num)&7)<<9) | (yyvsp[0].ea).ea); yyrc = _genea((yyvsp[0].ea)) - 1; }
#line 1990 "m68kasm.c"
    break;

  case 6:
#line 117 "m68kasm.y.txt"
                                { _genop((yyvsp[-4].opc) | (yyvsp[0].ea).ea); if (oplen==0) { _genop((yyvsp[-2].num) & 0xff); yyrc = _genea((yyvsp[0].ea)) - 3; }
		else if (oplen==1) { _genop((yyvsp[-2].num)); yyrc = _genea((yyvsp[0].ea)) - 3; } else { _genop((yyvsp[-2].num)>>16); _genop((yyvsp[-2].num) & 0xffff); yyrc = _genea((yyvsp[0].ea))-5; } }
#line 1997 "m68kasm.c"
    break;

  case 7:
#line 119 "m68kasm.y.txt"
           { _genop((yyvsp[0].rea).reg); if (((yyvsp[0].rea).reg&0xc0)==0xc0) yyrc = _genea((yyvsp[0].rea).ea) - 1; else { yyrc = -1; } }
#line 2003 "m68kasm.c"
    break;

  case 8:
#line 120 "m68kasm.y.txt"
                    { yyrc = _genbr((yyvsp[-1].brop).opc,(yyvsp[0].num),(yyvsp[-1].brop).len); }
#line 2009 "m68kasm.c"
    break;

  case 9:
#line 121 "m68kasm.y.txt"
                           { _genop((yyvsp[-3].opc) | ((yyvsp[-2].reg)<<9) | 0x100 | (yyvsp[0].ea).ea); yyrc = _genea((yyvsp[0].ea)) - 1; }
#line 2015 "m68kasm.c"
    break;

  case 10:
#line 122 "m68kasm.y.txt"
                                 { _genop((yyvsp[-4].opc) | 0x0800 | (yyvsp[0].ea).ea); _genop((yyvsp[-2].num)); yyrc = _genea((yyvsp[0].ea)) - 3; }
#line 2021 "m68kasm.c"
    break;

  case 11:
#line 123 "m68kasm.y.txt"
                         { _genop(0x4180 | ((yyvsp[0].reg)<<9) | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2027 "m68kasm.c"
    break;

  case 12:
#line 124 "m68kasm.y.txt"
                   { _genop((yyvsp[-1].opc) | (yyvsp[0].ea).ea); yyrc = _genea((yyvsp[0].ea)) - 1; }
#line 2033 "m68kasm.c"
    break;

  case 13:
#line 125 "m68kasm.y.txt"
                                 { _genop(0xb000 | ((yyvsp[-3].wl)<<6) | ((yyvsp[0].reg)<<9) | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2039 "m68kasm.c"
    break;

  case 14:
#line 126 "m68kasm.y.txt"
                          { _genop((yyvsp[-3].opc) | ((yyvsp[0].reg)<<9) | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2045 "m68kasm.c"
    break;

  case 15:
#line 127 "m68kasm.y.txt"
                                 { _genop(0xb0c0 | ((yyvsp[-3].wl)<<8) | ((yyvsp[0].reg)<<9) | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2051 "m68kasm.c"
    break;

  case 16:
#line 128 "m68kasm.y.txt"
                               { _genop(0xb108 | ((yyvsp[0].ea).ea<<9) | ((yyvsp[-3].wl)<<6) | (yyvsp[-2].ea).ea); yyrc = -1; }
#line 2057 "m68kasm.c"
    break;

  case 17:
#line 129 "m68kasm.y.txt"
                             { yyrc = _genbr((yyvsp[-3].opc) | (yyvsp[-2].reg), (yyvsp[0].num), 1); }
#line 2063 "m68kasm.c"
    break;

  case 18:
#line 130 "m68kasm.y.txt"
                                { _genop(0xb000 | ((yyvsp[-3].wl) << 6) | 0x100 | (yyvsp[0].ea).ea); yyrc = _genea((yyvsp[0].ea)) - 1; }
#line 2069 "m68kasm.c"
    break;

  case 19:
#line 131 "m68kasm.y.txt"
                          { _genop(0xc140 | ((yyvsp[-2].reg)<<9) | (yyvsp[0].reg)); yyrc = -1; }
#line 2075 "m68kasm.c"
    break;

  case 20:
#line 132 "m68kasm.y.txt"
                          { _genop(0xc148 | ((yyvsp[-2].reg)<<9) | (yyvsp[0].reg)); yyrc = -1; }
#line 2081 "m68kasm.c"
    break;

  case 21:
#line 133 "m68kasm.y.txt"
                          { _genop(0xc188 | ((yyvsp[0].reg)<<9) | (yyvsp[-2].reg)); yyrc = -1; }
#line 2087 "m68kasm.c"
    break;

  case 22:
#line 134 "m68kasm.y.txt"
                          { _genop(0xc188 | ((yyvsp[-2].reg)<<9) | (yyvsp[0].reg)); yyrc = -1; }
#line 2093 "m68kasm.c"
    break;

  case 23:
#line 135 "m68kasm.y.txt"
                      { _genop(0x4840 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].reg)); yyrc = -1; }
#line 2099 "m68kasm.c"
    break;

  case 24:
#line 136 "m68kasm.y.txt"
               { _genop((yyvsp[0].opc)); yyrc = -1; }
#line 2105 "m68kasm.c"
    break;

  case 25:
#line 137 "m68kasm.y.txt"
                { _genop((yyvsp[-1].opc) | (yyvsp[0].ea).ea); yyrc = _genea((yyvsp[0].ea)) -1; }
#line 2111 "m68kasm.c"
    break;

  case 26:
#line 138 "m68kasm.y.txt"
                         { _genop(0x41c0 | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2117 "m68kasm.c"
    break;

  case 27:
#line 139 "m68kasm.y.txt"
                                 { _genop(0x4e50 | (yyvsp[-3].reg)); _genop((yyvsp[0].num)); yyrc = -3; }
#line 2123 "m68kasm.c"
    break;

  case 28:
#line 140 "m68kasm.y.txt"
                                  { if ((yyvsp[0].ea).ea==074) { _genop(0x44c0 | ((yyvsp[0].ea).cnt==1?0x0200:0x0000) | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
							    else { int tmp = (((yyvsp[0].ea).ea&070)>>3)|(((yyvsp[0].ea).ea&7)<<3); _genop(0x0000 | ((yyvsp[-3].wl)<<12) | (tmp<<6) | (yyvsp[-2].ea).ea);
    	                           	   yyrc = _genea((yyvsp[-2].ea)) - 1; yyrc += _genea((yyvsp[0].ea)); } }
#line 2131 "m68kasm.c"
    break;

  case 29:
#line 143 "m68kasm.y.txt"
                         { _genop(0x40c0 | (yyvsp[0].ea).ea); yyrc = _genea((yyvsp[0].ea)) - 1; }
#line 2137 "m68kasm.c"
    break;

  case 30:
#line 144 "m68kasm.y.txt"
                          { _genop(0x4e68 | (yyvsp[0].reg));  yyrc = -1; }
#line 2143 "m68kasm.c"
    break;

  case 31:
#line 145 "m68kasm.y.txt"
                          { _genop(0x4e60 | (yyvsp[-2].reg));  yyrc = -1; }
#line 2149 "m68kasm.c"
    break;

  case 32:
#line 146 "m68kasm.y.txt"
                                { _genop(0x0040 | ((yyvsp[-3].wl)<<12) | ((yyvsp[0].reg)<<9) | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2155 "m68kasm.c"
    break;

  case 33:
#line 147 "m68kasm.y.txt"
                                     { _genop(0x4880 | ((yyvsp[-3].wl)<<6) | (yyvsp[0].ea).ea); _genop(((yyvsp[0].ea).ea&070)==040 ? (yyvsp[-2].mask).d : (yyvsp[-2].mask).x); yyrc = _genea((yyvsp[0].ea)) - 3; }
#line 2161 "m68kasm.c"
    break;

  case 34:
#line 148 "m68kasm.y.txt"
                                      { _genop(0x4c80 | ((yyvsp[-3].wl)<<6) | (yyvsp[-2].ea).ea); _genop((yyvsp[0].mask).x); yyrc = _genea((yyvsp[-2].ea)) - 3; }
#line 2167 "m68kasm.c"
    break;

  case 35:
#line 149 "m68kasm.y.txt"
                                { _genop(0x0108 | ((yyvsp[-2].reg)<<9) | ((yyvsp[-3].wl)<<6) | ((yyvsp[0].ea).ea & 7)); yyrc = _genea((yyvsp[0].ea)) - 1; }
#line 2173 "m68kasm.c"
    break;

  case 36:
#line 150 "m68kasm.y.txt"
                                { _genop(0x0188 | ((yyvsp[0].reg)<<9) | ((yyvsp[-3].wl)<<6) | ((yyvsp[-2].ea).ea & 7)); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2179 "m68kasm.c"
    break;

  case 37:
#line 151 "m68kasm.y.txt"
                              { _genop(0x7000 | ((yyvsp[0].reg)<<9) | ((yyvsp[-2].num)&0xff)); yyrc = -1; }
#line 2185 "m68kasm.c"
    break;

  case 38:
#line 152 "m68kasm.y.txt"
                        { _genop(0x4e72); yyrc = _genop((yyvsp[0].num)&0xffff) - 1; }
#line 2191 "m68kasm.c"
    break;

  case 39:
#line 153 "m68kasm.y.txt"
                                 { _genop((yyvsp[-4].opc) | ((yyvsp[0].reg)<<9) | ((yyvsp[-3].wl)<<8) | (yyvsp[-2].ea).ea); yyrc = _genea((yyvsp[-2].ea)) - 1; }
#line 2197 "m68kasm.c"
    break;

  case 40:
#line 154 "m68kasm.y.txt"
                  { _genop(0x4840 | (yyvsp[0].reg)); yyrc = -1; }
#line 2203 "m68kasm.c"
    break;

  case 41:
#line 155 "m68kasm.y.txt"
                        { _genop(0x4e40 | ((yyvsp[0].num) & 0x0f)); yyrc = -1; }
#line 2209 "m68kasm.c"
    break;

  case 42:
#line 156 "m68kasm.y.txt"
                  { _genop(0x4e58 | (yyvsp[0].reg)); yyrc = -1; }
#line 2215 "m68kasm.c"
    break;

  case 43:
#line 160 "m68kasm.y.txt"
             { (yyval.opc) = 0xd0c0; }
#line 2221 "m68kasm.c"
    break;

  case 44:
#line 161 "m68kasm.y.txt"
             { (yyval.opc) = 0x90c0; }
#line 2227 "m68kasm.c"
    break;

  case 45:
#line 164 "m68kasm.y.txt"
             { (yyval.opc) = 0xc100; }
#line 2233 "m68kasm.c"
    break;

  case 46:
#line 165 "m68kasm.y.txt"
                   { (yyval.opc) = 0xd100 | ((yyvsp[0].wl)<<6); }
#line 2239 "m68kasm.c"
    break;

  case 47:
#line 166 "m68kasm.y.txt"
             { (yyval.opc) = 0x8100; }
#line 2245 "m68kasm.c"
    break;

  case 48:
#line 167 "m68kasm.y.txt"
                   { (yyval.opc) = 0x9100 | ((yyvsp[0].wl)<<6); }
#line 2251 "m68kasm.c"
    break;

  case 49:
#line 171 "m68kasm.y.txt"
                  { (yyval.opc) = 0xd000 | ((yyvsp[0].wl)<<6); }
#line 2257 "m68kasm.c"
    break;

  case 50:
#line 172 "m68kasm.y.txt"
                  { (yyval.opc) = 0xc000 | ((yyvsp[0].wl)<<6); }
#line 2263 "m68kasm.c"
    break;

  case 51:
#line 173 "m68kasm.y.txt"
                  { (yyval.opc) = 0x8000 | ((yyvsp[0].wl)<<6); }
#line 2269 "m68kasm.c"
    break;

  case 52:
#line 174 "m68kasm.y.txt"
                  { (yyval.opc) = 0x9000 | ((yyvsp[0].wl)<<6); }
#line 2275 "m68kasm.c"
    break;

  case 53:
#line 178 "m68kasm.y.txt"
                   { (yyval.opc) = 0x0600 | ((yyvsp[0].wl)<<6); }
#line 2281 "m68kasm.c"
    break;

  case 54:
#line 179 "m68kasm.y.txt"
                   { (yyval.opc) = 0x0c00 | ((yyvsp[0].wl)<<6); }
#line 2287 "m68kasm.c"
    break;

  case 55:
#line 180 "m68kasm.y.txt"
                   { (yyval.opc) = 0x0400 | ((yyvsp[0].wl)<<6); }
#line 2293 "m68kasm.c"
    break;

  case 56:
#line 184 "m68kasm.y.txt"
                   { (yyval.opc) = 0x0200 | ((yyvsp[0].wl)<<6); }
#line 2299 "m68kasm.c"
    break;

  case 57:
#line 185 "m68kasm.y.txt"
                   { (yyval.opc) = 0x0a00 | ((yyvsp[0].wl)<<6); }
#line 2305 "m68kasm.c"
    break;

  case 58:
#line 186 "m68kasm.y.txt"
                   { (yyval.opc) = 0x0000 | ((yyvsp[0].wl)<<6); }
#line 2311 "m68kasm.c"
    break;

  case 59:
#line 190 "m68kasm.y.txt"
                   { (yyval.opc) = 0x5000 | ((yyvsp[0].wl)<<6); }
#line 2317 "m68kasm.c"
    break;

  case 60:
#line 191 "m68kasm.y.txt"
                   { (yyval.opc) = 0x5100 | ((yyvsp[0].wl)<<6); }
#line 2323 "m68kasm.c"
    break;

  case 61:
#line 195 "m68kasm.y.txt"
                 { (yyval.rea).reg = 0xe1c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2329 "m68kasm.c"
    break;

  case 62:
#line 196 "m68kasm.y.txt"
                          { (yyval.rea).reg = 0xe100 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2335 "m68kasm.c"
    break;

  case 63:
#line 197 "m68kasm.y.txt"
                 { (yyval.rea).reg = 0xe0c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2341 "m68kasm.c"
    break;

  case 64:
#line 198 "m68kasm.y.txt"
                          { (yyval.rea).reg = 0xe000 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2347 "m68kasm.c"
    break;

  case 65:
#line 199 "m68kasm.y.txt"
                 { (yyval.rea).reg = 0xe3c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2353 "m68kasm.c"
    break;

  case 66:
#line 200 "m68kasm.y.txt"
                          { (yyval.rea).reg = 0xe108 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2359 "m68kasm.c"
    break;

  case 67:
#line 201 "m68kasm.y.txt"
                 { (yyval.rea).reg = 0xe2c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2365 "m68kasm.c"
    break;

  case 68:
#line 202 "m68kasm.y.txt"
                          { (yyval.rea).reg = 0xe008 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2371 "m68kasm.c"
    break;

  case 69:
#line 203 "m68kasm.y.txt"
                 { (yyval.rea).reg = 0xe7c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2377 "m68kasm.c"
    break;

  case 70:
#line 204 "m68kasm.y.txt"
                          { (yyval.rea).reg = 0xe118 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2383 "m68kasm.c"
    break;

  case 71:
#line 205 "m68kasm.y.txt"
                 { (yyval.rea).reg = 0xe6c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2389 "m68kasm.c"
    break;

  case 72:
#line 206 "m68kasm.y.txt"
                          { (yyval.rea).reg = 0xe018 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2395 "m68kasm.c"
    break;

  case 73:
#line 207 "m68kasm.y.txt"
                  { (yyval.rea).reg = 0xe5c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2401 "m68kasm.c"
    break;

  case 74:
#line 208 "m68kasm.y.txt"
                           { (yyval.rea).reg = 0xe100 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2407 "m68kasm.c"
    break;

  case 75:
#line 209 "m68kasm.y.txt"
                  { (yyval.rea).reg = 0xe4c0 | (yyvsp[0].ea).ea; (yyval.rea).ea = (yyvsp[0].ea); }
#line 2413 "m68kasm.c"
    break;

  case 76:
#line 210 "m68kasm.y.txt"
                           { (yyval.rea).reg = 0xe000 | ((yyvsp[-1].wl)<<6) | (yyvsp[0].opc); }
#line 2419 "m68kasm.c"
    break;

  case 77:
#line 214 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6400; (yyval.brop).len = 1; }
#line 2425 "m68kasm.c"
    break;

  case 78:
#line 215 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6500; (yyval.brop).len = 1; }
#line 2431 "m68kasm.c"
    break;

  case 79:
#line 216 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6700; (yyval.brop).len = 1; }
#line 2437 "m68kasm.c"
    break;

  case 80:
#line 217 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6c00; (yyval.brop).len = 1; }
#line 2443 "m68kasm.c"
    break;

  case 81:
#line 218 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6e00; (yyval.brop).len = 1; }
#line 2449 "m68kasm.c"
    break;

  case 82:
#line 219 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6200; (yyval.brop).len = 1; }
#line 2455 "m68kasm.c"
    break;

  case 83:
#line 220 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6f00; (yyval.brop).len = 1; }
#line 2461 "m68kasm.c"
    break;

  case 84:
#line 221 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6300; (yyval.brop).len = 1; }
#line 2467 "m68kasm.c"
    break;

  case 85:
#line 222 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6d00; (yyval.brop).len = 1; }
#line 2473 "m68kasm.c"
    break;

  case 86:
#line 223 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6b00; (yyval.brop).len = 1; }
#line 2479 "m68kasm.c"
    break;

  case 87:
#line 224 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6600; (yyval.brop).len = 1; }
#line 2485 "m68kasm.c"
    break;

  case 88:
#line 225 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6a00; (yyval.brop).len = 1; }
#line 2491 "m68kasm.c"
    break;

  case 89:
#line 226 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6800; (yyval.brop).len = 1; }
#line 2497 "m68kasm.c"
    break;

  case 90:
#line 227 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6900; (yyval.brop).len = 1; }
#line 2503 "m68kasm.c"
    break;

  case 91:
#line 228 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6100; (yyval.brop).len = 1; }
#line 2509 "m68kasm.c"
    break;

  case 92:
#line 229 "m68kasm.y.txt"
            { (yyval.brop).opc = 0x6000; (yyval.brop).len = 1; }
#line 2515 "m68kasm.c"
    break;

  case 93:
#line 230 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6400; (yyval.brop).len = 0; }
#line 2521 "m68kasm.c"
    break;

  case 94:
#line 231 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6500; (yyval.brop).len = 0; }
#line 2527 "m68kasm.c"
    break;

  case 95:
#line 232 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6700; (yyval.brop).len = 0; }
#line 2533 "m68kasm.c"
    break;

  case 96:
#line 233 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6c00; (yyval.brop).len = 0; }
#line 2539 "m68kasm.c"
    break;

  case 97:
#line 234 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6e00; (yyval.brop).len = 0; }
#line 2545 "m68kasm.c"
    break;

  case 98:
#line 235 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6200; (yyval.brop).len = 0; }
#line 2551 "m68kasm.c"
    break;

  case 99:
#line 236 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6f00; (yyval.brop).len = 0; }
#line 2557 "m68kasm.c"
    break;

  case 100:
#line 237 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6300; (yyval.brop).len = 0; }
#line 2563 "m68kasm.c"
    break;

  case 101:
#line 238 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6d00; (yyval.brop).len = 0; }
#line 2569 "m68kasm.c"
    break;

  case 102:
#line 239 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6b00; (yyval.brop).len = 0; }
#line 2575 "m68kasm.c"
    break;

  case 103:
#line 240 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6600; (yyval.brop).len = 0; }
#line 2581 "m68kasm.c"
    break;

  case 104:
#line 241 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6a00; (yyval.brop).len = 0; }
#line 2587 "m68kasm.c"
    break;

  case 105:
#line 242 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6800; (yyval.brop).len = 0; }
#line 2593 "m68kasm.c"
    break;

  case 106:
#line 243 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6900; (yyval.brop).len = 0; }
#line 2599 "m68kasm.c"
    break;

  case 107:
#line 244 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6100; (yyval.brop).len = 0; }
#line 2605 "m68kasm.c"
    break;

  case 108:
#line 245 "m68kasm.y.txt"
                { (yyval.brop).opc = 0x6000; (yyval.brop).len = 0; }
#line 2611 "m68kasm.c"
    break;

  case 109:
#line 249 "m68kasm.y.txt"
             { (yyval.opc) = 0x0040; }
#line 2617 "m68kasm.c"
    break;

  case 110:
#line 250 "m68kasm.y.txt"
             { (yyval.opc) = 0x0080; }
#line 2623 "m68kasm.c"
    break;

  case 111:
#line 251 "m68kasm.y.txt"
             { (yyval.opc) = 0x00c0; }
#line 2629 "m68kasm.c"
    break;

  case 112:
#line 252 "m68kasm.y.txt"
             { (yyval.opc) = 0x0000; }
#line 2635 "m68kasm.c"
    break;

  case 113:
#line 256 "m68kasm.y.txt"
                  { (yyval.opc) = 0x4200 | ((yyvsp[0].wl)<<6); }
#line 2641 "m68kasm.c"
    break;

  case 114:
#line 257 "m68kasm.y.txt"
             { (yyval.opc) = 0x4800; }
#line 2647 "m68kasm.c"
    break;

  case 115:
#line 258 "m68kasm.y.txt"
                  { (yyval.opc) = 0x4400 | ((yyvsp[0].wl)<<6); }
#line 2653 "m68kasm.c"
    break;

  case 116:
#line 259 "m68kasm.y.txt"
                   { (yyval.opc) = 0x4000 | ((yyvsp[0].wl)<<6); }
#line 2659 "m68kasm.c"
    break;

  case 117:
#line 260 "m68kasm.y.txt"
                  { (yyval.opc) = 0x4600 | ((yyvsp[0].wl)<<6); }
#line 2665 "m68kasm.c"
    break;

  case 118:
#line 261 "m68kasm.y.txt"
            { (yyval.opc) = 0x54c0; }
#line 2671 "m68kasm.c"
    break;

  case 119:
#line 262 "m68kasm.y.txt"
            { (yyval.opc) = 0x55c0; }
#line 2677 "m68kasm.c"
    break;

  case 120:
#line 263 "m68kasm.y.txt"
            { (yyval.opc) = 0x57c0; }
#line 2683 "m68kasm.c"
    break;

  case 121:
#line 264 "m68kasm.y.txt"
           { (yyval.opc) = 0x51c0; }
#line 2689 "m68kasm.c"
    break;

  case 122:
#line 265 "m68kasm.y.txt"
            { (yyval.opc) = 0x5cc0; }
#line 2695 "m68kasm.c"
    break;

  case 123:
#line 266 "m68kasm.y.txt"
            { (yyval.opc) = 0x5ec0; }
#line 2701 "m68kasm.c"
    break;

  case 124:
#line 267 "m68kasm.y.txt"
            { (yyval.opc) = 0x52c0; }
#line 2707 "m68kasm.c"
    break;

  case 125:
#line 268 "m68kasm.y.txt"
            { (yyval.opc) = 0x5fc0; }
#line 2713 "m68kasm.c"
    break;

  case 126:
#line 269 "m68kasm.y.txt"
            { (yyval.opc) = 0x53c0; }
#line 2719 "m68kasm.c"
    break;

  case 127:
#line 270 "m68kasm.y.txt"
            { (yyval.opc) = 0x5dc0; }
#line 2725 "m68kasm.c"
    break;

  case 128:
#line 271 "m68kasm.y.txt"
            { (yyval.opc) = 0x5bc0; }
#line 2731 "m68kasm.c"
    break;

  case 129:
#line 272 "m68kasm.y.txt"
            { (yyval.opc) = 0x56c0; }
#line 2737 "m68kasm.c"
    break;

  case 130:
#line 273 "m68kasm.y.txt"
            { (yyval.opc) = 0x5ac0; }
#line 2743 "m68kasm.c"
    break;

  case 131:
#line 274 "m68kasm.y.txt"
           { (yyval.opc) = 0x50c0; }
#line 2749 "m68kasm.c"
    break;

  case 132:
#line 275 "m68kasm.y.txt"
            { (yyval.opc) = 0x58c0; }
#line 2755 "m68kasm.c"
    break;

  case 133:
#line 276 "m68kasm.y.txt"
            { (yyval.opc) = 0x59c0; }
#line 2761 "m68kasm.c"
    break;

  case 134:
#line 277 "m68kasm.y.txt"
            { (yyval.opc) = 0x4ac0; }
#line 2767 "m68kasm.c"
    break;

  case 135:
#line 278 "m68kasm.y.txt"
                  { (yyval.opc) = 0x4a00 | ((yyvsp[0].wl)<<6); }
#line 2773 "m68kasm.c"
    break;

  case 136:
#line 282 "m68kasm.y.txt"
             { (yyval.opc) = 0x81c0; }
#line 2779 "m68kasm.c"
    break;

  case 137:
#line 283 "m68kasm.y.txt"
             { (yyval.opc) = 0x80c0; }
#line 2785 "m68kasm.c"
    break;

  case 138:
#line 284 "m68kasm.y.txt"
             { (yyval.opc) = 0xc1c0; }
#line 2791 "m68kasm.c"
    break;

  case 139:
#line 285 "m68kasm.y.txt"
             { (yyval.opc) = 0xc0c0; }
#line 2797 "m68kasm.c"
    break;

  case 140:
#line 289 "m68kasm.y.txt"
             { (yyval.opc) = 0x54c8; }
#line 2803 "m68kasm.c"
    break;

  case 141:
#line 290 "m68kasm.y.txt"
             { (yyval.opc) = 0x55c8; }
#line 2809 "m68kasm.c"
    break;

  case 142:
#line 291 "m68kasm.y.txt"
             { (yyval.opc) = 0x57c8; }
#line 2815 "m68kasm.c"
    break;

  case 143:
#line 292 "m68kasm.y.txt"
             { (yyval.opc) = 0x5cc8; }
#line 2821 "m68kasm.c"
    break;

  case 144:
#line 293 "m68kasm.y.txt"
             { (yyval.opc) = 0x5ec8; }
#line 2827 "m68kasm.c"
    break;

  case 145:
#line 294 "m68kasm.y.txt"
             { (yyval.opc) = 0x52c8; }
#line 2833 "m68kasm.c"
    break;

  case 146:
#line 295 "m68kasm.y.txt"
             { (yyval.opc) = 0x5fc8; }
#line 2839 "m68kasm.c"
    break;

  case 147:
#line 296 "m68kasm.y.txt"
             { (yyval.opc) = 0x53c8; }
#line 2845 "m68kasm.c"
    break;

  case 148:
#line 297 "m68kasm.y.txt"
             { (yyval.opc) = 0x5dc8; }
#line 2851 "m68kasm.c"
    break;

  case 149:
#line 298 "m68kasm.y.txt"
             { (yyval.opc) = 0x5bc8; }
#line 2857 "m68kasm.c"
    break;

  case 150:
#line 299 "m68kasm.y.txt"
             { (yyval.opc) = 0x56c8; }
#line 2863 "m68kasm.c"
    break;

  case 151:
#line 300 "m68kasm.y.txt"
             { (yyval.opc) = 0x5ac8; }
#line 2869 "m68kasm.c"
    break;

  case 152:
#line 301 "m68kasm.y.txt"
             { (yyval.opc) = 0x58c8; }
#line 2875 "m68kasm.c"
    break;

  case 153:
#line 302 "m68kasm.y.txt"
             { (yyval.opc) = 0x59c8; }
#line 2881 "m68kasm.c"
    break;

  case 154:
#line 303 "m68kasm.y.txt"
             { (yyval.opc) = 0x51c8; }
#line 2887 "m68kasm.c"
    break;

  case 155:
#line 304 "m68kasm.y.txt"
             { (yyval.opc) = 0x50c8; }
#line 2893 "m68kasm.c"
    break;

  case 156:
#line 308 "m68kasm.y.txt"
                { (yyval.opc) = 0x4afc; }
#line 2899 "m68kasm.c"
    break;

  case 157:
#line 309 "m68kasm.y.txt"
            { (yyval.opc) = 0x4e71; }
#line 2905 "m68kasm.c"
    break;

  case 158:
#line 310 "m68kasm.y.txt"
              { (yyval.opc) = 0x4e70; }
#line 2911 "m68kasm.c"
    break;

  case 159:
#line 311 "m68kasm.y.txt"
            { (yyval.opc) = 0x4e73; }
#line 2917 "m68kasm.c"
    break;

  case 160:
#line 312 "m68kasm.y.txt"
            { (yyval.opc) = 0x4e77; }
#line 2923 "m68kasm.c"
    break;

  case 161:
#line 313 "m68kasm.y.txt"
            { (yyval.opc) = 0x4e75; }
#line 2929 "m68kasm.c"
    break;

  case 162:
#line 314 "m68kasm.y.txt"
              { (yyval.opc) = 0x4e76; }
#line 2935 "m68kasm.c"
    break;

  case 163:
#line 318 "m68kasm.y.txt"
            { (yyval.opc) = 0x4ec0; }
#line 2941 "m68kasm.c"
    break;

  case 164:
#line 319 "m68kasm.y.txt"
            { (yyval.opc) = 0x4e80; }
#line 2947 "m68kasm.c"
    break;

  case 165:
#line 320 "m68kasm.y.txt"
            { (yyval.opc) = 0x4840; }
#line 2953 "m68kasm.c"
    break;

  case 166:
#line 323 "m68kasm.y.txt"
                      { (yyval.opc) = ((yyvsp[-2].reg)<<9) | 0x20 | (yyvsp[0].reg); }
#line 2959 "m68kasm.c"
    break;

  case 167:
#line 324 "m68kasm.y.txt"
                            { (yyval.opc) = (((yyvsp[-2].num) & 7)<<9) | (yyvsp[0].reg); }
#line 2965 "m68kasm.c"
    break;

  case 168:
#line 327 "m68kasm.y.txt"
                    { (yyval.opc) = (((yyvsp[-2].ea).ea & 7) << 9) |          ((yyvsp[0].ea).ea & 7); }
#line 2971 "m68kasm.c"
    break;

  case 169:
#line 328 "m68kasm.y.txt"
                    { (yyval.opc) = (((yyvsp[-2].ea).ea & 7) << 9) | 0x0008 | ((yyvsp[0].ea).ea & 7); }
#line 2977 "m68kasm.c"
    break;

  case 170:
#line 331 "m68kasm.y.txt"
                      { if (((yyvsp[0].ea).ea & 070)==0) { /* dx,dy must be swapped */
						(yyval.rea).reg = ((yyvsp[0].ea).ea & 7)<<9; (yyvsp[0].ea).ea = (yyvsp[-2].reg) & 7; (yyval.rea).ea = (yyvsp[0].ea); }
					else { (yyval.rea).reg = ((yyvsp[-2].reg)<<9) | 0x100; (yyval.rea).ea = (yyvsp[0].ea); } }
#line 2985 "m68kasm.c"
    break;

  case 171:
#line 334 "m68kasm.y.txt"
                      { (yyval.rea).reg = ((yyvsp[0].reg)<<9); (yyval.rea).ea = (yyvsp[-2].ea); }
#line 2991 "m68kasm.c"
    break;

  case 172:
#line 337 "m68kasm.y.txt"
           { (yyval.reg)=0; }
#line 2997 "m68kasm.c"
    break;

  case 173:
#line 338 "m68kasm.y.txt"
           { (yyval.reg)=1; }
#line 3003 "m68kasm.c"
    break;

  case 174:
#line 339 "m68kasm.y.txt"
           { (yyval.reg)=2; }
#line 3009 "m68kasm.c"
    break;

  case 175:
#line 340 "m68kasm.y.txt"
           { (yyval.reg)=3; }
#line 3015 "m68kasm.c"
    break;

  case 176:
#line 341 "m68kasm.y.txt"
           { (yyval.reg)=4; }
#line 3021 "m68kasm.c"
    break;

  case 177:
#line 342 "m68kasm.y.txt"
           { (yyval.reg)=5; }
#line 3027 "m68kasm.c"
    break;

  case 178:
#line 343 "m68kasm.y.txt"
           { (yyval.reg)=6; }
#line 3033 "m68kasm.c"
    break;

  case 179:
#line 344 "m68kasm.y.txt"
           { (yyval.reg)=7; }
#line 3039 "m68kasm.c"
    break;

  case 180:
#line 347 "m68kasm.y.txt"
           { (yyval.reg)=0; }
#line 3045 "m68kasm.c"
    break;

  case 181:
#line 348 "m68kasm.y.txt"
           { (yyval.reg)=1; }
#line 3051 "m68kasm.c"
    break;

  case 182:
#line 349 "m68kasm.y.txt"
           { (yyval.reg)=2; }
#line 3057 "m68kasm.c"
    break;

  case 183:
#line 350 "m68kasm.y.txt"
           { (yyval.reg)=3; }
#line 3063 "m68kasm.c"
    break;

  case 184:
#line 351 "m68kasm.y.txt"
           { (yyval.reg)=4; }
#line 3069 "m68kasm.c"
    break;

  case 185:
#line 352 "m68kasm.y.txt"
           { (yyval.reg)=5; }
#line 3075 "m68kasm.c"
    break;

  case 186:
#line 353 "m68kasm.y.txt"
           { (yyval.reg)=6; }
#line 3081 "m68kasm.c"
    break;

  case 187:
#line 354 "m68kasm.y.txt"
           { (yyval.reg)=7; }
#line 3087 "m68kasm.c"
    break;

  case 188:
#line 357 "m68kasm.y.txt"
              { (yyval.wl) = 1; oplen = 0; }
#line 3093 "m68kasm.c"
    break;

  case 189:
#line 360 "m68kasm.y.txt"
              { (yyval.wl) = 0; oplen = 1; }
#line 3099 "m68kasm.c"
    break;

  case 190:
#line 361 "m68kasm.y.txt"
              { (yyval.wl) = 1; oplen = 2; }
#line 3105 "m68kasm.c"
    break;

  case 191:
#line 364 "m68kasm.y.txt"
              { (yyval.wl) = 0; oplen = 0; }
#line 3111 "m68kasm.c"
    break;

  case 192:
#line 365 "m68kasm.y.txt"
              { (yyval.wl) = 1; oplen = 1; }
#line 3117 "m68kasm.c"
    break;

  case 193:
#line 366 "m68kasm.y.txt"
              { (yyval.wl) = 2; oplen = 2; }
#line 3123 "m68kasm.c"
    break;

  case 194:
#line 369 "m68kasm.y.txt"
              { (yyval.wl) = 1; oplen = 0; }
#line 3129 "m68kasm.c"
    break;

  case 195:
#line 370 "m68kasm.y.txt"
              { (yyval.wl) = 3; oplen = 1; }
#line 3135 "m68kasm.c"
    break;

  case 196:
#line 371 "m68kasm.y.txt"
              { (yyval.wl) = 2; oplen = 2; }
#line 3141 "m68kasm.c"
    break;

  case 197:
#line 374 "m68kasm.y.txt"
              { (yyval.wl) = 3; oplen = 1; }
#line 3147 "m68kasm.c"
    break;

  case 198:
#line 375 "m68kasm.y.txt"
              { (yyval.wl) = 2; oplen = 2; }
#line 3153 "m68kasm.c"
    break;

  case 199:
#line 378 "m68kasm.y.txt"
             { (yyval.mask) = (yyvsp[0].mask); }
#line 3159 "m68kasm.c"
    break;

  case 200:
#line 379 "m68kasm.y.txt"
                         { (yyval.mask).x = (yyvsp[-2].mask).x | (yyvsp[0].mask).x; (yyval.mask).d = (yyvsp[-2].mask).d | (yyvsp[0].mask).d; }
#line 3165 "m68kasm.c"
    break;

  case 201:
#line 382 "m68kasm.y.txt"
             { (yyval.mask).x = movemx[(yyvsp[0].reg)]; (yyval.mask).d = movemd[(yyvsp[0].reg)]; }
#line 3171 "m68kasm.c"
    break;

  case 202:
#line 383 "m68kasm.y.txt"
             { (yyval.mask).x = movemx[(yyvsp[0].reg)+8]; (yyval.mask).d = movemd[(yyvsp[0].reg)+8]; }
#line 3177 "m68kasm.c"
    break;

  case 203:
#line 384 "m68kasm.y.txt"
                      { int i,l=(yyvsp[-2].reg),h=(yyvsp[0].reg); if (l>h) { l=(yyvsp[0].reg); h=(yyvsp[-2].reg); } (yyval.mask).x = (yyval.mask).d = 0; 
					for (i=l; i<=h; i++) { (yyval.mask).d |= movemx[i]; (yyval.mask).d |= movemd[i]; } }
#line 3184 "m68kasm.c"
    break;

  case 204:
#line 386 "m68kasm.y.txt"
                      { int i,l=(yyvsp[-2].reg),h=(yyvsp[0].reg); if (l>h) { l=(yyvsp[0].reg); h=(yyvsp[-2].reg); } (yyval.mask).x = (yyval.mask).d = 0; 
					for (i=l; i<=h; i++) { (yyval.mask).x |= movemx[i+8]; (yyval.mask).d |= movemd[i+8]; } }
#line 3191 "m68kasm.c"
    break;

  case 260:
#line 401 "m68kasm.y.txt"
             { (yyval.ea).ea = (yyvsp[0].reg); (yyval.ea).cnt = 0; }
#line 3197 "m68kasm.c"
    break;

  case 261:
#line 403 "m68kasm.y.txt"
             { (yyval.ea).ea = 010 | (yyvsp[0].reg); (yyval.ea).cnt = 0; }
#line 3203 "m68kasm.c"
    break;

  case 262:
#line 405 "m68kasm.y.txt"
                     { (yyval.ea).ea = 020 | (yyvsp[-1].reg); (yyval.ea).cnt = 0; }
#line 3209 "m68kasm.c"
    break;

  case 263:
#line 407 "m68kasm.y.txt"
                         { (yyval.ea).ea = 030 | (yyvsp[-1].reg); (yyval.ea).cnt = 0; }
#line 3215 "m68kasm.c"
    break;

  case 264:
#line 409 "m68kasm.y.txt"
                        { (yyval.ea).ea = 040 | (yyvsp[-1].reg); (yyval.ea).cnt = 0; }
#line 3221 "m68kasm.c"
    break;

  case 265:
#line 411 "m68kasm.y.txt"
                                { (yyval.ea).ea = 050 | (yyvsp[-1].reg); (yyval.ea).cnt = 1; (yyval.ea).arg[0] = (yyvsp[-3].num); }
#line 3227 "m68kasm.c"
    break;

  case 266:
#line 414 "m68kasm.y.txt"
                { (yyval.ea).ea = 060 | (yyvsp[-4].reg); (yyval.ea).cnt = 1; (yyval.ea).arg[0] = 0x8000 | ((yyvsp[-2].reg)<<12) | ((yyvsp[-1].wl)<<11) | ((yyvsp[-6].num) & 0xff); }
#line 3233 "m68kasm.c"
    break;

  case 267:
#line 416 "m68kasm.y.txt"
                { (yyval.ea).ea = 060 | (yyvsp[-4].reg); (yyval.ea).cnt = 1; (yyval.ea).arg[0] =          ((yyvsp[-2].reg)<<12) | ((yyvsp[-1].wl)<<11) | ((yyvsp[-6].num) & 0xff); }
#line 3239 "m68kasm.c"
    break;

  case 268:
#line 418 "m68kasm.y.txt"
                            { if ((yyvsp[0].wl)==0) { (yyval.ea).ea = 070; (yyval.ea).cnt = 1; (yyval.ea).arg[0] = (yyvsp[-2].num); } 
				          else {       (yyval.ea).ea = 071; (yyval.ea).cnt = 2; (yyval.ea).arg[0] = (yyvsp[-2].num) >> 16; (yyval.ea).arg[1] = (yyvsp[-2].num) & 0xffff; } }
#line 3246 "m68kasm.c"
    break;

  case 269:
#line 420 "m68kasm.y.txt"
                   { int tmp = ((yyvsp[-1].num)>>15) & 0x1ffff; if (tmp==0 || tmp==0x1ffff) { (yyval.ea).ea = 070; (yyval.ea).cnt = 1; (yyval.ea).arg[0] = (yyvsp[-1].num); }
			 else { (yyval.ea).ea = 070; (yyval.ea).cnt = 2;  (yyval.ea).arg[0] = (yyvsp[-1].num) >> 16; (yyval.ea).arg[1] = (yyvsp[-1].num) & 0xffff; } }
#line 3253 "m68kasm.c"
    break;

  case 270:
#line 423 "m68kasm.y.txt"
                              { (yyval.ea).ea = 072; (yyval.ea).cnt = 1; (yyval.ea).arg[0] = (yyvsp[-3].num); }
#line 3259 "m68kasm.c"
    break;

  case 271:
#line 424 "m68kasm.y.txt"
               { (yyval.ea).ea = 072; (yyval.ea).cnt = 1; (yyval.ea).arg[0] = (yyvsp[0].num); }
#line 3265 "m68kasm.c"
    break;

  case 272:
#line 427 "m68kasm.y.txt"
                { (yyval.ea).ea = 073; (yyval.ea).cnt = 1; (yyval.ea).arg[0] = 0x8000 | ((yyvsp[-2].reg)<<12) | ((yyvsp[-1].wl)<<11) | ((yyvsp[-6].num) & 0xff); }
#line 3271 "m68kasm.c"
    break;

  case 273:
#line 429 "m68kasm.y.txt"
                { (yyval.ea).ea = 073; (yyval.ea).cnt = 1; (yyval.ea).arg[0] = ((yyvsp[-2].reg)<<12) | ((yyvsp[-1].wl)<<11) | ((yyvsp[-6].num) & 0xff); }
#line 3277 "m68kasm.c"
    break;

  case 274:
#line 431 "m68kasm.y.txt"
                   { (yyval.ea).ea = 074; if (oplen==0) { (yyval.ea).cnt = 1; (yyval.ea).arg[0] = (yyvsp[0].num) & 0xff; }
				 else if (oplen==1) { (yyval.ea).cnt = 1; (yyval.ea).arg[0] = (yyvsp[0].num) & 0xffff; }
				 else { (yyval.ea).cnt = 2; (yyval.ea).arg[0] = (yyvsp[0].num) >> 16; (yyval.ea).arg[1] = (yyvsp[0].num) & 0xffff; } }
#line 3285 "m68kasm.c"
    break;

  case 275:
#line 435 "m68kasm.y.txt"
            { (yyval.ea).ea = 074; (yyval.ea).cnt = 0; }
#line 3291 "m68kasm.c"
    break;

  case 276:
#line 436 "m68kasm.y.txt"
           { (yyval.ea).ea = 074; (yyval.ea).cnt = 1; }
#line 3297 "m68kasm.c"
    break;


#line 3301 "m68kasm.c"

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
#line 437 "m68kasm.y.txt"


static void yyerror(char* s)
{
	/* do not emit anything, but set error flag */
	yyerrc = 1;
}

struct _optable {
	char* mnem;
	int token;
};

static struct _optable ops[] = {
	{ "abcd",	ABCD },		{ "add",	ADD },		{ "adda",	ADDA },		{ "addi",	ADDI },
	{ "addq",	ADDQ },		{ "addx",	ADDX },		{ "and",	AND },		{ "andi",	ANDI },
	{ "asl",	ASL }, 		{ "asr",	ASR },		{ "bcc",	BCC },		{ "bcs",	BCS },
	{ "beq",	BEQ },		{ "bge",	BGE },		{ "bgt",	BGT },		{ "bhi",	BHI },
	{ "ble",	BLE },		{ "bls",	BLS },		{ "blt",	BLT },		{ "bmi",	BMI },
	{ "bne",	BNE },		{ "bpl",	BPL },		{ "bvc",	BVC },		{ "bvs",	BVS },
	{ "bchg",	BCHG },		{ "bclr",	BCLR },		{ "bra",	BRA },		{ "bset",	BSET },
	{ "bsr",	BSR },		{ "btst",	BTST },		{ "chk",	CHK },		{ "clr",	CLR },
	{ "cmp",	CMP },		{ "cmpa",	CMPA },		{ "cmpi",	CMPI },		{ "cmpm",	CMPM },
	{ "dbcc",	DBCC },		{ "dbcs",	DBCS },		{ "dbeq",	DBEQ },		{ "dbf",	DBF },
	{ "dbge",	DBGE },		{ "dbgt",	DBGT },		{ "dbhi",	DBHI },		{ "dble",	DBLE },
	{ "dbls",	DBLS },		{ "dblt",	DBLT },		{ "dbmi",	DBMI },		{ "dbne",	DBNE },
	{ "dbpl",	DBPL },		{ "dbt",	DBT },		{ "dbvc",	DBVC },		{ "dbvs",	DBVS },
	{ "divs",	DIVS },		{ "divu",	DIVU },		{ "eor",	EOR },		{ "eori",	EORI },
	{ "exg",	EXG },		{ "ext",	EXT },		{ "illegal",ILLEGAL },	{ "jmp",	JMP },
	{ "jsr",	JSR },		{ "lea",	LEA },		{ "link",	LINK },		{ "lsl",	LSL },
	{ "lsr",	LSR }, 		{ "move",	MOVE },		{ "movea",	MOVEA },	{ "movem",	MOVEM },
	{ "movep",	MOVEP },	{ "moveq",	MOVEQ },	{ "muls",	MULS },		{ "mulu",	MULU },
	{ "nbcd",	NBCD },		{ "neg",	NEG },		{ "negx",	NEGX },		{ "nop",	NOP },
	{ "not",	NOT },		{ "or",		OR },		{ "ori",	ORI },		{ "pea",	PEA },
	{ "reset",	RESET },	{ "rol",	ROL },		{ "ror",	ROR },		{ "roxl",	ROXL },
	{ "roxr",	ROXR },		{ "rte",	RTE },		{ "rtr",	RTR },
	{ "rts",	RTS },		{ "scc",	SCC },		{ "scs",	SCS },		{ "seq",	SEQ },
	{ "sf",		SF },		{ "sge",	SGE },		{ "sgt",	SGT },		{ "shi",	SHI },
	{ "sle",	SLE },		{ "sls",	SLS },		{ "slt",	SLT },		{ "smi",	SMI },
	{ "sne",	SNE },		{ "spl",	SPL },		{ "st",		ST },		{ "svc",	SVC },
	{ "svs",	SVS },		{ "stop",	STOP },		{ "sub",	SUB },		{ "suba",	SUBA },
	{ "subi",	SUBI },		{ "subq",	SUBQ },		{ "subx",	SUBX },		{ "swap",	SWAP },
	{ "tas",	TAS },		{ "trap",	TRAP },		{ "trapv",	TRAPV },	{ "tst",	TST },
	{ "unlk",	UNLK },		{ "a0",		A0 },		{ "a1",		A1 },		{ "a2",		A2 },
	{ "a3",		A3 },		{ "a4",		A4 },		{ "a5",		A5 },		{ "a6",		A6 },
	{ "a7",		A7 },		{ "d0",		D0 },		{ "d1",		D1 },		{ "d2",		D2 },
	{ "d3",		D3 },		{ "d4",		D4 },		{ "d5",		D5 },		{ "d6",		D6 },
	{ "d7",		D7 },		{ "ccr",	CCR },		{ "sr",		SR },		{ "usp",	USP },
	{ "pc",		PC },		
	{ 0, 		0 }
};

typedef struct _ophash {
	struct _ophash* next;
	struct _optable* op;
} OPHASH;
#define OPHASHSIZE 97

static OPHASH **ophash = 0;

static int getophash(const char* s)
{
	int h = 0;
	while (*s++) h += (int)*s;
	return h % OPHASHSIZE;
}

static int oplookup(const char* s)
{
	int idx = getophash(s);
	OPHASH* oph = ophash[idx];
	if (oph) {
		if (oph->next) {
			while (oph) {
				if (!strcmp(s,oph->op->mnem)) return oph->op->token;
				oph = oph->next;
			}
			return 0;
		}
		return oph->op->token;
	}
	return 0;
}

static void init_ophash() 
{
	struct _optable* op = ops;
	OPHASH* oph;
	ophash = (OPHASH**)calloc(sizeof(OPHASH*),OPHASHSIZE);
	while (op->mnem) {
		int idx = getophash(op->mnem);
		oph = (OPHASH*)malloc(sizeof(OPHASH));
		oph->next = ophash[idx];
		oph->op = op;
		ophash[idx] = oph;
		op++;
	}
}

static char* yystream;

static int yylex()
{
	char ident[30];
	char *p = ident;
	char c = yystream[0];
	
	while (c != 0 && (c=='\t' || c==' ')) {
		c = *++yystream;
	}
	if (c==0) return EOF;
	
	if (isalpha(c)) {
		while (isalnum(c) && (p-ident)<28) {
			*p++ = tolower(c); c = *++yystream;
		}
		*p = 0;
		if (p>ident) { return oplookup(ident); }
		return EOF;
	} else if (isdigit(c)) {
		*p++ = c; 
		if (yystream[1]=='x' || yystream[1]=='X') { *p++ = 'x'; yystream++; }
		c = *++yystream;
		while ((isdigit(c) || isxdigit(c)) && (p-ident)<28) {
			*p++ = c; c = *++yystream;
		}
		*p = 0;
		yylval.num = strtol(ident,0,0);
		return NUMBER;
    } else if (c=='$') {
    	if (isdigit(yystream[1]) || isxdigit(yystream[1])) {
			c = *++yystream;
			while ((isdigit(c) || isxdigit(c)) && (p-ident)<28) {
				*p++ = c; c = *++yystream;
			}
			*p = 0;
			yylval.num = strtol(ident,0,16);
			return NUMBER;
		} else return '$';
	} else if (c == '-' && yystream[1] == '(') {
		yystream += 2; return PREDEC;
	} else if (c == ')' && yystream[1] == '+') {
		yystream += 2; return POSTINC;
	} else if (c == '.') {
		switch (yystream[1]) {
		case 'b': yystream += 2; return BSIZE;
		case 'w': yystream += 2; return WSIZE;
		case 'l': yystream += 2; return LSIZE;
		case 's': yystream += 2; return SSIZE;
		default: yystream++; return '.';
		}
	} else {
		++yystream; return c;
	}
}

static t_value *yyvalptr;
static t_addr yyaddr;

t_stat parse_sym_m68k(char* c, t_addr a, UNIT* u, t_value* val, int32 sw)
{
	char ch;
	
	if (!ophash) init_ophash();

	yyvalptr = val;
	yyaddr = a;

	yystream = c;
	yyerrc = 0;
	
	ch = *yystream;
	while (ch != 0 && (ch=='\t' || ch==' ')) {
		ch = *++yystream;
	}
	if (ch == 0) return 0;

	if (sw & SWMASK('Y')) yydebug = 1 - yydebug;
	if ((sw & SWMASK('A')) || ch=='\'') {
		if ((ch = yystream[1])) {
			val[0] = (uint32)ch;
			return SCPE_OK;
		} else return SCPE_ARG;
	}
	if ((sw & SWMASK('C')) || ch=='"') {
		if ((ch = yystream[1])) {
			val[0] = ((uint32)ch << 8) | (uint32)yystream[1];
			return SCPE_OK;
		} else return SCPE_ARG;
	}
	
	yyparse();
//    sim_printf("rc=%d\n",yyrc);
	if (yyerrc) return SCPE_ARG;
	return yyrc;
}

static int _genop(t_value arg)
{
//    sim_printf("_genop(%x)@%x\n",arg,(int)yyvalptr);
    *yyvalptr = (arg >> 8) & 0xff;
    yyvalptr++;
    *yyvalptr = arg & 0xff;
    yyvalptr++;
    return -1;
}

static int _genea(struct _ea arg)
{
	int i;
	for (i=0; i<arg.cnt; i++) _genop(arg.arg[i]);
	return -(arg.cnt*2)-1;
}

static int _genbr(t_value arg,t_addr tgt,int len) 
{
	t_addr a = tgt - yyaddr -2;
	if (len==1) {
		_genop(arg);
		_genop(a & 0xffff);
		a &= 0xffff8000;
		if (a != 0x00000000 && a != 0xffff8000) return SCPE_ARG;
		return -3;
	} else {
		_genop(arg | (a&0xff));
		a &= 0xffffff80;
		if (a != 0x00000000 && a != 0xffffff80) return SCPE_ARG;
		return -1;
	}
}
