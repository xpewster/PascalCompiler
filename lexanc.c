/* lexanc.c         14 Feb 01; 31 May 12; 11 Jan 18       */

/* This file contains code stubs for the lexical analyzer.
   Rename this file to be lexanc.c and fill in the stubs.    */

/* Copyright (c) 2018 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexan.h"

/* This file will work as given with an input file consisting only
   of integers separated by blanks:
   make lexanc
   lexanc
   12345 123    345  357
   */


/* Skip blanks and whitespace.  Expand this function to skip comments too. */
void skipblanks ()
  {
        int c;
        char IN_COMMENT_1_FLAG = 0;
        char IN_COMMENT_2_FLAG = 0;
        while ((c = peekchar()) != EOF
                && (c == ' ' || c == '\n' || c == '\t' || c == '{' || c == '}' || (c == '(' && peek2char() == '*') || (c == ')' && peek2char() == '*') || IN_COMMENT_1_FLAG == 1 || IN_COMMENT_2_FLAG == 1)) {
            c = getchar();
            if (c == '{') {
                IN_COMMENT_1_FLAG = 1;
            }
            else if (c == '}') {
                IN_COMMENT_1_FLAG = 0;
            }
            else if (c == '(') {
                int c2;
                if ((c2 = peekchar()) == '*') {
                    IN_COMMENT_2_FLAG = 1;
                    getchar();
                }
            }
            else if (c == '*') {
                int c2;
                if ((c2 = peekchar()) == ')') {
                    IN_COMMENT_2_FLAG = 0;
                    getchar();
                }
            }
        }
    }

/* Get identifiers and reserved words */
TOKEN identifier (TOKEN tok)
  {
        char c;
        char str[16] = {0};
        int cnt = 0;
        while ((c = peekchar()) != EOF && (CHARCLASS[c] == NUMERIC || CHARCLASS[c] == ALPHA)) {
            c = getchar();
            if (cnt < 15)
                strncat(str, &c, 1);
            cnt++;
        }
        int i;
        for (i = 0; i < 29; i++) {
            if (strcmp(_reserved[i], str) == 0) {
                tok->tokentype = RESERVED;
                tok->whichval = i+1;
            }
            if (i >= 13 && i < 19) {
                if (strcmp(_operator[i], str) == 0) {
                    tok->tokentype = OPERATOR;
                    tok->whichval = i+1;
                }
            }
        }
        if (tok->tokentype != RESERVED) {
            tok->tokentype = IDENTIFIERTOK;
            strcpy(tok->stringval, str);
        }
    }

TOKEN getstring (TOKEN tok)
  {
        char c;
        char str[16] = {0};
        int cnt = 0;
        char END_OF_STRING = 0;
        c = getchar();
        while ((c = peekchar()) != EOF && END_OF_STRING == 0) {
            c = getchar();
            if (c == '\'') {
                char c2 = peekchar();
                if (c2 != '\'') {
                    END_OF_STRING = 1;
                }
                else {
                    if (cnt < 15) 
                        strncat(str, &c, 1);
                    cnt++;
                    c = getchar();
                }
            }
            else {
                if (cnt < 15) 
                    strncat(str, &c, 1);
                cnt++;
            }        
        }
        tok->tokentype = STRINGTOK;
        strcpy(tok->stringval, str);
    }

TOKEN special (TOKEN tok)
  {
        char c;
        c = getchar();
        if (c == ':') {
            char c2 = peekchar();
            if (c2 == '=') {
                tok->tokentype = OPERATOR;
                tok->whichval = ASSIGNOP;
                getchar();
            }
            else {
                tok->tokentype = DELIMITER;
                tok->whichval = COLON-DELIMITER_BIAS;
            }
        }
        else if (c == '.') {
            char c2 = peekchar();
            if (c2 == '.') {
                tok->tokentype = DELIMITER;
                tok->whichval = DOTDOT-DELIMITER_BIAS;
                getchar();
            }
            else {
                tok->tokentype = OPERATOR;
                tok->whichval = DOTOP;
            }
        }
        else if (c == '<') {
            char c2 = peekchar();
            if (c2 == '=') {
                tok->tokentype = OPERATOR;
                tok->whichval = LEOP;
                getchar();
            }
            else if (c2 == '>') {
                tok->tokentype = OPERATOR;
                tok->whichval = NEOP;
                getchar();
            }
            else {
                tok->tokentype = OPERATOR;
                tok->whichval = LTOP;
            }
        }
        else if (c == '>') {
            char c2 = peekchar();
            if (c2 == '=') {
                tok->tokentype = OPERATOR;
                tok->whichval = GEOP;
                getchar();
            }
            else {
                tok->tokentype = OPERATOR;
                tok->whichval = GTOP;
            }
        }
        else {
            int i;
            for (i = 0; i < 26; i++) {
                if (i < 7) {
                    if (c == _delimiter[i][0]) {
                        tok->tokentype = DELIMITER;
                        tok->whichval = i+1;
                    }
                }
                if (i < 13) {
                    if (c == _operator[i][0]) {
                        tok->tokentype = OPERATOR;
                        tok->whichval = i+1;
                    }
                }
            }
        }
  }

