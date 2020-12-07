#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "220.149.128.100"
#define SERV_PORT 4061
#define BACKLOG 10

#define end "exit"
#define INIT_MSG "=====================\nHello! I'm P2P File Sharing Server...\nPlease, LOG-IN!\n=====================\n"
#define USER1_ID "user1"
#define USER1_PW "passwd1"
#define USER2_ID "user2"
#define USER2_PW "passwd2"
#define Failms "LOG-IN FAIL .. Incorrect ID or PW .." /* fail message */
#define Sucms1 "LOG-IN Success! Hi [user1] *^^*" /* user1 login message */
#define Sucms2 "LOG-IN Success! Hi [user2] *^^*" /* user2 login message */
#define chatst "====== Welcome to Chatting Room ======" /*chat start message */
#define file "FILE"

#define MAXLINE 512
#define MAX_SOCK 3

int main(int argc, char *argv[])
{
	/* listen of sock_fd, new connection on new_fd */
	int sockfd, new_fd;
	int val = 1;	
	pid_t pid, pid1 ;
	int a = 0;
	int user;

	struct sockaddr_in client_addr;

	/* my address information, address where I run this program */
	struct sockaddr_in my_addr;

	/* remote address information */
	struct sockaddr_in their_addr;
	unsigned int sin_size;

	/* buffer */
	int rcv_byte;

	char buf[512];
	char buf1[512];

	char id[20];
	char pw[20];
	char clientip[20];
	char clientport[20];

	char msg[512];

	char message[512];

	
	int fds[2];
	int fds2[2];
	int f_fds1[2];
	int f_fds11[2];
	int f_fds2[2];
	int f_fds22[2];
		
	char user1mes[20] = "<User1> ";
	char user2mes[20] = "<User2> ";
	/* socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("Server-socker() error lol!");
		exit(1);
	}
	else printf("Server-socker() sockfd is OK...\n");

	/* host byte order */
	my_addr.sin_family = AF_INET;

	/* short, network byte order */
	my_addr.sin_port = htons(SERV_PORT);

	//my_addr.sin_addr.s_addr = inet_addr(SERV_IP);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	/* zero the rest of the struct */
	memset(&(my_addr.sin_zero), 0, 8);

	/* to prevent 'Address already in use...'*/
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val)) < 0){
		perror("setsockopt");
		close(sockfd);
		return -1;
	}

	/* bind */
	if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("Server-bind() error lol!");
		exit(1);
	}
	else printf("Server-bind() is OK...\n");

	/* listen */
	if(listen(sockfd, BACKLOG) == -1)
	{
		perror("listen() error lol!");
		exit(1);
	}
	else printf("listen() is OK...\n\n");

	pipe(fds);
	pipe(fds2);
	pipe(f_fds1);
	pipe(f_fds11);
	pipe(f_fds2);
	pipe(f_fds22);
	if(pipe(fds) == -1)
	{
		perror("pipe error!!\n");
		exit(1);
	}
	if(pipe(fds2) == -1)
	{
		perror("pipe error!!\n");
		exit(1);
	}
	if(pipe(f_fds1) == -1)
	{
		perror("pipe error!!\n");
		exit(1);
	}
	if(pipe(f_fds11) == -1)
	{
		perror("pipe error!!\n");
		exit(1);
	}
	if(pipe(f_fds2) == -1)
	{
		perror("pipe error!!\n");
		exit(1);
	}
	if(pipe(f_fds22) == -1)
	{
		perror("pipe error!!\n");
		exit(1);
	}

	while(1)
	{
		
		/* ...other codes to read the received data... */
		sin_size = sizeof(struct sockaddr_in);
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		pid = fork();

		if(pid == 0)
		{
			printf("accept() is OK...\n\n");
			close(sockfd);
			/* send INIT_MSG */
			send(new_fd, INIT_MSG, strlen(INIT_MSG) + 1, 0);
			
			rcv_byte = recv(new_fd, buf, sizeof(buf), 0);			
			rcv_byte = recv(new_fd, buf1, sizeof(buf1), 0);
			
			if(strcmp(buf, USER1_ID)==0 && strcmp(buf1, USER1_PW)==0)
			{
				printf("%s\n\n", Sucms1);
				int suc = send(new_fd, Sucms1, strlen(Sucms1)+1, 0);
				if(suc != -1)
				{
					recv(new_fd, clientip, sizeof(clientip), 0);
					clientip == clientip;
					recv(new_fd, clientport, sizeof(clientport), 0);
					clientport == clientport;
				}
				send(new_fd, chatst, strlen(chatst)+1, 0);
				user = 1;
				
			}
			else if(strcmp(buf, USER2_ID)==0 && strcmp(buf1, USER2_PW)==0)
			{	
				printf("%s\n\n", Sucms2);
				int suc2 = send(new_fd, Sucms2, strlen(Sucms2)+1, 0);
				if(suc2 != -1)
				{
					recv(new_fd, clientip, sizeof(clientip), 0);
					clientip == clientip;
					recv(new_fd, clientport, sizeof(clientport), 0);
					clientport == clientport;
				}
				send(new_fd, chatst, strlen(chatst)+1, 0);
				user = 2;
				
			}
		
			else
			{
				printf("%s\n\n", Failms);
				send(new_fd, Failms, strlen(Failms)+1, 0);
				user = 0;
				
			}
			
			if(user > 0)
			{
				printf("%s\n",chatst);

				pid1 = fork();
				while(1)
				{
					if (pid1 > 0)
					{
						rcv_byte = recv(new_fd, message, sizeof(message), 0);
						if(user == 1)
						{
							if(rcv_byte != -1)
							{
								if(strcmp(message, end) != 0)
								{
									printf("<User1> %s\n",message);
									write(fds[1],message,MAXLINE);
									if(!(strstr(message,file)==NULL))
									{
										write(f_fds1[1],clientip,20);
										write(f_fds11[1],clientport,20);
									}
									memset(message, 0, 512);
								}
								else if(strcmp(message, end) == 0)
								{
									printf("User1 Bye~\n");
									exit(0);
								}
							}
						}
						else if(user == 2)
						{
							if(rcv_byte != -1)
							{
								if(strcmp(message, end) != 0)
								{
									printf("<User2> %s\n",message);
									write(fds2[1],message, MAXLINE);
									if(!(strstr(message,file)==NULL))
									{
										write(f_fds2[1],clientip,20);
										write(f_fds22[1],clientport,20);
									}
									memset(message, 0, 512);
								}
								else if(strcmp(message, end) == 0)
								{
									printf("User2 Bye~\n");
									exit(0);
								}
							}
						}
					}
					else if(pid1 == 0)
					{
						char user1mes[20] = "<User1> ";
						char user2mes[20] = "<User2> ";
						if(user == 1)
						{
							read(fds2[0],message,sizeof(message));
							strcat(user2mes,message);
							send(new_fd,user2mes,strlen(user2mes)+1,0);
							if(!(strstr(message, file) == NULL))
							{
								read(f_fds2[0],clientip,sizeof(clientip));
								send(new_fd,clientip,strlen(clientip)+1,0);
								read(f_fds22[0],clientport, sizeof(clientport));
								sleep(1);
								send(new_fd,clientport,strlen(clientport)+1,0);
							}
							memset(user2mes,0,512);
						}
						else if(user == 2)
						{
							read(fds[0],message, sizeof(message));
							strcat(user1mes, message);
							send(new_fd, user1mes, strlen(user1mes)+1,0);
							if(!(strstr(message,file)==NULL))
							{
								read(f_fds1[0],clientip,sizeof(clientip));
								send(new_fd,clientip,strlen(clientip)+1,0);
								read(f_fds11[0],clientport,sizeof(clientport));
								sleep(1);
								send(new_fd,clientport,strlen(clientport)+1,0);
							}
							memset(user1mes, 0,512);
						}
					}
				}
			}
			close(new_fd);
			exit(0);
		}
		close(new_fd);
	}	
	close(new_fd);
	close(sockfd);
	return 0;
}
