/*
 * --------------------
 * Company             : LUOYANG GINGKO TECHNOLOGY CO.,LTD.
                       : 洛阳银杏科技有限公司
 * --------------------
 * Project Name        : iCore3 lan_http
 * Description         : iCore3 lan_http
 * --------------------
 * Tool Versions       : uVision V5.17.0.0
 * Target Device       : STM32F407IGT6
 * --------------------
 * Engineer            : ysloveivy.
 * Revision            : 0.01
 * Created Date        : 2015.12.20
 * --------------------
 * Engineer            :
 * Revision            :
 * Modified Date       :
 * --------------------
 * Additional Comments :
 *
 * --------------------
 */
//------------------------- Include -----------------------//
#include "..\fwlib\inc\stm32f4xx_gpio.h"

#include "..\include\led.h"
#include "..\include\main.h"
#include "..\include\spi1.h"
#include "..\include\w5500.h"
#include "..\include\socket.h"
#include "..\include\httputil.h"
#include "..\include\adc.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//------------------------- Define ------------------------//

//------------------------ Variable -----------------------//

//------------------- Function Prototype ------------------//

//------------------------ Function -----------------------//
/*
 * Name                : main
 * Description         : ---
 * Author              : ysloveivy.
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 12/20/2015
 * 
 * create.
 * --------------------
 */
int main(void)
{
	int i;

	/*初始化*/	
	led.initialize();
	adc.initialize();
	spi1.initialize();
	w5500.initialize();
	socket(0,Sn_MR_TCP,80,0);
	
	LED_GREEN_ON;
	
	while(1){
		/*http处理*/
		do_http();
		/*ADC 电源监视*/
		for(i = 0;i < 5;i++){
			adc.read(i);
		}
	}
}
