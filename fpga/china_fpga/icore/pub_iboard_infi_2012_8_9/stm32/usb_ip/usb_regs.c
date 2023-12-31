/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_regs.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Interface functions to USB cell registers
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
* Function Name  : SetCNTR.
* Description    : Set the CNTR register value.
* Input          : wRegValue: new register value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetCNTR(unsigned short int wRegValue)
{
	_SetCNTR(wRegValue);
}

/*******************************************************************************
* Function Name  : GetCNTR.
* Description    : returns the CNTR register value.
* Input          : None.
* Output         : None.
* Return         : CNTR register Value.
*******************************************************************************/
unsigned short int GetCNTR(void)
{
	return(_GetCNTR());
}

/*******************************************************************************
* Function Name  : SetISTR.
* Description    : Set the ISTR register value.
* Input          : wRegValue: new register value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetISTR(unsigned short int wRegValue)
{
	_SetISTR(wRegValue);
}

/*******************************************************************************
* Function Name  : GetISTR
* Description    : Returns the ISTR register value.
* Input          : None.
* Output         : None.
* Return         : ISTR register Value
*******************************************************************************/
unsigned short int GetISTR(void)
{
	return(_GetISTR());
}

/*******************************************************************************
* Function Name  : GetFNR
* Description    : Returns the FNR register value.
* Input          : None.
* Output         : None.
* Return         : FNR register Value
*******************************************************************************/
unsigned short int GetFNR(void)
{
	return(_GetFNR());
}

/*******************************************************************************
* Function Name  : SetDADDR
* Description    : Set the DADDR register value.
* Input          : wRegValue: new register value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetDADDR(unsigned short int wRegValue)
{
	_SetDADDR(wRegValue);
}

/*******************************************************************************
* Function Name  : GetDADDR
* Description    : Returns the DADDR register value.
* Input          : None.
* Output         : None.
* Return         : DADDR register Value
*******************************************************************************/
unsigned short int GetDADDR(void)
{
	return(_GetDADDR());
}

/*******************************************************************************
* Function Name  : SetBTABLE
* Description    : Set the BTABLE.
* Input          : wRegValue: New register value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetBTABLE(unsigned short int wRegValue)
{
	_SetBTABLE(wRegValue);
}

/*******************************************************************************
* Function Name  : GetBTABLE.
* Description    : Returns the BTABLE register value.
* Input          : None.
* Output         : None.
* Return         : BTABLE address.
*******************************************************************************/
unsigned short int GetBTABLE(void)
{
	return(_GetBTABLE());
}

/*******************************************************************************
* Function Name  : SetENDPOINT
* Description    : Setthe Endpoint register value.
* Input          : bEpNum: Endpoint Number.
*                  wRegValue.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetENDPOINT(unsigned char bEpNum, unsigned short int wRegValue)
{
	_SetENDPOINT(bEpNum, wRegValue);
}

/*******************************************************************************
* Function Name  : GetENDPOINT
* Description    : Return the Endpoint register value.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Endpoint register value.
*******************************************************************************/
unsigned short int GetENDPOINT(unsigned char bEpNum)
{
	return(_GetENDPOINT(bEpNum));
}

/*******************************************************************************
* Function Name  : SetEPType
* Description    : sets the type in the endpoint register.
* Input          : bEpNum: Endpoint Number.
*                  wType: type definition.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPType(unsigned char bEpNum, unsigned short int wType)
{
	_SetEPType(bEpNum, wType);
}

/*******************************************************************************
* Function Name  : GetEPType
* Description    : Returns the endpoint type.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Endpoint Type
*******************************************************************************/
unsigned short int GetEPType(unsigned char bEpNum)
{
	return(_GetEPType(bEpNum));
}

