#include<stdio.h>
#include<string.h> //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h> //write

int main(int argc, char *argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char *message;

	//Create socket
	socket_desc=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc==-1)
	{
		printf("Could not create socket");
	}

	//Prepare the sockaddr_instructure
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_family=AF_INET;
	server.sin_port=htons(8888);

	//Bind
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server))<0)
	{
		puts("Bind Failed");
	}

	puts("Bind Done");

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connection...");
	c=sizeof(struct sockaddr_in);
	while((new_socket=accept(socket_desc,(struct sockaddr *)&client,(socklen_t *)&c)))
	{
		puts("Connection accepted");

		//Reply to client
		message="Hello Client, received your connection but I have to go bye \n";
		write(new_socket, message, strlen(message));
	}

	if(new_socket<0)
	{
		perror("Accept Failed");
	}

	return 0;
}
