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
    char *message, server_reply[2000];

    /* AF_INET -> IPv4, SOCK_STREAM -> tcp, 0 -> IP */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Nao foi possivel criar o socket");
        return 1;
    }

    /* informa os dados do servidor para onde vamos nos conectar */
   server.sin_addr.s_addr = inet_addr("172.217.28.132"); /* converte IP para long */
    server.sin_family = AF_INET; /* ip v4 */
    server.sin_port = htons(80);

    /* conecta-se ao servidor */
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        printf("Erro ao conectar-se\n");
        return 1;
    }

    printf("Conectado.\n");

    /* envia dados */
    message = "GET / HTTP/1.1\r\n\r\n";

    if(send(socket_desc, message, strlen(message), 0) < 0)
    {
        printf("Erro ao enviar.\n");
        return 1;
    }

    printf("Enviado com sucesso.\n");

    /* recebe dados do servidor */

    if (recv(socket_desc, server_reply, 2000, 0) < 0)
    {
        printf("Falha no recv\n");
        return 1;
    }

    printf("Resposta recebida.\n");
    printf("%s\n", server_reply);

    close(socket_desc);

    return 0;
}