#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "Estructuras.h"


// Funcion void para leer archivo
// Entrada: char x float x int 
// Salida : float * out
void *leerArchivoFloat(void * params){
	
    //Se accede a los valores de la estructura pasada por referencia.
	struct StructLectura *my_template = (struct StructLectura*)params;

	//printf("Nombre archivo %s\n", my_template->fileName);
	//printf("Salida %.2f\n", my_template->out);
	
    FILE* fid = fopen( my_template->fileName, "rb");

    if(fid == NULL){
        printf("Error en funcion leerArchivo() no pudo leer archivo %s \n",my_template->fileName);
        exit(0);
    }
    //Se lee el archivo, y se asigna a la variable out.
    //Automaticamente queda en nuestro arreglo la informacion correspondiente. 
    fread(my_template->out, sizeof(float),my_template->len, fid);
    //Se cierra el archivo
    fclose(fid);
	// Se libera la memoria luego de haber sido usada.
    //free (params);

}

/*
Funcion obtenerParteReal real permite acceder a las posiciones del arreglo visible.
y luego retornar un arreglo solo con la parte real de la imagen.
Entrada: float X int
salida : *float
*/
void *obtenerParteReal(void * params){
	
	//Se accede a los valores de la estructura pasada por referencia.	
	struct StructParteReal *my_template = (struct StructParteReal*)params;

	printf("obtenerParteReal()\n");
	printf("Visibilidades	:%d\n",my_template->visibilidades);
	printf("Largo	:%d\n",my_template->largo);

	//Se crea un puntero float y se asigna memoria de forma dinamica.   
    float *realVector = (float*) malloc(my_template->largo * sizeof(float));
    
    //Se recorre solo las posiciones pares de *visible.
    for(int i=0, j=0 ; i<2*my_template->largo ;j++, i+=2 ){
        //Se asigna a arreglo dinamico solo los indices
        //pares, por ende sus valores.
        realVector[j]=my_template->visibilidades[i];
    }

    //return realVector;

}



void * comparar(void* pair){
    struct Pairs *my_pair = (struct Pairs*)pair;
    printf("\nfloat recibido %ld\n", (*my_pair).vs);

    // free that memory after it has been used
    free (pair);
    return NULL;
}

/*
	Método encargado de mostrar resultados utilizando un formato.
*/
void * estructuraResultados(void *val){
	int thisVal = (int)val;
	printf("id de hebra es: %i\n", thisVal);
	printf(" ----------------------------------------\n|");
	printf("|\timage\t |\tNearly black\t|\n");
	printf("|----------------|----------------------|\n");
	printf("|----------------|----------------------|\n");
	printf("|----------------|----------------------|\n");
}

