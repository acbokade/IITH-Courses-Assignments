/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
  if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
    YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */
/*    Specifies number of nested comments     */
int noOfNestedComments = 0;
/*    function that checks if character specified in argument can be added to string buffer and if so, it then adds     */
int writeToStringBuffer(char *text);
%}

/*    state when string just begins   */
%x str 
/*    state when multi line (* comment starts   */
%x comment
/*    state when single line -- comment starts    */
%x dashComments
/*    state when null character occurs in string or string's length becomes greater than specified    */
%x invalidStr

/*
 * Define names for regular expressions here.
 */

/*    reserved keywords in COOL    */
/*    ?i stands for case insensitive    */
DARROW          =>
ASSIGN          <-
CLASS           (?i:class)
INHERITS        (?i:inherits)
NEW             (?i:new)
FALSE           (?i:false)
TRUE            (?i:true)
IF              (?i:if)
THEN            (?i:then)
ELSE            (?i:else)
FI              (?i:fi)
WHILE           (?i:while)
LOOP            (?i:loop)
POOL            (?i:pool)
ISVOID          (?i:isvoid)
LET             (?i:let)
IN              (?i:in)
CASE            (?i:case)
OF              (?i:of)
ESAC            (?i:esac)
NOT             (?i:not)

/*    All whitespace characters   */
WHITESPACE      [ \t\r\f\v]+

/*    Integers, Type Identifiers, Object Identifiers    */
INTEGERS            [0-9]+
TYPE_IDENTIFIERS    [A-Z][_0-9a-zA-Z]*   
OBJECT_IDENTIFIERS  [a-z][_0-9a-zA-Z]*     

%%
 /*
  *  Nested comments
  */
        /*   Changing state to comment and incrementing no of nested comments for (* pattern   */
"(*"        {
              noOfNestedComments++;
              BEGIN(comment);
            }
        /*   If a *) is matched while in INITIAL state, then ERROR "Unmatched *)" is displayed   */
"*)"        {
              cool_yylval.error_msg = "Unmatched *)";
              return ERROR;
            }

        /* Multi Line comments  state */
<comment>"(*"   { noOfNestedComments++; } 
        /*  Simply incrementing current line number when \n occurs   */ 
<comment>\n     { curr_lineno++; }
        /* When a *) is matched in comment state, then checking if it has its corresponding (*
        *   by comparing noOfNestedComments with 0. If it does not then displaying ERROR "Unmatched *)"
        *   Else decrementing noOfNestedComments. Also, changing state to INITIAL if noOfNestedComments becomes 0.
        */
<comment>"*)"   {
                  noOfNestedComments--;
                  if(noOfNestedComments < 0)
                  {
                    noOfNestedComments = 0;
                    cool_yylval.error_msg = "Unmatched *)";
                    BEGIN(INITIAL);
                    return ERROR;
                  }
                  else if(noOfNestedComments == 0)
                    BEGIN(INITIAL); 
                }
        /*   If EOF is encountered then ERROR "EOF in comment" is displayed   */
<comment><<EOF>>  {
                    BEGIN(INITIAL);
                    cool_yylval.error_msg = "EOF in comment";
                    return ERROR;
                  }
        /*  No action performed for other characters   */
<comment>.  ;

        /*  Single line dash comments, state is changed to dashComments   */
"--"          { BEGIN(dashComments); }
        /*  If a \n occurs, single line comment ends and hence state is changed to INITIAL and line no is incremented  */
<dashComments>\n      { 
                        curr_lineno++; 
                        BEGIN(INITIAL);
                      }
        /*  Eating up all other characters  */
<dashComments>[^\n]*  ;
      
        /*  invalid string state which occurs when string contains null character or string constant exceeds 1024 characters  */
        /*  if in invalidStr state, characters are consumed with no action till a closing " or newline occurs.  */
<invalidStr>\"          { BEGIN(INITIAL); }
        /*  incrementing line no and changing state to INITIAL   */
<invalidStr>\n          {
                          curr_lineno++;
                          BEGIN(INITIAL);
                        }
        /*  Eating up all other characters  */
<invalidStr>.           ;

  /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */
              /*      beginning of string constant, assigning string_buf_ptr to start of buffer array     */
\"            {
                string_buf_ptr = string_buf;
                BEGIN(str);
              }
              /*      end of the string constant, adding string constant to stringtable     */
<str>\"       {
                *string_buf_ptr = '\0';
                BEGIN(INITIAL);
                cool_yylval.symbol = stringtable.add_string(string_buf);  
                return STR_CONST;
              }
              /*      EOF in string, hence returning error and changing state to INITIAL     */
<str><<EOF>>  {
                cool_yylval.error_msg = "EOF in string constant";
                BEGIN(INITIAL);
                return ERROR;
              }
              /*      unescaped newline character, hence returning error     */
<str>\n       {
                cool_yylval.error_msg = "Unterminated string constant";
                curr_lineno++;
                *string_buf_ptr = '\0';
                BEGIN(INITIAL);
                return ERROR;
              }
              /*      null character in string, returning error    */
<str>\0       {
                cool_yylval.error_msg = "String contains null character";
                *string_buf_ptr = '\0';
                BEGIN(invalidStr);
                return ERROR;
              }
              /*      newline character in string , adding \n to string     */
