
#include <stdio.h>
#include <string.h>
#include "ip_arp_udp_tcp.h"
#include "enc28j60.h"
#include "net.h"

#define PSTR(s) s
extern void delay_ms(unsigned char ms);
extern char LAN_info[];

// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:
static uint8_t mymac[6] = {0x54,0x55,0x58,0x10,0x00,0x24};
// how did I get the mac addr? Translate the first 3 numbers into ascii is: TUX
static uint8_t myip[4] = {192,168,0,6};
// listen port for tcp/www (max range 1-254)
#define MYWWWPORT 80
//
// listen port for udp
#define MYUDPPORT 1200

#define BUFFER_SIZE 1500//450
static uint8_t buf[BUFFER_SIZE+1];

// the password string (only the first 5 char checked), (only a-z,0-9,_ characters):
static char password[]="12345678"; // must not be longer than 9 char

// 
uint8_t verify_password(char *str)
{
        // the first characters of the received string are
        // a simple password/cookie:
        if (strncmp(password,str,5)==0){
                return(1);
        }
        return(0);
}

// takes a string of the form password/commandNumber and analyse it
// return values: -1 invalid password, otherwise command number
//                -2 no command given but password valid
//                -3 valid password, no command and no trailing "/"
int8_t analyse_get_url(char *str)
{
        uint8_t loop=1;
        uint8_t i=0;
        while(loop){
                if(password[i]){
                        if(*str==password[i]){
                                str++;
                                i++;
                        }else{
                                return(-1);
                        }
                }else{
                        // end of password
                        loop=0;
                }
        }
        // is is now one char after the password
        if (*str == '/'){
                str++;
        }else{
                return(-3);
        }
        // check the first char, garbage after this is ignored (including a slash)
        if (*str < 0x3a && *str > 0x2f){
                // is a ASCII number, return it
                return(*str-0x30);
        }
        return(-2);
}

