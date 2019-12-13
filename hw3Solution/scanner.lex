%{ 
/* Declarations section */

	#include "hw3_output.hpp"
	#include "structs.hpp"
	#include "parser.tab.hpp"
	#include<iostream>
    using namespace std;
	using namespace output;
	

	
	
%} 

%option yylineno 
%option noyywrap 	

whitespace										([\t\n\r ])

%%

void											{
													yylval = new VOID_T();
													return VOID;
												}
int												{
													yylval = new INT_T();
													return INT;
												}
byte											{
													yylval = new BYTE_T();
													return BYTE;
												}
b												{
													yylval = new B_T();
													return B;
												}
bool											{
													yylval = new BOOL_T();
													return BOOL;
												}
enum											{
													yylval = new ENUM_T();
													return ENUM;
												}
and 											{
													yylval = new AND_T();
													return AND;
												}
or												{
													yylval = new OR_T();
													return OR;
												}
not												{
													yylval = new NOT_T();
													return NOT;
												}
true											{
													yylval = new TRUE_T();
													return TRUE;
												}
false 											{
													yylval = new FALSE_T();
													return FALSE;
												}
return											{
													yylval = new RETURN_T();
													return RETURN;
												}
if												{
													yylval = new IF_T();
													return IF;
												}
else											{
													yylval = new ELSE_T();
													return ELSE;
												}
while											{
													yylval = new WHILE_T();
													return WHILE;
												}
break											{
													yylval = new BREAK_T();
													return BREAK;
												}
continue 										{
													yylval = new CONTINUE_T();
													return CONTINUE;
												}
\;												{
													yylval = new SC_T();
													return SC;
												}
\,												{
													yylval = new COMMA_T();
													return COMMA;
												}
\(												{
													yylval = new LPAREN_T();
													return LPAREN;
												}
\)												{
													yylval = new RPAREN_T();
													return RPAREN;
												}
\{												{
													yylval = new LBRACE_T();
													return LBRACE;
												}
\}												{
													yylval = new RBRACE_T();
													return RBRACE;
												}
\=												{
													yylval = new ASSIGN_T();
													return ASSIGN;
												}
"<="|">="|"<"|">"								{
													yylval = new RELATIONOP_T();
													((RELATIONOP_T*) yylval)->op=yytext; 
													return RELATIONOP;
												}	
"=="|"!="										{
													yylval = new EQUALOP_T();
													((EQUALOP_T*) yylval)->op=yytext; 
													return EQUALOP;
												}
\+|\-											{
													yylval = new ADDOPS_T();
													((ADDOPS_T*) yylval)->op=yytext; 
													return ADDOPS;
												}
\*|\/											{
													yylval = new MULTOPS_T();
													((MULTOPS_T*) yylval)->op=yytext; 
													return MULTOPS;
												}
[a-zA-Z][a-zA-Z0-9]*							{ 
													yylval = new ID_T(); 
													((ID_T*) yylval)->id=yytext; 
													return ID; 
												} 
0|[1-9][0-9]*									{ 
													yylval = new NUM_T(); 
													((NUM_T*) yylval)->value=stoi(yytext); 
													return NUM; 
												} 
["](([^\n\r\"\\]|\\[rnt"\\])+)["]				{
													yylval = new STRING_T();
										
													((STRING_T*) yylval)->value=yytext;
													return STRING;
												}
"//"[^\r\n]*[ \r|\n|\r\n]?						;				;
{whitespace}									;
.												{ errorLex(yylineno); exit(0);}

%%

