/* codgen.c       Generate Assembly Code for x86         07 May 18   */

/* Copyright (c) 2018 Gordon S. Novak Jr. and The University of Texas at Austin
    */

/* Starter file for CS 375 Code Generation assignment.           */
/* Written by Gordon S. Novak Jr.                  */

/* This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License (file gpl.text) for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "symtab.h"
#include "lexan.h"
#include "genasm.h"
#include "codegen.h"
#include "pprint.h"

void genc(TOKEN code);

/* Set DEBUGGEN to 1 for debug printouts of code generation */
#define DEBUGGEN 0

int nextlabel;    /* Next available label number */
int stkframesize;   /* total stack frame size */

char regavail[32];

/* Top-level entry for code generator.
   pcode    = pointer to code:  (program foo (output) (progn ...))
   varsize  = size of local storage in bytes
   maxlabel = maximum label number used so far

Add this line to the end of your main program:
    gencode(parseresult, blockoffs[blocknumber], labelnumber);
The generated code is printed out; use a text editor to extract it for
your .s file.
         */

void gencode(TOKEN pcode, int varsize, int maxlabel)
  {  TOKEN name, code;
     name = pcode->operands;
     code = name->link->link;
     nextlabel = maxlabel + 1;
     stkframesize = asmentry(name->stringval,varsize);
     genc(code);
     asmexit(name->stringval);
  }

/*  version: always returns RBASE + 0 */
/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
int getreg(int kind)
  {
    /*     *****  *****   */
    int c;
    if (kind == FLOAT) {
        c = FBASE;
        while (c <= FMAX) {
            if (regavail[c] == 0) {
                regavail[c] = 1;
                return c;
            }
            c++;
        }
    } else if (kind == WORD || kind == ADDR) { 
        c = RBASE;
        while (c <= RMAX) {
            if (regavail[c] == 0) {
                regavail[c] = 1;
                return c;
            }
            c++;
        }
    } 
    printf("OUT OF REGISTERS!\n");
     return RBASE;
  }



