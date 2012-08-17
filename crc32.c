/*
 * $Id: crc32.c,v 1.1.1.1 2002/03/28 00:02:10 andrew_belov Exp $
 * ---------------------------------------------------------------------------
 * This file contains CRC32 calculation routines.
 *
 */

#include "arj.h"

DEBUGHDR(__FILE__)                      /* Debug information block */

#define CRCPOLY          0xEDB88320UL    /* CRC32 polynomial */
#define UPDATE_CRC(r, c) crc32tab[((unsigned char)((uint32_t)r)^(unsigned char)((uint32_t)c))&0xFFUL]^(((uint32_t)r)>>((uint32_t)CHAR_BIT))

uint32_t crc32term;
uint32_t crc32tab[256];

/* CRC32 initialization */

void build_crc32_table()
{
  unsigned int i, j;
  uint32_t r;

  for(i=0; i<=UCHAR_MAX; i++)
  {
   r=i;
   for(j=CHAR_BIT; j>0; j--)
   {
    if(r&1)
     r=(r>>1UL)^CRCPOLY;
    else
     r>>=1UL;
   }
   crc32tab[i]=r;
  }
}

/* Calculates CRC32 for a given block */

void crc32_for_block(char *block, unsigned int b_size)
{
  while(b_size--)
   crc32term=UPDATE_CRC(crc32term, *block++);
}

#if SFX_LEVEL>=ARJSFX||defined(REARJ)||defined(REGISTER)||defined(ARJUTIL)

/* Calculates CRC32 for a given ASCIIz string */

void crc32_for_string(char *sptr)
{
  while(*sptr!='\0')
   crc32term=UPDATE_CRC(crc32term, (unsigned char)(*sptr++));
}

/* Evaluates CRC32 based on character and term given */

uint32_t crc32_for_char(uint32_t crc32_term, unsigned char newc)
{
  return(UPDATE_CRC(crc32_term, newc));
}

#endif

