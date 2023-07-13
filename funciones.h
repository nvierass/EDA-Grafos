#ifndef funciones_h
#define funciones_h

#define costoInfinito 100000000

typedef struct datosGrafo{
	int** matrizAdyacencia;
	int vertices;
	int idEntrada;
	int idSalida;
	int idKey;
} grafo;	

void dijkstra (grafo g,int inicial);
void printResultado(grafo g,int origen,int* costo,int* anterior);
void liberarGrafo(grafo* g);
grafo* leerGrafo();
int leerCantidadAristas();

#endif