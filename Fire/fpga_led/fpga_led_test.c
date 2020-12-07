#include "../include/fpga_test.h"
unsigned char quit = 0;
void user_signal1(int sig) { quit = 1; }

/*
int main(int argc, char**argv){
	int dev;
	unsigned char data;
	ssize_t ret;

	char usage[50];
	sprintf(usage, "Usage:/n/tfpga_led_test <%d ~ %d>\n", LED_MIN,LED_MAX);
	assert(argc == 2, usage);
	
	/*if(argc != 2){
		printf("%s",usage);
		exit(1);
	}

	data = atoi(argv[1]);	
	printf("%d\n",data);
	
	dev = open(LED_DEVICE, O_RDWR);
	assert2(dev >= 0, "Device open error", LED_DEVICE);

	ret = write(dev, &data, 1);
	assert2(ret >= 0, "Device wrtie error", LED_DEVICE);

	sleep(1);

	ret = read(dev, &data, 1);
	assert2(ret >= 0, "Device read error", LED_DEVICE);

	printf("Current LED value: %d\n", data);
	printf("\n");

	close(dev);
	return 0;
} 
*/

int main()
{
	int led_dev;
	unsigned char data = 1;
	
	(void)signal(SIGINT, user_signal1);

	led_dev = open(LED_DEVICE, O_RDWR);
	assert2(led_dev >= 0, "Device open error", LED_DEVICE);

	while(!quit)
	{
		for(;data<129;data*=2)
		{
			write(led_dev, &data, 1);
			read(led_dev, &data, 1);
			
		}
		data = 1;
	}
	close(led_dev);
	return 0;
}




