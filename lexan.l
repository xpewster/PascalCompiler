%{    /* lex2.l -- partial lex specification for Pascal   16 Sep 20 */

/* Copyright (c) 2019 Gordon S. Novak Jr. and The University of Texas at Austin
   */
/* 22 Jul 13; 20 Feb 19
   */

/* This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>. */

/* To use:
        make lex2
        lex2
        x < 3.14            */

/* This file will work as given on a simple input such as:
   if i<j then x := 3.14

   Copy this file to lexan.l and expand it for your assignment.
   Use:
        make lexer
        lexer <graph1.pas
   */

#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexan.h"

int maketoken(int type, int which);
int install_id();
int install_num();
int install_fnum();
int install_string();
int yywrap();
void comment_flag(int which, int stop);

/* If the lex yytext buffer turns out to be too small to hold comments,
   add the following lines:
 #undef YYLMAX
 #define YYLMAX 256
 */

TOKEN talloc();

TOKEN yylval;     /* This is the type of the lexical analyzer result */

char COMMENT_1_FLAG = 0;
char COMMENT_2_FLAG = 0;

%}

/* regular definitions */

string   '([^']|"''")*'
delim    [ \t\n]
ws       {delim}+
letter   [A-Za-z]
digit    [0-9]
id       {letter}({letter}|{digit})*
number   {digit}+
fnumber  {digit}+(\.{digit}+)?([eE][+\-]?{digit}+)?

%%

{ws}      { /* no action and no return */ }
array     {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, ARRAY));}}
begin     {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, BEGINBEGIN));}}
case      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, CASE));}}
const     {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, CONST));}}
do        {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, DO));}}
downto    {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, DOWNTO));}}
else      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, ELSE));}}
end       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, END));}}
file      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, FILEFILE));}}
for       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, FOR));}}
function  {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, FUNCTION));}}
goto      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, GOTO));}}
if        {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, IF));}}
label     {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, LABEL));}}
nil       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, NIL));}}
of        {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, OF));}}
packed    {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, PACKED));}}
procedure {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, PROCEDURE));}}
program   {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, PROGRAM));}}
record    {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, RECORD));}}
repeat    {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, REPEAT));}}
set       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, SET));}}
then      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, THEN));}}
to        {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, TO));}}
type      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, TYPE));}}
until     {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, UNTIL));}}
var       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, VAR));}}
while     {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, WHILE));}}
with      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(RESERVED, WITH));}}
{id}      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(install_id());}}
{number}  {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(install_num());}}
{fnumber} {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(install_fnum());}}
{string}  {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(install_string());}}
"+"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, PLUS));}}
"-"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, MINUS));}}
"*"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, TIMES));}}
"/"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, DIVIDE));}}
"^"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, POINT));}}
"<"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, LT));}}
"<="      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, LE));}}
"="       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, EQ));}}
"<>"      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, NE));}}
">"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, GT));}}
">="      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, GE));}}
":="      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, ASSIGN));}}
"."       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(OPERATOR, DOT));}}
","       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, COMMA));}}
";"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, SEMICOLON));}}
":"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, COLON));}}
"("       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, LPAREN));}}
")"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, RPAREN));}}
"["       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, LBRACKET));}}
"]"       {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, RBRACKET));}}
".."      {if (COMMENT_1_FLAG != 1 && COMMENT_2_FLAG != 1) {return(maketoken(DELIMITER, DOTDOT));}}
"{"       {comment_flag(1, 0);}
"}"       {comment_flag(1, 1);}
"(*"      {comment_flag(2, 0);}
"*)"      {comment_flag(2, 1);}

%%

/* Note that lex always returns two values:
   1. "What is it?": a small integer such as NUMBER that indicates the
      kind of item that was found; this is the return() value.
   2. The value itself.  This is yylval, which points to a TOKEN.   */

/* Make simple tokens. */
int maketoken(int type, int which)
  {
  yylval = talloc();  /* Make new token, set yylval to point to it */
  yylval->tokentype = type;
  if (type == RESERVED)
     yylval->whichval = which - RESERVED_BIAS;
     else if (type == OPERATOR)
             yylval->whichval = which - OPERATOR_BIAS;
             else if (type == DELIMITER)
                     yylval->whichval = which - DELIMITER_BIAS;
                     else yylval->whichval = which;
  return(which);
  }

int install_id()
 { int i, c, n;
  yylval = talloc();  /* Make new token, set yylval to point to it */
  yylval->tokentype = IDENTIFIERTOK;
  n = yyleng;            /* number of characters */
  if ( n > 15 ) n = 15;
  for (i = 0; i < n ; i++)
   { c = yytext[i];
          /* if (islower(c)) c = toupper(c); */ /* to raise to upper case */
     yylval->stringval[i] = c;
    };
  yylval->stringval[n] = '\0';
          /* printf("id  %10s   n = %4d\n", yytext, n); */
  return(IDENTIFIER);
 }

 int install_num() {  /* Note -- you may use sscanf for this assignment. */
  int num;
  yylval = talloc();   /* Make new token, set yylval to point to it */
  yylval->tokentype = NUMBERTOK;
  yylval->basicdt = INTEGER;
       /* printf("num %10s   n = %4d\n",yytext,yyleng); */
  sscanf(yytext, "%d", &num);
  yylval->intval = num;
  return(NUMBER);
 }

int install_fnum() {  /* Note -- you may use sscanf for this assignment. */
  float fnum;
  yylval = talloc();   /* Make new token, set yylval to point to it */
  yylval->tokentype = NUMBERTOK;
  yylval->basicdt = REAL;
       /* printf("num %10s   n = %4d\n",yytext,yyleng); */
  sscanf(yytext, "%f", &fnum);
  yylval->realval = fnum;
  return(NUMBER);
 }

 int install_string() {  /* Note -- you may use sscanf for this assignment. */
  char str[16];
  yylval = talloc();   /* Make new token, set yylval to point to it */
  yylval->tokentype = STRINGTOK;
       /* printf("num %10s   n = %4d\n",yytext,yyleng); */
  //sscanf(yytext, "\'%15[[^']|[i{2,2}]]\'", str);
  char *p = yytext;
  ++p;
  char *s = str;
  strcpy(s, "");
  while (*p != '\0' && s-str < 15) {
     if (*p == '\'') {
        if (*(++p) == '\'') {
           strncat(s, p, 1);
        }
        else {
           break;
        }
     }
     else {
        strncat(s, p, 1);
     }
     ++s;
     ++p;
  }
  *s = '\0';
  strcpy(yylval->stringval, str);
  return(STRING);
 }


int yywrap() {  return(1);  }       /* lex may need this. */

void comment_flag(int which, int stop) {
   if (stop == 0) {
      if (which == 1)
         COMMENT_1_FLAG = 1;
      else if (which == 2)
         COMMENT_2_FLAG = 1;
   }
   else if (stop == 1) {
      if (which == 1)
         COMMENT_1_FLAG = 0;
      else if (which == 2)
         COMMENT_2_FLAG = 0;
   }
}