/*******************************************************************************
* Function Name  : SetEPTxStatus
* Description    : Set the status of Tx endpoint.
* Input          : bEpNum: Endpoint Number.
*                  wState: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPTxStatus(unsigned char bEpNum, unsigned short int wState)
{
	_SetEPTxStatus(bEpNum, wState);
}

/*******************************************************************************
* Function Name  : SetEPRxStatus
* Description    : Set the status of Rx endpoint.
* Input          : bEpNum: Endpoint Number.
*                  wState: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPRxStatus(unsigned char bEpNum, unsigned short int wState)
{
	_SetEPRxStatus(bEpNum, wState);
}

/*******************************************************************************
* Function Name  : SetDouBleBuffEPStall
* Description    : sets the status for Double Buffer Endpoint to STALL
* Input          : bEpNum: Endpoint Number.
*                  bDir: Endpoint direction.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetDouBleBuffEPStall(unsigned char bEpNum, unsigned char bDir)
{
	unsigned short int Endpoint_DTOG_Status;
	Endpoint_DTOG_Status = GetENDPOINT(bEpNum);
	if (bDir == EP_DBUF_OUT) { /* OUT double buffered endpoint */
		_SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPRX_DTOG1);
	}else if (bDir == EP_DBUF_IN) { /* IN double buffered endpoint */
		_SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPTX_DTOG1);
	}
}

/*******************************************************************************
* Function Name  : GetEPTxStatus
* Description    : Returns the endpoint Tx status.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Endpoint TX Status
*******************************************************************************/
unsigned short int GetEPTxStatus(unsigned char bEpNum)
{
	return(_GetEPTxStatus(bEpNum));
}

/*******************************************************************************
* Function Name  : GetEPRxStatus
* Description    : Returns the endpoint Rx status.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Endpoint RX Status
*******************************************************************************/
unsigned short int GetEPRxStatus(unsigned char bEpNum)
{
	return(_GetEPRxStatus(bEpNum));
}

