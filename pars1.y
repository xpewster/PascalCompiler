%{     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 25 Jul 19   */

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
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"
#include "pprint.h"

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN
//int yydebug=1;

TOKEN parseresult;

%}

/* Order of tokens corresponds to tokendefs.c; do not change */

%token IDENTIFIER STRING NUMBER   /* token types */

%token PLUS MINUS TIMES DIVIDE    /* Operators */
%token ASSIGN EQ NE LT LE GE GT POINT DOT AND OR NOT DIV MOD IN

%token COMMA                      /* Delimiters */
%token SEMICOLON COLON LPAREN RPAREN LBRACKET RBRACKET DOTDOT

%token ARRAY BEGINBEGIN           /* Lex uses BEGIN */
%token CASE CONST DO DOWNTO ELSE END FILEFILE FOR FUNCTION GOTO IF LABEL NIL
%token OF PACKED PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL
%token VAR WHILE WITH


%%

program    :  PROGRAM IDENTIFIER LPAREN idlist RPAREN SEMICOLON vblock DOT /* change this! */       
                                        { parseresult = makeprogram($1, $2, $7); }
             ;
idlist       :  IDENTIFIER COMMA idlist { $$ = cons($1, $3); }
             |  IDENTIFIER { $$ = cons($1, NULL); }
             ;
vblock       :  VAR varspecs block { $$ = $3; }
             |  block
             ;
varspecs     :  vargroup SEMICOLON varspecs
             |  vargroup SEMICOLON
             ;
vargroup     :  idlist COLON type { instvars($1, $3); };
type         :  simpletype
             ;
simpletype   : IDENTIFIER { $$ = findtype($1); }
             ;
block        : BEGINBEGIN statement endpart { $$ = makeprogn($1,cons($2, $3)); };
  statement  :  BEGINBEGIN statement endpart
                                       { $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
             |  FOR assignment TO expr DO statement  { $$ = makefor(1, $1, $2, $3, $4, $5, $6); }
             |  FOR assignment DOWNTO expr DO statement  { $$ = makefor(-1, $1, $2, $3, $4, $5, $6); }
             |  assignment
             |  function
             ;
  endpart    :  SEMICOLON statement endpart    { $$ = cons($2, $3); }
             |  END                            { $$ = NULL; }
             ;
  endif      :  ELSE statement                 { $$ = $2; }
             |  /* empty */                    { $$ = NULL; }
             ;
function     :  IDENTIFIER LPAREN arglist RPAREN {$$ = makefuncall($2, $1, $3); }
             ;
arglist      :  expr COMMA arglist             { $$ = cons($1, $3); }
             |  expr { $$ = cons($1, NULL); }
             ;
  assignment :  variable ASSIGN expr           { $$ = binop($2, $1, $3); }
             ;
  expr       :  expr PLUS term                 { $$ = binop($2, $1, $3); }
             |  term 
             ;
  term       :  term TIMES factor              { $$ = binop($2, $1, $3); }
             |  factor
             ;
  factor     :  LPAREN expr RPAREN             { $$ = $2; }
             |  variable
             |  NUMBER
             |  STRING
             ;
  variable   : IDENTIFIER                      { $$ = findid($1); }
%%

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

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item);
         dbugprinttok(list);
       };
    return item;
  }

TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { op->operands = lhs;          /* link operands to operator       */
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
    args->link = statements;
    name->operands = args;
    return name;
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
    TOKEN i = findid(asg->operands);
    i->link = endexpr;
    to->operands = i;
    TOKEN inc = makeop(ASSIGNOP);
    TOKEN _i = findid(asg->operands);
    /* TOKEN plus = maketoken(OPERATOR, PLUSOP); */
    TOKEN plus = makeplus(findid(asg->operands), makeintc(1), tokb);
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

/* TOKEN makefor(TOKEN tok, TOKEN assignpart, TOKEN topart, TOKEN dopart) {
    tok->tokentype = OPERATOR;
    tok->whichval = PROGNOP;
    TOKEN label = maketoken(OPERATOR, LABELOP);
    TOKEN j = maketoken(NUMBERTOK, INTEGER);
    j->intval = labelnumber++;
    label->operands = j;
    TOKEN to = maketoken(OPERATOR, LEOP);
    TOKEN i = findid(assignpart->operands);
    i->link = topart;
    to->operands = i;
    TOKEN inc = maketoken(OPERATOR, ASSIGNOP);
    TOKEN _i = findid(assignpart->operands);
    TOKEN plus = maketoken(OPERATOR, PLUSOP);
    TOKEN __i = findid(assignpart->operands);
    __i->link = maketoken(NUMBERTOK, INTEGER);
    __i->link->intval = 1;
    plus->operands = __i;
    _i->link = plus;
    inc->operands = _i;
    TOKEN _goto = maketoken(OPERATOR, GOTOOP);
    _goto->operands = j;
    dopart->link = inc;
    dopart->link->link = _goto;
    label->link = makeif(maketoken(OPERATOR, IFOP), to, makeprogn(maketoken(OPEARTOR, PROGNOP), dopart), NULL);
    assignpart->link = label;
    tok->operands = assignpart;
    return tok;
} */

/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {
    tok->tokentype = OPERATOR;
    tok->whichval = FUNCALLOP;
    tok->operands = fn;
    tok->operands->link = args;
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

TOKEN findid(TOKEN tok) { /* the ID token */
    if (DEBUG & DB_FINDID) {
      printf("findid\n");
      dbugprinttok(tok);
    }
  
    SYMBOL sym, typ;
    sym = searchst(tok->stringval);
    tok->symentry = sym;
    typ = sym->datatype;
    tok->symtype = typ;
    if ( typ->kind == BASICTYPE ||
        typ->kind == POINTERSYM)
    tok->basicdt = typ->basicdt;
}


TOKEN findtype(TOKEN tok) { /* the type token */
    SYMBOL sym, typ;
    sym = searchins(tok->stringval);
    tok->symtype = sym;
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
     /* 
    gencode(parseresult, blockoffs[blocknumber], labelnumber);
 */
  }