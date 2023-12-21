# Minishell Remoto

Proyecto de shell remoto que facilita la conexión entre cliente y servidor. Este sistema permite visualizar las respuestas del servidor a través 
de la terminal de comandos del cliente.

## Uso

Principalmente se usa el archivo shell_client.c shell_server.c tcp.h y tcp.c , siendo estos últimos dos los protocolos de conexión brindados por 
el profesor John Sanabria, aunque el resto de archivos también se deben descargar con el fin de hacer más pruebas y estar el directorio más
completo.

Para poder hacer uso del proyecto, abre dos terminales, en una se abre y se ejecuta el servidor, en la otra se abre y se ejecuta el cliente.

## Archivos principales des proyecto

- shell_client.c: Código fuente del cliente.
- shell_server.c: Código fuente del servidor.
- tcp.h: Encabezado que contiene las definiciones de funciones y estructuras para la comunicación TCP. (Brindado por Prof. John Sanabria).
- tcp.c: Implementación de las funciones definidas en tcp.h para la comunicación TCP. (Brindado por Prof. John Sanabria).

El resto de archivos también son de propiedad del Prof. John Sanabria.
