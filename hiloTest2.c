#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier1; //declaro barrera

int SharedVariable = 0;

void *SimpleThread(void *args)
{
    int num,val;
    int which = (int)args;

    for(num = 0; num < 20; num++) {
        pthread_mutex_lock(&mutex1); //wait
        val = SharedVariable;
        pthread_mutex_unlock(&mutex1);
        printf("*** Hilo %d ve valor %d\n", which, val);
        SharedVariable = val + 1;
        
    }

    pthread_barrier_wait(&barrier1);

    val = SharedVariable;
    printf("Hebra %d ve final valor %d\n", which, val);
    return 0;
}

int main (int argc, char *argv[])
{
    //aca se define el numero de hilos
    int num_threads = 3;

    //Si el numero de hilos es mayor a cero, entra al if
    if (num_threads > 0) {

        //Se crean las hebras
        pthread_t threads[num_threads];
        
        int rc;
        int t;

        rc = pthread_barrier_init(&barrier1, NULL, num_threads);

        if (rc) {
            fprintf(stderr, "pthread_barrier_init: %s\n", strerror(rc));
            exit(1);
        }

        for (t = 0; t < num_threads; t++) {
            printf("In main: creating thread %ld\n", t);
            rc = pthread_create(&threads[t], NULL, SimpleThread, (void* )t);
            if (rc) {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
        }

        for (t = 0; t < num_threads; t++) {
            pthread_join(threads[t], NULL); //hebra principal espere el temrino de ejecucion de las otrs hebras
        }
    }
    else {
        printf("ERROR: The parameter should be a valid positive number.\n");
        exit(-1);
    }

    return 0;
}