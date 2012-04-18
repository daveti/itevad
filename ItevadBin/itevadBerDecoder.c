/*
Itevad Protocol Binary Ber Decoder Example
April 1, 2012
http://daveti.blog.com
Reference: Using the Open Source ASN.1 Compiler
by Lev Walkin
*/

#include <stdio.h>
#include <sys/types.h>
#include "ItevadMessage.h"

int main( int ac, char **av)
{
	char buf[ 1024]; /* Temp buffer */
	ItevadMessage_t *itevadMsg = NULL; /* Type to decode */
	asn_dec_rval_t rval; /* Decoder return value */
	FILE *fp;	/* Input file handler */
	size_t size;	/* Number of bytes read */
	char *filename;	/* Input file name */

	/* Require a single filename argument */
	if ( ac != 2)
	{
		fprintf( stderr, "Usage: %s <file.ber>\n", av[ 0]);
		exit(64); /* better, EX_USAGE */
	}
	else
	{
		filename = av[ 1];
	}

	/* Open input file as read-only binary */
	fp = fopen( filename, "rb");
	if ( !fp)
	{
		perror( filename);
		exit(66); /* better, EX_NOINPUT */
	}

	/* Read up to the buffer size */
	size = fread( buf, 1, sizeof( buf), fp);
	fclose( fp);
	if ( !size)
	{
		fprintf( stderr, "%s: Empty or broken\n", filename);
		exit(65); /* better, EX_DATAERR */
	}

	/* Decode the input buffer as Itevad type */
	rval = ber_decode( 0, &asn_DEF_ItevadMessage, (void **)&itevadMsg, buf, size);
	if ( rval.code != RC_OK)
	{
		fprintf( stderr, "%s: Broken ItevadMessage decoding at byte %ld\n",
			filename, (long)rval.consumed);
		exit(65); /* better, EX_DATAERR */
	}

	/* Print the decoded Itevad type as XML */
	xer_fprint( stdout, &asn_DEF_ItevadMessage, itevadMsg);

	/* Decoding finished successfully */
	return 0;
}
