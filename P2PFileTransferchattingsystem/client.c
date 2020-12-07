#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BACKLOG 10

#define end "exit" /* exit message */
#define SERV_IP "220.149.128.100"
#define MY_IP "220.149.128.101"
#define SERV_PORT 4061
#define MYPORT 4062
#define MY_PORT "4062"
#define MAXLINE 512
#define file "FILE"

int main(int argc, char *argv[])
{
	int sockfd,new_fd, fsendfd, frecvfd; /* will hole the destination addr */
	struct sockaddr_in dest_addr;
	struct sockaddr_in their_addr;
	struct sockaddr_in my_addr;
	unsigned int sin_size;
	int num, state;

	pid_t pid, pid1;

	int val = 1;
	int rcv_byte = 0;
	char select[10];
	char nselect[10];
	char reselectfile[100];
	char buf[512];
	
	char user2ip[20];
	char user2port[20];
	char id[20];
	char pw[20];
	char result[512];
	char chatst[512];
	char message1[512];
	char message2[512];
	char yourip[20];
	char yourport[20];
	char User2fname[3][10];
	char refname[30];
	char filemessage[100];
	pid_t wait;

	FILE *eunjin, *fp;
	char c,fname[3][20] = {"FILE1_1", "FILE2_1", "FILE3_1"};
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd == -1)
	{
		perror("Client-socker() error lol!");
		exit(1);
	}
	else printf("Client-socker() sockfd is OK.../n");

	/* host byte order */
	dest_addr.sin_family = AF_INET;

	/*short, netword byte order */
	dest_addr.sin_port = htons(SERV_PORT);
	dest_addr.sin_addr.s_addr = inet_addr(SERV_IP);

	/* zero the rest of the struct */
	memset(&(dest_addr.sin_zero), 0, 8);

	/* connect */
	if(connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("Client-connect() error lol\n\n");
		exit(1);
	}
	else printf("Client-connect() is OK...\n\n");

	/* receive INIT_MSG */
	rcv_byte = recv(sockfd, buf, sizeof(buf), 0);
	printf("%s\n", buf);

	printf("ID : ");
	scanf("%s", id);
	send(sockfd, id, strlen(id)+1, 0);
	printf("PW : ");
	scanf("%s", pw);
	send(sockfd, pw, strlen(pw)+1, 0);

	rcv_byte = recv(sockfd, result, sizeof(result), 0);
	printf("%s\n\n", result);
	if(rcv_byte != -1)
	{
		send(sockfd, MY_IP, strlen(MY_IP)+1, 0);
		send(sockfd, MY_PORT, strlen(MY_PORT)+1,0);
	}
	rcv_byte = recv(sockfd, chatst, sizeof(chatst), 0);
	printf("%s\n\n", chatst);
	
	pid = fork();
	while(1)
	{
		if (pid > 0)
		{
			printf(">> ");
			fgets(message1, sizeof(message1), stdin);
			message1[strlen(message1)-1] = '\0';
			send(sockfd, message1, strlen(message1)+1,0);
			if(strcmp(message1, end) == 0)
			{
				exit(0);
			}

			if(!(strstr(message1,file)==NULL))
			{
				pid1 = fork();
				if(pid1 == 0)
				{
					close(sockfd);
					fsendfd = socket(AF_INET, SOCK_STREAM, 0);
					if(fsendfd == -1)
					{
						perror("User1 Server-socker() error lol!");
						exit(1);
					}
					else printf("User1 Server-socker() fsendfd is OK...\n");
					my_addr.sin_family = AF_INET;
					my_addr.sin_port = htons(MYPORT);
					my_addr.sin_addr.s_addr = INADDR_ANY;
					memset(&(my_addr.sin_zero),0,8);

					if(setsockopt(fsendfd, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val))<0)
					{
						perror("setsockpot");
						close(fsendfd);
						return -1;
					}
					if(bind(fsendfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
					{
						perror("User1 Server-bind() error lol!");
						exit(1);
					}
					else printf("User1 Server-bind() is OK...\n");

					if(listen(fsendfd, BACKLOG) == -1)
					{
						perror("User1 listen() error lol!");
						exit(1);
					}
					else printf("User1 listen() is OK...\n");

					sin_size = sizeof(struct sockaddr_in);
					new_fd = accept(fsendfd, (struct sockaddr *)&their_addr, &sin_size);
					for(int h = 0; h<3; h++)
					{
						recv(new_fd, User2fname[h],sizeof(User2fname[h]),0);
					}
					printf("\n-------FILE MODE START-------\n");
					printf("-------FILE LIST-------\n");
					for(int f = 0 ;f<3;f++)
					{
						printf("(%d) %s\n", f+1, User2fname[f]);
					}
					printf("\nPlease select a FILE >> ");
					scanf("%s",nselect);
					send(new_fd,nselect,strlen(nselect)+1,0);
					recv(new_fd,reselectfile,sizeof(reselectfile),0);
					recv(new_fd,refname,sizeof(refname),0);
					sleep(1);
					printf("-------What's in the file-------\n");
					printf("<FILE Name> : %s ",refname);
					printf(", <FILE Contents> : %s\n",reselectfile);

					printf("-------Saving FILE-------\n");
					fp = fopen(refname,"w");
					if(fp == NULL)
					{
						printf("File open error!\n");
						exit(1);
					}
					fputs(reselectfile, fp);
					fclose(fp);
					fp = fopen(refname,"r");
					if(fp == NULL)
					{
						printf("File open error!\n");
						exit(1);
					}
					while((c=fgetc(fp))!=EOF)
					{
						fputc(c,stdout);
					}
					fclose(fp);
					for(int m = 0;m<3;m++)
					{
						sleep(1);
						printf(" .");
					}
					printf("\nSave Success ! ! \n");
					printf("-------File Mode End-------\n");
					exit(0);
				}
				else if(pid1>0)
				{
					do
					{
						wait = waitpid(pid1, &state, WNOHANG);
						sleep(1);
					}while(wait==0);
					continue;
				}
			}
		}
		else if( pid == 0)
		{
			rcv_byte = recv(sockfd, message2, sizeof(message2),0);
			if(strlen(message2)>1 && rcv_byte != -1)
			{
				if(!(strstr(message2,file)==NULL))
				{
					pid1=fork();
					if(pid1 == 0)
					{
						printf("%s\n",message2);
						recv(sockfd, yourip, sizeof(yourip),0);
						recv(sockfd, yourport, sizeof(yourport),0);
							
						frecvfd = socket(AF_INET, SOCK_STREAM, 0);
						if(frecvfd == -1)
						{
							perror("Clinet-socker() error lol!");
							exit(1);
						}
						else printf("\nUser1 Client-socker() frecvfd is OK...\n");
	
						dest_addr.sin_family = AF_INET;
						dest_addr.sin_port = htons(atoi(yourport));
						dest_addr.sin_addr.s_addr = inet_addr(yourip);
						memset(&(dest_addr.sin_zero),0,8);
	
						if(connect(frecvfd,(struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
						{
							perror("User1 Client-connect() error lol\n\n");
							exit(1);
						}
						else printf("User1 Client-connect() is OK...\n\n");
	
						close(sockfd);
					
						for(int h = 0 ;h<3;h++)
						{
							eunjin = fopen(fname[h], "w");
							fprintf(eunjin, "Num %d File >> Now Time %d : %d\n",h+1,h+10,h+23);
							sleep(1);
							send(frecvfd, fname[h],strlen(fname[h])+1,0);
							fclose(eunjin);
						}
					
						while((c = fgetc(eunjin)) != EOF)
						{
							fputc(c,stdout);
						}
						
						recv(frecvfd, select,sizeof(select),0);
						num = atoi(select);
						sleep(1);
						if(num == 1)
						{
							printf("%dst file has been requested!\n", num);
							eunjin = fopen(fname[0],"r");
							if(eunjin == NULL)
								perror("Error opening file\n");
							else
							{
								fgets(filemessage,100,eunjin);
								sleep(1);
								send(frecvfd,filemessage,strlen(filemessage)+1,0);
								sleep(1);
								send(frecvfd,fname[0],strlen(fname[0])+1,0);
								printf("Send Success ! ! \n\n");
							}
						}
						else if(num == 2)
						{
							printf("%dnd file has been requested!\n",num);
							eunjin = fopen(fname[1],"r");
							if(eunjin == NULL)
								perror("Error opening file\n");
							else
							{
								fgets(filemessage,100,eunjin);
								sleep(1);
								send(frecvfd,filemessage,strlen(filemessage)+1,0);
								send(frecvfd,fname[1],strlen(fname[1])+1,0);
								printf("Send Success ! ! \n\n");
							}
						}
						else
						{
							printf("%drd file has been requested!\n",num);
							eunjin = fopen(fname[2],"r");
							if(eunjin == NULL)			
								perror("Error opening file\n");
							else
							{
								fgets(filemessage,100,eunjin);
								sleep(1);
								send(frecvfd,filemessage,strlen(filemessage)+1,0);
								send(frecvfd,fname[2],strlen(fname[2])+1,0);
								printf("Send Success ! ! \n\n");
							}
						}
						exit(0);
					}
					else
					{
						do
						{
							wait = waitpid(pid1,&state,WNOHANG);
							sleep(1);
						}while(wait==0);
						continue;
					}
				}
				else
				{
					printf("\r%s\n",message2);
					memset(message2, 0, 512);
					if(strcmp(message2, end) == 0)	
					{
						exit(0);
					}
				}
			}
		}
	}
	close(fsendfd);
	close(frecvfd);
	close(sockfd);
	return 0;
}
