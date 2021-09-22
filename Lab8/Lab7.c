#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define nThreads 4

int x = 0;
sem_t sem1, sem2;

void* A(void* t){
    int* id = (int*) t;
    sem_wait(&sem1);
    printf(" Fique a vontade. ");
    x++;
    sem_post(&sem1);
    if(x==2){
        sem_post(&sem2);
    }
    pthread_exit(NULL);
}

void* B(void* t){
    int* id = (int*) t;
    puts("\n Seja bem vindo!");
    x=0;
    sem_post(&sem1);
    pthread_exit(NULL);
}

void* C(void* t){
    int* id = (int*)t;
    sem_wait(&sem2);
    puts("\n Volte sempre!");
    pthread_exit(NULL);
}

void* D(void* t){
    int* id = (int*)t;
    sem_wait(&sem1);
    printf(" Sente-se por favor! ");
    x++;
    sem_post(&sem1);
    if(x==2){
        sem_post(&sem2);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t tid[nThreads];
    int* id[3];

    for(int i = 0; i<nThreads; i++){
        if((id[i]=malloc(sizeof(int)))==NULL){
            pthread_exit(NULL);
            return 1;
        }
        *id[i] = i;
    }

    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    if (pthread_create(&tid[1], NULL, B, (void *)id[0])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
    if (pthread_create(&tid[3], NULL, D, (void *)id[1])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
    if (pthread_create(&tid[2], NULL, C, (void *)id[2])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
    if (pthread_create(&tid[0], NULL, A, (void *)id[1])) { printf("--ERRO: pthread_create()\n"); exit(-1); }

    for(int i =0; i<nThreads; i++){
        if(pthread_join(tid[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        free(id[i]);
    }
    pthread_exit(NULL);
    

}