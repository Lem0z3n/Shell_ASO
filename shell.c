/* shell.c -- Shell elemental. Solo admite jobs con una orden */

#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"

// Variables globales
struct listaJobs listaJobs = {NULL, NULL};

void handle_signal(int sig)
{
    //hacer algo con la signal
    ;    
}

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
    signal(SIGTTOU, SIG_IGN);
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);

    // Repetir
    while (1) {
    
    // Si no hay job_en_foreground
    if(listaJobs.fg == NULL){
	    // Comprobar finalización de jobs

        //compruebaJobs

	    // Leer ordenes
	    if (!otraOrden) {
            if (leeOrden(stdin, orden)) break;
            otraOrden = orden;
        }

	    // Si la orden no es vacia, analizarla y ejecutarla
	    if (!analizaOrden(&otraOrden,&JobNuevo,&esBg) && JobNuevo.numProgs) {
		    ejecutaOrden(&JobNuevo,&listaJobs,esBg);
        }
    }
    // (Else) Si existe job en foreground
        else{
        // Esperar a que acabe el proceso que se encuentra en foreground
        int status;
        waitpid(listaJobs.fg->progs[0].pid,&status,NULL);
	    // Recuperar el terminal de control
        tcsetpgrp(0,getpid());
	    // Si parada_desde_terminal
        if(!WIFEXITED(status)){
            // Informar de la parada
            printf("parado programa %s\n",listaJobs.fg->texto);

	        // Actualizar el estado del job y la lista como lo
            listaJobs.fg->stoppedProgs=1;
            insertaJob(&listaJobs,listaJobs.fg,0);
        }

	    // (Else) si no	        
        else{
            // Eliminar el job de la lista
            eliminaJob(&listaJobs,listaJobs.fg->progs[0].pid,0);
        }


	        

        }
	    



    }

   // Salir del programa (codigo error)
   exit(EXIT_FAILURE);
}

