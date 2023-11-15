/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : lz41ci.h
*
* Description  : The CI file for the LZ4 package.
*
* Environment  : OS and HW independent
*
* Responsible  : Jan Horbach, Unicontrol
*
* Guidelines   : SMK V4.10
*
* Template name: OOLite Interface, Revision 1.0
*
* CASE-Tool    : Together Architect, Version 1.1
*
* Revision List: (Will be filled by MKS)
* Archive: $Log: lz41ci.h  $
* Archive: Revision 1.1 2014/01/07 07:59:47CET Locker, Thomas (uidf3900) 
* Archive: Initial revision
* Archive: Member added to project /id/_gen/sw/pkg/Basic/lz4/prv/Test/Win7/test_lz4/test_lz4/project.pj
* Archive: Revision 1.1 2013/11/29 15:38:33CET Horbach-EXT, Jan (uidt1466) 
* Archive: Initial revision
* Archive: Member added to project /id/_gen/sw/pkg/Basic/lz4/adapt/project.pj
****************************************************************************/

#ifndef LZ41CI_H
#define LZ41CI_H

//#include "cdef.h"

#define LZ4__nSupport_Compress   1
#define LZ4__nSupport_Uncompress 1
//#define LZ4__nSupport_xxHash     0  // Do not change because xxHash is not qualified yet!
#define LZ4__nSupport_Streaming  0  // Do not change because streaming is not qualified yet!


/* Options for lz4.c */

#define LZ4_FORCE_UNALIGNED_ACCESS 1

/* Memory options */

#if ( LZ4__nSupport_Compress == 1 )  // only needed for compression

/* Using TLSF */
//#include "tlsf_c1.h"
//#define LZ4__nAlloc(n,s)  TLSF_pvMallocMempool( TLSF_nLZ4_ID, n * s )
//#define LZ4__nFree(o)     TLSF_vFreeMempool( TLSF_nLZ4_ID, o )

/* Using calloc and free */
#define LZ4__nAlloc(n,s)  calloc( n, s )
#define LZ4__nFree(o)     free( o )

#endif

#endif /* LZ41CI_H */
