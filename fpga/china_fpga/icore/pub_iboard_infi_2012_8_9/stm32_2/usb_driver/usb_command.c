#include "..\usb_include\usb_lib.h"
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\flash.h"
#include "..\include\spi.h"
#include "..\include\evtft.h"
#include "..\include\fsmc.h"
#include <string.h>


static int send_2_command(unsigned char command_parent, unsigned char command_child);
static int send_check_data(unsigned char parent_command,        //1字节命令
			   unsigned char bag_end_flag,                                          //1字节发送完毕标志位
			   unsigned long int bags_num,                                          //4字节自定义
			   unsigned char *send_buffer);                                 //60字节数据
static unsigned char* get_picture_30_points(int x, int y);
static int set_picture_line_points(int y, unsigned short int *color_data);
static int send_picture_data(unsigned char command_parent,      //1字节命令
			     unsigned char bag_end_flag,                                //1字节发送完毕标志位
			     unsigned short int bags_num,                               //2字节自定义
			     unsigned char *send_buffer);                               //60字节数据

static void capture_handle(void);

USB_COMMANDT_T usb_command = {
	.send = send_2_command,
	.send_check_data = send_check_data,
	.get_picture_30_points = get_picture_30_points,
	.set_picture_line_points = set_picture_line_points,
	.send_picture_data = send_picture_data,
	.capture_handle = capture_handle
};




static void send_capture(void)
{
	send_picture_data(COMMAND_PICTURE_LOAD_SEND,
			  usb_command.hid.picture_send.bag_end_flag,
			  usb_command.hid.picture_send.bags_count,
			  get_picture_30_points(usb_command.hid.picture_send.point_x_count,
						usb_command.hid.picture_send.point_y_count));
}

static void capture_handle(void)
{
	if (usb_command.capture_flag) {
		send_capture();
		while (usb_command.capture_flag) ;
	}
}


//发送2字节命令
static int send_2_command(unsigned char command_parent, unsigned char command_child)
{
	unsigned char buf[64];
	memset(buf, 0, 64);
	buf[0] = command_parent;
	buf[1] = command_child;
	usb.send_data(buf);
	return 0;
}
//发送校验数据
static int send_check_data(unsigned char command_parent, //1字节命令
			   unsigned char bag_end_flag,                                   //1字节发送完毕标志位
			   unsigned long int bags_num,                                   //4字节自定义
			   unsigned char *send_buffer)                                   //60字节数据
{
	unsigned char buf[64];
	buf[0] = command_parent;
	buf[1] = bag_end_flag;
	buf[2] = bags_num;
	buf[3] = bags_num >> 8;
	buf[4] = bags_num >> 16;
	buf[5] = bags_num >> 24;
	memcpy(&buf[6], send_buffer, 58);
	usb.send_data(buf);
	return 0;
}

