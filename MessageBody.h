/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "ITEVAD"
 * 	found in "itevad.asn1"
 */

#ifndef	_MessageBody_H_
#define	_MessageBody_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MessageRequest.h"
#include "MessageReply.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MessageBody_PR {
	MessageBody_PR_NOTHING,	/* No components present */
	MessageBody_PR_messageRequest,
	MessageBody_PR_messageReply
} MessageBody_PR;

/* MessageBody */
typedef struct MessageBody {
	MessageBody_PR present;
	union MessageBody_u {
		MessageRequest_t	 messageRequest;
		MessageReply_t	 messageReply;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MessageBody_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MessageBody;

#ifdef __cplusplus
}
#endif

#endif	/* _MessageBody_H_ */
