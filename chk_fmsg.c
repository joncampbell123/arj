/*
 * $Id: chk_fmsg.c,v 1.2 2003/02/07 17:21:01 andrew_belov Exp $
 * ---------------------------------------------------------------------------
 * The purpose of this module is to check the integrity of the message section
 * by comparing its CRC-32 with the stored value.
 *
 */

#include "arj.h"

DEBUGHDR(__FILE__)                      /* Debug information block */

/* uncomment this if you want to debug CRC errors --J.C. */
/* #define DEBUG_CRC */

/* Checks the integrity of FMSG section. Reports CRC error in case of CRC
   mismatch. */

void check_fmsg(int skip_check)
{
 FMSGP *index_ptr;
 #if SFX_LEVEL>=ARJ
  char fmsg_buf[MSGTEXT_MAX];
 #endif

 crc32term=CRC_MASK;
 #ifdef DEBUG_CRC
   fprintf(stderr,"CRC start %08lx\n",(unsigned long)crc32term);
 #endif

 #if SFX_LEVEL>=ARJ
 if(skip_check!=CHKMSG_SKIP)
 #else
 if(skip_check==CHKMSG_SKIP)
 #endif
 {
  for(index_ptr=FARMSGS; *index_ptr!=NULL; index_ptr++)
  {
   #ifdef FMSG_ST
    far_strcpyn((char FAR *)fmsg_buf, (char FAR *)*index_ptr, sizeof(fmsg_buf));
    crc32_for_string(fmsg_buf);
    #ifdef DEBUG_CRC
     fprintf(stderr,"CRC check result [FMSG_ST] %08lx for '%s' => '%s'\n",(unsigned long)crc32term,*index_ptr,fmsg_buf);
    #endif
   #else
    crc32_for_string(*index_ptr);
    #ifdef DEBUG_CRC
     fprintf(stderr,"CRC check result %08lx for '%s'\n",(unsigned long)crc32term,*index_ptr);
    #endif
   #endif
  }
  if(crc32term!=FARMSGS_CRC32) {
   #ifdef DEBUG_CRC
   fprintf(stderr,"CRC check failed: got=%08lx expected=%08lx\n",
     (unsigned long)crc32term,
     (unsigned long)FARMSGS_CRC32);
   #endif
   error(M_CRC_ERROR);
  }
 }
 #if SFX_LEVEL<=ARJSFXV
 else
 {
  msg_cprintf(0, strform, M_SFX_USAGE);
  msg_cprintf(0, strform, M_SFX_COMMANDS);
 }
 #endif
}
