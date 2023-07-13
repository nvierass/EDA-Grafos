#ifndef funciones_c
#define funciones_c

#include "funciones.h"

int leerCantidadAristas(){
	FILE* archivoEntrada=fopen("Entrada.in","r");
	if(archivoEntrada==NULL){
		printf("Error en la lectura del archivo\n");
		return -1;
	}
	int contador=0;
	char linea[16];
	while( !feof(archivoEntrada)){
		fgets(linea,16,archivoEntrada);
		contador++;
	}
	fclose(archivoEntrada);
	return contador-4;
}

grafo* leerGrafo(){
	grafo* actual=(grafo*)malloc(sizeof(grafo));
	int i,j,verticeOrigen,verticeFin,costo,cantidadAristas=leerCantidadAristas();
	if(cantidadAristas==-1){
		actual->matrizAdyacencia=NULL;
		return actual;
	}
	FILE* archivoEntrada=fopen("Entrada.in","r");
	fscanf(archivoEntrada,"%d",&(actual->vertices));
	fgetc(archivoEntrada);fgetc(archivoEntrada);
	fscanf(archivoEntrada,"%d",&(actual->idEntrada));
	fgetc(archivoEntrada);fgetc(archivoEntrada);
	fscanf(archivoEntrada,"%d",&(actual->idKey));
	fgetc(archivoEntrada);fgetc(archivoEntrada);
	fscanf(archivoEntrada,"%d",&(actual->idSalida));
	actual->idEntrada=actual->idEntrada-1;
	actual->idKey=actual->idKey-1;
	actual->idSalida=actual->idSalida-1;
	actual->matrizAdyacencia=(int**)malloc(actual->vertices*sizeof(int*));
	for(i=0;i<actual->vertices;i++){
		actual->matrizAdyacencia[i]=(int*)malloc(actual->vertices*sizeof(int));
	}
	for(i=0;i<actual->vertices;i++){
		for(j=0;j<actual->vertices;j++){
			actual->matrizAdyacencia[i][j]=0;
		}
	}
	for(i=0;i<cantidadAristas;i++){
		fscanf(archivoEntrada,"%d",&verticeOrigen);
		fscanf(archivoEntrada,"%d",&verticeFin);
		fscanf(archivoEntrada,"%d",&costo);
		actual->matrizAdyacencia[verticeOrigen-1][verticeFin-1]=costo;
		actual->matrizAdyacencia[verticeFin-1][verticeOrigen-1]=costo;
	}
	fclose(archivoEntrada);
	return actual;
}

void liberarGrafo(grafo* g){
	int i;
	for (i=0;i<g->vertices;i++){
		free(g->matrizAdyacencia[i]);
	}
	free(g->matrizAdyacencia);
	free(g);
}

void printResultado(grafo g,int origen,int* costo,int* anterior){
	FILE* archivoSalida;
	int temp[g.vertices];
	int contador=0;
	int i;
	int nodoAnterior;
	if(origen==g.idEntrada){
		archivoSalida=fopen("Salida.out","w");
		if(costo[g.idKey]==costoInfinito){
			fprintf(archivoSalida,"No se ha llegado desde la entrada a la llave\n");
			printf("No se ha llegado desde la entrada a la llave\n");
			fclose(archivoSalida);
		}
		else{
			temp[contador]=g.idKey;
			contador++;
			nodoAnterior=anterior[g.idKey];
			while(nodoAnterior!=-1){
				temp[contador]=nodoAnterior;
				contador++;
				nodoAnterior=anterior[nodoAnterior];
			}
			temp[contador]=origen;
			fprintf(archivoSalida,"Camino entrada a llave:\n");
			for(i=contador-1;i>0;i--){
				fprintf(archivoSalida," %d -",temp[i]+1);
			}
			fprintf(archivoSalida," %d\n",temp[0]+1);
			fprintf(archivoSalida,"Distancia recorrida: %d\n\n",costo[g.idKey]);
			printf("Se ha encontrado un camino desde entrada a llave\n");
			fclose(archivoSalida);
		}
	}
	else if(origen==g.idKey){
		archivoSalida=fopen("Salida.out","a");
		if(costo[g.idSalida]==costoInfinito){
			fprintf(archivoSalida,"No se ha llegado desde la llave a la salida\n");
			printf("No se ha llegado desde la llave a la salida\n");
			fclose(archivoSalida);
		}
		else{
			temp[contador]=g.idSalida;
			contador++;
			nodoAnterior=anterior[g.idSalida];
			while(nodoAnterior!=-1){
				temp[contador]=nodoAnterior;
				contador++;
				nodoAnterior=anterior[nodoAnterior];
			}
			temp[contador]=origen;
			fprintf(archivoSalida,"Camino llave a salida:\n");
			for(i=contador-1;i>0;i--){
				fprintf(archivoSalida," %d -",temp[i]+1);
			}
			fprintf(archivoSalida," %d\n",temp[0]+1);
			fprintf(archivoSalida,"Distancia recorrida: %d\n\n",costo[g.idSalida]);
			fclose(archivoSalida);
			printf("Se ha encontrado un camino desde llave a salida\n");
		}
	}
}

void dijkstra (grafo g,int inicial){
	int* costo=(int*)malloc(g.vertices*sizeof(int));
	int* anterior=(int*)malloc(g.vertices*sizeof(int));
	int* alcanzados=(int*)malloc(g.vertices*sizeof(int));
	int u,costoU,nuevoCosto;
	int i;
	//Se inicializan los valores en distancias infinitas
	for(i=0;i<g.vertices;i++){
		anterior[i]=-1;
		alcanzados[i]=0;
		if(i!=inicial){
			costo[i]=costoInfinito;
		}
		else{
			costo[i]=0;
		}
	}
	u=inicial;
	costoU=0;
	while((u!=-1) && (costoU!=costoInfinito)){
		alcanzados[u]=1;
		for(i=0;i<g.vertices;i++){
			if(g.matrizAdyacencia[u][i]>0){
				if(alcanzados[i]==0){
					nuevoCosto=costoU+g.matrizAdyacencia[u][i];
					if(nuevoCosto<costo[i]){
						anterior[i]=u;
						costo[i]=nuevoCosto;
					}
				}
			}
		}
		costoU=costoInfinito;
		u=-1;
		for(i=0;i<g.vertices;i++){
			if(alcanzados[i]==0 && costo[i]<costoU){
				costoU=costo[i];
				u=i;
			}
		}
	}
	printResultado(g,inicial,costo,anterior);
	free(costo);
	free(anterior);
	free(alcanzados);
}

#endif

