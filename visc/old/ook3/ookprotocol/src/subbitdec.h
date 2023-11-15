#include "cdef.h"


#define sbd_recbuffer_size	(100)

#define sbd_bittime	(500)
#define sbd_bittolerance (252)
#define sbd_starttime	(2000)

typedef enum sbd_testate{
	idle = 0,
	receiving,
	done,
}sbd_testate;

typedef struct sbd_tstate{
	u8 recbuffer[sbd_recbuffer_size];
	u8 b;
	u8 i;
	sbd_testate recstate;
	//statistics

	u8 nr_restarts;
	u8 nr_errors;
}sbd_tstate;

extern sbd_tstate sbd_state;