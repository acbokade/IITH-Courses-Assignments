%{
	#include <iostream>
	#include <stdio.h>
	#include <string.h>
	using namespace std;
	int yylex();
	char chessBoard[9][9];
	void displayBoard();
	void yyset_in(FILE*);
	void yyerror(const char*);
%}

	/*	different dataypes used for values in value stack 	*/
%union
{
	int intVal;		/*	used for rows and columns	*/
	char charVal;	/*	used for special pieces such as R,N,B,K,Q 	*/
}

	/*	defining start state, terminal symbols along with their types	*/
%start S
%token <intVal> ROW COLUMN 
%token <charVal> SPECIALPIECES

%%
	/*	Grammar rules 	*/
S 		:  
		| S Move 
		;
	/*	rules for All possible moves in input file and corresponding changes in chessboard configuration 	*/
Move 	: COLUMN ROW '-' COLUMN ROW 					{ chessBoard[$5][$4] = 'P'; chessBoard[$2][$1] = ' ';} 	
		| COLUMN ROW 'x' COLUMN ROW   					{ chessBoard[$5][$4] = 'P'; chessBoard[$2][$1] = ' ';}
		| SPECIALPIECES COLUMN ROW '-' COLUMN ROW   	{ chessBoard[$6][$5] = $1 ; chessBoard[$3][$2] = ' ';}
		| SPECIALPIECES COLUMN ROW 'x' COLUMN ROW   	{ chessBoard[$6][$5] = $1 ; chessBoard[$3][$2] = ' ';}
		| COLUMN ROW  '-' COLUMN ROW '=' SPECIALPIECES	{
															chessBoard[$5][$4] = $7;																
														}
		;

%%

	/*	Main function	*/
int main()
{
	FILE* input;
	input = fopen("input.txt", "r");
	yyset_in(input);
	int i;
	memset(chessBoard, ' ', 9*9);
	/*	Setting up the defualt chess board 	*/
	chessBoard[0][1] = 'a';chessBoard[0][2] = 'b';
	chessBoard[0][3] = 'c';chessBoard[0][4] = 'd';
	chessBoard[0][5] = 'e';chessBoard[0][6] = 'f';
	chessBoard[0][7] = 'g';chessBoard[0][8] = 'h';
	chessBoard[1][0] = '1';chessBoard[2][0] = '2';
	chessBoard[3][0] = '3';chessBoard[4][0] = '4';
	chessBoard[5][0] = '5';chessBoard[6][0] = '6';
	chessBoard[7][0] = '7';chessBoard[8][0] = '8';

	chessBoard[1][1] = chessBoard[8][1] = chessBoard[1][8] = chessBoard[8][8] = 'R';
	chessBoard[1][2] = chessBoard[8][2] = chessBoard[1][7] = chessBoard[8][7] = 'N';
	chessBoard[1][3] = chessBoard[8][3] = chessBoard[1][6] = chessBoard[8][6] = 'B';
	chessBoard[1][4] = chessBoard[8][4] = 'Q';
	chessBoard[1][5] = chessBoard[8][5] = 'K';

	for(i=1;i<=8;i++)
	{
		chessBoard[2][i] = chessBoard[7][i] = 'P';
	}
	yyparse();
	/*	displaying the board after parsing 	*/
	displayBoard();
	fclose(input);
}

	/*	function for error handling, printed in stderr	*/
void yyerror(const char* str)
{
	fprintf(stderr, "%s\n", str);
	return;
}

	/*	Function for printing the chess board	*/
void displayBoard()
{
	int i,j;
	for(i=0;i<=8;i++)
	{
		for(j=0;j<=8;j++)
		{
			cout<<chessBoard[i][j]<<"\t";
		}
		cout<<endl<<endl;
	}
}