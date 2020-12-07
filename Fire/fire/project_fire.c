#include "../include/fpga_test.h"
#include "/root/work/achroimx6q/fpga_driver/include/fpga_dot_font.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

unsigned char quit = 0;
void user_signal1(int sig) {quit = 1;}

int fire_led(int a)
{
	unsigned char led_data1, led_data2;
	led_data1 = 15;
	led_data2 = 240;

	write(a, &led_data1, 1);   //led 실행
	usleep(500000);
	write(a, &led_data2, 1);
}
	
int main(void)
{

	unsigned char text_lcd_buf[TEXT_LCD_MAX_BUF];
	unsigned char fire_text_lcd[TEXT_LCD_MAX_BUF];
	int len1, len2;
	//char str[TEXT_LCD_MAX_BUF] = " : ";
	//char fire_time[TEXT_LCD_MAX_BUF] = "    Fire Time   ";
	//char now_time[TEXT_LCD_MAX_BUF];// = "  Current Time  ";
	char main[TEXT_LCD_MAX_BUF];

	int t_hour = 0, t_min = 0, t_sec = 0;
	int fire_h, fire_m, fire_s;

	pid_t pid;
	pid_t pid1;

	unsigned char push_sw_buf[PUSH_SWITCH_MAX_BUTTON];
	unsigned char buzzer_state;

	unsigned char step_motor_state[3];
	unsigned char step_motor_state_stop[3];

	unsigned char fire_data[4];
	memset(fire_data, 0, sizeof(fire_data));

	unsigned char led_reset;
	led_reset = 0;

	int fd, buzzer_dev, dot_dev, step_dev, led_dev, push_dev, text_lcd_dev; //open
	int fnd_dev;

	int j;
	int fire;

	int count = 0;

	char buf[10] = {0};

	int mon = 6, day = 19;

	fd = open("/dev/ext_fire_sens", O_RDWR);   //불꽃 감지 센서 오픈
	buzzer_dev = open(BUZZER_DEVICE, O_RDWR); //부저 오픈
	dot_dev = open(DOT_DEVICE, O_WRONLY);  //도트매트릭스 오픈
	step_dev = open(STEP_MOTOR_DEVICE, O_WRONLY); //스텝모터 오픈
	push_dev = open(PUSH_SWITCH_DEVICE, O_RDONLY); //푸시 스위치 오픈
	text_lcd_dev = open(TEXT_LCD_DEVICE, O_WRONLY); //text lcd open
	led_dev = open(LED_DEVICE, O_RDWR);
	fnd_dev = open(FND_DEVICE, O_RDWR);

	memset(step_motor_state, 0, sizeof(step_motor_state)); //스텝모터(on/off , right/left , fast/slow)
	step_motor_state[0] = 1; //start
	step_motor_state[1] = 0; //right
	step_motor_state[2] = 2; //speed 2 (숫자가 낮을수록 빠름)

	memset(step_motor_state_stop, 0, sizeof(step_motor_state_stop)); //스텝모터 변수 초기화
	step_motor_state_stop[0] = 0; //스텝모터 중지
	step_motor_state_stop[1] = 0;
	step_motor_state_stop[2] = 2;
	

	if(fd<0)
	{
		perror("/dev/ext_fire_sens error");
		exit(-1);
	}
	else
	{
		printf("< ext_fire_sens device has been detected >\n");
	}
	pid = fork();
	pid1 = fork();

	(void)signal(SIGINT,user_signal1);

	memset(text_lcd_buf, ' ', TEXT_LCD_MAX_BUF);
	write(text_lcd_dev, text_lcd_buf, TEXT_LCD_MAX_BUF);
	


	while(!quit)
	{
		if(pid > 0)
		{
			read(fd,buf,10);
			write(dot_dev, fpga_set_smile, sizeof(fpga_set_smile)); //dot매트릭스
			count = 0;
			if(buf[0] == '0') //불꽃이 감지가 되면
			{	
				printf("outbreak of fire ! !\n"); //불꽃 감지 출력
				buzzer_state = BUZZER_ON; //buzzer_state변수에 0(on)을 저장
				push_sw_buf[0] = 0;
				while(1)
				{
					usleep(400000);
					read(push_dev, &push_sw_buf, sizeof(push_sw_buf));
					
					buzzer_state = BUZZER_TOGGLE(buzzer_state); //부저 토글
					write(buzzer_dev, &buzzer_state, 1); //부저 실행
					//write(led_dev, &led_data, 1);   //led 실행
					fire_led(led_dev);
					write(dot_dev, fpga_fire, sizeof(fpga_fire)); //dot매트릭스 불모양  실행
					usleep(500000); //dot매트릭스 (불모양)을 깜빡거리게 하기 위함
					write(dot_dev, fpga_set_blank, sizeof(fpga_set_blank)); //dot매트릭스 끔
					count++;
					if(count > 5)
						write(step_dev,step_motor_state,3);

					if(push_sw_buf[7] == 1)
					{
						printf("--------Stop working--------\n");
						write(step_dev,step_motor_state_stop,3); //중지 실행 -> 스텝모터 중지
						buzzer_state = BUZZER_OFF; //부저 중지
						write(buzzer_dev, &buzzer_state, 1); //부저 중지
						write(dot_dev, fpga_set_smile, sizeof(fpga_set_smile)); //dot매트릭스 끔
						write(led_dev, &led_reset, 1);   //led 끄기
						break;
					}
				}	
			}	
		}
	
		else if(pid == 0)
		{
			if(t_sec >= 60)
			{
				t_sec = 0;
				t_min += 1;
			}
			if(t_min >= 60)
			{
				t_min = 0;
				t_hour += 1;
			}	
			if(t_hour >= 24)
				t_hour = 0;

			char now_time[TEXT_LCD_MAX_BUF] = "  Current Time  ";
			memset(text_lcd_buf, ' ', strlen(text_lcd_buf));
			char str[TEXT_LCD_MAX_BUF] = " : ";
			char bin[TEXT_LCD_MAX_BUF] = "     ";
			sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec, bin);
			sprintf(main,"%s%s\n",now_time,text_lcd_buf); 
			
			printf("%d : %d : %d\n", t_hour, t_min, t_sec);
			
			write(text_lcd_dev, main, strlen(main));
			
			sprintf(fire_data, "%02d%02d", mon, day);
			//printf("%s\n",fire_data);
			for(j=0;j<4;j++)
				fire_data[j] = fire_data[j] - 0x30;
			write(fnd_dev,fire_data,FND_MAX_DIGIT);

			usleep(500000);	
			t_sec = t_sec+1;

			usleep(500000);
			read(fd,buf,10);
			if(buf[0] == '0')
			{
				fire_h = t_hour;
				fire_m = t_min;
				fire_s = t_sec;
				printf("-----fire time = %d : %d : %d ------\n", fire_h, fire_m, fire_s);
				
				/*if(fire_h >= 10)
				{
					fire = ((fire_h/10)*1000+(fire_h%10)*100+(fire_m/10)*10+(fire_m)%10);
					sprintf(fire_data,"%d",fire);
					printf("%s\n",fire_data);
					for(j=0;j<4;j++)
						fire_data[j] = fire_data[j] - 0x30;
					write(fnd_dev,fire_data,FND_MAX_DIGIT);
				}
				else if(fire_h < 10)
				{
					fire = ((fire_h/10)*1000+(fire_h%10)*100+(fire_m/10)*10+(fire_m)%10);
					sprintf(fire_data,"%04d",fire);
					printf("%s\n",fire_data);
					for(j=0;j<4;j++)
						fire_data[j] = fire_data[j] - 0x30;
					write(fnd_dev,fire_data,FND_MAX_DIGIT);
				}*/
				//write(fnd_dev,fire_data,FND_MAX_DIGIT);
			}
		
			read(push_dev, &push_sw_buf, sizeof(push_sw_buf));
			if(push_sw_buf[0] == 1)
			{
				printf("--------Time set mode--------\n");
				//memset(text_lcd_buf, ' ', TEXT_LCD_MAX_BUF);
				char set[TEXT_LCD_MAX_BUF] = "    Time set    ";
				char str[TEXT_LCD_MAX_BUF] = " : ";
				char bin[TEXT_LCD_MAX_BUF] = "     ";
				memset(text_lcd_buf, ' ', strlen(text_lcd_buf));
				sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec,bin);
				sprintf(main,"%s%s\n",set,text_lcd_buf); 
				write(text_lcd_dev, main, strlen(main));
				while(push_sw_buf[2] != 1)
				{
					usleep(400000);
					read(push_dev, &push_sw_buf, sizeof(push_sw_buf));
					if(push_sw_buf[3] == 1)
					{
						if(t_hour < 23)
						{
							t_hour += 1;
							printf("%d hour\n", t_hour);
					
							sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec,bin);
							sprintf(main,"%s%s\n",set,text_lcd_buf);
							write(text_lcd_dev, main, strlen(main));
						}
						else if(t_hour >=23)
						{
							t_hour = 0;
							if(mon <= 12)
							{
								if(mon > 2 && mon%2 == 0)
								{
									if(day<30)
									{
										day += 1;
										printf("day++\n");
									}
									else if(day == 30)
									{
										mon += 1;
										day = 1;
									}
								}
								else if(mon%2 != 0)
								{
									if(day<31)
										day += 1;
									else if(day == 31)
										mon += mon;
								}
								else if(mon == 2)
								{
									if(day<28)
										day += 1;
									else if(day == 28)
									{
										mon += 1;
										day = 1;
									}
								}
							}
							else if(mon == 12)
							{
								if(day<30)
								{
									day += 1;
									printf("day++\n");
								}
								else if(day == 30)
								{
									mon = 1;
									day = 1;
								}
							}
							printf("%d hour\n", t_hour);
							sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec,bin);
							sprintf(main,"%s%s\n",set,text_lcd_buf);
							write(text_lcd_dev, main, strlen(main));
						}
					}

					else if(push_sw_buf[4] == 1)
					{
						if(t_min < 59)
						{
							t_min += 1;
							printf("%d min\n", t_min);
							sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec,bin);
							sprintf(main,"%s%s\n",set,text_lcd_buf);
							write(text_lcd_dev, main, strlen(main));	
						}
						else if(t_min >= 59)
						{
							t_min = 0;
							t_hour += 1;
							printf("%d min\n", t_min);
							sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec,bin);
							sprintf(main,"%s%s\n",set,text_lcd_buf);
							write(text_lcd_dev, main, strlen(main));
						}
					}

					else if(push_sw_buf[5] == 1)
					{
						if(t_sec < 59)
						{
							t_sec += 1;
							printf("%d sec\n", t_sec);	
							sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec,bin);
							sprintf(main,"%s%s\n",set,text_lcd_buf);
							write(text_lcd_dev, main, strlen(main));
						}
						else if(t_sec >= 59)
						{
							t_sec = 0;
							t_min += 1;
							printf("%d sec\n", t_sec);
							sprintf(text_lcd_buf, "  %d%s%d%s%d%s", t_hour, str, t_min, str, t_sec,bin);
							sprintf(main,"%s%s\n",set,text_lcd_buf);
							write(text_lcd_dev, main, strlen(main));
						}
					}	
				}
			}
			else if(push_sw_buf[6] ==1)
			{
				while(push_sw_buf[8]!=1)
				{
					usleep(400000);
					read(push_dev, &push_sw_buf, sizeof(push_sw_buf));
					if(t_sec >= 60)
					{
						t_sec = 0;
						t_min += 1;
					}
					if(t_min >= 60)
					{
						t_min = 0;
						t_hour += 1;
					}	
					if(t_hour >= 24)
						t_hour = 0;
					sleep(1);	
					t_sec = t_sec+1;
					char bin[TEXT_LCD_MAX_BUF] = "     ";
					char fire_time[TEXT_LCD_MAX_BUF] = "    Fire Time   ";
					sprintf(text_lcd_buf, "  %d%s%d%s%d%s", fire_h, str, fire_m, str, fire_s,bin);
					sprintf(main,"%s%s\n",fire_time,text_lcd_buf);
					write(text_lcd_dev, main, strlen(main));
				}
			}
		}
	}
	close(fnd_dev);
	close(buzzer_dev);
	close(step_dev);
	close(led_dev);
	close(dot_dev);
	close(text_lcd_dev);
	close(fd);
	printf("--------END--------\n");
	return 0;	
}
