/*
    Carlos Cozzolino
    DRE: 115086800
    Laboratório 5 - Computação Concorrente
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <unistd.h>
#include <time.h>

int blocked = 0;
pthread_mutex_t xmutex;
pthread_cond_t xcond;
int nThreads;
int* vector;
int sum;

void barrier (int nThreads){
    pthread_mutex_lock(&xmutex);
    if(blocked == (nThreads-1)){
        pthread_cond_broadcast(&xcond);
        blocked = 0;
    }else{
        blocked++;
        pthread_cond_wait(&xcond, &xmutex);
    }
    pthread_mutex_unlock(&xmutex);
}





int myRand ()  
{ 
    srand(time(NULL));
    int next; 
    next = ((rand() * rand()) / 100 ) % 10000 ; 
    return next ; 
} 

void* task(void* arg){
    int id = *(int*) arg;
    int sum = 0;
    
    for(int i = 0; i<nThreads; i++){
        sum = sum += vector[i];
        printf("(%dth)\n",i+1);
        printf("Thread |%d| com soma [%d]\n", id, sum);
        barrier(nThreads);
        sleep(1);
        if (id == i)
        {
            vector[i] = myRand()%9;
            printf("Thread |%d| trocou o valor de vector[%d] para [%d]\n", id, i, vector[i]);    
        }
        barrier(nThreads);
        sleep(1);
        
        
    }
    pthread_exit(NULL);
}

int main(){
    time_t t;
    srand((unsigned)time(&t));
    puts("Quantas threads deseja utilizar?\n");
    scanf("%d", &nThreads);
    pthread_t threads[nThreads];
    int id[nThreads];
    

    pthread_mutex_init(&xmutex, NULL);
    pthread_cond_init(&xcond, NULL);

    vector = (int*)malloc(sizeof(int)*nThreads);
   

    for(int i = 0; i<nThreads; i++){
        vector[i] = rand()%9;
    }
    puts("\nVetor INICIAL:\n");
    for(int i = 0; i<nThreads; i++){
        printf("[%d]", vector[i]);
    }
    puts("\n");
    sleep(1);

    for(int i = 0; i<nThreads; i++){
        id[i] = i;
        pthread_create(&threads[i], NULL, task, (void*)&id[i]);
    }
    for(int i = 0; i<nThreads; i++){
        
        pthread_join(threads[i], NULL);
    }
    puts("\nVetor Final:\n");
    for(int i = 0; i<nThreads; i++){
        printf("[%d]", vector[i]);
    }
    pthread_mutex_destroy(&xmutex);
    pthread_cond_destroy(&xcond);
    free(vector);
    return puts("\nEND\n");
}
