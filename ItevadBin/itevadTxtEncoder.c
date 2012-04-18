/*
Itevad Protocol Text Encoder Example
http://daveti.blog.com
April 5, 2012
Reference: Using the Open Source ASN.1 Compiler
by Lev Walkin
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "ItevadMessage.h"

#define TEXT_ENCODE_BUFFER_SIZE_MAX	1000

#define PTR_MOVE( step, forward, backward)			\
	{							\
		forward += step;				\
		backward -= step;				\
		if ( backward < 0)				\
		{						\
			fprintf( stderr, "No buffer left"	\
				" - backward: %d\n", backward);	\
		}						\
	}

/*
Text encoding helper function
to convert OCTET_STRING to string.
*/
char *txt_octetString2String( OCTET_STRING_t *octetString)
{
	/* Defensive checking */
	if ( octetString == NULL)
	{
		fprintf( stderr, "Invalid parameter\n");
		return NULL;
	}
	if ( octetString->size <= 0)
	{
		fprintf( stderr, "Empty Octet string\n");
		return NULL;
	}

	/* Allocate the string buffer from HEAP */
	char *string = (char *)calloc( 1, (octetString->size+1));

	/* Convert the uint8_t into ASCII characters */
	int i;
	for ( i = 0; i < octetString->size; i++)
	{
		string[ i] = (char)octetString->buf[ i];
	}

	/* Though redundant - just make it clear:) */
	string[ octetString->size] = '\0';

	return string;
}

/*
Text encoding core function
to convert the ItevadMessage_t type
into Text based Itevad message.
*/
int txt_encode( char *encodeBuffer, ItevadMessage_t *itevadMsg)
{
	/* Defensive checking */
	if ( (encodeBuffer == NULL) || (itevadMsg == NULL))
	{
		fprintf( stderr, "Invalid parameters\n");
		return -1;
	}

	/* Go thru itevadMsg to do Text encoding */

	char *txtPtr = encodeBuffer;
	int lengthOfBuffer = TEXT_ENCODE_BUFFER_SIZE_MAX;
	int numOfChar = 0;

	/* Construct msg header */
	numOfChar = snprintf( txtPtr, lengthOfBuffer,
			"Itevad/%d ", itevadMsg->version);
	PTR_MOVE( numOfChar, txtPtr, lengthOfBuffer);

	/* Construct IP address */
	if ( itevadMsg->ip4Address.address.size != 4)
	{
		fprintf( stderr, "Invalid IP address size: %d\n",
			itevadMsg->ip4Address.address.size);
		return -1;
	}
	numOfChar = snprintf( txtPtr, lengthOfBuffer,
			"[%u.%u.%u.%u]",
			itevadMsg->ip4Address.address.buf[ 0],
			itevadMsg->ip4Address.address.buf[ 1],
			itevadMsg->ip4Address.address.buf[ 2],
			itevadMsg->ip4Address.address.buf[ 3]);
	PTR_MOVE( numOfChar, txtPtr, lengthOfBuffer);

	/* Construct the port number if it is available */
	if ( itevadMsg->ip4Address.portNumber != NULL)
	{
		numOfChar = snprintf( txtPtr, lengthOfBuffer,
				":%ld", *(itevadMsg->ip4Address.portNumber));
		PTR_MOVE( numOfChar, txtPtr, lengthOfBuffer);
	}

	/* Move to a new line */
	numOfChar = snprintf( txtPtr, lengthOfBuffer, "%s", "\n");
	PTR_MOVE( numOfChar, txtPtr, lengthOfBuffer);

	/* Construct the Transaction */
	long transId = 0;
	char *contentP = NULL;
	switch ( itevadMsg->messageBody.present)
	{
		case MessageBody_PR_messageRequest:
		{
			/* Get the transId */
			if ( asn_INTEGER2long(
				&(itevadMsg->messageBody.choice.messageRequest.transactionId),
				&(transId)) == -1)
			{
				fprintf( stderr, "Encode transId in messageRequest error\n");
				return -1;
			}

			/* Get the ask content */
			contentP = txt_octetString2String(
				&(itevadMsg->messageBody.choice.messageRequest.askContent));

			numOfChar = snprintf( txtPtr, lengthOfBuffer,
					"Transaction = %ld {\n"
					"\tAsk = \"%s\"\n"
					"}\n",
					transId, contentP);
		}
		break;

		case MessageBody_PR_messageReply:
		{
			/* Get the transId */
			if ( asn_INTEGER2long(
				&(itevadMsg->messageBody.choice.messageReply.transactionId),
				&(transId)) == -1)
			{
				fprintf( stderr, "Encode transId in messageReply error\n");
				return -1;
			}

			/* Get the answer content */
			contentP = txt_octetString2String(
				&(itevadMsg->messageBody.choice.messageReply.answerContent));

			numOfChar = snprintf( txtPtr, lengthOfBuffer,
					"Reply = %ld {\n"
					"\tAnswer = \"%s\"\n"
					"}\n",
					transId, contentP);
		}
		break;

		default:
		{
			fprintf( stderr, "Invalid message type: %d\n",
				itevadMsg->messageBody.present);
			return -1;
		}
		break;
	}

	free( contentP);
	PTR_MOVE( numOfChar, txtPtr, lengthOfBuffer);

	return (txtPtr - encodeBuffer);
}

