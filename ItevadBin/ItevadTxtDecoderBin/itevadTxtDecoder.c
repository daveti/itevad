/*
Itevad Protocol Text Decoder Example
April 18, 2012
http://daveti.blog.com
*/

#include <stdio.h>
#include <sys/types.h>
#include "itevadTxtFlex2.h"
#include "ItevadMessage.h"

extern int yyparse( ItevadMessage_t *itevadMsg);

int main( int ac, char **av)
{
	char buf[ 1024] = {0}; /* Temp buffer - NOTE: may overflow...*/
	ItevadMessage_t *itevadMsg = NULL; /* Type to decode */
	int rval; /* Decoder return value */
	FILE *fp;	/* Input file handler */
	size_t size;	/* Number of bytes read */
	char *filename;	/* Input file name */

	/* Require a single filename argument */
	if ( ac != 2)
	{
		fprintf( stderr, "Usage: %s <file.msg>\n", av[ 0]);
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
        itevadMsg = calloc( 1, sizeof(ItevadMessage_t));
        if ( itevadMsg == NULL)
        {
                fprintf( stderr, "Memory allocation failure for itevadMsg\n");
                exit(65);
        }

	printf("itevadTxtDecoderBin-debug: calling yy_scan_string() - buf:\n"
		"%s\n", buf);
	yy_scan_string( buf);

	printf("itevadTxtDecoderBin-debug: calling yyparse()\n");
	rval = yyparse( itevadMsg);
	if ( rval != 0)
	{
		fprintf( stderr, "%s: Broken ItevadMessage Bison decoding\n",
			filename);
		exit(65); /* better, EX_DATAERR */
	}

	/* Print the decoded Itevad type as XML */
	printf("itevadTxtDecoderBin-debug: calling xer_fprint()\n");
	xer_fprint( stdout, &asn_DEF_ItevadMessage, itevadMsg);

	/* Decoding finished successfully */
	return 0;
}
