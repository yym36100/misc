#ifndef __USB_COMMAND_H__
#define __USB_COMMAND_H__

/**********************发送命令****************************/
//擦除FLASH
#define COMMAND_FLASH_ERASE_SEND	  		0xff	   
#define COMMAND_FLASH_ERASE_OK_SEND	  		0xfe	   
//烧写FLASH
#define COMMAND_FLASH_WRITE_SEND            0xfd
#define COMMAND_FLASH_WRITE_CONTINUE_SEND   0xfc
#define COMMAND_FLASH_WRITE_END_SEND        0xfb
//字库校验
#define COMMAND_FLASH_CHECK_SEND 	   		0xfa
//截图
#define COMMAND_PICTURE_LOAD_SEND  			0xf9   
//显示图片
#define COMMAND_PICTURE_WRITE_SEND			0xf8
#define COMMAND_PICTURE_WRITE_CONTINUE_SEND	0xf7
#define COMMAND_PICTURE_WRITE_END_SEND	    0xf6
//用户自定义命令
#define COMMAND_USER_CUSTOM_SEND   			0xf5
#define COMMAND_USER_CUSTOM_OK_SEND  		0xf4




/**********************接收命令****************************/
//擦除FLASH
#define COMMAND_FLASH_ERASE_RECEIVE	  		0xff	  
//烧写FLASH
#define COMMAND_FLASH_WRITE_RECEIVE	  		0xfe	   
#define COMMAND_FLASH_WRITE_START_RECEIVE	0xfd	   
#define COMMAND_FLASH_WRITE_DATA_RECEIVE 	0xfc
//字库校验
#define COMMAND_FLASH_CHECK_RECEIVE 		0xfb
#define COMMAND_FLASH_CHECK_START_RECEIVE   0xfa
#define COMMAND_FLASH_CHECK_CAN_RECEIVE 	0xf9
//截图
#define COMMAND_PICTURE_LOAD_RECEIVE        0xf8	  
#define COMMAND_PICTURE_LOAD_START_RECEIVE	0xf7
#define COMMAND_PICTURE_LOAD_CAN_RECEIVE	0xf6	      	  
//显示图片 
#define COMMAND_PICTURE_WRITE_RECEIVE		0xf5
#define COMMAND_PICTURE_WRITE_START_RECEIVE	0xf4
#define COMMAND_PICTURE_WRITE_DATA_RECEIVE	0xf3
//用户自定义命令
#define COMMAND_USER_CUSTOM_RECEIVE         0xf2


typedef struct{
	union{
		struct{//FLASH烧写
			unsigned char sector;			   //1：烧写扇区号
			unsigned char bytes_32_count;      //1: 32字节计数，8次清一次0 
			unsigned long int bytes_256_count; //4：256字节计数
			unsigned char buf[256];		   	   //256：256字节页烧写
	//		unsigned char reserve[762];		   //762：保留字节
		}flash_write;

		struct{//FLASH校验
			unsigned char sector;			   //1：烧写扇区号
			unsigned long int bags_count;	   //4：数据包计数
			unsigned long int bags_num_total;  //4：总数据包数
			unsigned char bag_end_flag;		   //1：包结束标志	
			unsigned char buf[58];		   	   //58：含32字节校验数据
	//		unsigned char reserve[956];		   //956：保留字节
		}flash_read;

		struct{//截图
			unsigned short int point_x_count;  //2: x点坐标
			unsigned short int point_y_count;  //2: y点坐标
			unsigned short int bags_count;	   //2:	数据包计数
			unsigned char bag_end_flag;		   //1:	包结束标志
			unsigned char buf[60];			   //60: 预装30点数据缓冲区
	//		unsigned char reserve[957];	   	   //957：保留字节
		}picture_send;

		struct{//接收图片
			unsigned short int line_y_count;   //2: y行计数
			unsigned short int bags_count;	   //2：数据包计数
			unsigned char line_buf[960];	   //960：行数据缓存区
	//	    unsigned char reserve[60];	   	   //60：保留字节
		}picture_receive;
		
		unsigned char buf[1024];			   //hid数据传输分配1024字节内存
	}hid;

	unsigned char receive_buffer[64];		  //HID接收缓冲区

	int (* send)(unsigned char/*parent_command*/,unsigned char/*child_command*/);
	int (* send_check_data)(unsigned char    /*command_parent*/,
							unsigned char    /*bag_end_flag*/,
							unsigned long int/*bags_num*/,
							unsigned char*   /*send_buffer*/);
    unsigned char* (* get_picture_30_points)(int x/*point_x_count*/,int y/*point_y_count*/);
	int (*set_picture_line_points)(int y/*line_y_count*/,unsigned short int * /*color_data*/);
	int (*send_picture_data)(unsigned char   /*command_parent*/,	      //1字节命令
							 unsigned char   /*bag_end_flag*/,			  //1字节发送完毕标志位
							 unsigned short  /*int bags_num*/,	  		  //2字节自定义							 
							 unsigned char * /*send_buffer*/);			  //60字节数据	
	void (* capture_handle)(void);

	int capture_flag;
}USB_COMMANDT_T;
	

extern USB_COMMANDT_T usb_command;

#endif //__USB_COMMAND_H__
