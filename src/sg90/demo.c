#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <unistd.h>
#define SG90Pin 10
int jd;
int count = 0;
static int i = 0;
void signal_handler(int signum)
{
	if(i <= jd){
		digitalWrite(SG90Pin, HIGH);
	}else{
		digitalWrite(SG90Pin, LOW);
	}
	if(i == 40){
		i = 0;
        count++;
	}
	i++;
}
int main(int argc,char** argv)
{
    int flag = 1;
	if(argc != 2)
		printf("sudo ./a.out **\n");
	struct itimerval itv;
	jd = 0;
	wiringPiSetup();
	pinMode(SG90Pin, OUTPUT);
	//设定定时时间
	itv.it_interval.tv_sec = 0;
	itv.it_interval.tv_usec = 500;
	//设定开始生效，启动定时器的时间
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	//设定定时方式
	if( -1 == setitimer(ITIMER_REAL, &itv, NULL)){
		perror("error");
		exit(-1);
	}
	//jd = atoi(argv[1]);
	//printf("%d",jd);
	//信号处理
	signal(SIGALRM,signal_handler);
	while(flag){
		jd = atoi(argv[1]);
        if(count >= 100)
        flag = 0;
		//printf("input jd: 1-0 2-45 3-90 4-135 \n");
		//scanf("%d",&jd);
	}
	return 0;
}

