#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tcp.h"

void ejecutar_comando(int client_socket) {
    // Leer comando del cliente
    char comando[BUFSIZ];
    TCP_Read_String(client_socket, comando, BUFSIZ);

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
            // Procesar comando
            ejecutar_comando(client_socket);

            // Cerrar conexión del cliente y terminar el proceso hijo
            TCP_Close(client_socket);
            exit(EXIT_SUCCESS);
        } else if (pid > 0) {  // Proceso padre
            // Cerrar conexión del cliente
            TCP_Close(client_socket);
        } else {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
     }
     // Cerrar conexión del servidor
     TCP_Close(server_socket);
     return 0;
}
