#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

#define As 6
#define Bs 5
#define Cs 4

int a=0, b=0, c=0;
sem_t emA, emB, emC;
sem_t rec;

void *A () {
    while(1) {
        sem_wait(&emA);
        a++;
        if(a==1) {
            sem_wait(&rec);
        }
        sem_post(&emA);
        printf("\nSC: usa o recurso A#%d", pthread_self());
        
        sem_wait(&emA);
        a--;
        sleep(1);
        if(a==0){ 
            
            sem_post(&rec);
            
        }
        sem_post(&emA);
    }
}
//funcao executada pelas Bs
void *B () {
    while(1) {
        sem_wait(&emB);
        b++;
        if(b==1) {
            sem_wait(&rec);
        }
        sem_post(&emB);
        printf("\nSC: usa o recurso B#%d", pthread_self());
        
        sem_wait(&emB);
        b--;
        sleep(1);
        if(b==0){
             sem_post(&rec);
        }
        sem_post(&emB);
    }
}

void *C () {
    while(1) {
    sem_wait(&emC);
    c++;
    if(c==1) {
        sem_wait(&rec);
    }
    sem_post(&emC);
    printf("\nSC: usa o recurso C#%d", pthread_self());
    
    sem_wait(&emC);
    c--;
    sleep(1);
    if(c==0){
         sem_post(&rec);
    }
    sem_post(&emC);
    }
}

int main(){

    pthread_t a[As], b[Bs], c[Cs];

    sem_init(&emA, 0, 1);
    sem_init(&emB, 0, 1);
    sem_init(&emC, 0, 1);
    sem_init(&rec, 0, 1);

    //Criando as threads:
    for(int i = 0; i<As; i++){
        pthread_create(&a[i], NULL, (void *)A, NULL);
    }

    for(int i = 0; i<Bs; i++){
        pthread_create(&b[i], NULL, (void *)B, NULL);
    }

    for(int i = 0; i<Cs; i++){
        pthread_create(&c[i], NULL, (void *)C, NULL);
    }

    

    // Join para esperar a finalizacao das threads:
    for(int i = 0; i < As; i++) {
        
        if(pthread_join(a[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }
    
    for(int i = 0; i < Bs; i++) {
        if(pthread_join(b[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }

    for(int i = 0; i < Cs; i++) {
        if(pthread_join(c[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }
    

    //Libera os semaforos criados:
    sem_destroy(&emA);
    sem_destroy(&emB);
    sem_destroy(&emC);
    sem_destroy(&rec);
    
    return 0;
}