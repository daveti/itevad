/*
Itevad Protocol Binary Ber Encoder Example
http://daveti.blog.com
April 1, 2012
Reference: Using the Open Source ASN.1 Compiler
by Lev Walkin
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "ItevadMessage.h"

/*
 * This is a custom function which writes the
 * encoded output into some FILE stream.
 */
static int
write_out( const void *buffer, size_t size, void *app_key)
{
	FILE *out_fp = app_key;
	size_t wrote;
	wrote = fwrite( buffer, 1, size, out_fp);
	return ((wrote == size) ? 0 : -1);
}

int main( int ac, char **av)
{
	/* Type to encode */
	ItevadMessage_t *itevadMsg;

	/* Encoder return value */
	asn_enc_rval_t ec;

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
	
	/* BER encode the data if filename is given */
	if ( ac < 2)
	{
		fprintf( stderr, "Specify filename for BER output\n");
	}
	else
	{
		/* NOTE: need memory deallocaiton before exit ! */

		const char *filename = av[ 1];
		FILE *fp = fopen( filename, "wb"); /* for BER output */
		if ( !fp)
		{
			perror( filename);
			exit(71);
		}

		/* Encode the ItevadMessage type as BER (DER) */
		ec = der_encode( &asn_DEF_ItevadMessage, itevadMsg, write_out, fp);
		fclose( fp);

		if ( ec.encoded == -1)
		{
			fprintf( stderr, "Could not encode ItevadMessage (at %s)\n",
				ec.failed_type ? ec.failed_type->name : "unknown");
			exit(65); /* Better, EX_DATAERR */
		}
		else
		{
			fprintf( stderr, "Created %s with BER encoded ItevadMessage\n", filename);
		}
	} /* else... */

	/* Also print the constructured Itevad XER encoded (XML) */
	xer_fprint( stdout, &asn_DEF_ItevadMessage, itevadMsg);

	/* NOTE: Need memory deallocaiton here! */

	/* Encoding finished successfully */
	return 0;
}
