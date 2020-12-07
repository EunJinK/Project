#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <signal.h>

#define BUZZER_DEVICE "/dev/fpga_buzzer"

unsigned char quit = 0;

void user_signal1(int sit)
{
	quit = 1;
}

int main(int argc, char **argv)
{
	int dev;
	unsigned char state = 0;
	unsigned char retval;
	unsigned char data;

	dev = open(BUZZER_DEVICE, O_RDWR);
	if(dev < 0){
		printf("Device open error : %s\n",BUZZER_DEVICE);
		exit(1);
	}

	(void)signal(SIGINT, user_signal1);

	printf("Press <ctrl+c> to exit.\n");
	
	int scale[7] ={3822, 3405, 3034,2863,2551,2273,2025};
	int count = 0, lv =0;
	
	while(!quit){
		if(state != 0){
			state = 0;
			data = 1;
			retval = write(dev, &data, 1);
			if(retval < 0){
				printf("Write Error! \n");
				return -1;
			}
		}
		else{
			state = 1;
			data = 0;
			retval = write(dev, &data, 1);
			if(retval < 0){
				printf("Write Error!\n");
				return -1;
			}
		}
		usleep(scale[lv]/2);
		count++;
		if(count*scale[lv]/2 >2000*1000)
		{
			count =0;
			lv = (lv+1)%7;
			
		}
	}

	printf("Current Buzzer Value : %d\n",data);
	close(dev);

	return(0);
}