// answer HTTP/1.0 301 Moved Permanently\r\nLocation: password/\r\n\r\n
// to redirect to the url ending in a slash
uint16_t moved_perm(uint8_t *buf)
{
        uint16_t plen;
        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 301 Moved Permanently\r\nLocation: "));
        plen=fill_tcp_data(buf,plen,password);
        plen=fill_tcp_data_p(buf,plen,PSTR("/\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<h1>301 Moved Permanently</h1>\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("add a trailing slash to the url\n"));
        return(plen);
}


// prepare the webpage by writing the data to the tcp send buffer
uint16_t print_webpage(uint8_t *buf,uint8_t on_off)
{
        uint16_t plen;
        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<center><p>Output is: "));
        if (on_off){
                plen=fill_tcp_data_p(buf,plen,PSTR("<font color=\"#00FF00\"> ON</font>"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("OFF"));
        }
        plen=fill_tcp_data_p(buf,plen,PSTR(" <small><a href=\".\">[refresh status]</a></small></p>\n<p><a href=\"."));
        if (on_off){
                plen=fill_tcp_data_p(buf,plen,PSTR("/0\">Switch off</a><p>"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("/1\">Switch on</a><p>"));
        }
        plen=fill_tcp_data_p(buf,plen,PSTR("</center><hr><br>Ver 1.0, ��ӭʹ�ú�о����FPGA������\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("</center><hr><br>http://shop57125352.taobao.com\n"));
		return(plen);
}

int WebServer_main(void){
        uint16_t plen;
        uint16_t dat_p;
        uint8_t i=0;
        uint8_t cmd_pos=0;
        int8_t cmd;
        uint8_t payloadlen=0;
        char str[30];
        char cmdval;
        

        // set the clock speed to "no pre-scaler" (8MHz with internal osc or 
        // full external speed)
        // set the clock prescaler. First write CLKPCE to enable setting of clock the
        // next four instructions.
        //CLKPR=(1<<CLKPCE); // change enable
        //CLKPR=0; // "no pre-scaler"
        //delay_ms(200);
		printf("A simple Web Server\r\n");

        /* enable PD2/INT0, as input */
        //DDRD&= ~(1<<DDD2);

        /*initialize enc28j60*/
        enc28j60Init(mymac);
        enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
        delay_ms(10);
        
        // LED
        /* enable PB1, LED as output */
        //DDRB|= (1<<DDB1);
		///IODIR |= LED;	//xsyan mask	   //����IO��Ϊ����� 

        /* set output to Vcc, LED off */
        //PORTB|= (1<<PB1);
		printf("LED = 1\r\n");//IOSET = LED;		//xsyan mask
		/*
        // the transistor on PD7
        DDRD|= (1<<DDD7);
        PORTD &= ~(1<<PD7);// transistor off
        */
        /* Magjack leds configuration, see enc28j60 datasheet, page 11 */
        // LEDB=yellow LEDA=green
        //
        // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
        // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
        //enc28j60PhyWrite(PHLCON,0x476);
        enc28j60PhyWrite(PHLCON,0xD76);	//0x476	  
        delay_ms(20);
        
        /* set output to GND, red LED on */
        //PORTB &= ~(1<<PB1);
		printf("LED = 0\r\n");//IOCLR = LED; //xsyan mask
        i=1;

        //init the ethernet/ip layer:
        init_ip_arp_udp_tcp(mymac,myip,MYWWWPORT);
		
		sprintf( str, "Chip rev: 0x%x \r\n",enc28j60getrev());
		printf( str );

        while(1)
		{
                // get the next new packet:
                plen = enc28j60PacketReceive(BUFFER_SIZE, buf);

				//printf( "enc28j60PacketReceive,plen = %d\r\n",plen);

                /*plen will ne unequal to zero if there is a valid 
                 * packet (without crc error) */
                if(plen==0){
						//printStr( "no data\n" );
						OSTimeDlyHMSM(0, 0, 0, 2);
                        continue;
                }
				printf( "Get it\r\n" );
				memset(LAN_info,0x0,28);
				sprintf(LAN_info,"Get data from pc by Ethernet.");
                        
                // arp is broadcast if unknown but a host may also
                // verify the mac address by sending it to 
                // a unicast address.
                if(eth_type_is_arp_and_my_ip(buf,plen)){
                        make_arp_answer_from_request(buf);
						//printStr( "make_arp_answer_from_request\n" );
						OSTimeDlyHMSM(0, 0, 0, 2);
                        continue;
                }

                // check if ip packets are for us:
                if(eth_type_is_ip_and_my_ip(buf,plen)==0){
						OSTimeDlyHMSM(0, 0, 0, 2);
                        continue;
                }
                // led----------
                if (i){
                        /* set output to Vcc, LED off */
						printf("LED = 1\r\n");//IOSET = LED;//xsyan mask
                        //PORTB|= (1<<PB1);
                        i=0;
                }else{
                        /* set output to GND, LED on */
                        //PORTB &= ~(1<<PB1);
						printf("LED = 0\r\n");//IOCLR = LED;//xsyan mask
                        i=1;
                }
                
                if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
                        // a ping packet, let's send pong
                        make_echo_reply_from_request(buf,plen);
						//printStr( "make_echo_reply_from_request\n" );
						OSTimeDlyHMSM(0, 0, 0, 2);
                        continue;
                }
                // tcp port www start, compare only the lower byte
                if (buf[IP_PROTO_P]==IP_PROTO_TCP_V&&buf[TCP_DST_PORT_H_P]==0&&buf[TCP_DST_PORT_L_P]==MYWWWPORT)
				{
                        if (buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V){
                                make_tcp_synack_from_syn(buf);
                                // make_tcp_synack_from_syn does already send the syn,ack
                                OSTimeDlyHMSM(0, 0, 0, 2);
                                continue;
                        }
                        if (buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V){
                                init_len_info(buf); // init some data structures
                                // we can possibly have no data, just ack:
                                dat_p=get_tcp_data_pointer();
                                if (dat_p==0){
                                        if (buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V){
                                                // finack, answer with ack
                                                make_tcp_ack_from_any(buf);
                                        }
                                        // just an ack with no data, wait for next packet
                                        OSTimeDlyHMSM(0, 0, 0, 2);
                                        continue;
                                }
                                if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
                                        // head, post and other methods:
                                        //
                                        // for possible status codes see:
                                        // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
                                        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>200 OK</h1>"));
                                        goto SENDTCP;
                                }
                                if (strncmp("/ ",(char *)&(buf[dat_p+4]),2)==0){
                                        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"));
                                        plen=fill_tcp_data_p(buf,plen,PSTR("<p>RedCore RCQ208_V3 FPGA ������ �������壡</p>\n"));
                                        goto SENDTCP;
                                }
                                cmd=analyse_get_url((char *)&(buf[dat_p+5]));
                                // for possible status codes see:
                                // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
                                if (cmd==-1){
                                        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
                                        goto SENDTCP;
                                }
                                if (cmd==1){
                                        //PORTD|= (1<<PD7);// transistor on
										printf("LED2 = 0\r\n");//IOCLR = LED;//xsyan mask
										i = 1;
                                }
                                if (cmd==0){
                                        //PORTD &= ~(1<<PD7);// transistor off
										printf("LED2 = 1\r\n");//IOSET = LED;//xsyan mask
										i = 0;
                                }
                                if (cmd==-3){
                                        // redirect to add a trailing slash
                                        plen=moved_perm(buf);
                                        goto SENDTCP;
                                }
                                // if (cmd==-2) or any other value
                                // just display the status:
                                //plen=print_webpage(buf,(PORTD & (1<<PD7)));
								plen=print_webpage(buf,(i));
                                //
SENDTCP:
                                make_tcp_ack_from_any(buf); // send ack for http get
                                make_tcp_ack_with_data(buf,plen); // send data
                                OSTimeDlyHMSM(0, 0, 0, 2);
                                continue;
                        }

                }
                // tcp port www end
                //
                // udp start, we listen on udp port 1200=0x4B0
                if (buf[IP_PROTO_P]==IP_PROTO_UDP_V&&buf[UDP_DST_PORT_H_P]==4&&buf[UDP_DST_PORT_L_P]==0xb0)
				{
                        payloadlen=buf[UDP_LEN_L_P]-UDP_HEADER_LEN;
                        // you must sent a string starting with v
                        // e.g udpcom version 10.0.0.24
                        if (verify_password((char *)&(buf[UDP_DATA_P]))){
                                // find the first comma which indicates 
                                // the start of a command:
                                cmd_pos=0;
                                while(cmd_pos<payloadlen){
                                        cmd_pos++;
                                        if (buf[UDP_DATA_P+cmd_pos]==','){
                                                cmd_pos++; // put on start of cmd
                                                break;
                                        }
                                }
                                // a command is one char and a value. At
                                // least 3 characters long. It has an '=' on
                                // position 2:
                                if (cmd_pos<2 || cmd_pos>payloadlen-3 || buf[UDP_DATA_P+cmd_pos+1]!='='){
                                        strcpy(str,"e=no_cmd");
                                        goto ANSWER;
                                }
                                // supported commands are
                                // t=1 t=0 t=?
                                if (buf[UDP_DATA_P+cmd_pos]=='t'){
                                        cmdval=buf[UDP_DATA_P+cmd_pos+2];
                                        if(cmdval=='1'){
                                                //PORTD|= (1<<PD7);// transistor on
												printf("LED = 0\r\n");//IOCLR = LED;//xsyan mask
                                                strcpy(str,"t=1");
                                                goto ANSWER;
                                        }else if(cmdval=='0'){
                                                //PORTD &= ~(1<<PD7);// transistor off
												printf("LED = 1\r\n");//IOSET = LED;//xsyan mask
                                                strcpy(str,"t=0");
                                                goto ANSWER;
                                        }else if(cmdval=='?'){
                                                //if (PORTD & (1<<PD7)){
												if (1/*IOPIN & LED*/){//xsyan mask
                                                        strcpy(str,"t=1");
                                                        goto ANSWER;
                                                }
                                                strcpy(str,"t=0");
                                                goto ANSWER;
                                        }
                                }
                                strcpy(str,"e=no_such_cmd");
                                goto ANSWER;
                        }
                        strcpy(str,"e=invalid_pw");
ANSWER:
                        make_udp_reply_from_request(buf,str,strlen(str),MYUDPPORT);
						OSTimeDlyHMSM(0, 0, 0, 2);
                }
        }
        return (0);
}
