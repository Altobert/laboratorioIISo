#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int valor = 5;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *sumar(void *id){
	(int)id;
	printf("id es: %i\n", id);
	pthread_mutex_lock(&mutex);//provee exclusion mutua
	valor++;
	pthread_mutex_unlock(&mutex);
	printf("el valor es: %i\n", valor);
}
int main(){
	pthread_t *h1;
	h1 = malloc(sizeof(pthread_t)*5);
	char g;
	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&h1[i], NULL, sumar, (void *)i );

	}
	for (int i = 0; i < 5; ++i)
	{
		pthread_join(h1[i], NULL);
	}
	
	return 0;
}