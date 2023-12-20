#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp.h"

int main(int argc, char *argv[]) {
    // Verificar argumentos de línea de comandos
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <host> <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *host = argv[1];
    int port = atoi(argv[2]);

    while (1) {
        // Conectar al servidor
        int sockfd = TCP_Open(host, port);

        char comando[BUFSIZ];
        // Leer comando del usuario
        printf("> ");
        fgets(comando, BUFSIZ, stdin);
        comando[strlen(comando) - 1] = '\0';

        // Salir si el usuario escribe "salida"
        if (strcmp(comando, "salida") == 0) {
            // Cerrar conexión y salir del bucle
            TCP_Close(sockfd);
            printf("Conexión cerrada en el cliente.\n");
            break;
        }

        // Enviar comando al servidor
        TCP_Write_String(sockfd, comando);

        // Recibir y mostrar la salida del servidor
        char respuesta[BUFSIZ];
        TCP_Read_String(sockfd, respuesta, BUFSIZ);
        printf("Respuesta del servidor:\n%s\n", respuesta);

        // Cerrar conexión
        TCP_Close(sockfd);
    }

    return 0;
}