<str>\\n      {
                if(writeToStringBuffer("\n") == 0)
                {
                  yylval.error_msg = "String constant too long";
                  *string_buf_ptr = '\0';
                  BEGIN(invalidStr);
                  return ERROR;
                }
              }
              /*      escaped newline , adding \n to string and incrementing line number     */
<str>\\\n     {
                curr_lineno++;
                if(writeToStringBuffer("\n") == 0)
                {
                  yylval.error_msg = "String constant too long";
                  *string_buf_ptr = '\0';
                  BEGIN(invalidStr);
                  return ERROR;
                }
              }
              /*      adding \t to string     */
<str>\\t      {
                if(writeToStringBuffer("\t") == 0)
                {
                  yylval.error_msg = "String constant too long";
                  *string_buf_ptr = '\0';
                  BEGIN(invalidStr);
                  return ERROR;
                }
              }
              /*      adding \b to string     */
<str>\\b      {
                if(writeToStringBuffer("\b") == 0)
                {
                  yylval.error_msg = "String constant too long";
                  *string_buf_ptr = '\0';
                  BEGIN(invalidStr);
                  return ERROR;
                }
              }
              /*      adding \f to string     */
<str>\\f      {
                if(writeToStringBuffer("\f") == 0)
                {
                  yylval.error_msg = "String constant too long";
                  *string_buf_ptr = '\0';
                  BEGIN(invalidStr);
                  return ERROR;
                }
              }
              /*    for escaped character \c except \n,\b,\f,\t adding c to the string    */
<str>\\.      {
                if(writeToStringBuffer(yytext+1) == 0)
                {
                  yylval.error_msg = "String constant too long";
                  *string_buf_ptr = '\0';
                  BEGIN(invalidStr);
                  return ERROR;
                }
              }
              /*    adding to string all other characters    */
<str>.        {
                if(writeToStringBuffer(yytext) == 0)
                {
                  yylval.error_msg = "String constant too long";
                  *string_buf_ptr = '\0';
                  BEGIN(invalidStr);
                  return ERROR;
                }
              }
   
 /*
  *  The multiple-character operators.
  */
{DARROW}    { return (272); }
{ASSIGN}    { return (280); }

        /*  For single characters, their integer ASCII value is being returned.    */
"{"         { return (123); }
"}"         { return (125); }
"("         { return (40); }
")"         { return (41); }
":"         { return (58); }
";"         { return (59); }
"."         { return (46); }
","         { return (44); }
"+"         { return (43); }
"-"         { return (45); }
"*"         { return (42); }
"="         { return (61); }
"<"         { return (60); }
"<="        { return (282); }
"@"         { return (64); }
"/"         { return (47); }
"~"         { return (126); }

        /*   For reserved keywords, integer codes representing their syntactic category as defined in cool-parse.h is returned.   */
{CLASS}     { return (258); }
{INHERITS}  { return (263); }      
{NEW}       { return (273); }          
{IF}        { return (261); }      
{THEN}      { return (267); }      
{ELSE}      { return (259); }    
{FI}        { return (260); }      
{WHILE}     { return (268); }     
{LOOP}      { return (265); }      
{POOL}      { return (266); }     
{ISVOID}    { return (274); }     
{LET}       { return (264); }      
{IN}        { return (262); }      
{CASE}      { return (269); }      
{OF}        { return (271); }      
{ESAC}      { return (270); }     
{NOT}       { return (281); }  


 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
          /*  
          *   For keywords true and false, care has been taken that they are case sensitive (first character lowercase)
          *   and if matched, cool_yylval.boolean is being changed accordingly and BOOL_CONST is returned.
          */  
(t)(?i:rue)     { 
                 cool_yylval.boolean = true;
                 return (BOOL_CONST);
                }

(f)(?i:alse)    {
                 cool_yylval.boolean = false;
                 return (BOOL_CONST);
                }  

           /*
           *  For type identifiers, object identifiers, integers, their semantic value is stored in the field 
           *  cool_yylval.symbol and TYPEID, OBJECTID and INT_CONST is being returned respectively.
           */     
          /*  Integers  */
{INTEGERS}            {
                        cool_yylval.symbol = inttable.add_string(yytext);
                        return INT_CONST;
                      }

          /* Object Identifiers  */
{OBJECT_IDENTIFIERS}  {
                        cool_yylval.symbol = idtable.add_string(yytext);
                        return OBJECTID;
                      }

          /* Type identifiers   */
{TYPE_IDENTIFIERS}    {
                        cool_yylval.symbol = idtable.add_string(yytext);
                        return TYPEID;
                      }
                      
          /*  Eating up all whitespace characters  */
{WHITESPACE}+   ;

          /*  incrementing line number when \n occurs  */
\n              curr_lineno++;
    
          /*  If no pattern has matched from above, its invalid character, displaying that character and returning error   */
.               {
                  cool_yylval.error_msg = yytext;
                  return ERROR;
                }

%%

          /*  Function definition that checks if character specified in argument can be added to string buffer and if so, it then adds  */
int writeToStringBuffer(char *text)
{
  if(string_buf_ptr - string_buf + 1 >= MAX_STR_CONST)
  {
    return 0;
  }
  else
  {
    *string_buf_ptr = *text;
    string_buf_ptr++;
  }
  return 1;
}
