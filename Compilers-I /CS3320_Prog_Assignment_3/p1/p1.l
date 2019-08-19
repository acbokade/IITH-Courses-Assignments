%{
	#include "y.tab.h"
	void yyerror(const char*);
%}
	/*	Names for regular expressions	*/
DIGITS 			[0-9]
INTEGERS		{DIGITS}+
ROWS			[1-8]
COLUMNS			[a-h]
SPECIALPIECE 	[RBQKN]	
MOVENUMBER		{INTEGERS}[ \t]*"."	

%%
	/*	Eating up all the move numbers	*/
{MOVENUMBER}			;
	/*	matching the row number in the move */	
{ROWS}					{ 
							yylval.intVal = atoi(yytext);
							return ROW; 
						}
	/*	matching the column number in the move and converting it to digit	*/
{COLUMNS}				{ 
							yylval.intVal = *yytext - 'a' + 1;
							return COLUMN;
						}
	/*	matching special pieces such as R,B,Q,K,N	*/
{SPECIALPIECE}			{ 
							yylval.charVal = *yytext;
							return SPECIALPIECES;
						}			
	/*	matching hyphen equals to and x character and returning it as is	*/
[-=x]					{ return *yytext; }
	/*	eating up whitepsaces and newine	*/
[ \t\n]					;
	/*	any other character not matched above is invalid	*/
.						{
							char buffer[20];
							sprintf(buffer,"invalid character %c ", *yytext);
							yyerror(buffer);
						}
%%

int yywrap()
{
	return 1;
}