/* ���� */
/* �ṩprintf�ӳ��� */

//#include	<reg52.h>
#include	"CH376INC.H"
#include	"HAL.H"

#ifndef	__DEBUG_H__
#define __DEBUG_H__

#ifdef __CX51__
#ifndef __C51__
#define __C51__		1
#endif
#endif

#ifdef __C51__
#define	BIG_ENDIAN		1
#endif
#ifdef __C51__
#pragma NOAREGS
#endif

/* ������״̬,�����������ʾ������벢ͣ��,Ӧ���滻Ϊʵ�ʵĴ�����ʩ,������ʾ������Ϣ,�ȴ��û�ȷ�Ϻ����Ե� */
void	mStopIfError( UINT8 iError );

/* Ϊprintf��getkey���������ʼ������ */
void	mInitSTDIO( void );

#endif