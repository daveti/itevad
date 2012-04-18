/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "ITEVAD"
 * 	found in "itevad.asn1"
 */

#ifndef	_MessageRequest_H_
#define	_MessageRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TransactionId.h"
#include "AskContent.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MessageRequest */
typedef struct MessageRequest {
	TransactionId_t	 transactionId;
	AskContent_t	 askContent;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MessageRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MessageRequest;

#ifdef __cplusplus
}
#endif

#endif	/* _MessageRequest_H_ */