int optable[29] = {0, ADDL, SUBL, IMULL, DIVL, 0, CMPL, CMPL, CMPL, CMPL, CMPL, CMPL, MOVL, MOVL, ANDL, ORL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int optablef[29] = {0, ADDSD, SUBSD, MULSD, DIVSD, 0, CMPSD, CMPSD, CMPSD, CMPSD, CMPSD, CMPSD, MOVSD, MOVSD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int optableq[29] = {0, ADDQ, SUBQ, IMULQ, DIVSD, 0, CMPQ, CMPQ, CMPQ, CMPQ, CMPQ, CMPQ, MOVQ, MOVQ, ANDQ, ORQ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int movtable[3] = {MOVL, MOVSD, MOVQ};

/*  version */
/* Generate code for arithmetic expression, return a register number */
int genarith(TOKEN code)
  {   int num, reg;

     if (DEBUGGEN)
       { printf("genarith\n");
	 dbugprinttok(code);
       };
      switch ( code->tokentype )
       { case NUMBERTOK:
           switch (code->basicdt)
             { case INTEGER:
          num = code->intval;
          reg = getreg(WORD);
          if ( num >= MINIMMEDIATE && num <= MAXIMMEDIATE )
            asmimmed(MOVL, num, reg);
          break;
	       case REAL:
            reg = getreg(FLOAT);
            makeflit(code->realval, nextlabel);
            asmldflit(MOVSD, nextlabel, reg);
            nextlabel++;
		      break;
         case POINTER:
            num = code->realval;
            reg = getreg(ADDR);
            if ( num >= MINIMMEDIATE && num <= MAXIMMEDIATE )
              asmimmed(MOVQ, num, reg);
		      break;
	       }
	   break;
       case IDENTIFIERTOK:
        switch(code->symtype->kind) {
            default:
                if (code->symtype->basicdt == INTEGER) {
                  reg = getreg(WORD);
                  asmld(MOVL, -stkframesize+code->symentry->offset, reg, code->stringval); 
                } else if (code->symtype->basicdt == REAL) {
                  reg = getreg(FLOAT);
                  asmld(MOVSD, -stkframesize+code->symentry->offset, reg, code->stringval); 
                } else {
                  reg = getreg(ADDR);
                  asmld(MOVQ, -stkframesize+code->symentry->offset, reg, code->stringval); 
                }
                break;
        }
         
	   break;
       case OPERATOR:
    /*     *****  *****   */
        if (code->whichval == POINTEROP) {
          return genarith(code->operands);
        }
        if (code->whichval == FUNCALLOP) {
          if (code->basicdt == INTEGER) {
            reg = EAX;
          } else if (code->basicdt == REAL) {
            reg = XMM0;
          } else {
            reg = RAX;
          }
          // int load = 0;
          // if (regavail[reg] == 1) {
          //   asmsttemp(reg);
          //   load = 1;
          // }
          genc(code);
          regavail[reg] = 1;
          // int reg2;
          // if (code->basicdt == INTEGER) {
          //   reg2 = getreg(WORD);
          // } else if (code->basicdt == REAL) {
          //   reg2 = getreg(FLOAT);
          // } else {
          //   reg2 = getreg(ADDR);
          // }
          // if (load == 1)
          //   asmldtemp(reg2);
          return reg;
        }

        if (code->whichval == AREFOP) {
          int tempreg = genarith(code->operands);
          reg = getreg(ADDR);
          asmldr(MOVQ, code->operands->link->intval, tempreg, reg, "^.");
          return reg;
        }
        reg = genarith(code->operands);
        int reg2 = -1;
        if (code->operands->link != NULL) {
          int load = 0;
          if (code->operands->link->tokentype == OPERATOR && code->operands->link->whichval == FUNCALLOP) {
            if (regavail[reg] == 1) {
              asmsttemp(reg);
              load = 1;
            }
          }
          reg2 = genarith(code->operands->link);
          if (load == 1) {
            int tempreg;
            if (code->operands->link->basicdt == INTEGER) {
              tempreg = getreg(WORD);
            } else if (code->operands->link->basicdt == REAL) {
              tempreg = getreg(FLOAT);
            } else {
              tempreg = getreg(ADDR);
            }
            asmldtemp(tempreg);
            reg = tempreg;
          }
        } else if (code->whichval == FLOATOP) {
          reg2 = reg;
          reg = getreg(FLOAT);
          asmfloat(reg2, reg);
          break;
        } else if (code->whichval == MINUSOP) {
          reg2 = getreg(FLOAT);
          asmfneg(reg, reg2);
          break;
        }
        if (reg >= FBASE && reg <= FMAX) {
          if (reg2 != -1)
            asmrr(optablef[code->whichval], reg2, reg);
          else
            asmr(optablef[code->whichval], reg);
        } else {
          if (code->operands->symtype->basicdt != INTEGER) {
            if (reg2 != -1)
              asmrr(optableq[code->whichval], reg2, reg);
            else
              asmr(optableq[code->whichval], reg);
          } else {
            if (reg2 != -1)
              asmrr(optable[code->whichval], reg2, reg);
            else
              asmr(optable[code->whichval], reg);
          }
        }
        regavail[reg2] = 0;

	   break;
       };
     return reg;
    }

int jmpoptable[6] = {JE, JNE, JL, JLE, JGE, JG};

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code)
  {  TOKEN tok, lhs, rhs;
     int reg, offs;
     SYMBOL sym;
     if (DEBUGGEN)
       { printf("genc\n");
	 dbugprinttok(code);
       };
     if ( code->tokentype != OPERATOR )
        { printf("Bad code token");
	  dbugprinttok(code);
	};

    memset(regavail, 0, 32*sizeof(char));

     switch ( code->whichval )
       { case PROGNOP:
	   tok = code->operands;
	   while ( tok != NULL )
	     {  genc(tok);
		tok = tok->link;
	      };
	   break;
	 case ASSIGNOP:                   
      // lhs = code->operands;
      // rhs = lhs->link;
      // int is_lhs_aref = (lhs->tokentype == OPERATOR && lhs->whichval == AREFOP) ? 1 : 0;
      // int is_rhs_aref = (rhs->tokentype == OPERATOR && rhs->whichval == AREFOP) ? 1 : 0;

      // if (!is_lhs_aref & !is_rhs_aref == 1) {
      //   reg = genarith(rhs);              /* generate rhs into a register */
      //   if (lhs->tokentype == IDENTIFIERTOK) {
      //     sym = lhs->symentry;              /* assumes lhs is a simple var  */
      //     offs = sym->offset - stkframesize; /* net offset of the var   */
          
      //     switch (code->basicdt)            /* store value into lhs  */
      //         { case INTEGER:
      //             asmst(MOVL, reg, offs, lhs->stringval);
      //             break;
      //         case REAL:
      //             asmst(MOVSD, reg, offs, lhs->stringval);
      //             break;
      //           default:
      //             asmst(MOVQ, reg, offs, lhs->stringval);
      //         };
      //   }
      // } else if (is_lhs_aref & !is_rhs_aref == 1) {

      // }

        lhs = code->operands;
        rhs = lhs->link;
        if (lhs->tokentype == IDENTIFIERTOK) {
          sym = lhs->symentry;              /* assumes lhs is a simple var  */
          offs = sym->offset - stkframesize; /* net offset of the var   */
          if (rhs->tokentype == OPERATOR && rhs->whichval == AREFOP) {
            if (rhs->operands->tokentype == OPERATOR && rhs->operands->whichval == POINTEROP) {
              int reg2 = genarith(rhs->operands);
              int tempreg;
              //int reg3 = genarith(lhs->operands->link);
              switch (code->basicdt)           
                { case INTEGER:
                    tempreg = getreg(WORD);
                    asmldr(MOVL, rhs->operands->link->intval, reg2, tempreg, "^. ");
                    asmst(MOVL, tempreg, offs, lhs->stringval);
                    break;
                case REAL:
                    tempreg = getreg(FLOAT);
                    asmldr(MOVSD, rhs->operands->link->intval, reg2, tempreg, "^. ");
                    asmst(MOVSD, tempreg, offs, lhs->stringval);
                    break;
                  default:
                    tempreg = getreg(ADDR);
                    asmldr(MOVQ, rhs->operands->link->intval, reg2, tempreg, "^. ");
                    asmst(MOVQ, tempreg, offs, lhs->stringval);
                };
            } else {
            int reg2 = genarith(rhs->operands->link);
            int tempreg;
            asmop(CLTQ);
            switch (code->basicdt) {           /* store value into lhs  */
                { case INTEGER:
                    tempreg = getreg(WORD);
                    asmldrr(MOVL, -stkframesize+rhs->operands->symtype->offset, reg2, tempreg, rhs->operands->stringval);
                    asmst(MOVL, tempreg, offs, lhs->stringval);
                    break;
                case REAL:
                    tempreg = getreg(FLOAT);
                    asmldrr(MOVSD, -stkframesize+rhs->operands->symtype->offset, reg2, tempreg, rhs->operands->stringval);
                    asmst(MOVSD, tempreg, offs, lhs->stringval);
                    break;
                  default:
                    tempreg = getreg(ADDR);
                    asmldrr(MOVQ, -stkframesize+rhs->operands->symtype->offset, reg2, tempreg, rhs->operands->stringval);
                    asmst(MOVQ, tempreg, offs, lhs->stringval);
                };
              }
            }
          } else {
              reg = genarith(rhs);              /* generate rhs into a register */
            switch (code->basicdt)            /* store value into lhs  */
                { case INTEGER:
                    asmst(MOVL, reg, offs, lhs->stringval);
                    break;
                case REAL:
                    asmst(MOVSD, reg, offs, lhs->stringval);
                    break;
                  default:
                    asmst(MOVQ, reg, offs, lhs->stringval);
                };
            }
        } else if (lhs->tokentype == OPERATOR) {
          if (lhs->whichval == AREFOP) {
            reg = genarith(rhs);              /* generate rhs into a register */
            if (lhs->operands->tokentype == OPERATOR && lhs->operands->whichval == POINTEROP) {
              int reg2 = genarith(lhs->operands);
              //int reg3 = genarith(lhs->operands->link);
              switch (code->basicdt)            /* store value into lhs  */
                { case INTEGER:
                    asmstr(MOVL, reg, lhs->operands->link->intval, reg2, "^. ");
                    break;
                case REAL:
                    asmstr(MOVSD, reg, lhs->operands->link->intval, reg2, "^. ");
                    break;
                  default:
                    asmstr(MOVQ, reg, lhs->operands->link->intval, reg2, "^. ");
                };
            } else {
              int reg2 = genarith(lhs->operands->link);
              asmop(CLTQ);
              
              switch (code->basicdt)            /* store value into lhs  */
                { case INTEGER:
                    asmstrr(MOVL, reg, -stkframesize+lhs->operands->symtype->offset, reg2, lhs->operands->stringval);
                    break;
                case REAL:
                    asmstrr(MOVSD, reg, -stkframesize+lhs->operands->symtype->offset, reg2, lhs->operands->stringval);
                    break;
                  default:
                    asmstrr(MOVQ, reg, -stkframesize+lhs->operands->symtype->offset, reg2, lhs->operands->stringval);
                };
            }
          } else {
            printf("non aref operator: %i\n", lhs->whichval);
          }
        }
        break;
	 case FUNCALLOP:
    /*     *****  *****   */
    if (code->operands->link != NULL) {
      reg = genarith(code->operands->link);
      if (code->operands->link->basicdt == INTEGER) {
        if (reg != EDI)
          asmrr(MOVL, reg, EDI);
      } else if (code->operands->link->basicdt == REAL) {
        if (reg != XMM0)
          asmrr(MOVSD, reg, XMM0);
      } else {
        int labelnum = nextlabel++;
        makeblit(code->operands->link->stringval, labelnum);
        asmlitarg(labelnum, RDI);
      }
    }
    if (searchlev(code->operands->stringval, 0) != NULL) {
      asmcall(code->operands->stringval);
    }
    // if (strcmp(code->operands->stringval,"writelni") == 0 || strcmp(code->operands->stringval,"write") == 0 || strcmp(code->operands->stringval,"writelnf") == 0) {
    //   asmcall(code->operands->stringval);
    // }
	   break;
	 case GOTOOP:
    /*     *****  *****   */
    asmjump(JMP, code->operands->intval);
	   break;
	 case LABELOP:
    /*     *****  *****   */
    asmlabel(code->operands->intval);
	   break;
	 case IFOP: {
    /*     *****  *****   */
      genarith(code->operands);
      int labeltwo = nextlabel++;
      int labelthree = nextlabel++;
      asmjump(jmpoptable[code->operands->whichval-6], labeltwo);
      if (code->operands->link->link != NULL)
        genc(code->operands->link->link);
      asmjump(JMP, labelthree);
      asmlabel(labeltwo);
      genc(code->operands->link);
      asmlabel(labelthree);
	   break;
   }
	 };
  }