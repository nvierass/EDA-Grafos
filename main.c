#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "funciones.c"


int main(){
	printf("\n\n\n******************************************\n");
	printf("****Comienzo de ejecucion del programa****\n");
	printf("******************************************\n\n\n");
	grafo* g=leerGrafo();
	if(g->matrizAdyacencia==NULL){
		free(g);
		printf("\n\n\n******************************************\n");
		printf("************+Fin del programa*************\n");
		printf("******************************************\n\n\n");
		getchar();
		return -1;
	}
	dijkstra(*g,g->idEntrada);
	dijkstra(*g,g->idKey);
	liberarGrafo(g);
	printf("\n\n\n******************************************\n");
	printf("************+Fin del programa*************\n");
	printf("******************************************\n\n\n");
	getchar();
	return 0;
}
