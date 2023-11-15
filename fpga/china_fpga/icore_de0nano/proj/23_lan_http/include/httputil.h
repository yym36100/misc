#ifndef	__HTTPUTIL_H__
#define	__HTTPUTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\include\types.h"
#include "..\include\httpd.h"


void proc_http(SOCKET s, u_char * buf);
void do_http(void);
void cgi_ipconfig(st_http_request *http_request);

#endif
