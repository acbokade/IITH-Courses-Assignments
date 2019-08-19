%{
	#include <iostream>
	#include <stdio.h>
	#include <string.h>
	using namespace std;
	int yylex();
	void yyset_in(FILE*);
	void yyerror(const char*);
%}

	/*	different dataypes used for values in value stack	*/
%union
{
	int intVal;			/*	used for integers	*/
	char strVal[300];	/*	used for identifiers, comparison operators, binary digits of seven segment display	*/
}

	/*	defining start state, terminal symbols along with their types	*/
%start S
%token INIT SELECT DELAY INT READINT IF ELSE 
%token <strVal> IDENTIFIER COMPARATOR BINARYDIGITS
%token <intVal> INTEGER 

%%
	/*	Grammar rules 	*/
S 		: init 
		  multipleDisplay 		{
		  							printf("\t}\n}\n");
		  						}
	/*	matching init and printing it	*/
init 	: INIT					{
									printf("#include<stdio.h>\n#include<stdlib.h>\n#include<seven_segment.h>\nint main()\n{\n\tinit();\n\twhile(1)\n\t{\n");	
								}
	/*	rule for multiple display statements in input file 	*/
multipleDisplay : multipleDisplay display 
				| display 
				;
	/*	rule for each statment and printing corresponding C source code 	*/
display : IDENTIFIER ':' INT 					{
													printf("\t\tint %s;\n",$1); 
												}
		| IDENTIFIER '=' READINT 				{
													printf("\t\t%s = readInt();\n",$1); 
												}
		| SELECT ':' INTEGER 					{
													printf("\t\tselect(%d);\n",$3);
												}
		| BINARYDIGITS 							{
													printf("\t\twrite(strtol(\"%s\"));\n", $1);
												}
		| IF IDENTIFIER	COMPARATOR INTEGER ':' BINARYDIGITS  ELSE ':' BINARYDIGITS	{
																						printf("\t\tif(%s%s%d)\n\t\t{\n\t\t\twrite(strtol(\"%s\"));\n\t\t}\n\t\telse\n\t\t{\n\t\t\twrite(strtol(\"%s\"));\n\t\t}\n",$2,$3,$4,$6,$9);
																					}							
		| DELAY ':' INTEGER  					{
													printf("\t\tdelay(%d);\n",$3);
												}																					 
		;

%%

	/*	Main function	*/
int main()
{
	FILE* input;
	input = fopen("input.txt", "r");
	yyset_in(input);
	yyparse();
	fclose(input);
}
	/*	function for error handling, printed in stderr	*/
void yyerror(const char* str)
{
	fprintf(stderr, "%s\n", str);
}
