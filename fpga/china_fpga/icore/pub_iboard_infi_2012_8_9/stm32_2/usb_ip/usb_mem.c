/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_mem.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Utility functions for memory transfers to/from PMA
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "..\usb_include\usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : UserToPMABufferCopy
* Description    : Copy a buffer from user memory area to packet memory area (PMA)
* Input          : - pbUsrBuf: pointer to user memory area.
*                  - wPMABufAddr: address into PMA.
*                  - wNBytes: no. of bytes to be copied.
* Output         : None.
* Return         : None	.
*******************************************************************************/
void UserToPMABufferCopy(unsigned char *pbUsrBuf, unsigned short int wPMABufAddr, unsigned short int wNBytes)
{
	unsigned long int n = (wNBytes + 1) >> 1; /* n = (wNBytes + 1) / 2 */
	unsigned long int i, temp1, temp2;
	unsigned short int *pdwVal;
	pdwVal = (unsigned short int*)(wPMABufAddr * 2 + PMAAddr);
	for (i = n; i != 0; i--) {
		temp1 = (unsigned short int)*pbUsrBuf;
		pbUsrBuf++;
		temp2 = temp1 | (unsigned short int)*pbUsrBuf << 8;
		*pdwVal++ = temp2;
		pdwVal++;
		pbUsrBuf++;
	}
}
/*******************************************************************************
* Function Name  : PMAToUserBufferCopy
* Description    : Copy a buffer from user memory area to packet memory area (PMA)
* Input          : - pbUsrBuf    = pointer to user memory area.
*                  - wPMABufAddr = address into PMA.
*                  - wNBytes     = no. of bytes to be copied.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PMAToUserBufferCopy(unsigned char *pbUsrBuf, unsigned short int wPMABufAddr, unsigned short int wNBytes)
{
	unsigned long int n = (wNBytes + 1) >> 1; /* /2*/
	unsigned long int i;
	unsigned long int *pdwVal;
	pdwVal = (unsigned long int*)(wPMABufAddr * 2 + PMAAddr);
	for (i = n; i != 0; i--) {
		*(unsigned short int*)pbUsrBuf++ = *pdwVal++;
		pbUsrBuf++;
	}
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
