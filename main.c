#include <reg51.h>       //包含头文件
#include <stdlib.h>
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
unsigned int systemTime;
unsigned char k1 = 0;
void time0(void) interrupt 1 using 1
{
	TH0 = 0x00;
	TL0 = 0xff;

	systemTime++; 
	if (systemTime > 32767)
		systemTime = 0;
}

void inter0() interrupt 0{
k1 = 1;
P1_1 = 1;
}
//毫秒级延时函数
void delay(unsigned int x)
{
  unsigned char i;
 while(x--)
 {
   for(i = 0;i < 255;i++);
 }
}
//字符发送函数
void putchar(unsigned char data1)  
{
  SBUF = data1;               //将待发送的字符送入发送缓冲器
 while(TI == 0);            //等待发送完成
 TI = 0;                     //发送中断标志请0
}
//字符串发送函数
void putstring(unsigned char *dat)
{
  while(*dat != '\0')           //判断字符串是否发送完毕
 {
   putchar(*dat);        //发送单个字符
  dat++;                 //字符地址加1，指向先下一个字符
  delay(5);
 }
}

//主函数
void main(void)
{
	unsigned char k;
	unsigned int i;
	unsigned int j;
	unsigned char x;
	unsigned int ran_num;
	unsigned int ran2;
	unsigned char ran3;
	P0 = 0x00;
	P1 = 0x00;
	P2 = 0x00;
	 SCON = 0x50;         //串口工作方式设置
	 TMOD = 0x20;         //定时器工作方式设置
	 PCON = 0x00;        //波特率倍增设置
	 TL1 = 0xfd;         //波特率设置
	 TH1 = 0xfd;        //
	 TI = 0;           // 清0发送中断标志         
	 TR1 = 1;          //开启定时器
	
	  TH0 = 0x00;
	 TL0 = 0xff;
	 TR0 = 1;
	 ET0 = 1;
	 EA = 1;
	 EX0 = 1;
	 IT0 = 1;
	 while(1){
 	 while(k1){
		 j = systemTime % 255;
		 srand(j);
  	 		 for (x=0;x<10;x++){
			    ran_num = rand()%15;
				putstring("Start:");
			 	putchar(65+ran_num);
			  	//printf("StartTo: %d\n",ran_num);
				for (i = 0; i < ran_num * 10; i = i + 10){
					for (k = 0; k < i; k ++){
						P1_0 = !P1_0;
						delay(1500 / i);
					}
				}
				ran2 = rand()%255;
				putstring("\nGoAhead:");
				putchar(ran2);
 			  	//printf("GoAhead: %d\n",ran_num);
				for (i = 0; i < ran2 ;i++){
					P1_0 = !P1_0;
						delay(150 / ran2);
				}
  			  	//printf("SlowDown..\n");
				putstring("SlowDowe:\n");
				for (i = ran_num*10; i > 0;i = i-10){
					for (k = 0; k < i; k ++){
						P1_0 = !P1_0;
						delay(500 / i);
					}
				 }

				 ran3 = rand()%255;
				 //printf("stop! %d\n",ran3);
				 putstring("Stop:");
				 putchar(ran3);
				 P1_0 = 0;
				 delay(ran3*10);
				 putstring("\n");

			}
		}
	}
}	  
