/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SLASH = 258,
     LBRKT = 259,
     RBRKT = 260,
     COLON = 261,
     EQUAL = 262,
     NUMBER = 263,
     LSB = 264,
     RSB = 265,
     quotedString = 266,
     ItevadToken = 267,
     TransToken = 268,
     ReplyToken = 269,
     AskToken = 270,
     AnswerToken = 271,
     DOT = 272,
     IPv4Address = 273
   };
#endif
/* Tokens.  */
#define SLASH 258
#define LBRKT 259
#define RBRKT 260
#define COLON 261
#define EQUAL 262
#define NUMBER 263
#define LSB 264
#define RSB 265
#define quotedString 266
#define ItevadToken 267
#define TransToken 268
#define ReplyToken 269
#define AskToken 270
#define AnswerToken 271
#define DOT 272
#define IPv4Address 273




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 35 "itevadTxtBison2.y"
{
	unsigned long		ulongVal;
	char *			stringVal;
	ItevadMessage_t		itevadMsgVal;
	IP4Address_t		ipv4AddressVal;
	MessageBody_t		messageBodyVal;
	MessageRequest_t	messageReqVal;
	MessageReply_t		messageRepVal;
	AskContent_t		askContentVal;
	AnswerContent_t		answerContentVal;
}
/* Line 1529 of yacc.c.  */
#line 97 "itevadTxtBison2.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

