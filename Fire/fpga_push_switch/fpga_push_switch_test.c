#include "../include/fpga_test.h"
unsigned char quit = 0;
void user_signal1(int sig) { quit = 1; }

int main(void) {
	unsigned char push_sw_buf[PUSH_SWITCH_MAX_BUTTON];
	int dev;
	int i;

	dev = open(PUSH_SWITCH_DEVICE, O_RDONLY);
	assert2(dev >= 0, "Device open error", PUSH_SWITCH_DEVICE);

	(void)signal(SIGINT, user_signal1);
	printf("Press <ctrl+c> to quit.\n");

	while (!quit) {
		usleep(400000);
		read(dev, &push_sw_buf, sizeof(push_sw_buf));
		for (i = 0; i < PUSH_SWITCH_MAX_BUTTON; i++)
			printf("[%d]", push_sw_buf[i]);
		printf("\n");
	}
	close(dev);
	return 0;
}

