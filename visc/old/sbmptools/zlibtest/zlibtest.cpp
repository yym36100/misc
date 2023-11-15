// zlibtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>

// zlib stuff ======================================================
#include "zlib.h"
#include <assert.h>
#if defined(WIN32)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384
// zlib stuff ======================================================

char data[CHUNK]="some text to compress not a lot just enough to test the inflate and delflate algorithms"
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccc";
char out[CHUNK];
unsigned outsize=0;

char reko[CHUNK];

/* Compress from file source to file dest until EOF on source.
def() returns Z_OK on success, Z_MEM_ERROR if memory could not be
allocated for processing, Z_STREAM_ERROR if an invalid compression
level is supplied, Z_VERSION_ERROR if the version of zlib.h and the
version of the library linked do not match, or Z_ERRNO if there is
an error reading or writing the files. */
int def(char *pin,char *pout, int level)
{
	z_stream strm;
	int ret,flush=Z_FINISH;
	unsigned have;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, level);
	if (ret != Z_OK)
		return ret;

	
	strm.avail_in = strlen(pin);
	strm.next_in = (Bytef*)pin;	

	strm.avail_out = CHUNK;
	strm.next_out = (Bytef*)pout;

	ret = deflate(&strm, flush);    /* no bad return value */
	assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
	have = CHUNK - strm.avail_out;
	outsize = have;

	/* clean up and return */
	(void)deflateEnd(&strm);
	return Z_OK;
}

/* Decompress from file source to file dest until stream ends or EOF.
inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
allocated for processing, Z_DATA_ERROR if the deflate data is
invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
the version of the library linked do not match, or Z_ERRNO if there
is an error reading or writing the files. */
int inf(char *pin,char *pout)
{
	int ret;
	unsigned have;
	z_stream strm;

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit(&strm);
	if (ret != Z_OK)
		return ret;

	strm.avail_in = outsize;
	strm.next_in = (Bytef*)pin;

	strm.avail_out = CHUNK;
	strm.next_out = (Bytef*)pout;
	ret = inflate(&strm, Z_NO_FLUSH);

	have = CHUNK - strm.avail_out;
	
	/* clean up and return */
	(void)inflateEnd(&strm);
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int _tmain(int argc, _TCHAR* argv[])
{
//	def(data,out,Z_BEST_COMPRESSION);
//	inf(out,reko);
	unsigned long dsize = CHUNK;
	unsigned long dsize2 = CHUNK;
	compress2((Bytef*)out,&dsize,(Bytef*)data,strlen(data),9);
	uncompress((Bytef*)reko,&dsize2,(Bytef*)out,dsize);
	return 0;
}

