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
laboratorio que tiene como finalidad tomar una imagen, obtener su parte real (tarea realizada por las hebras)
luego binarizarla de acuerdo a umbral ingresado por consola para obtener una imagen de acuerdo al umbral o extremadamente
oscura o mas bien con un porcentaje de claridad aceptable para ser catalogada.
*/

int valor = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Problemas al utilizar barrier con mac osx-
// En linux no hay problema. Finalmente se termina desarrollo utilizando UBUNTU V20
pthread_barrier_t barrier;

int main(int argc, char *argv[]){

		
	//Variables que ingresaran por consola
	int h = 0, c=0, u=0, n=0, flag = 0;

	//Nombre del archivo que se debe leer
	char  nombreArchivo[30]   = "ifft_HLTau.raw";
	int size = 1024;
	
	//Tamanio del archivo a leer.
	int lenComplex = 2*size*size;
	
	//valor largo de la salida.
	int len =size*size;
	

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

	//Estructura creada y relacionada con la lectura. 
	strlectura.fileName = nombreArchivo;
	strlectura.len=Visibilidades;
	strlectura.out=lenComplex;
	
	//Se hace referencia a que solamente es una hebra, la cual será la principal 
	//que lea el archivo con extension .raw
	int hbPrincipal=1;
	/*Presente hebra será la encargada de leer archivo*/
	pthread_t *hebraPpal;//Referencia a hebras
	//Se asigna memoria dinamica a la hebra principal
	hebraPpal = malloc(sizeof(pthread_t)*hbPrincipal);
	pthread_create(&hebraPpal[0], NULL, leerArchivoFloat, (void*)&strlectura);
	/*Presente hebra sera la encargada de leer archivo*/
	
	
	//Se crea la cantidad de hebras que el usuario
	//ingresa por consola por mediante el atributo -h.
	pthread_t *hebras;//Referencia a hebras
	hebras = malloc(sizeof(pthread_t)*h);

	//Estructura creada y relacionada con la obtencion de la parte real. 
	strParteReal.largo = len;
	strParteReal.visibilidades = Visibilidades;	
	
	//Las n hebras creadas iran obteniendo parte real. Se pasa el parametro por referencia al metodo
	for (int i = 0; i < h; ++i){		
		pthread_create(&hebras[i], NULL, obtenerParteReal, (void*)&strParteReal);
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

