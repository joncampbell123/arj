/*
 * $Id: arjsec_l.h,v 1.1.1.1 2002/03/28 00:01:19 andrew_belov Exp $
 * ---------------------------------------------------------------------------
 * Prototypes of the functions located in ARJSEC_L.C are declared here.
 *
 */

#ifndef ARJSEC_L_INCLUDED
#define ARJSEC_L_INCLUDED

/* Prototypes */

int create_envelope(FILE *stream, uint32_t offset, int iter);

void arjsec_term(uint32_t *block, uint32_t *dest, int iter);
void arjsec_xor(uint32_t *dest, uint32_t *src);
void arjsec_newblock(uint32_t *dest);
void arjsec_invert(uint32_t *block);
void arjsec_crcterm(uint32_t *block, unsigned char c);
void arjsec_read(uint32_t *block, FILE *stream, uint32_t len);

void rev_arjsec_term(uint32_t *block, uint32_t *dest, int iter);
void arjsec_revert(uint32_t *block);

#endif

