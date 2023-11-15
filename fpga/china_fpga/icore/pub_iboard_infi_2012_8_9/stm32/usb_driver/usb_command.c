#include "..\usb_include\usb_lib.h"
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\flash.h"
#include "..\include\spi.h"
#include "..\include\evtft.h"
#include "..\include\fsmc.h"
#include <string.h>


static int send_2_command(unsigned char command_parent, unsigned char command_child);
static int send_check_data(unsigned char parent_command,        //1�ֽ�����
			   unsigned char bag_end_flag,                                          //1�ֽڷ�����ϱ�־λ
			   unsigned long int bags_num,                                          //4�ֽ��Զ���
			   unsigned char *send_buffer);                                 //60�ֽ�����
static unsigned char* get_picture_30_points(int x, int y);
static int set_picture_line_points(int y, unsigned short int *color_data);
static int send_picture_data(unsigned char command_parent,      //1�ֽ�����
			     unsigned char bag_end_flag,                                //1�ֽڷ�����ϱ�־λ
			     unsigned short int bags_num,                               //2�ֽ��Զ���
			     unsigned char *send_buffer);                               //60�ֽ�����

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


//����2�ֽ�����
static int send_2_command(unsigned char command_parent, unsigned char command_child)
{
	unsigned char buf[64];
	memset(buf, 0, 64);
	buf[0] = command_parent;
	buf[1] = command_child;
	usb.send_data(buf);
	return 0;
}
//����У������
static int send_check_data(unsigned char command_parent, //1�ֽ�����
			   unsigned char bag_end_flag,                                   //1�ֽڷ�����ϱ�־λ
			   unsigned long int bags_num,                                   //4�ֽ��Զ���
			   unsigned char *send_buffer)                                   //60�ֽ�����
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