/* Get and convert unsigned numbers of all types. */
TOKEN number (TOKEN tok)
  { long num;
    long mantissa = 0;
    int  c, charval;
    int dec = -1;
    int sdec = 0;
    int pos_digits = -1;
    long exp = 0;
    char EXP_FLAG = 0;
    int EXP_SIGN = 1;
    num = 0;
    int numsigd = -1;
    int ERROR_FLAG = 0;
    int ERROR_CONTINUE_FLAG = 0;
    while ( (c = peekchar()) != EOF
            && (CHARCLASS[c] == NUMERIC || (c == '.' && CHARCLASS[peek2char()] == NUMERIC) || c == 'e' || (EXP_FLAG == 1 && c == '-') || (EXP_FLAG == 1 && c == '+')) && ERROR_FLAG == 0) 
    {   
        c = getchar();
            if (c == 'e') {
                EXP_FLAG = 1;
                continue;
            }
            if (c == '.') {
                if (dec != -1) {
                    printf("error: more than 1 decimal place in token\n");
                    ERROR_FLAG = 1;
                    break;
                }
                else {
                    dec = 0;
                    continue;
                }
            }
            if (EXP_FLAG == 0) {
                if (numsigd > -1 || (numsigd == -1 && c != '0'))
                    numsigd++;
                if (numsigd == -1 && dec > -1) 
                    sdec++;
                if (numsigd < MAX_SIGNIFICANT_DIGITS) {
                    charval = (c - '0');
                    mantissa = mantissa * 10 + charval;
                    if (dec > -1)
                        dec++;
                }
                if (dec == -1) {
                    if (numsigd > -1)
                        pos_digits++;
                    charval = (c - '0');
                    if (num > INTMAX/10 || (num == INTMAX/10 && charval > 7)) {
                        ERROR_CONTINUE_FLAG = 1;
                        continue;
                    }
                    else {
                        num = num * 10 + charval;
                    }
                }
            }
            else if (EXP_FLAG >= 1) {
                if (c == '-') {
                    if (EXP_FLAG == 1) {
                        EXP_SIGN = -1;
                    }
                } else if (c == '+') {
                    
                } else {
                    charval = (c - '0');
                    int _dec = (dec == -1) ? 0 : dec;
                    // if (exp > INTMAX/10 || (exp == INTMAX/10 && charval > 7)){
                    //     printf("error: exponent %d too large. tokentype: %d datatype: %d\n", exp, NUMBERTOK, (dec > -1) ? REAL : INTEGER);
                    //     ERROR_CONTINUE_FLAG = 1;
                    //     continue;
                    // }
                    exp = exp * 10 + charval;
                }
                EXP_FLAG++;
            }
        
    }
    if (dec == -1 && EXP_FLAG == 0)
    {
        tok->tokentype = NUMBERTOK;
        tok->basicdt = INTEGER;
        if (ERROR_CONTINUE_FLAG == 1) {
            printf("Integer number out of range\n");
        }
        tok->intval = num;
    }
    else if (dec == -1) {
        tok->tokentype = NUMBERTOK;
        tok->basicdt = REAL;
        double exnum = 0;
        if (exp*EXP_SIGN+pos_digits > 38) {
            printf("Floating number out of range\n");
        }
        else if (exp*EXP_SIGN+pos_digits < -38) {
            printf("Floating number out of range\n");
        }
        else {
            double m = 0.0;
            if (mantissa > 9999999) {
                m = (double)mantissa / 10000000.0;
            }
            else {
                int i = 0;
                m = (double)mantissa;
                while (i < pos_digits) {
                    m /= 10.0;
                    i++;
                }
            }
            if (exp*EXP_SIGN+pos_digits < 0)
                exnum = m * 1.0/EXPTABLE[0 - exp*EXP_SIGN - pos_digits];
            else
                exnum = m * EXPTABLE[exp + pos_digits];
        }
        tok->realval = exnum;
    }
    else
    {
        double realnum = 0.0;
        if (exp*EXP_SIGN-sdec+pos_digits > 38) {
            printf("Floating number out of range\n");
        }
        else if (exp*EXP_SIGN-sdec+pos_digits < -38) {
            printf("Floating number out of range\n");
        }
        else {
            double m = 0.0;
            if (mantissa > 9999999) {
                m = (double)mantissa / 10000000.0;
            }
            else {
                int i = 0;
                m = (double)mantissa;
                int _dec = (dec == -1) ? 0 : dec-sdec;
                while (i < pos_digits+_dec) {
                    m /= 10.0;
                    i++;
                }
            }
            // else if (dec <= 0) {
            //     int i = 0;
            //     m = (double)mantissa;
            //     while (i < pos_digits) {
            //         m /= 10.0;
            //         i++;
            //     }
            // }
            // else {
            //     int i = 0;
            //     m = (double)mantissa;
            //     while (i < dec) {
            //         m *= 10.0;
            //         i++;
            //     }
            // }
            // printf("%d = %f\n", mantissa, m);
            // printf("EE%d\n", exp*EXP_SIGN+pos_digits-sdec);
            if (exp*EXP_SIGN+pos_digits-sdec < 0)
                realnum = m * 1.0/EXPTABLE[sdec - exp*EXP_SIGN - pos_digits];
            else
                realnum = m * EXPTABLE[exp*EXP_SIGN + pos_digits - sdec];
        }
        tok->tokentype = NUMBERTOK;
        tok->basicdt = REAL;
        tok->realval = realnum;
    }
    return (tok);
  }
