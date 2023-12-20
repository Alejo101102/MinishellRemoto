
#include "tcp.h"


#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()


void ejecutar_comando(int client_socket) {
    // Leer comando del cliente
    char comando[BUFSIZ];
    TCP_Read_String(client_socket, comando, BUFSIZ);
    //Verifica si capta el comando salida
    printf("Comando recibido del cliente: %s\n", comando);

    // Ejecutar comando y capturar salida
    FILE *fp = popen(comando, "r");
    char buffer[BUFSIZ];
    size_t bytesRead;

    // Enviar salida al cliente
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        TCP_Write_String(client_socket, buffer);
    }

    // Cerrar el flujo de lectura
    pclose(fp);
}

int main(int argc, char *argv[]) {
    // Verificar argumentos de línea de comandos
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    // Configurar servidor y esperar conexiones
    int server_socket = TCP_Server_Open(port);

    while (1) {
        // Aceptar conexión entrante
        printf("Esperando conexión entrante...\n");
        int client_socket = TCP_Accept(server_socket);
        printf("Conexión aceptada.\n");

        // Crear un nuevo proceso para manejar el comando
        pid_t pid = fork();
        if (pid == 0) {  // Proceso hijo

            //Verifica si entro a proceso hijo
            printf("Proceso hijo creado.\n");

            // Procesar comando
            ejecutar_comando(client_socket);

            // Cerrar conexión del cliente y terminar el proceso hijo
            TCP_Close(client_socket);
            printf("Cerró aquí.\n");

            //exit(EXIT_SUCCESS);
            break;

        } else if (pid > 0) {  // Proceso padre

            // Cerrar conexión del cliente
            TCP_Close(client_socket);

        } else {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
     }
     printf("Salió del while.\n");

     // Cerrar conexión del servidor
     TCP_Close(server_socket);
     
     //exit(-1);
     printf("Conexión servidor cerrada.\n");
     return 0;
}
