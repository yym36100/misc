/* CH376оƬ Ӳ������� V1.0 */
/* �ṩ�����ӳ��� */

#include	"HAL.H"

/* ��ʱָ��΢��ʱ��,���ݵ�Ƭ����Ƶ����,����ȷ */
void	mDelayuS( UINT8 us )
{
	//us += 1;
	//while ( us -- );  /* 24MHz MCS51 */
	usleep(us);
}

/* ��ʱָ������ʱ��,���ݵ�Ƭ����Ƶ����,����ȷ */
void	mDelaymS( UINT8 ms )
{
	while ( ms -- ) {
		mDelayuS( 250 );
		mDelayuS( 250 );
		mDelayuS( 250 );
		mDelayuS( 250 );
	}
}