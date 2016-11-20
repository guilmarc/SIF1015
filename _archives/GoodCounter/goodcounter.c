
/*
 * goodcnt.c - A properly synchronized counter program
 */
/* $begin goodcnt */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITERS 10000000
void *count(void *arg);

/* shared variables */
unsigned int cnt; /* counter */
sem_t mutex;      /* semaphore that protects counter */

int main()
{
    pthread_t tid1, tid2;

    //Création d'une sémaphone nommée qui fonctionne bien en OSX.
    //mutex = sem_open("/semaphore", O_CREAT, 0644, 1);

    sem_init(&mutex, 0, 1);  /* mutex = 1 0 = Toujours 0, 1 = Une ressource à partager dans un seul pipeline (la variable cnt)  */
    pthread_create(&tid1, NULL, count, NULL);
    pthread_create(&tid2, NULL, count, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if (cnt != (unsigned)NITERS*2)
        printf("BOOM! cnt=%d\n", cnt);
    else
        printf("OK cnt=%d\n", cnt);
    exit(0);

    //Au besoin on pourrait utiliser sem_detroy() pour détruire le sémaphore
}

/* thread routine */
void *count(void *arg)
{
    int i;
    for (i = 0; i < NITERS; i++) {
        sem_wait(&mutex);  //On protège (bloque) la ressoure
        cnt++;
        sem_post(&mutex); //Important pour libérer la ressource
    }
    return NULL;
}

