/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "ITEVAD"
 * 	found in "itevad.asn1"
 */

#ifndef	_ItevadMessage_H_
#define	_ItevadMessage_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Version.h"
#include "IP4Address.h"
#include "MessageBody.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ItevadMessage */
typedef struct ItevadMessage {
	Version_t	 version;
	IP4Address_t	 ip4Address;
	MessageBody_t	 messageBody;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ItevadMessage_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ItevadMessage;

#ifdef __cplusplus
}
#endif

#endif	/* _ItevadMessage_H_ */