//Entradas: Recibe 
//argc: que consiste en el contador de argumentos ingresados en la linea de comandos.
//El nombre del programa que se ejecuta se cuenta como un argumento
//argv: arreglo con las entradas ingresadas por linea de comandos
//*n y *flag: punteros a variables que se utilizaran para pasar valores por referencia, ambos son enteros
//Funcionamiento:
//Salida: No posee retorno, ya que es una función void
void recibirArgumentos(int argc, char *argv[], int *h,int *c,int *u, int *n, int *flag){

	int flags, opt;
	char *aux3=NULL;
	char *auxC=NULL;
	char *auxH=NULL;
	char *auxU=NULL;
	char *auxN=NULL;

	/*
		Se crea espacio de memoria para cada variable recibida por consola.
		Tambien es casteada a tipo de dato entero.
	*/
	aux3 = malloc(10*sizeof(char));
	auxC = malloc(10*sizeof(char));
	auxH = malloc(10*sizeof(char));
	auxU = malloc(10*sizeof(char));
	auxN = malloc(10*sizeof(char));

	if(argc <3){//si se ingresa un numero de argumentos menor a 3, se finaliza la ejecucion del programa
		//Debe ser 3, porque el nombre del programa se considera como un argumento, siendo -h y el valor que acompañe a -h los dos argumentos faltantes. No se considera -m (que seria el cuarto argumento) porque es un flag que puede ser especificado por el usuario o no
		printf("Se ingreso un numero incorrecto de argumentos\n");
		fprintf(stderr, "Uso correcto: %s [-h numero entero] [-m]\n",
				   argv[0]);
		   exit(EXIT_FAILURE);
	}

	//Se inicializan variables con el fin de no tener fallos por punteros en malas condiciones.	
	int H = -1, C = -1, U = -1, N = -1;
	flags = 0;

	//Se inicia un ciclo while hasta que se verifiquen todos los argumentos ingresados como entradas, 
	//los cuales se reciben con getopt()
	//int getopt (int argc, char *const *argv, const char *options): Siempre se le debe entregar argc y argv. 
	//El tercer argumento consiste en el formato de las entradas, ya sea
	//el caracter correspondiente a la opcion/entrada que se quiere recibir 
	//y además se debe indicar si dicha entrada estará acompañada de algún valor
	//Esto se indica con ":". Por lo tanto, "h:" quiere decir que se espera recibir la opcion -h 
	//y esta si o si debe estar acompañada de un valor
	//En cambio, la opcion "-b" no necesita estar acompañada de un valor
	while((opt = getopt(argc, argv, "bc:h:u:n:")) != -1) { 
	   //opt recibe el argumento leido (se hace de forma secuencial) y se ingresa a un switch
	   //En caso de que opt sea -1, se dejaran de buscar entradas y por lo tanto se podrá salir del while
	   switch(opt) {
	   
	   case 'b'://se busca la entrada -m, en caso de ser encontrado se setea el valor flags = 1, no se considera lo que se ingrese despues del flag -m
		   flags = 1;
		   break;
       
	   case 'c'://se busca la entrada -c	   		
	   		C = strtol(optarg, &auxC, 10);//se parsea el argumento ingresado junto al flag -h a entero
			if(optarg!=0 && C==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-c numero entero]\n", argv[0]); 
				exit(EXIT_FAILURE);
		    }	   		
		   break;		   

	   case 'h': //se busca la entrada -h
		   H = strtol(optarg, &auxH, 10);//se parsea el argumento ingresado junto al flag -h a entero
		   if(optarg!=0 && H==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-h numero entero] [-m]\n", argv[0]); 
				exit(EXIT_FAILURE);
		   }
		   break;

		case 'u': //se busca la entrada -u
		   U = strtol(optarg, &auxU, 10);//se parsea el argumento ingresado junto al flag -h a entero
		   if(optarg!=0 && U==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-h numero entero] [-m]\n", argv[0]); 
				exit(EXIT_FAILURE);
		   }
		   break;

		case 'n': //se busca la entrada -n
		   N = strtol(optarg, &auxN, 10);//se parsea el argumento ingresado junto al flag -h a entero
		   if(optarg!=0 && N==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-h numero entero] [-m]\n", argv[0]); 
				exit(EXIT_FAILURE);
		   }
		   break;
		

	   default: /* '?' */
		   fprintf(stderr, "Uso correcto: %s [-h numero entero] [-m]\n",
				   argv[0]);
		   exit(EXIT_FAILURE);
	   }
	}

	if(flags==1){//si se encontro un flag -m, se setea la variable global flag = 1, respecto al scope del proceso principal
		(*flag) = 1;
	}

	(*h) = H; //se iguala la variable n a N, para poder acceder al valor en el main
	(*c) = C; //se iguala la variable c a C, para poder acceder al valor en el main
	(*u) = U; //se iguala la variable u a U, para poder acceder al valor en el main
	(*n) = N; //se iguala la variable n a N, para poder acceder al valor en el main

	if(N<=0){
		printf("El valor que acompaña a -h debe ser mayor a 0\n");
		fprintf(stderr, "Uso correcto: %s [-h nchild] [-m]\n", argv[0]); //si el valor que acompaña a -h es negativo, se retorna un error
		exit(EXIT_FAILURE);
	}


}