#include "../include/fpga_test.h"

int main() {
	int dev;
	unsigned char data[4];
	ssize_t ret;
	int data_len;
	int i = 8888;
	int j=0;

	memset(data, 0, sizeof(data));
	printf("%s\n",data);
	sprintf(data,"%d",i);
	printf("%s\n",data);

	for(j=0;j<4;j++)
	{
		data[j] = data[j] - '0';
	}
	dev = open(FND_DEVICE, O_RDWR);
	assert2(dev >= 0, "Device open error", FND_DEVICE);

	ret = write(dev, data, FND_MAX_DIGIT);
	assert2(ret >= 0, "Device write error", FND_DEVICE);



	printf("Current FND value: ");
	for (i = 0; i < 4; i++) {
		printf("data[%d] = %d", i, data[i]);
	}
	printf("\n");

	close(dev);
	return 0;
}

