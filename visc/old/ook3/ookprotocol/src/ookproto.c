#include "cdef.h"
#include "ookproto.h"


/*

layers:

1. Application - get data to be sent from the application
2. Presentation - put the data in a container format len + data + crc
3. Crypt - encrypt data (add another byte whith encryption info/seed)
4. Hamming coding (8,4)
5. Bit coding
*/

/* encoder, TX side ---------------------------------------------------------- */

char a_buffer[a_size];
char p_buffer[p_size];
char c_buffer[c_size];
char h_buffer[h_size];
char b_buffer[b_size];


u8 seed=0;
u8 key=0;
u8 rrr;

static u16 ook_crc16(u16 crc, u8 a);

static u8 ook_prbs_seed = 0x05d;
u8 ook_prbs7();
u8 ook_hammingcode(u8 nib);
u8 getparity(u8 data, u8 mask);

void ook_a_SendData(char *i,u8 len)
{
	if(len<a_size)
	{
		memcpy(a_buffer,i,len);
		//ook__p_MakeCont(a_buffer,len);
	}
}

#define ook_init_crc_val	(0x5d5d)
 void ook__p_MakeCont(char *i,u8 len)
{
	u8 j;
	u16 crc = ook_init_crc_val;
	p_buffer[0] = len;
	//memcpy(p_buffer+1,i,len);
	//todo why not crc covers also the length of the data (first byte)
	for(j = 0;j<len;j++)
	{
		(p_buffer+1)[j] = i[j];
		crc = ook_crc16(crc,i[j]);
	}

	p_buffer[len+1] = (crc>>8)&0xff;
	p_buffer[len+2] = (crc>>0)&0xff;
//	ook__c_EncrypData(p_buffer,len+3);
}

#define xorkey	0x5c
 void ook__c_EncrypData(char *i,u8 len)
{
	u8 j;
	u8 prev,prev2;
	
	
	//encryption	
	//seed++;
	///rrr =rand();
	key = i[len-2]^rrr;
	ook_prbs_seed = seed^xorkey^key;
	//key = ook_prbs7();
	


	c_buffer[0] = seed^xorkey^key;
	c_buffer[1] = key^xorkey;

	prev = 0x5d;
	prev2 = 0xf9;
	for(j = 0;j<len;j++)
	{
		(c_buffer+2)[j] = (i[j]^xorkey)^ook_prbs7();		
	}
//	ook__h_EncodeData(c_buffer,len+2);
}

 void ook__h_EncodeData(char *i,u8 len)
{
	//x2 size increese here use hamming 4,8 encoding
	// dummy for now just dupplicate nibbles
	u8 j;
	/*for(j=0;j<len;j++)
	{
		h_buffer[j*2+1]= (i[j]&0x0f) | ((i[j]&0x0f)<<4);
		h_buffer[j*2+0]= (i[j]&0xf0) | ((i[j]&0xf0)>>4);
	}*/
	for(j=0;j<len;j++)
	{
		h_buffer[j*2+0] = ook_hammingcode((i[j]&0xf0)>>4);
		h_buffer[j*2+1] = ook_hammingcode(i[j]&0x0f);
	}
	//ook__b_SerializeData(h_buffer,len*2);
}

 void ook__b_SerializeData(char *i,u8 len)
 {
	 //encode bits
	 //start = 1110, 1 = 110, 0 = 100
	 u8 j,b;
	 b_buffer[0] = 0x15;
	 b_buffer[1] = 0x4e;
	 for(j = 0;j<len;j++)
	 {
		 // for each byte will result 3 bytes
		 u32 buffer =0;
		 for(b=0;b<8;b++)
		 {
			 if((i[j]&(1<<(7-b)))!=0)
			 {
				 //encode 1
				 buffer = (buffer<<3) | 0x06;
			 }
			 else
			 {
				 //encode 0
				 buffer = (buffer<<3) | 0x04;
			 }
		 }
		 (b_buffer+2)[j*3+0]=(buffer>>16)&0xff;
		 (b_buffer+2)[j*3+1]=(buffer>>8)&0xff;;
		 (b_buffer+2)[j*3+2]=(buffer>>0)&0xff;;
	 }

 }

static u16 ook_crc16(u16 crc, u8 a)
    {
        u8 i;
        crc ^= a;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA048;
            else
                crc = (crc >> 1);
        }
        return crc;
    }

u8 ook_prbs7()
{    	 
	u8 a = ook_prbs_seed;
	u8 newbit = (((a >> 7) ^ (a >> 5)^ (a >> 4)^ (a >> 3)) & 1); //prbs7	
	ook_prbs_seed = ((a << 1) | newbit) & 0xff;
	return a;
}

u8 ook_hammingcode(u8 nib)
{
	//todo this can be optimized by a simple lookup table
	u8 tmp;
	u8 p0,p1,p2,p3,p4;
	tmp = ((nib>>3)<<4)|(nib&0x7);
	p3 = getparity(tmp,0xf);
	tmp |=p3<<3;
	p2 = getparity(tmp,0x33);
	tmp |= p2<<5;
	p1 = getparity(tmp,0x55);
	tmp |= p1<<6;
	tmp<<=1;
	p0 = getparity(tmp,0xfe);
	tmp|=p0;
	
	return tmp;
}
u8 getparity(u8 data, u8 mask)
{
	u8 i;
	u8 nr1 =0;
	for(i=0;i<8;i++)
	{
		if((((data&mask)>>i)&1)!=0) nr1++;
	}
	return nr1&1;
}

/* decoder, RX side ---------------------------------------------------------- */

char ra_buffer[a_size];
char rp_buffer[p_size];
char rc_buffer[c_size];
char rh_buffer[h_size];
char rb_buffer[b_size];
char rxlen=0;

