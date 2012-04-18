/*
Itevad Protocol Text Encoding Lexical Analyzer Stand Alone Example
April 6, 2012
http://daveti.blog.com
Reference: itevad.abnf
NOTE: This is a Flex file NOT Lex!
*/

%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum yytokentype
{
	DOT,
	LSB,
	RSB,
	EQUAL,
	COLON,
	LBRKT,
	RBRKT,
	SLASH,
	ItevadToken,
	TransToken,
	ReplyToken,
	AskToken,
	AnswerToken,
	quotedString,
	IPv4Address,
	NUMBER
};	
%}

/* Configure our lexer */
%option stack noyywrap case-insensitive

%%

"."			{ return DOT; }			/* Dot */
"["			{ return LSB; }			/* Left square bracket */
"]"			{ return RSB; }			/* Right square bracket */
"="			{ return EQUAL; }		/* Equal */
":"			{ return COLON; }		/* Colon */
"{"			{ return LBRKT; }		/* Left brace */
"}"			{ return RBRKT; }		/* Right brace */
"/"			{ return SLASH; }		/* Slash */
"Itevad"		{ return ItevadToken; } 	/* Itevad Token */
"Transaction"		{ return TransToken; }		/* Transaction Token */
"Reply"			{ return ReplyToken; }		/* Reply Token */
"Ask"			{ return AskToken; }		/* Ask Token */
"Answer"		{ return AnswerToken; }		/* Answer Token */
\"(.*)\"		{ printf("Debug - quoted string: %s\n", yytext);
			  return quotedString;
			}				/* Quoted String */
[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3} 	{  /* IPv4 address handling here */
			  printf("Debug - IPv4 address: %s\n", yytext);
			  return IPv4Address;
			}				/* IPv4 Address */
[0-9]+			{ printf("Debug - number: %s\n", yytext);
			  return NUMBER;
			}				/* Number */
[ \t\r\n\v]		{ /* Ignore */ }		/* White spaces */

%%

int main( int argc, char **argv)
{
	int token;
	while ( token = yylex())
	{
		printf("Token: %d\n", token);
	}

	return 0;
}