//一次拷贝30个字，即60字节
static unsigned char* get_picture_30_points(int x, int y) //一共发4352个包，所以自定义字节用来装载发送的是第几鳇
{
	int i;
	unsigned char k = 0;

	for (i = x; i < x + 30; i++) { //y为定点，x移动30个点
		usb_command.hid.picture_send.buf[k] = lcd.get_point(i, y);
		usb_command.hid.picture_send.buf[k + 1] = lcd.get_point(i, y) >> 8;

		k += 2;
	}

	return usb_command.hid.picture_send.buf;
}
//按行刷写液晶
static int set_picture_line_points(int y, unsigned short int *color_data)
{
	for (int i = 0; i < 480; i++)
		lcd.set_point(i, y, color_data[i]);

	return 0;
}
//发送图片数据
static int send_picture_data(unsigned char command_parent,      //1字节命令
			     unsigned char bag_end_flag,                                //1字节发送完毕标志位
			     unsigned short int bags_num,                               //2字节自定义
			     unsigned char *send_buffer)                                //60字节数据
{
	unsigned char buf[64];
	buf[0] = command_parent;
	buf[1] = bag_end_flag;
	buf[2] = bags_num;
	buf[3] = bags_num >> 8;
	memcpy(&buf[4], send_buffer, 60);
	usb.send_data(buf);
	return 0;
}
//USB端点1接收中断
void EP1_OUT_Callback(void)
{
	PMAToUserBufferCopy(usb_command.receive_buffer, ENDP1_RXADDR, 64);

	switch (usb_command.receive_buffer[0]) {
	//FLASH擦除
	case COMMAND_FLASH_ERASE_RECEIVE:
		for (unsigned char i = usb_command.receive_buffer[1]; i <= usb_command.receive_buffer[2]; i++)
			flash.sector_erase(i);
		send_2_command(COMMAND_FLASH_ERASE_SEND, COMMAND_FLASH_ERASE_OK_SEND);
		break;

	//FLASH烧写
	case COMMAND_FLASH_WRITE_RECEIVE:
		//接到开始写命令，进行初始化
		if (usb_command.receive_buffer[1] == COMMAND_FLASH_WRITE_START_RECEIVE) {
			usb_command.hid.flash_write.sector = usb_command.receive_buffer[2];        //扇区号
			usb_command.hid.flash_write.bytes_32_count = 0;
			usb_command.hid.flash_write.bytes_256_count = 0;
			//发送继续烧写命令
			send_2_command(COMMAND_FLASH_WRITE_SEND, COMMAND_FLASH_WRITE_CONTINUE_SEND);
		}
		//开始接收烧写数据
		else if (usb_command.receive_buffer[1] == COMMAND_FLASH_WRITE_DATA_RECEIVE) { //首先将收到32字节有效数据装入缓冲区
			memcpy(&usb_command.hid.flash_write.buf[usb_command.hid.flash_write.bytes_32_count * 32],
			       &usb_command.receive_buffer[4], 32);
			usb_command.hid.flash_write.bytes_32_count++;

			if (8 == usb_command.hid.flash_write.bytes_32_count) {
				flash.write_256(usb_command.hid.flash_write.sector * 65536 + usb_command.hid.flash_write.bytes_256_count * 256,
						(char*)usb_command.hid.flash_write.buf);
				usb_command.hid.flash_write.bytes_32_count = 0;
				usb_command.hid.flash_write.bytes_256_count++;
			}
			if (usb_command.receive_buffer[2] != 1)
				send_2_command(COMMAND_FLASH_WRITE_SEND, COMMAND_FLASH_WRITE_CONTINUE_SEND);
			else
				send_2_command(COMMAND_FLASH_WRITE_SEND, COMMAND_FLASH_WRITE_END_SEND);
		}
		break;

	//FLASH校验
	case COMMAND_FLASH_CHECK_RECEIVE:
		if (usb_command.receive_buffer[1] == COMMAND_FLASH_CHECK_START_RECEIVE) {
			usb_command.hid.flash_read.bags_count = 0;
			usb_command.hid.flash_read.bag_end_flag = 0;
			usb_command.hid.flash_read.bags_num_total = (unsigned long int)usb_command.receive_buffer[2] | \
								    ((unsigned long int)usb_command.receive_buffer[3]) << 8 | \
								    ((unsigned long int)usb_command.receive_buffer[4]) << 16 | \
								    ((unsigned long int)usb_command.receive_buffer[5]) << 24;

			memset(usb_command.hid.flash_read.buf, 0, 58);
		}else if (usb_command.receive_buffer[1] == COMMAND_FLASH_CHECK_CAN_RECEIVE) {
			usb_command.hid.flash_read.bags_count++;
			if (usb_command.hid.flash_read.bags_count == usb_command.hid.flash_read.bags_num_total - 1)
				usb_command.hid.flash_read.bag_end_flag = 1;
		}
		flash.read_32(usb_command.hid.flash_read.sector * 65536 + usb_command.hid.flash_read.bags_count * 32,
			      (char*)usb_command.hid.flash_read.buf);
		send_check_data(COMMAND_FLASH_CHECK_SEND,
				usb_command.hid.flash_read.bag_end_flag,
				usb_command.hid.flash_read.bags_count,
				usb_command.hid.flash_read.buf);
		break;

	//截图
	case COMMAND_PICTURE_LOAD_RECEIVE:        //64个字节一个包，30个点一发,1字节命令+3字节自定义+60字节（30点），一共发4352个包
		if (usb_command.receive_buffer[1] == COMMAND_PICTURE_LOAD_START_RECEIVE) {
			usb_command.capture_flag = 1;

			usb_command.hid.picture_send.point_x_count = 0;                          //全部初始化为0，发第0个包
			usb_command.hid.picture_send.point_y_count = 271;
			usb_command.hid.picture_send.bag_end_flag = 0;
			usb_command.hid.picture_send.bags_count = 0;
			break;
		}
		//发出第0个包后，才会收到此命令
		else if (usb_command.receive_buffer[1] == COMMAND_PICTURE_LOAD_CAN_RECEIVE) {
			usb_command.hid.picture_send.bags_count++;
			usb_command.hid.picture_send.point_x_count += 30;                 //第一次x =30;
			usb_command.hid.picture_send.bag_end_flag = 0;                //发送未完成

			//一旦加x+30后达到480；那么要进行换行，同时x回到0点
			if (usb_command.hid.picture_send.point_x_count == 480 && usb_command.hid.picture_send.point_y_count > 0) {
				usb_command.hid.picture_send.point_x_count = 0;
				usb_command.hid.picture_send.point_y_count--;                 //换行
			}
			//一旦到达y到达271，即最后一行，且x加到450，此时为最后一包数据，x,y不变，获取从(450,271)开始的30点
			//发送完成标志位置1
			if (usb_command.hid.picture_send.point_x_count == 450 && usb_command.hid.picture_send.point_y_count == 0) {
				usb_command.hid.picture_send.bag_end_flag = 1;
				usb_command.capture_flag = 0;
			}
		}

		send_capture();
		break;
	//刷写图片
	case COMMAND_PICTURE_WRITE_RECEIVE:
		if (usb_command.receive_buffer[1] == COMMAND_PICTURE_WRITE_START_RECEIVE) {
			usb_command.hid.picture_receive.line_y_count = 271;
			usb_command.hid.picture_receive.bags_count = 0;
			send_2_command(COMMAND_PICTURE_WRITE_SEND, COMMAND_PICTURE_WRITE_CONTINUE_SEND);
		}else if (usb_command.receive_buffer[1] == COMMAND_PICTURE_WRITE_DATA_RECEIVE) {
			memcpy(&usb_command.hid.picture_receive.line_buf[usb_command.hid.picture_receive.bags_count * 60],
			       &usb_command.receive_buffer[4], 60);
			usb_command.hid.picture_receive.bags_count++;        //包计数，每包16个点，30个包一行

			if (16 == usb_command.hid.picture_receive.bags_count) {
				set_picture_line_points(usb_command.hid.picture_receive.line_y_count,
							(unsigned short int*)usb_command.hid.picture_receive.line_buf);

				usb_command.hid.picture_receive.bags_count = 0;
				usb_command.hid.picture_receive.line_y_count--;         //换行
			}
			if (usb_command.receive_buffer[2] == 0)
				send_2_command(COMMAND_PICTURE_WRITE_SEND, COMMAND_PICTURE_WRITE_CONTINUE_SEND);
			else
				send_2_command(COMMAND_PICTURE_WRITE_SEND, COMMAND_PICTURE_WRITE_END_SEND);
		}
		break;

	//自定义命令
	case COMMAND_USER_CUSTOM_RECEIVE:
		//添加自定义代码区:


		send_2_command(COMMAND_USER_CUSTOM_SEND, COMMAND_USER_CUSTOM_OK_SEND);
		break;

	default:;
	}

	SetEPRxStatus(ENDP1, EP_RX_VALID);
}
