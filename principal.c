#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "funciones.h"
#include "Estructuras.h"

/*
Laboratorio II Sistemas Operativos.
Objetivo: Utilizando los conceptos de hilos, barriers, se implementa
laboratorio con funciona
*/

int valor = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Problemas al utilizar barrier con mac osx
pthread_barrier_t barrier;

void *sumar(void *id){
	int mival = (int)id;
	printf("id de hebra es: %i\n", mival);
	pthread_mutex_lock(&mutex);//provee exclusion mutua
	valor++;
	pthread_mutex_unlock(&mutex);
	printf("El valor es: %i\n", valor);
}


int main(int argc, char *argv[]){

	//Declaracion de estructuras
	struct Pairs 	 *pair;
	

	//Variables que ingresaran por consola
	int h = 0, c=0, u=0, n=0, flag = 0;

	//Nombre del archivo que se debe leer
	char  nombreArchivo[30]   = "ifft_HLTau.raw";
	int size = 1024;
	//Tamanio del archivo a leer.
	int lenComplex = 2*size*size;
	//valor largo de la salida.
	int len =size*size;
	printf("len %d\n",len);

	recibirArgumentos(argc, argv, &h, &c, &u, &n, &flag);
	if(flag==1){
		//Si se agrega el flag -b, entonces, se muestra tabla de resultados
		int valor=1000;
		//pasando valor por referencia a funcion estructuraResultados 
		estructuraResultados((void *)valor);
	}
	printf("-h cantidad de hebras  : %d\n", h);	
	printf("-c cantidad de imagenes: %d\n", c);	
	printf("-u umbral para binarizar es: %d\n", u);	
	printf("-n umbral para clasificacion es: %d\n", n);	
	printf("-b bandera que indica si mostrar o no resultados.\n");	

	//Se crea barrera para la cantidad de hebras 
	//creadas por linea de comandos.
	pthread_barrier_init(&barrier, NULL, h);

	//Memoria dinamica creada para recibir los valores. 
	int *Visibilidades    = (int *)malloc(sizeof(int )*lenComplex);
	int *VisibilidadesOut = (int *)malloc(sizeof(int )*lenComplex);

	printf("Visibilidades %d\n", Visibilidades);

	strlectura.fileName = nombreArchivo;
	strlectura.len=Visibilidades;
	strlectura.out=lenComplex;
	
	//Se hace referencia a que solamente es una hebra, la cual será la principal 
	//que lea el archivo con extension .raw
	int hbPrincipal=2;
	/*Presente hebra sera la encargada de leer archivo*/
	pthread_t *hebraPpal;//Referencia a hebras
	//Se asigna memoria dinamica a la hebra principal
	hebraPpal = malloc(sizeof(pthread_t)*hbPrincipal);
	pthread_create(&hebraPpal[0], NULL, leerArchivoFloat, (void*)&strlectura);
	/*Presente hebra sera la encargada de leer archivo*/
	
	strParteReal.largo = len;
	strParteReal.visibilidades = Visibilidades;

	pthread_create(&hebraPpal[1], NULL, obtenerParteReal, (void*)&strParteReal);
	pthread_join(hebraPpal[0], NULL);
	pthread_join(hebraPpal[1], NULL);


	//Se crea la cantidad de hebras que el usuario
	//ingresa por consola por medi del atributo h.
	pthread_t *hebras;//Referencia a hebras
	hebras = malloc(sizeof(pthread_t)*h);
	
	
	//Las hebras creadas iran sumando. Se pasa el parametro por referencia al metodo
	for (int i = 0; i < h; ++i){
		pthread_create(&hebras[i], NULL, sumar, (void *)i );
	}

	//La cantidad de hebras contenidas en h se iran cerrando.
	for (int i = 0; i < h; ++i){
		pthread_join(hebras[i], NULL);
	}

	//Funcionalidad o parametro que permite destruir barrier.
	pthread_barrier_destroy(&barrier);

	//Se libera memoria dinamica asignada.
	free(Visibilidades);
	free(VisibilidadesOut);

	return 0;
}

