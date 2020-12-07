#include "../include/fpga_test.h"

int main() {
	unsigned char buf[TEXT_LCD_MAX_BUF] = "hi";
	int dev, len1, len2;
	int i;

	unsigned char *str1 = "                      ";




	dev = open(TEXT_LCD_DEVICE, O_WRONLY);
	assert2(dev >= 0, "Device open error", TEXT_LCD_DEVICE);

	memset(buf, ' ', TEXT_LCD_MAX_BUF);

	sprintf(buf,"%s",str1);
 
	write(dev, buf, TEXT_LCD_MAX_BUF);

	close(dev);
	return 0;
}

