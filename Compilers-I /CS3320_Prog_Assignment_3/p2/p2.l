%{
	#include "y.tab.h"
	void yyerror(const char*);
%}

%x comments
	/*	Names for regular expressions	*/
LETTERS			[_a-zA-Z]
DIGITS 			[0-9]
INTEGERS		{DIGITS}+
IDENTIFIERS 	{LETTERS}({LETTERS}|{DIGITS})*

%%
	/*	8 binary digits of seven segment display with each digit separated by tab	*/
[\t][(0|1)][\t][(0|1)][\t][(0|1)][\t][(0|1)][\t][(0|1)][\t][(0|1)][\t][(0|1)][\t][(0|1)]	{
																								strcpy(yylval.strVal,strtok(yytext,"\t"));
																								strcat(yylval.strVal,strtok(NULL,"\t")); 
																								strcat(yylval.strVal,strtok(NULL,"\t"));
																								strcat(yylval.strVal,strtok(NULL,"\t")); 
																								strcat(yylval.strVal,strtok(NULL,"\t")); 
																								strcat(yylval.strVal,strtok(NULL,"\t")); 
																								strcat(yylval.strVal,strtok(NULL,"\t")); 
																								strcat(yylval.strVal,strtok(NULL,"\t")); 																								
																								return BINARYDIGITS; 
																							}
	/*	eating up whitespace characters	*/
[ \t]+ 			;
	/*	state changed to comment when # is encountered	*/
"#"				{ BEGIN(comments); }
	/*	eating up all characters in comment state	*/
<comments>.   	;
	/*	state changed to INITITAL when newline is encountered	*/
<comments>"\n"	{ BEGIN(INITIAL); }
	/*	special keywords of input file being matched in case insensitive form	*/
(?i:INIT)		{ return INIT; }
(?i:Select)		{ return SELECT; }
(?i:int)		{ return INT; }
(?i:readInt) 	{ return READINT; }
(?i:if)			{ return IF; }
(?i:Else)	 	{ return ELSE; }
(?i:Delay)		{ return DELAY; }
	/*	all the different comparison operators in the condition of if statement	*/
("=="|"!="|">"|"<"|">="|"<=")	{
									strcpy(yylval.strVal, yytext); 
									return COMPARATOR; 
								}
	/*	matching colon and equal to and returning it as is	*/
[:=]				{ return yytext[0]; }
	/*	Names for regular expressions	*/
[\n]				;
	/*	matching integers and converting it to int type from string	*/
{INTEGERS}			{
						yylval.intVal = atoi(yytext);
						return INTEGER;
					}
	/*	matching the identifiers 	*/
{IDENTIFIERS}		{
						strcpy(yylval.strVal, yytext);
						return IDENTIFIER;
					}
	/*	any other character not matched above is invalid	*/
.					{
						char buffer[20];
						sprintf(buffer,"invalid character %c ", yytext[0]);
						yyerror(buffer);
					}
%%

int yywrap()
{
	return 1;
}