//u8 ook_a_GetData();
//void ook__rc_Decrypt();
//void ook__rh_HammingDecode();
//void ook__rb_BitDecode();

enum rxcodes{rx_ok=0, rx_crcerror,rx_seedlockedout};

u8 ook_a_GetData()
{
	u8 res =rx_ok;
	u8 i;	
	u16 crc = ook_init_crc_val;
	u16 reccrc;
	rxlen-=2;
	for(i=1;i<rxlen;i++)
	{		
		crc = ook_crc16(crc,rp_buffer[i]);
	}
	//todo veryfy, compare crc
	reccrc = (((u8)rp_buffer[rxlen+0])<<8)| ((u8)rp_buffer[rxlen+1]);
	if(crc!=reccrc) res = rx_crcerror;

	for(i=1;i<rxlen;i++)
	{		
		ra_buffer[i-1]=rp_buffer[i];
	}
	return res;
}

u8 dec_key;
u8 dec_seed;
u8 last_seed =0xff;
#define max_seed_distance (20)
u8 ook__rc_Decrypt()
{
	u8 res=rx_ok;
	u8 seed,key,i;
	memset (rp_buffer,0,p_size);

	key = rc_buffer[1]^xorkey;
	seed = rc_buffer[0]^xorkey^key;

	dec_key = key;
	dec_seed = seed;

	//seed validation
	if(last_seed<255-max_seed_distance)
	{
		//last seed = 0 - 255-lim
		if(dec_seed<=last_seed)
		{
			res = rx_seedlockedout;
		}
	}
	else
	{
		// last seed  = 255-lim  - 255
		if((dec_seed<=last_seed) ||( (dec_seed>(255-max_seed_distance*2))&& (dec_seed<(255-max_seed_distance)) ) )
		{
			res = rx_seedlockedout;
		}

	}

	

	last_seed = dec_seed;


	ook_prbs_seed = seed^xorkey^key;
	//(void)ook_prbs7();

	rxlen-=2;
	for(i=0;i<rxlen;i++)
	{
		(rp_buffer)[i] = ((rc_buffer+2)[i]^xorkey)^ook_prbs7();
	}
	return res;
}

u8 ook__rh_hammingcorrect(u8 b);

u8 ook_checkbits(u8 b);
u8 ook_checkbits(u8 b)
{
	u8 p1,p2,p4,p0;

	p0=b^(b>>1);
	p0 ^= p0>>2;
	p0 ^= p0>>4;

	p1 = b^(b>>2);
	p1^= p1>>4;

	p2 = b^(b>>1);
	p2^= p2>>4;

	p4 = b^(b>>1);
	p4^= p4>>2;

	return ((p1>>1)&1) | ((p2>>0)&2) | ((p4<<1)&4) | ((p0<<7)&0x80);
}
u8 ook_dec_b1error;
u8 ook_dec_b2error;
u8 ook__rh_hammingcorrect(u8 b)
{
	u8 r;

	r = ook_checkbits(b);
	if(r!=0)
	{
//		errors++;//correct code
		if(r==0x80)
		{
			//single bit p0 error, no correction needed
			ook_dec_b1error++;
		}
		else if(r&0x80)
		{
			//correct single bit errors
			b^=1<<(8-(r&0xf));
			ook_dec_b1error++;
		}
		else
		{
			//double bit error
			ook_dec_b2error++;
		}
	}
	b>>=1;
	return (((b>>4)&1)<<3)| b&0x7;
}

void ook__rh_HammingDecode()
{
	u8 i;
	u8 dh1,dh2;
	memset (rc_buffer,0,c_size);
	for(i=0;i<rxlen;i+=2)
	{
		dh1 = ook__rh_hammingcorrect(rh_buffer[i]);
		dh2 = ook__rh_hammingcorrect(rh_buffer[i+1]);
		rc_buffer[i/2] = (dh1<<4) | dh2;
	}
	rxlen/=2;
}

void ook__rb_BitDecode()
{
	u8 i,j;
	u8 bc=0,bp1=0,bp2=0,bb;
	enum st{head=0,start};
	u8 state = head;
	u8 di=0,dj=0;
	u8 skip = 2;
	memset (rh_buffer,0,h_size);
	rxlen = 0;
	//todo optimized bzise buffer can be half full
	
	for(i=0;i<b_size;i++)
	{
		//get byte
		for(j=0;j<8;j++)
		{
			//get bit
			if( (rb_buffer[i]>>(7-j))&1 )
			{
				//1
				bc = 1;
			}
			else
			{
				//0
				bc = 0;
			}
			if(skip>0)skip--;
			if( skip == 0 )
			{
				//evaluate bit state
				bb=2;
				if( (bc == 1)&&(bp1 == 1)&&(bp2 == 1))
				{
					//start bit
					state = start;					
					skip = 4;
					//rxlen = 1;
				}
				else if ( (bc == 0)&&(bp1 == 1)&&(bp2 == 1))
				{
					bb = 1;					
				}
				else if ( (bc == 0)&&(bp1 == 0)&&(bp2 == 1))
				{
					bb = 0;					
				}
				else if ( (bc == 0)&&(bp1 == 0)&&(bp2 == 0))
				{
					state = head;
				}

				if (state ==head)
				{
					//nothing to do skip bit
				}
				else if(state = start)
				{
					//encode bit
					if(bb<=1)
					{
						skip = 3;
						rh_buffer[di] |= (bb<<(7-dj));
						if(dj==7)
						{
							dj = 0;
							di++;
							rxlen++;
						}
						else
						{
							dj++;
						}
					}
				}
				
			}
			bp2 = bp1;
			bp1 = bc;
		}

	}
}
