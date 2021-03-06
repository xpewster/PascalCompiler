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
#include <string.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"
#include "pprint.h"
#include "codegen.h"

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN
int yydebug=0;

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

program    :  PROGRAM IDENTIFIER LPAREN idlist RPAREN SEMICOLON lblock DOT /* change this! */       
                                        { parseresult = makeprogram($2, $4, $7); }
             ;


lblock       :  LABEL labellist cblock    { $$ = $3; }
             |  cblock
             ;
labellist    :  label COMMA labellist    { $$ = cons($1, $3); }
             |  label SEMICOLON { $$ = cons($1, NULL); }
label        :  NUMBER { instlabel($1); };


cblock       :  CONST constgroup tblock { $$ = $3; }
             |  tblock
             ;
constgroup   :  constdef SEMICOLON constgroup
             |  constdef SEMICOLON
             ;
constdef     :  IDENTIFIER EQ expr { instconst($1, $3); }
             ;


tblock       :  TYPE typegroup vblock { $$ = $3; }
             |  vblock
             ;
typegroup    :  typedef SEMICOLON typegroup
             |  typedef SEMICOLON
             ;
typedef      :  IDENTIFIER EQ complextype { insttype($1, $3); }
             ;
complextype  :  record
             |  enum
             |  pointer
             |  array
             ;  
record    :  RECORD fieldspecs END { $$ = instrec($1, $2); }
             ;
fieldspecs   :  fieldgroup SEMICOLON fieldspecs { $$ = nconc($1, $3); }
             |  fieldgroup { $$ = $1; }
             ;
fieldgroup   :  idlist COLON type { instfields($1, $3); $$ = $1; } 
             ;
enum      :  LPAREN idlist RPAREN { $$ = instenum($2); }
             ;
pointer   :  POINT type { $$ = instpoint($1, $2); }
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
             |  complextype
             ;
simpletype   : IDENTIFIER { $$ = findtype($1); }
             ;
array        :  ARRAY LBRACKET subrangegroup RBRACKET OF type { $$ = instarray($3, $6); }
             ;
subrangegroup:  subrange COMMA subrangegroup { $$ = cons($1, $3); }
             |  subrange { $$ = cons($1, NULL); }
             ;
subrange     :  NUMBER DOTDOT NUMBER { $$ = makesubranget($2, $1, $3); }
             |  IDENTIFIER { $$ = findtype($1); }
             ;


block        : BEGINBEGIN statement endpart { $$ = makeprogn($1,cons($2, $3)); };
  statement  :  BEGINBEGIN statement endpart
                                       { $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
             |  FOR assignment TO expr DO statement  { $$ = makefor(1, $1, $2, $3, $4, $5, $6); }
             |  FOR assignment DOWNTO expr DO statement  { $$ = makefor(-1, $1, $2, $3, $4, $5, $6); }
             |  REPEAT statements UNTIL expr { $$ = makerepeat($1, $2, $3, $4); }
             |  WHILE expr DO statement { $$ = makewhile($1, $2, $3, $4); }
             |  assignment
             |  function
             |  labelstatement { $$ = makeprogn(makeop(PROGNOP), $1); }
             |  gotostatement
             ;
  labelstatement: NUMBER COLON statements                    { $$ = dolabel($1, $2, $3); }
             ;
  gotostatement: GOTO NUMBER                    { $$ = dogoto($1, $2); }
             ;
  statements : statement SEMICOLON statements             { $$ = cons($1, $3); };
             | statement                       { $$ = cons($1, NULL); }
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
             /* %token PLUS MINUS TIMES DIVIDE    
%token ASSIGN EQ NE LT LE GE GT POINT DOT AND OR NOT DIV MOD IN */
  expr       :  expr PLUS term                 { $$ = binop($2, $1, $3); }
             |  expr MINUS term                 { $$ = binop($2, $1, $3); }
             |  expr DIVIDE expr                   { $$ = binop($2, $1, $3); }
             |  expr TIMES expr                   { $$ = binop($2, $1, $3); }
             |  expr EQ expr                   { $$ = binop($2, $1, $3); }
             |  expr NE expr                   { $$ = binop($2, $1, $3); }
             |  expr LT expr                   { $$ = binop($2, $1, $3); }
             |  expr LE expr                   { $$ = binop($2, $1, $3); }
             |  expr GE expr                   { $$ = binop($2, $1, $3); }
             |  expr GT expr                   { $$ = binop($2, $1, $3); }
             |  expr POINT expr                   { $$ = binop($2, $1, $3); }
             |  expr DOT expr                   { $$ = binop($2, $1, $3); }
             |  expr AND expr                   { $$ = binop($2, $1, $3); }
             |  expr OR expr                   { $$ = binop($2, $1, $3); }
             |  expr NOT expr                   { $$ = binop($2, $1, $3); }
             |  expr DIV expr                   { $$ = binop($2, $1, $3); }
             |  expr MOD expr                   { $$ = binop($2, $1, $3); }
             |  expr IN expr                   { $$ = binop($2, $1, $3); }
             |  term 
             ;
  term       :  term TIMES factor              { $$ = binop($2, $1, $3); }
             |  MINUS factor                   { $$ = unaryop($1, $2); }
             |  factor
             ;
  factor     :  LPAREN expr RPAREN             { $$ = $2; }
             |  variable
             |  function
             |  NIL                            { $$ = makeintc(0); }
             |  NUMBER
             |  STRING
             ;
  variable   : IDENTIFIER                      { $$ = findid($1); }
             |  dotref
             |  pointref
             |  arrayref
             ;
  dotref     :  variable DOT IDENTIFIER      { $$ = reducedot($1, $2, $3); }
             ;
  pointref   :  variable POINT               { $$ = dopoint($1, $2); }
             ;
  arrayref   :  variable LBRACKET exprgroup RBRACKET { $$ = arrayref($1, $2, $3, $4); }
             ;
  exprgroup  :  expr COMMA exprgroup         { $$ = cons($1, $3); }
             |  expr                         { $$ = cons($1, NULL); };
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
 int userlabels[50];

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

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
     
    gencode(parseresult, blockoffs[blocknumber], labelnumber);

  }