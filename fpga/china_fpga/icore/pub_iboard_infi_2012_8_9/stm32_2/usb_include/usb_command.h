#ifndef __USB_COMMAND_H__
#define __USB_COMMAND_H__

/**********************��������****************************/
//����FLASH
#define COMMAND_FLASH_ERASE_SEND	  		0xff	   
#define COMMAND_FLASH_ERASE_OK_SEND	  		0xfe	   
//��дFLASH
#define COMMAND_FLASH_WRITE_SEND            0xfd
#define COMMAND_FLASH_WRITE_CONTINUE_SEND   0xfc
#define COMMAND_FLASH_WRITE_END_SEND        0xfb
//�ֿ�У��
#define COMMAND_FLASH_CHECK_SEND 	   		0xfa
//��ͼ
#define COMMAND_PICTURE_LOAD_SEND  			0xf9   
//��ʾͼƬ
#define COMMAND_PICTURE_WRITE_SEND			0xf8
#define COMMAND_PICTURE_WRITE_CONTINUE_SEND	0xf7
#define COMMAND_PICTURE_WRITE_END_SEND	    0xf6
//�û��Զ�������
#define COMMAND_USER_CUSTOM_SEND   			0xf5
#define COMMAND_USER_CUSTOM_OK_SEND  		0xf4




/**********************��������****************************/
//����FLASH
#define COMMAND_FLASH_ERASE_RECEIVE	  		0xff	  
//��дFLASH
#define COMMAND_FLASH_WRITE_RECEIVE	  		0xfe	   
#define COMMAND_FLASH_WRITE_START_RECEIVE	0xfd	   
#define COMMAND_FLASH_WRITE_DATA_RECEIVE 	0xfc
//�ֿ�У��
#define COMMAND_FLASH_CHECK_RECEIVE 		0xfb
#define COMMAND_FLASH_CHECK_START_RECEIVE   0xfa
#define COMMAND_FLASH_CHECK_CAN_RECEIVE 	0xf9
//��ͼ
#define COMMAND_PICTURE_LOAD_RECEIVE        0xf8	  
#define COMMAND_PICTURE_LOAD_START_RECEIVE	0xf7
#define COMMAND_PICTURE_LOAD_CAN_RECEIVE	0xf6	      	  
//��ʾͼƬ 
#define COMMAND_PICTURE_WRITE_RECEIVE		0xf5
#define COMMAND_PICTURE_WRITE_START_RECEIVE	0xf4
#define COMMAND_PICTURE_WRITE_DATA_RECEIVE	0xf3
//�û��Զ�������
#define COMMAND_USER_CUSTOM_RECEIVE         0xf2


typedef struct{
	union{
		struct{//FLASH��д
			unsigned char sector;			   //1����д������
			unsigned char bytes_32_count;      //1: 32�ֽڼ�����8����һ��0 
			unsigned long int bytes_256_count; //4��256�ֽڼ���
			unsigned char buf[256];		   	   //256��256�ֽ�ҳ��д
	//		unsigned char reserve[762];		   //762�������ֽ�
		}flash_write;

		struct{//FLASHУ��
			unsigned char sector;			   //1����д������
			unsigned long int bags_count;	   //4�����ݰ�����
			unsigned long int bags_num_total;  //4�������ݰ���
			unsigned char bag_end_flag;		   //1����������־	
			unsigned char buf[58];		   	   //58����32�ֽ�У������
	//		unsigned char reserve[956];		   //956�������ֽ�
		}flash_read;

		struct{//��ͼ
			unsigned short int point_x_count;  //2: x������
			unsigned short int point_y_count;  //2: y������
			unsigned short int bags_count;	   //2:	���ݰ�����
			unsigned char bag_end_flag;		   //1:	��������־
			unsigned char buf[60];			   //60: Ԥװ30�����ݻ�����
	//		unsigned char reserve[957];	   	   //957�������ֽ�
		}picture_send;

		struct{//����ͼƬ
			unsigned short int line_y_count;   //2: y�м���
			unsigned short int bags_count;	   //2�����ݰ�����
			unsigned char line_buf[960];	   //960�������ݻ�����
	//	    unsigned char reserve[60];	   	   //60�������ֽ�
		}picture_receive;
		
		unsigned char buf[1024];			   //hid���ݴ������1024�ֽ��ڴ�
	}hid;

	unsigned char receive_buffer[64];		  //HID���ջ�����

	int (* send)(unsigned char/*parent_command*/,unsigned char/*child_command*/);
	int (* send_check_data)(unsigned char    /*command_parent*/,
							unsigned char    /*bag_end_flag*/,
							unsigned long int/*bags_num*/,
							unsigned char*   /*send_buffer*/);
    unsigned char* (* get_picture_30_points)(int x/*point_x_count*/,int y/*point_y_count*/);
	int (*set_picture_line_points)(int y/*line_y_count*/,unsigned short int * /*color_data*/);
	int (*send_picture_data)(unsigned char   /*command_parent*/,	      //1�ֽ�����
							 unsigned char   /*bag_end_flag*/,			  //1�ֽڷ�����ϱ�־λ
							 unsigned short  /*int bags_num*/,	  		  //2�ֽ��Զ���							 
							 unsigned char * /*send_buffer*/);			  //60�ֽ�����	
	void (* capture_handle)(void);

	int capture_flag;
}USB_COMMANDT_T;
	

extern USB_COMMANDT_T usb_command;

#endif //__USB_COMMAND_H__