/*******************************************************************************
* Function Name  : SetEPTxValid
* Description    : Valid the endpoint Tx Status.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPTxValid(unsigned char bEpNum)
{
	_SetEPTxStatus(bEpNum, EP_TX_VALID);
}

/*******************************************************************************
* Function Name  : SetEPRxValid
* Description    : Valid the endpoint Rx Status.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPRxValid(unsigned char bEpNum)
{
	_SetEPRxStatus(bEpNum, EP_RX_VALID);
}

/*******************************************************************************
* Function Name  : SetEP_KIND
* Description    : Clear the EP_KIND bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEP_KIND(unsigned char bEpNum)
{
	_SetEP_KIND(bEpNum);
}

/*******************************************************************************
* Function Name  : ClearEP_KIND
* Description    : set the  EP_KIND bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ClearEP_KIND(unsigned char bEpNum)
{
	_ClearEP_KIND(bEpNum);
}
/*******************************************************************************
* Function Name  : Clear_Status_Out
* Description    : Clear the Status Out of the related Endpoint
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Clear_Status_Out(unsigned char bEpNum)
{
	_ClearEP_KIND(bEpNum);
}
/*******************************************************************************
* Function Name  : Set_Status_Out
* Description    : Set the Status Out of the related Endpoint
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_Status_Out(unsigned char bEpNum)
{
	_SetEP_KIND(bEpNum);
}
/*******************************************************************************
* Function Name  : SetEPDoubleBuff
* Description    : Enable the double buffer feature for the endpoint.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPDoubleBuff(unsigned char bEpNum)
{
	_SetEP_KIND(bEpNum);
}
/*******************************************************************************
* Function Name  : ClearEPDoubleBuff
* Description    : Disable the double buffer feature for the endpoint.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ClearEPDoubleBuff(unsigned char bEpNum)
{
	_ClearEP_KIND(bEpNum);
}
/*******************************************************************************
* Function Name  : GetTxStallStatus
* Description    : Returns the Stall status of the Tx endpoint.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Tx Stall status.
*******************************************************************************/
unsigned short int GetTxStallStatus(unsigned char bEpNum)
{
	return(_GetTxStallStatus(bEpNum));
}
/*******************************************************************************
* Function Name  : GetRxStallStatus
* Description    : Returns the Stall status of the Rx endpoint.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Rx Stall status.
*******************************************************************************/
unsigned short int GetRxStallStatus(unsigned char bEpNum)
{
	return(_GetRxStallStatus(bEpNum));
}
/*******************************************************************************
* Function Name  : ClearEP_CTR_RX
* Description    : Clear the CTR_RX bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ClearEP_CTR_RX(unsigned char bEpNum)
{
	_ClearEP_CTR_RX(bEpNum);
}
/*******************************************************************************
* Function Name  : ClearEP_CTR_TX
* Description    : Clear the CTR_TX bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ClearEP_CTR_TX(unsigned char bEpNum)
{
	_ClearEP_CTR_TX(bEpNum);
}
/*******************************************************************************
* Function Name  : ToggleDTOG_RX
* Description    : Toggle the DTOG_RX bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ToggleDTOG_RX(unsigned char bEpNum)
{
	_ToggleDTOG_RX(bEpNum);
}
/*******************************************************************************
* Function Name  : ToggleDTOG_TX
* Description    : Toggle the DTOG_TX bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ToggleDTOG_TX(unsigned char bEpNum)
{
	_ToggleDTOG_TX(bEpNum);
}
/*******************************************************************************
* Function Name  : ClearDTOG_RX.
* Description    : Clear the DTOG_RX bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ClearDTOG_RX(unsigned char bEpNum)
{
	_ClearDTOG_RX(bEpNum);
}
/*******************************************************************************
* Function Name  : ClearDTOG_TX.
* Description    : Clear the DTOG_TX bit.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ClearDTOG_TX(unsigned char bEpNum)
{
	_ClearDTOG_TX(bEpNum);
}
/*******************************************************************************
* Function Name  : SetEPAddress
* Description    : Set the endpoint address.
* Input          : bEpNum: Endpoint Number.
*                  bAddr: New endpoint address.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPAddress(unsigned char bEpNum, unsigned char bAddr)
{
	_SetEPAddress(bEpNum, bAddr);
}
/*******************************************************************************
* Function Name  : GetEPAddress
* Description    : Get the endpoint address.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Endpoint address.
*******************************************************************************/
unsigned char GetEPAddress(unsigned char bEpNum)
{
	return(_GetEPAddress(bEpNum));
}
/*******************************************************************************
* Function Name  : SetEPTxAddr
* Description    : Set the endpoint Tx buffer address.
* Input          : bEpNum: Endpoint Number.
*                  wAddr: new address.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPTxAddr(unsigned char bEpNum, unsigned short int wAddr)
{
	_SetEPTxAddr(bEpNum, wAddr);
}
/*******************************************************************************
* Function Name  : SetEPRxAddr
* Description    : Set the endpoint Rx buffer address.
* Input          : bEpNum: Endpoint Number.
*                  wAddr: new address.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPRxAddr(unsigned char bEpNum, unsigned short int wAddr)
{
	_SetEPRxAddr(bEpNum, wAddr);
}
/*******************************************************************************
* Function Name  : GetEPTxAddr
* Description    : Returns the endpoint Tx buffer address.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Rx buffer address.
*******************************************************************************/
unsigned short int GetEPTxAddr(unsigned char bEpNum)
{
	return(_GetEPTxAddr(bEpNum));
}
/*******************************************************************************
* Function Name  : GetEPRxAddr.
* Description    : Returns the endpoint Rx buffer address.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Rx buffer address.
*******************************************************************************/
unsigned short int GetEPRxAddr(unsigned char bEpNum)
{
	return(_GetEPRxAddr(bEpNum));
}
/*******************************************************************************
* Function Name  : SetEPTxCount.
* Description    : Set the Tx count.
* Input          : bEpNum: Endpoint Number.
*                  wCount: new count value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPTxCount(unsigned char bEpNum, unsigned short int wCount)
{
	_SetEPTxCount(bEpNum, wCount);
}
/*******************************************************************************
* Function Name  : SetEPCountRxReg.
* Description    : Set the Count Rx Register value.
* Input          : *pdwReg: point to the register.
*                  wCount: the new register value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPCountRxReg(unsigned long int *pdwReg, unsigned short int wCount)
{
	_SetEPCountRxReg(dwReg, wCount);
}
/*******************************************************************************
* Function Name  : SetEPRxCount
* Description    : Set the Rx count.
* Input          : bEpNum: Endpoint Number.
*                  wCount: the new count value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPRxCount(unsigned char bEpNum, unsigned short int wCount)
{
	_SetEPRxCount(bEpNum, wCount);
}
/*******************************************************************************
* Function Name  : GetEPTxCount
* Description    : Get the Tx count.
* Input          : bEpNum: Endpoint Number.
* Output         : None
* Return         : Tx count value.
*******************************************************************************/
unsigned short int GetEPTxCount(unsigned char bEpNum)
{
	return(_GetEPTxCount(bEpNum));
}
/*******************************************************************************
* Function Name  : GetEPRxCount
* Description    : Get the Rx count.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Rx count value.
*******************************************************************************/
unsigned short int GetEPRxCount(unsigned char bEpNum)
{
	return(_GetEPRxCount(bEpNum));
}
/*******************************************************************************
* Function Name  : SetEPDblBuffAddr
* Description    : Set the addresses of the buffer 0 and 1.
* Input          : bEpNum: Endpoint Number.
*                  wBuf0Addr: new address of buffer 0.
*                  wBuf1Addr: new address of buffer 1.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPDblBuffAddr(unsigned char bEpNum, unsigned short int wBuf0Addr, unsigned short int wBuf1Addr)
{
	_SetEPDblBuffAddr(bEpNum, wBuf0Addr, wBuf1Addr);
}
/*******************************************************************************
* Function Name  : SetEPDblBuf0Addr
* Description    : Set the Buffer 1 address.
* Input          : bEpNum: Endpoint Number
*                  wBuf0Addr: new address.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPDblBuf0Addr(unsigned char bEpNum, unsigned short int wBuf0Addr)
{
	_SetEPDblBuf0Addr(bEpNum, wBuf0Addr);
}
/*******************************************************************************
* Function Name  : SetEPDblBuf1Addr
* Description    : Set the Buffer 1 address.
* Input          : bEpNum: Endpoint Number
*                  wBuf1Addr: new address.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPDblBuf1Addr(unsigned char bEpNum, unsigned short int wBuf1Addr)
{
	_SetEPDblBuf1Addr(bEpNum, wBuf1Addr);
}
/*******************************************************************************
* Function Name  : GetEPDblBuf0Addr
* Description    : Returns the address of the Buffer 0.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
unsigned short int GetEPDblBuf0Addr(unsigned char bEpNum)
{
	return(_GetEPDblBuf0Addr(bEpNum));
}
/*******************************************************************************
* Function Name  : GetEPDblBuf1Addr
* Description    : Returns the address of the Buffer 1.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Address of the Buffer 1.
*******************************************************************************/
unsigned short int GetEPDblBuf1Addr(unsigned char bEpNum)
{
	return(_GetEPDblBuf1Addr(bEpNum));
}
/*******************************************************************************
* Function Name  : SetEPDblBuffCount
* Description    : Set the number of bytes for a double Buffer
*                  endpoint.
* Input          : bEpNum,bDir, wCount
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPDblBuffCount(unsigned char bEpNum, unsigned char bDir, unsigned short int wCount)
{
	_SetEPDblBuffCount(bEpNum, bDir, wCount);
}
/*******************************************************************************
* Function Name  : SetEPDblBuf0Count
* Description    : Set the number of bytes in the buffer 0 of a double Buffer
*                  endpoint.
* Input          : bEpNum, bDir,  wCount
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPDblBuf0Count(unsigned char bEpNum, unsigned char bDir, unsigned short int wCount)
{
	_SetEPDblBuf0Count(bEpNum, bDir, wCount);
}
/*******************************************************************************
* Function Name  : SetEPDblBuf1Count
* Description    : Set the number of bytes in the buffer 0 of a double Buffer
*                  endpoint.
* Input          : bEpNum,  bDir,  wCount
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetEPDblBuf1Count(unsigned char bEpNum, unsigned char bDir, unsigned short int wCount)
{
	_SetEPDblBuf1Count(bEpNum, bDir, wCount);
}
/*******************************************************************************
* Function Name  : GetEPDblBuf0Count
* Description    : Returns the number of byte received in the buffer 0 of a double
*                  Buffer endpoint.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Endpoint Buffer 0 count
*******************************************************************************/
unsigned short int GetEPDblBuf0Count(unsigned char bEpNum)
{
	return(_GetEPDblBuf0Count(bEpNum));
}
/*******************************************************************************
* Function Name  : GetEPDblBuf1Count
* Description    : Returns the number of data received in the buffer 1 of a double
*                  Buffer endpoint.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : Endpoint Buffer 1 count.
*******************************************************************************/
unsigned short int GetEPDblBuf1Count(unsigned char bEpNum)
{
	return(_GetEPDblBuf1Count(bEpNum));
}
/*******************************************************************************
* Function Name  : GetEPDblBufDir
* Description    : gets direction of the double buffered endpoint
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : EP_DBUF_OUT, EP_DBUF_IN,
*                  EP_DBUF_ERR if the endpoint counter not yet programmed.
*******************************************************************************/
EP_DBUF_DIR GetEPDblBufDir(unsigned char bEpNum)
{
	if ((unsigned short int)(*_pEPRxCount(bEpNum) & 0xFC00) != 0)
		return(EP_DBUF_OUT);
	else if (((unsigned short int)(*_pEPTxCount(bEpNum)) & 0x03FF) != 0)
		return(EP_DBUF_IN);
	else
		return(EP_DBUF_ERR);
}
/*******************************************************************************
* Function Name  : FreeUserBuffer
* Description    : free buffer used from the application realizing it to the line
                   toggles bit SW_BUF in the double buffered endpoint register
* Input          : bEpNum, bDir
* Output         : None.
* Return         : None.
*******************************************************************************/
void FreeUserBuffer(unsigned char bEpNum, unsigned char bDir)
{
	if (bDir == EP_DBUF_OUT) { /* OUT double buffered endpoint */
		_ToggleDTOG_TX(bEpNum);
	}else if (bDir == EP_DBUF_IN) { /* IN double buffered endpoint */
		_ToggleDTOG_RX(bEpNum);
	}
}

/*******************************************************************************
* Function Name  : ToWord
* Description    : merge two byte in a word.
* Input          : bh: byte high, bl: bytes low.
* Output         : None.
* Return         : resulted word.
*******************************************************************************/
unsigned short int ToWord(unsigned char bh, unsigned char bl)
{
	unsigned short int wRet;
	wRet = (unsigned short int)bl | ((unsigned short int)bh << 8);
	return(wRet);
}
/*******************************************************************************
* Function Name  : ByteSwap
* Description    : Swap two byte in a word.
* Input          : wSwW: word to Swap.
* Output         : None.
* Return         : resulted word.
*******************************************************************************/
unsigned short int ByteSwap(unsigned short int wSwW)
{
	unsigned char bTemp;
	unsigned short int wRet;
	bTemp = (unsigned char)(wSwW & 0xff);
	wRet = (wSwW >> 8) | ((unsigned short int)bTemp << 8);
	return(wRet);
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
