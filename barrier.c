#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

int b; //var global 
void* thread_func(void* aArgs)
{
	pthread_mutex_lock(mutex);
	b;  //seccion critica
	pthread_mutex_unlock(mutex);
	pthread_barrier_wait(&barrier);

	printf("\n Entering thread %pn", (void*)pthread_self());
	int i;
	for(i = 0 ; i < 5; i++)
		printf("\n val is %d in thread %p n", i, (void*)pthread_self());
	}

int main()
{
	pthread_t thread_1, thread_2;
	pthread_barrier_init(&barrier, NULL, 2);

	pthread_create(&thread_1, NULL, (void*)thread_func, NULL);
	printf("\n Thread %p createdn", (void*)thread_1);


	pthread_create(&thread_2, NULL, (void*)thread_func, NULL);
	printf("\n Thread %p createdn", (void*)thread_2);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	pthread_barrier_destroy(&barrier);

return 0;
}