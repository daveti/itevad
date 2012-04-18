/*
Itevad Protocol Text Encoding Lexical Analyzer Example
April 6, 2012
http://daveti.blog.com
Reference: itevad.abnf
NOTE: This is a Flex file NOT Lex!
*/

%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ItevadMessage.h"
#include "itevadTxtBison.tab.h"
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
\"(.)*\"		{ printf("Debug - quoted string: %s\n", yytext);
			  /* Delete the prefix and suffix double quotes */
			  char *content = strndup( (yytext+1), (strlen(yytext)-2));
			  yylval.stringVal = content;
			  printf("flex-debug: quotedString: %s\n", yylval.stringVal);
			  return quotedString;
			} 				/* Quoted String */
[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3} 	{  /* IPv4 address handling here */
			  printf("Debug - IPv4 address: %s\n", yytext);
			  /* Try to convert the IPv4 format into octet string format
			   * to help the parser for value assignment.
			   * "49.49.49.49" --> "1111"
			   * char '1' has ASCII code "49"
			   * NOTE: we do have a bug here as NOT all the IPv4 address
 			   * could be translated into "xxxx" format string!!!!!!!!
			   */
			  char *ipv4Address = strdup( yytext);
			  char *octecString = calloc( 1, 5);
			  int i = 0;
			  unsigned char value = '\0';
			  char *headPtr = ipv4Address;
			  char *ptr = ipv4Address;
			  while ( *ptr != '\0')
			  {
				if ( *ptr == '.')
				{
					*ptr = '\0';
					value = (unsigned char)strtoul( headPtr, NULL, 10);
					i += snprintf( octecString+i, 5-i, "%c", value);
					headPtr = ptr + 1;
				}
				ptr++;
			  }
			  /* Convert the last octec char */
			  value = (unsigned char)strtoul( headPtr, NULL, 10);
			  i += snprintf( octecString+i, 5-i, "%c", value);
			  yylval.stringVal = octecString;
			  printf("flex-debug: IPv4Address: %s\n", yylval.stringVal);
			  return IPv4Address;
			} 				/* IPv4 Address */
[0-9]+			{ printf("Debug - number: %s\n", yytext);
			  yylval.ulongVal = strtoul(yytext, NULL, 10);
			  printf("flex-debug: NUMBER: %lu\n", yylval.ulongVal);
			  return NUMBER;
			} 				/* Number */
[ \t\r\n\v]		{ /* Ignore */ }		/* White spaces */
.			{ printf( "Decode failure at %c\n", *yytext); }

%%
