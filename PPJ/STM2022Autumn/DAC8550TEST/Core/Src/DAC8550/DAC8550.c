#include "DAC8550.h"

float pi = 3.141592;
const int32_t sinbox[200] = {
	0,
1029,
2058,
3084,
4107,
5126,
6140,
7148,
8149,
9142,
10126,
11100,
12063,
13014,
13952,
14876,
15786,
16680,
17558,
18418,
19261,
20084,
20887,
21670,
22431,
23170,
23887,
24580,
25248,
25892,
26510,
27102,
27667,
28205,
28715,
29197,
29649,
30073,
30467,
30831,
31164,
31467,
31739,
31979,
32188,
32365,
32510,
32623,
32703,
32752,
32767,
32752,
32703,
32623,
32510,
32365,
32188,
31979,
31739,
31467,
31164,
30831,
30467,
30073,
29649,
29197,
28715,
28205,
27667,
27102,
26510,
25892,
25248,
24580,
23887,
23170,
22431,
21670,
20887,
20084,
19261,
18418,
17558,
16680,
15786,
14876,
13952,
13014,
12063,
11100,
10126,
9142,
8149,
7148,
6140,
5126,
4107,
3084,
2058,
1029,
0,
-1029,
-2058,
-3084,
-4107,
-5126,
-6140,
-7148,
-8149,
-9142,
-10126,
-11100,
-12063,
-13014,
-13952,
-14876,
-15786,
-16680,
-17558,
-18418,
-19261,
-20084,
-20887,
-21670,
-22431,
-23170,
-23887,
-24580,
-25248,
-25892,
-26510,
-27102,
-27667,
-28205,
-28715,
-29197,
-29649,
-30073,
-30467,
-30831,
-31164,
-31467,
-31739,
-31979,
-32188,
-32365,
-32510,
-32623,
-32703,
-32752,
-32768,
-32752,
-32703,
-32623,
-32510,
-32365,
-32188,
-31979,
-31739,
-31467,
-31164,
-30831,
-30467,
-30073,
-29649,
-29197,
-28715,
-28205,
-27667,
-27102,
-26510,
-25892,
-25248,
-24580,
-23887,
-23170,
-22431,
-21670,
-20887,
-20084,
-19261,
-18418,
-17558,
-16680,
-15786,
-14876,
-13952,
-13014,
-12063,
-11100,
-10126,
-9142,
-8149,
-7148,
-6140,
-5126,
-4107,
-3084,
-2058,
-1029
};
int32_t cal_dac(uint16_t frequency,uint16_t fre_i)
{
	int32_t temp = 0;
	temp = ((int32_t)(sin((2*pi)/frequency*fre_i)+1))*65535-32768;
	return temp;
}
void DAC8550_init(void)
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
// 	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA端口时钟
//	
//	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);				 //LED0-->PA.8 端口配置
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOC,(GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11));						 //PA.8 输出高
}

//向8550写数据
void write_8550(uint32_t data) 
{ 
  uint8_t i;  
	SYNC1;   
//	Delay_Us(2);  
	SCLK0;   
//	Delay_Us(2);  
	SYNC0; 
	Delay_Us(2); 
	for(i=0;i<24;i++)   
	{ 
    if(0x800000&data)
		{
			DIN1; 
		}
	    
		else
		{
			DIN0;  
		}
   
		SCLK1;
		Delay_Us(1);  
		SCLK0;
		Delay_Us(1);  
		data=data<<1;   
	} 
  Delay_Us(2);   
	SYNC1; 
	Delay_Us(2);
	SCLK1;
} 
// date的范围从–32768 到 32767对应输出0到5V
void voltage_output(int32_t data)
{
	uint32_t ctr=0; //正常输出 
	ctr = ctr|(data&0xffff);  
	write_8550(ctr); 
}









