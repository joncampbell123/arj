/*
 * $Id: crc32.h,v 1.1.1.1 2002/03/28 00:02:10 andrew_belov Exp $
 * ---------------------------------------------------------------------------
 * Interface to the CRC32 module.
 *
 */

#ifndef CRC32_INCLUDED
#define CRC32_INCLUDED

/* Jonathan C: Changed their CRC code to use uint32_t rather than unsigned long.
 *             This is necessary for their CRC32 routines to work when compiled as x86_64 */
#include <stdint.h>

/* The following are externals exported from assembly-language routines: */

extern uint32_t crc32term;
#ifdef TILED
 extern unsigned short crc32tab_lo[256];
 extern unsigned short crc32tab_hi[256];
#else
 extern uint32_t crc32tab[256];
#endif

/* Platform-independent CRC macro */

#ifdef TILED
 #define get_crc32tab(i) ((((uint32_t)crc32tab_hi[i])<<16L)+(uint32_t)crc32tab_lo[i])
#else
 #define get_crc32tab(i) crc32tab[i]
#endif

/* Prototypes */

void build_crc32_table();
void crc32_for_block(char *block, unsigned int size);
void crc32_for_string(char *str);
uint32_t crc32_for_char(uint32_t crc32_term, unsigned char c);
uint32_t rev_crc32_for_char(uint32_t crc32_term, unsigned char c);
uint32_t afl_mul(uint32_t term, uint32_t multiplier);

#endif
