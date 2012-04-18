/*
Itevad Protocol Text Encoding Sematic Analyzer Example
April 9, 2012
http://daveti.blog.com
Reference: itevad.abnf
NOTE: This is a Bison file NOT Yacc!
*/

%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ItevadMessage.h"
%}

/* Token list */
%token SLASH LBRKT RBRKT COLON EQUAL NUMBER LSB RSB quotedString
%token ItevadToken TransToken ReplyToken AskToken AnswerToken
%token DOT IPv4Address

/* Type list */
%type <ulongVal>		version transactionId portNumber NUMBER
%type <stringVal>		quotedString IPv4Address
%type <itevadMsgVal>		itevadMessage
%type <ipv4AddressVal>		ipv4Address
%type <messageBodyVal>		messageBody
%type <messageReqVal>		messageRequest
%type <messageRepVal>		messageReply
%type <askContentVal>		askContent
%type <answerContentVal>	answerContent

%union
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

%start itevadMessage

%%

itevadMessage:
	ItevadToken SLASH version ipv4Address messageBody
		{ $$.version = $3;
		  $$.ip4Address = $4;
		  $$.messageBody = $5;
		}
		;

version:
	NUMBER
		{ printf("bison-debug: version: %lu\n", $1);
		  $$ = $1;
		}
		;

ipv4Address:
	LSB IPv4Address RSB
		{ printf("bison-debug: IPv4Address-$2: %s\n", $2);
		  OCTET_STRING_t myAddress;
		  memset( &myAddress, 0, sizeof(OCTET_STRING_t));
		  if ( OCTET_STRING_fromString( &myAddress, $2) == -1)
		  {
			yyerror( "OCTET_STRING_fromString failure for ip4Address.address\n");
		  }
		  $$.address = myAddress;
		}
	| LSB IPv4Address RSB COLON portNumber
		{ printf("bison-debug: IPv4Address-$2: %s\n", $2);
		  OCTET_STRING_t myAddress;
		  memset( &myAddress, 0, sizeof(OCTET_STRING_t));
		  if ( OCTET_STRING_fromString( &myAddress, $2) == -1)
		  {
			yyerror( "OCTET_STRING_fromString failure for ip4Address.address\n");
		  }
		  $$.address = myAddress;
		  $$.portNumber = &($5);
		}
		;

portNumber:
	NUMBER
		{ printf("bison-debug: portNumber: %lu\n", $1);
		  $$ = $1;
		}
		;

messageBody:
	messageRequest
		{ $$.present = MessageBody_PR_messageRequest;
		  $$.choice.messageRequest = $1;
		}
	| messageReply
		{ $$.present = MessageBody_PR_messageReply;
		  $$.choice.messageReply = $1;
		}
		;

messageRequest:
	TransToken EQUAL transactionId LBRKT askContent RBRKT
		{ INTEGER_t myTransId;
		  memset( &myTransId, 0, sizeof(INTEGER_t));
		  if ( asn_long2INTEGER( &myTransId, $3) == -1)
		  {
			yyerror( "asn_long2INTEGER failure for transId in messageRequest\n");
		  }
		  $$.transactionId = myTransId;
		  $$.askContent = $5;
		}
		;

messageReply:
	ReplyToken EQUAL transactionId LBRKT answerContent RBRKT
		{ INTEGER_t myTransId;
		  memset( &myTransId, 0, sizeof(INTEGER_t));
		  if ( asn_long2INTEGER( &myTransId, $3) == -1)
		  {
			yyerror( "asn_long2INTEGER failure for transId in messageReply\n");
		  }
		  $$.transactionId = myTransId;
		  $$.answerContent = $5;
		}
		;

transactionId:
	NUMBER
		{ printf("bison-debug: transactionId: %lu\n", $1);
		  $$ = $1;
		}
		;

askContent:
	AskToken EQUAL quotedString
		{ printf("bison-debug: askContent-quotedString-$3: %s\n", $3);
		  AskContent_t myAskContent;
		  memset( &myAskContent, 0, sizeof(OCTET_STRING_t));
		  if ( OCTET_STRING_fromString( &myAskContent, $3) == -1)
		  {
			yyerror( "OCTET_STRING_fromString failure for askContent\n");
		  }
		  $$ = myAskContent;
		}
		;

answerContent:
	AnswerToken EQUAL quotedString
		{ printf("bison-debug: answerContent-quotedString-$3: %s\n", $3);
		  AnswerContent_t myAnswerContent;
		  memset( &myAnswerContent, 0, sizeof(OCTET_STRING_t));
		  if ( OCTET_STRING_fromString( &myAnswerContent, $3) == -1)
		  {
			yyerror( "OCTET_STRING_fromString failure for answerContent\n");
		  }
		  $$ = myAnswerContent;
		}
		;

%%

int main( int argc, char **argv)
{
	yyparse();
	return 0;
}

int yyerror( const char *msg)
{
	fprintf( stderr, "yyerror: %s\n", msg);
}

