/*------------------------------------------------------
   FILE NAME   : flash.c
   DESCRIPTION : flsh driver .
   VERSION     : 0.0.0 (C)aureole
   AUTHOR      : Aureole
   CREATE DATE : 10.26.2006
   MODIFY DATE :
   LOGS        :-\
   -V 0.1.0 First created. 10.26.2006

   --------------------------------------------------------*/
//-----------------Include files-------------------------//
#include "..\include\flash.h"
#include "..\include\spi.h"

#include <string.h>
#include <stdlib.h>

//-----------------Function Prototype--------------------//
/*
 *
 *
 *
 * read_status_register
 *
 *
 */
static unsigned char
read_status_register(void)
{
	unsigned char buf[2];

	buf[0] = READ_REGISTER;

	spi1.write(2, buf);

	return buf[1];
}

/*
 *
 *
 * enable_write_status_register
 *
 *
 */
static void
enable_write_status_register(void)
{
	unsigned char buf = EN_WRITE_REGISTER;

	spi1.write(1, &buf);
}

/*
 *
 *
 * write_status_register
 *
 */
static void
write_status_register(char byte)
{
	unsigned char buf[2];

	buf[0] = WRITE_REGISTER;
	buf[1] = byte;

	spi1.write(2, buf);
}

/*
 *
 * enable_write
 *
 */
static void
enable_write(void)
{
	unsigned char buf;

	buf = EN_WRITE_FLASH;

	spi1.write(1, &buf);
}

/*
 *
 * disable_write
 *
 */
static void
disable_write(void)
{
	unsigned char buf;

	buf = DIS_WRITE_FLASH;

	spi1.write(1, &buf);
}

/*
 *
 * read_jedec_id
 *
 *
 */
static unsigned long int
read_jedec_id(void)
{
	unsigned long id = 0;
	unsigned char buf[4];

	buf[0] = READ_ID;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;

	spi1.write(4, buf);

	id |= buf[1];
	id <<= 8;
	id |= buf[2];
	id <<= 8;
	id |= buf[3];

	return id;
}

/*
 *
 *
 * read
 *
 *
 */

static unsigned char
read(unsigned long int address)
{
	unsigned char buf[5];

	buf[0] = READ_FLASH;
	buf[1] = (address & 0xff0000) >> 16;
	buf[2] = (address & 0xff00) >> 8;
	buf[3] = address & 0xff;
	buf[4] = 0;

	spi1.write(5, buf);

	return buf[4];
}

/*
 *
 *
 * read_72
 *
 *
 */
static int
read_72(unsigned long int address, char * dat)
{
	unsigned char buf[76];

	buf[0] = READ_FLASH;
	buf[1] = (address & 0xff0000) >> 16;
	buf[2] = (address & 0xff00) >> 8;
	buf[3] = address & 0xff;


	spi1.write(76, buf);

	memcpy(dat, buf + 4, 72);

	return 0;
}

/*
 *
 *
 * read_32
 *
 *
 */
static int
read_32(unsigned long int address, char * dat)
{
	unsigned char buf[36];

	buf[0] = READ_FLASH;
	buf[1] = (address & 0xff0000) >> 16;
	buf[2] = (address & 0xff00) >> 8;
	buf[3] = address & 0xff;


	spi1.write(36, buf);

	memcpy(dat, buf + 4, 32);

	return 0;
}
/*
 *
 *
 * read_256
 *
 *
 */
static int
read_256(unsigned long int address, char * dat)
{
	unsigned char buf[260];

	buf[0] = READ_FLASH;
	buf[1] = (address & 0xff0000) >> 16;
	buf[2] = (address & 0xff00) >> 8;
	buf[3] = address & 0xff;


	spi1.write(260, buf);

	memcpy(dat, buf + 4, 256);

	return 0;
}
/*
 *
 *
 * write_byte
 *
 *
 */

static int
write_byte(unsigned long int address, char byte)
{
	unsigned char buf[5];

	enable_write();

	buf[0] = WRITE_FLASH;
	buf[1] = (address & 0xff0000) >> 16;
	buf[2] = (address & 0xff00) >> 8;
	buf[3] = address & 0xff;
	buf[4] = byte;

	spi1.write(5, buf);

	//disable_write();

	return 0;
}
static int
write_256(unsigned long int address, char * dat)
{
	unsigned char buf[260];

	enable_write();

	buf[0] = WRITE_FLASH;
	buf[1] = (address & 0xff0000) >> 16;
	buf[2] = (address & 0xff00) >> 8;
	buf[3] = address & 0xff;

	memcpy(buf + 4, dat, 256);

	spi1.write(260, buf);

//	disable_write();

	return 0;
}

/*
 * waiting_busy
 *
 *
 */
void waiting_busy(void)
{
//	while(read_status_register() == UNBUSY_FLAG);

//	read_status_register();
}

/*
 *
 *
 * chip_erase
 *
 */

static int
chip_erase(void)
{
	unsigned char buf[2];

	enable_write();

	buf[0] = ERASE;

	spi1.write(1, buf);

	while (read_status_register() & 0x1) ;

	disable_write();

	return 0;
}

/*
 *
 *
 * lock_flash
 *
 *
 */

static int
lock_flash(void)
{
	enable_write_status_register();
	write_status_register(0x1c);

	disable_write();

	return 0;
}

/*
 *
 *
 * unlock_flash
 *
 *
 */
static int
unlock_flash(void)
{
	enable_write_status_register();
	write_status_register(0);

	enable_write();

	return 0;
}




static int
sector_erase(int sector)
{
	unsigned long int address;

	unsigned char buf[5];


	enable_write();

	address = sector * 65536 + 100;

	buf[0] = SECTOR_ERASE;
	buf[1] = (address & 0xff0000) >> 16;
	buf[2] = (address & 0xff00) >> 8;
	buf[3] = address & 0xff;

	spi1.write(4, buf);

	while (read_status_register() & 0x1) ;

	return 0;
}

//--------------------define------------------------------//

SFLASH_T flash = {
	.read_jedec_id = read_jedec_id,
	.read = read,
	.read_32 = read_32,
	.read_72 = read_72,
	.read_256 = read_256,
	.write = write_byte,
	.write_256 = write_256,
	.lock = lock_flash,
	.unlock = unlock_flash,
	.chip_erase = chip_erase,
	.sector_erase = sector_erase
};





