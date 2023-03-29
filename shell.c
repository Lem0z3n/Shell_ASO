/* shell.c -- Shell elemental. Solo admite jobs con una orden */

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

// Variables globales
struct listaJobs listaJobs = {NULL, NULL};



// Programa principal
int main(int argc, char **argv) {

    char orden[LONG_MAX_ORDEN + 1];
    char *otraOrden = NULL;
    struct job JobNuevo;
    int esBg=0;

    // Procesamiento argumentos de entrada (versión simplificada)
    if (argc > 1) {
        fprintf(stderr, "Uso: Shell");
        exit(EXIT_FAILURE);
    }

    // Ignorar la señal SIGTTOU, capturar SIGINT, SIGQUIT...


    // Repetir
    while (1) {
    
    // Si no hay job_en_foreground

	    // Comprobar finalización de jobs

	    // Leer ordenes
	    if (!otraOrden) {
            if (leeOrden(stdin, orden)) break;
            otraOrden = orden;
        }

	    // Si la orden no es vacia, analizarla y ejecutarla
	    if (!analizaOrden(&otraOrden,&JobNuevo,&esBg) && JobNuevo.numProgs) {
		    ejecutaOrden(&JobNuevo,&listaJobs,esBg);
        }

    // (Else) Si existe job en foreground

	    // Esperar a que acabe el proceso que se encuentra en foreground

	    // Recuperar el terminal de control

	    // Si parada_desde_terminal

	        // Informar de la parada

	        // Actualizar el estado del job y la lista

	    // (Else) si no

	        // Eliminar el job de la lista




    }

   // Salir del programa (codigo error)
   exit(EXIT_FAILURE);
}

