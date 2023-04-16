/* shell1.c -- elemental.  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 10
#define LONG_MAX_ARG 100
char *copiarargumento(char *buf);
int ejecutaorden (char *argv[]);

int main(int argc, char **argv) {
    char *listaargumentos[MAX_ARGS + 1];
    int numargs, status;
    char buffer[LONG_MAX_ARG];


    if (argc > 1) {
        fprintf(stderr, "argumentos no esperados; Uso: shell \n");
        exit(1);
    }

    numargs = 0;
    while (numargs < MAX_ARGS) {
        /* solicitar orden y argumentos de forma incremental. argv[0]
        es el comando a ejecutar, el resto los argumentos */
        printf("argv[%d]? ", numargs);
        if ( fgets(buffer, LONG_MAX_ARG, stdin) && (buffer[0] != '\n')){
            listaargumentos[numargs++] =  copiarargumento(buffer);
        } else {
            if (numargs > 0) {
                listaargumentos[numargs] = NULL; /* marcar el final de lista */
                status=ejecutaorden(listaargumentos); /* ejecutar orden */
                printf("ejecutada orden %s, estado %d\n", ...); /*completar*/
                numargs = 0;
            }
        }
    }
    return 0;
}


char *copiarargumento(char *buf)
{
    char *ptrc;
    buf[strlen(buf)-1] = '\0'; /* elimina caracter \n */
    ptrc = malloc(strlen(buf)+1);
    if (ptrc == NULL){
        fprintf(stderr, "no hay memoria disponible en el heap\n");
        exit(1);
    }
    strcpy(ptrc,buf); /* copia caracteres */
    return ptrc;

}

int ejecutaorden (char *argv[])
{
 /*
  * Utilizar fork, "exec" y wait para 
  * ejecutar la orden en un nuevo proceso hijo
  *
  */
   
   /* completar */

}