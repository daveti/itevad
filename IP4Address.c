/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "ITEVAD"
 * 	found in "itevad.asn1"
 */

#include <asn_internal.h>

#include "IP4Address.h"

static int
memb_address_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 4)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_portNumber_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 65536)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_TYPE_member_t asn_MBR_IP4Address_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IP4Address, address),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_address_constraint_1,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"address"
		},
	{ ATF_POINTER, 1, offsetof(struct IP4Address, portNumber),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_portNumber_constraint_1,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"portNumber"
		},
};
static ber_tlv_tag_t asn_DEF_IP4Address_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_IP4Address_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* address at 24 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* portNumber at 25 */
};
static asn_SEQUENCE_specifics_t asn_SPC_IP4Address_specs_1 = {
	sizeof(struct IP4Address),
	offsetof(struct IP4Address, _asn_ctx),
	asn_MAP_IP4Address_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_IP4Address = {
	"IP4Address",
	"IP4Address",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_IP4Address_tags_1,
	sizeof(asn_DEF_IP4Address_tags_1)
		/sizeof(asn_DEF_IP4Address_tags_1[0]), /* 1 */
	asn_DEF_IP4Address_tags_1,	/* Same as above */
	sizeof(asn_DEF_IP4Address_tags_1)
		/sizeof(asn_DEF_IP4Address_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_IP4Address_1,
	2,	/* Elements count */
	&asn_SPC_IP4Address_specs_1	/* Additional specs */
};