//һ�ο���30���֣���60�ֽ�
static unsigned char* get_picture_30_points(int x, int y) //һ����4352�����������Զ����ֽ�����װ�ط��͵��ǵڼ���
{
	int i;
	unsigned char k = 0;

	for (i = x; i < x + 30; i++) { //yΪ���㣬x�ƶ�30����
		usb_command.hid.picture_send.buf[k] = lcd.get_point(i, y);
		usb_command.hid.picture_send.buf[k + 1] = lcd.get_point(i, y) >> 8;

		k += 2;
	}

	return usb_command.hid.picture_send.buf;
}
//����ˢдҺ��
static int set_picture_line_points(int y, unsigned short int *color_data)
{
	for (int i = 0; i < 480; i++)
		lcd.set_point(i, y, color_data[i]);

	return 0;
}
//����ͼƬ����
static int send_picture_data(unsigned char command_parent,      //1�ֽ�����
			     unsigned char bag_end_flag,                                //1�ֽڷ�����ϱ�־λ
			     unsigned short int bags_num,                               //2�ֽ��Զ���
			     unsigned char *send_buffer)                                //60�ֽ�����
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
//USB�˵�1�����ж�
void EP1_OUT_Callback(void)
{
	PMAToUserBufferCopy(usb_command.receive_buffer, ENDP1_RXADDR, 64);

	switch (usb_command.receive_buffer[0]) {
	//FLASH����
	case COMMAND_FLASH_ERASE_RECEIVE:
		for (unsigned char i = usb_command.receive_buffer[1]; i <= usb_command.receive_buffer[2]; i++)
			flash.sector_erase(i);
		send_2_command(COMMAND_FLASH_ERASE_SEND, COMMAND_FLASH_ERASE_OK_SEND);
		break;

	//FLASH��д
	case COMMAND_FLASH_WRITE_RECEIVE:
		//�ӵ���ʼд������г�ʼ��
		if (usb_command.receive_buffer[1] == COMMAND_FLASH_WRITE_START_RECEIVE) {
			usb_command.hid.flash_write.sector = usb_command.receive_buffer[2];        //������
			usb_command.hid.flash_write.bytes_32_count = 0;
			usb_command.hid.flash_write.bytes_256_count = 0;
			//���ͼ�����д����
			send_2_command(COMMAND_FLASH_WRITE_SEND, COMMAND_FLASH_WRITE_CONTINUE_SEND);
		}
		//��ʼ������д����
		else if (usb_command.receive_buffer[1] == COMMAND_FLASH_WRITE_DATA_RECEIVE) { //���Ƚ��յ�32�ֽ���Ч����װ�뻺����
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

	//FLASHУ��
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

	//��ͼ
	case COMMAND_PICTURE_LOAD_RECEIVE:        //64���ֽ�һ������30����һ��,1�ֽ�����+3�ֽ��Զ���+60�ֽڣ�30�㣩��һ����4352����
		if (usb_command.receive_buffer[1] == COMMAND_PICTURE_LOAD_START_RECEIVE) {
			usb_command.capture_flag = 1;

			usb_command.hid.picture_send.point_x_count = 0;                          //ȫ����ʼ��Ϊ0������0����
			usb_command.hid.picture_send.point_y_count = 271;
			usb_command.hid.picture_send.bag_end_flag = 0;
			usb_command.hid.picture_send.bags_count = 0;
			break;
		}
		//������0�����󣬲Ż��յ�������
		else if (usb_command.receive_buffer[1] == COMMAND_PICTURE_LOAD_CAN_RECEIVE) {
			usb_command.hid.picture_send.bags_count++;
			usb_command.hid.picture_send.point_x_count += 30;                 //��һ��x =30;
			usb_command.hid.picture_send.bag_end_flag = 0;                //����δ���

			//һ����x+30��ﵽ480����ôҪ���л��У�ͬʱx�ص�0��
			if (usb_command.hid.picture_send.point_x_count == 480 && usb_command.hid.picture_send.point_y_count > 0) {
				usb_command.hid.picture_send.point_x_count = 0;
				usb_command.hid.picture_send.point_y_count--;                 //����
			}
			//һ������y����271�������һ�У���x�ӵ�450����ʱΪ���һ�����ݣ�x,y���䣬��ȡ��(450,271)��ʼ��30��
			//������ɱ�־λ��1
			if (usb_command.hid.picture_send.point_x_count == 450 && usb_command.hid.picture_send.point_y_count == 0) {
				usb_command.hid.picture_send.bag_end_flag = 1;
				usb_command.capture_flag = 0;
			}
		}

		send_capture();
		break;
	//ˢдͼƬ
	case COMMAND_PICTURE_WRITE_RECEIVE:
		if (usb_command.receive_buffer[1] == COMMAND_PICTURE_WRITE_START_RECEIVE) {
			usb_command.hid.picture_receive.line_y_count = 271;
			usb_command.hid.picture_receive.bags_count = 0;
			send_2_command(COMMAND_PICTURE_WRITE_SEND, COMMAND_PICTURE_WRITE_CONTINUE_SEND);
		}else if (usb_command.receive_buffer[1] == COMMAND_PICTURE_WRITE_DATA_RECEIVE) {
			memcpy(&usb_command.hid.picture_receive.line_buf[usb_command.hid.picture_receive.bags_count * 60],
			       &usb_command.receive_buffer[4], 60);
			usb_command.hid.picture_receive.bags_count++;        //��������ÿ��16���㣬30����һ��

			if (16 == usb_command.hid.picture_receive.bags_count) {
				set_picture_line_points(usb_command.hid.picture_receive.line_y_count,
							(unsigned short int*)usb_command.hid.picture_receive.line_buf);

				usb_command.hid.picture_receive.bags_count = 0;
				usb_command.hid.picture_receive.line_y_count--;         //����
			}
			if (usb_command.receive_buffer[2] == 0)
				send_2_command(COMMAND_PICTURE_WRITE_SEND, COMMAND_PICTURE_WRITE_CONTINUE_SEND);
			else
				send_2_command(COMMAND_PICTURE_WRITE_SEND, COMMAND_PICTURE_WRITE_END_SEND);
		}
		break;

	//�Զ�������
	case COMMAND_USER_CUSTOM_RECEIVE:
		//����Զ��������:


		send_2_command(COMMAND_USER_CUSTOM_SEND, COMMAND_USER_CUSTOM_OK_SEND);
		break;

	default:;
	}

	SetEPRxStatus(ENDP1, EP_RX_VALID);
}
