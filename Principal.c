#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
Laboratorio II Sistemas Operativos.
Principalmente se traba de llevar la funcionalidad del laboratorio anterior 
pero en esta oportunidad utilizar hebras o hilos (threads)
*/

void printGlobal();
void obtenerParteReal();
void binarizarImagen();
void analizarProiedades();
void estructuraResultados();
void recibirArgumentos(int argc, char *argv[], int *h,int *c,int *u, int *n, int *flag);

int main(int argc, char *argv[]){

	int h = 0, c=0, u=0, n=0, flag = 0;
	recibirArgumentos(argc, argv, &h, &c, &u, &n, &flag);
	if(flag==1){
		printf("Se utilizo flag -b\n");
	}
	printf("El argumento de flag -h es: %d\n", h);	
	printf("El argumento de flag -c es: %d\n", c);	
	printf("El argumento de flag -u es: %d\n", u);	
	printf("El argumento de flag -n es: %d\n", n);	
	//printGlobal(10);
}

/*void printGlobal(int valor){
	printf("Valor de variable global: %d\n", valor);
}*/


//Entradas: Recibe 
//argc: que consiste en el contador de argumentos ingresados en la linea de comandos. El nombre del programa que se ejecuta se cuenta como un argumento
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
	//En cambio, la opcion "-m" no necesita estar acompañada de un valor
	while((opt = getopt(argc, argv, "bc:h:u:n:")) != -1) { 
	   //opt recibe el argumento leido (se hace de forma secuencial) y se ingresa a un switch
	   //En caso de que opt sea -1, se dejaran de buscar entradas y por lo tanto se podrá salir del while
	   switch(opt) {
	   
	   case 'b'://se busca la entrada -m, en caso de ser encontrado se setea el valor flags = 1, no se considera lo que se ingrese despues del flag -m
		   flags = 1;
		   break;
       
	   case 'c':	   		
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

		case 'u': //se busca la entrada -h
		   U = strtol(optarg, &auxU, 10);//se parsea el argumento ingresado junto al flag -h a entero
		   if(optarg!=0 && U==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-h numero entero] [-m]\n", argv[0]); 
				exit(EXIT_FAILURE);
		   }
		   break;

		case 'n': //se busca la entrada -h
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
	(*u) = U;
	(*n) = N;

	if(N<=0){
		printf("El valor que acompaña a -h debe ser mayor a 0\n");
		fprintf(stderr, "Uso correcto: %s [-h nchild] [-m]\n", argv[0]); //si el valor que acompaña a -h es negativo, se retorna un error
		exit(EXIT_FAILURE);
	}


}