/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "ITEVAD"
 * 	found in "itevad.asn1"
 */

#ifndef	_IP4Address_H_
#define	_IP4Address_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* IP4Address */
typedef struct IP4Address {
	OCTET_STRING_t	 address;
	long	*portNumber	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} IP4Address_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IP4Address;

#ifdef __cplusplus
}
#endif

#endif	/* _IP4Address_H_ */