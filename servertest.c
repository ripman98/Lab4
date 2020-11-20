#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread,c;
	struct sockaddr_in address,client;
	int opt=1;
	int addrlen=sizeof(address);
	char buffer[1024]={0};
	char *hello="Hello from server";
	char message[4000];
	char reply[4000];

	//Creating socket file descriptor
	if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		perror("Socket Failed");
		exit(EXIT_FAILURE);
	}

	//Forcefully attaching socket to the port 8888
	if(setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8888);

	//Force attaching socket to the port
	if(bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if(listen(server_fd, 3)<0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if((new_socket=accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	listen(server_fd, 3);

	valread=read(new_socket, buffer, 1024);
	printf("%s\n",buffer);
	send(new_socket,hello,strlen(hello),0);
	printf("Hello message sent \n");

	c=sizeof(struct sockaddr_in);

	while((new_socket=accept(server_fd,(struct sockaddr *)&client,(socklen_t *)&c)))
	{
		recv(new_socket,reply,4000,0);
		printf("Message from client : %s",reply);
		printf("Enter message from client :");
		fgets(message,4000,stdin);
		send(new_socket,message,4000,0);
	}

	return 0;
}
