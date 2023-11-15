/*
 * FILE						: httputil.c
 * DESCRIPTION		: This file is iCore3 files.
 * Author					: ysloveivy
 * Copyright			:
 *
 * History
 * --------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * --------------------
 */
 
//------------------------- Include -----------------------//
#include "..\fwlib\inc\stm32f4xx_gpio.h"

#include "..\include\main.h"
#include "..\include\httputil.h"
#include "..\include\socket.h"
#include "..\include\w5500.h"
#include "..\include\httpd.h"
#include "..\include\util.h"
#include "..\include\webpage.h"
#include "..\include\adc.h"


#include "..\include\led.h"

//------------------------- Define ------------------------//
#define SOCK_HTTP   0  

//------------------------ Variable -----------------------//
extern char tx_buf[MAX_URI_SIZE];
extern char rx_buf[MAX_URI_SIZE];
unsigned char boundary[64];

//------------------- Function Prototype ------------------//
static void make_measure_response(char* response_buf);

//------------------------ Function -----------------------//
/*
 * Name						: do_http
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void do_http(void)
{
  uint8 ch = SOCK_HTTP;
  uint16 len;

  st_http_request *http_request;
  memset(rx_buf,0x00,MAX_URI_SIZE);
  http_request = (st_http_request*)rx_buf;		           // struct of http request  
	
	//´¦Àíhttp
  switch(getSn_SR(ch))
  {
    case SOCK_INIT:
      listen(ch);
      break;
    case SOCK_LISTEN:
      break;
    case SOCK_ESTABLISHED:
					
      if(getSn_IR(ch) & Sn_IR_CON)
      {
        setSn_IR(ch, Sn_IR_CON);
      }
      if ((len = getSn_RX_RSR(ch)) > 0)		
      {
				if(len > 1460)len = 1460;
        len = recv(ch, (unsigned char*)http_request, len); 
        *(((unsigned char*)http_request)+len) = 0;
        proc_http(ch, (unsigned char*)http_request);     // request is processed
        disconnect(ch);
      }

      break;
    case SOCK_CLOSE_WAIT:   
      if ((len = getSn_RX_RSR(ch)) > 0)
      {
        len = recv(ch, (unsigned char*)http_request, len);       
        *(((unsigned char*)http_request)+len) = 0;
        proc_http(ch, (unsigned char*)http_request);    // request is processed
      }
      disconnect(ch);
      break;
    case SOCK_CLOSED:                   
      socket(ch, Sn_MR_TCP, 80, 0x00);                  /* reinitialize the socket */
      break;
    default:
    break;
  }// end of switch
}
/*
 * Name						: proc_http
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void proc_http(SOCKET s, uint8 * buf)
{
  char* name;                                        //get method request file name
	char req_name[32]={0x00,};                         //post method request file name
	unsigned long int file_len = 0;
	unsigned short int send_len = 0;
  unsigned char* http_response;
  st_http_request *http_request;
  memset(tx_buf,0x00,MAX_URI_SIZE);
  http_response = (unsigned char*)rx_buf;
  http_request = (st_http_request*)tx_buf;
  parse_http_request(http_request, buf);             // After analyze request, convert into http_request
	
  //method Analyze
  switch (http_request->METHOD)		
  {
    case METHOD_ERR :
			memcpy(http_response, ERROR_REQUEST_PAGE, sizeof(ERROR_REQUEST_PAGE));
			send(s, (unsigned char *)http_response, strlen((char const*)http_response));
      break;
    case METHOD_HEAD:
    case METHOD_GET:
      //get file name from uri
      name = http_request->URI;
			if(strcmp(name,"/index.htm")==0 || strcmp(name,"/")==0 || (strcmp(name,"/index.html")==0))
			{
				file_len = strlen(ALLOCATION_HTML);
				make_http_response_head((uint8*)http_response, PTYPE_HTML,file_len);
				send(s,http_response,strlen((char const*)http_response));
				send_len=0;
				while(file_len)
				{
					if(file_len>1024)
					{
						if(getSn_SR(s)!=SOCK_ESTABLISHED)
						{
							return;
						}
						send(s, (uint8 *)ALLOCATION_HTML+send_len, 1024);
						send_len+=1024;
						file_len-=1024;
					}
					else
					{
						send(s, (uint8 *)ALLOCATION_HTML+send_len, file_len);
						send_len+=file_len;
						file_len-=file_len;
					} 
				}
			}else if(strcmp(name,"/demo_get.asp") == 0){
						make_measure_response(tx_buf);
						sprintf((char *)http_response,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:%d\r\n\r\n%s",strlen(tx_buf),tx_buf);
						send(s, (u_char *)http_response, strlen((char *)http_response));	
			}
      break;
      /*POST method*/
    case METHOD_POST:
		LED_BLUE_ON;
		break;

      //get file name from uri
		
    default :
      break;
  }
}
/*
 * Name						: make_measure_response
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void make_measure_response(char* response_buf)
{
	sprintf(response_buf,
	"<table border='1' width='auto'>\
	<tr><th>[V]</th><th>%4.3fV</th></tr>\
	<tr><th>[I]</th><th>%4.3fA</th></tr>\
	<tr><th>[1.2V]</th><th>%4.3fV</th></tr>\
	<tr><th>[3.3V]</th><th>%4.3fV</th></tr>\
	<tr><th>[2.5V]</th><th>%4.3fV</th></tr>\
	</table>",adc.value[0] * 6,adc.value[1] / 2,adc.value[2],adc.value[3] * 2,adc.value[4] * 2);
}
