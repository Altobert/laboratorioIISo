#ifndef Estructuras_h_
#define Estructuras_h_

typedef struct
{
  float vs;
  int b;
  
}visibilidad;

visibilidad var;

struct Pairs {
    float *vs;
  	int b;
};

struct StructLectura {
	char* fileName; 
	float * out;
	int len;
	int tam;
}strlectura;


struct StructParteReal {
	float * visibilidades;
	int largo;
}strParteReal;

#endif // Estructuras_h_

