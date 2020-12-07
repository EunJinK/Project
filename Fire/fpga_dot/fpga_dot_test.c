#include "/root/work/achroimx6q/fpga_driver/include/fpga_test.h"
#include "/root/work/achroimx6q/fpga_driver/include/fpga_dot_font.h"

int main() {
	int dev, num;
	ssize_t ret;
	int i;


	dev = open(DOT_DEVICE, O_WRONLY);

	ret = write(dev, fpga_fire, sizeof(fpga_fire));

	close(dev);
	return 0;
}

