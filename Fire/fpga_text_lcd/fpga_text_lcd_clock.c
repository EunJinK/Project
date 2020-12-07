#include "../include/fpga_test.h"
#include <unistd.h>
#include <time.h>

/*
int main(int argc, char **argv) // input ./fpga_text_lcd_test hello -> hello = argv
{
	unsigned char buf[TEXT_LCD_MAX_BUF];
	int dev, len1, len2;

	len1 = strlen(ex[1]);
	//assert(len1 <= TEXT_LCD_LINE_BUF, errmsg);

	dev = open(TEXT_LCD_DEVICE, O_WRONLY);
	assert2(dev >= 0, "Device open error", TEXT_LCD_DEVICE); //error
	memset(buf, ' ', TEXT_LCD_MAX_BUF);
	memcpy(buf, argv[1], len1);	

	if (argc == 3)
		memcpy(buf + TEXT_LCD_LINE_BUF, argv[2], len2);
	
	write(dev, buf, TEXT_LCD_MAX_BUF);

	close(dev);
	return 0;
}
*/

int main(void)
{
	unsigned char buf[TEXT_LCD_MAX_BUF];
	int dev, len1, len2;
	char str[TEXT_LCD_MAX_BUF] = " : ";
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	len1 = strlen(str);
	//assert(len1 <= TEXT_LCD_LINE_BUF, errmsg);

	dev = open(TEXT_LCD_DEVICE, O_WRONLY);
	memset(buf, ' ', TEXT_LCD_MAX_BUF);
	while(1)
	{
		sprintf(buf, "%d%s%d%s%d", tm.tm_hour, str, tm.tm_min,str,tm.tm_sec);
		printf("%d : %d : %d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		write(dev, buf, TEXT_LCD_MAX_BUF);
		sleep(1);
		tm.tm_sec = tm.tm_sec+1;
		if(tm.tm_sec >= 60)
		{
			tm.tm_sec = 0;
			tm.tm_min += 1;
		}
	}
/*	memcpy(buf, str, len1);

	write(dev, buf, TEXT_LCD_MAX_BUF);

	memset(buf, ' ', TEXT_LCD_MAX_BUF);
	char st[TEXT_LCD_MAX_BUF] = "HEllo";
	len1 = strlen(st);
	memcpy(buf, st, len1);

	sleep(2);

	write(dev, buf, TEXT_LCD_MAX_BUF);
*/
	close(dev);
	return 0;
}