int main( int ac, char **av)
{
	/* Type to encode */
	ItevadMessage_t *itevadMsg;

	/* Return value for Text encoding */
	int ec;

	/* Text encoding buffer */
	char textEncodeBuffer[ TEXT_ENCODE_BUFFER_SIZE_MAX] = {0};

	/* Allocate the ItevadMessage_t */
	itevadMsg = calloc( 1, sizeof(ItevadMessage_t));
	if ( !itevadMsg)
	{
		perror("calloc() failed");
		exit(71); /* better, EX_OSERR */
	}

	/* Initialize the ItevadMessage members */

	/* Set version number - 1 */
	itevadMsg->version = 1;

	/* Set IPv4 address - "1111" */
	if ( OCTET_STRING_fromString( &(itevadMsg->ip4Address.address), "1111") == -1)
	{
		perror("OCTET_STRING_fromString() failed for encoding 'address'");
		exit(71);
	}

	/* Set port number - 7777 */
	long portNumber = 7777;
	itevadMsg->ip4Address.portNumber = &portNumber;

	/* Set the msg as a request */
	itevadMsg->messageBody.present = MessageBody_PR_messageRequest;

	/* Set the transId - 0xffff */
	long transId = 0xffff;
	if ( asn_long2INTEGER( &(itevadMsg->messageBody.choice.messageRequest.transactionId),
		transId) == -1)
	{
		perror("asn_long2INTEGER() failed for encoding 'transId'");
		exit(71);
	}

	/* Set the askContent - 'who r you?' */
	const char* askContent = "who r you?";
	if ( OCTET_STRING_fromString( &(itevadMsg->messageBody.choice.messageRequest.askContent),
		askContent) == -1)
	{
		perror("OCTET_STRING_fromString() failed for encoding 'askContent'");
		exit(71);
	}
	
	/* Text encode the data if filename is given */
	if ( ac < 2)
	{
		fprintf( stderr, "Specify filename for Text output\n");
	}
	else
	{
		/* NOTE: need memory deallocaiton before exit ! */

		/* Encode the ItevadMessage type as Text */
		ec = txt_encode( textEncodeBuffer, itevadMsg);

		if ( ec == -1)
		{
			fprintf( stderr, "Could not encode ItevadMessage\n");
			exit(65); /* Better, EX_DATAERR */
		}
		else
		{
			/* Write the encoded msg into file */
			const char *filename = av[ 1];
			FILE *fp = fopen( filename, "wb"); /* for Text output */
			if ( !fp)
			{
				perror( filename);
				exit(71);
			}
			fprintf( fp, "%s", textEncodeBuffer);
			fclose( fp);

			fprintf( stderr, "Created %s with Text encoded ItevadMessage\n", filename);
		}
	} /* else... */

	/* Also print the constructured Itevad XER encoded (XML) */
	xer_fprint( stdout, &asn_DEF_ItevadMessage, itevadMsg);

	/* NOTE: Need memory deallocaiton here! */

	/* Encoding finished successfully */
	return 0;
}
