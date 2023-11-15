#include "cdef.h"
#pragma once

#define a_size	(20)
#define p_size (a_size+1/*len*/+2/*crc*/)
#define c_size (p_size+1/*seed*/+1/*key*/)
#define h_size (c_size*2)
#define b_size (h_size*3+2/*start&sync*/)

/* tx stuff */
extern char a_buffer[a_size];
extern char p_buffer[p_size];
extern char c_buffer[c_size];
extern char h_buffer[h_size];
extern char b_buffer[b_size];

extern u8 seed;
extern u8 key;
extern u8 rrr;

extern u8 ook_dec_b1error;
extern u8 ook_dec_b2error;


void ook_a_SendData(char *i,u8 len);
 void ook__p_MakeCont(char *i,u8 len);
 void ook__c_EncrypData(char *i,u8 len);
 void ook__h_EncodeData(char *i,u8 len);
 void ook__b_SerializeData(char *i,u8 len);

/* rx stuff */

 extern char ra_buffer[a_size];
extern char rp_buffer[p_size];
extern char rc_buffer[c_size];
extern char rh_buffer[h_size];
extern char rb_buffer[b_size];

extern char rxlen;


extern u8 dec_key;
extern u8 dec_seed;

u8 ook_a_GetData();
u8 ook__rc_Decrypt();
void ook__rh_HammingDecode();
void ook__rb_BitDecode();