#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    int socket_desc; 
    struct sockaddr_in server;

    /* Abre um socket */

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Nao foi possivel criar o socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; /* Escute em qualquer IP de máquina */
    server.sin_port = htons(8888);

    if(bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        printf("Erro ao fazer o bind\n");
        return 1;
    }
    printf("Bind feito com sucesso.\n");

    return 0;
}