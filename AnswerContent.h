/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "ITEVAD"
 * 	found in "itevad.asn1"
 */

#ifndef	_AnswerContent_H_
#define	_AnswerContent_H_


#include <asn_application.h>

/* Including external dependencies */
#include <IA5String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* AnswerContent */
typedef IA5String_t	 AnswerContent_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AnswerContent;
asn_struct_free_f AnswerContent_free;
asn_struct_print_f AnswerContent_print;
asn_constr_check_f AnswerContent_constraint;
ber_type_decoder_f AnswerContent_decode_ber;
der_type_encoder_f AnswerContent_encode_der;
xer_type_decoder_f AnswerContent_decode_xer;
xer_type_encoder_f AnswerContent_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _AnswerContent_H_ */
