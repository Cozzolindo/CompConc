#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

#define N 5
#define W1 1
#define W2 1
#define NA 3

sem_t s, x, h;
int aux = 0, k = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;


void wait() {
//pre-condicao: a thread corrente detem o lock de ’m’
    for(;;){
        sem_wait(&x);
        aux++;
        
        
        sem_post(&x);
        pthread_mutex_unlock(&m);
        printf("\n == A mimir == [%d] == \n", pthread_self());
        sleep(1);
        sem_wait(&h);
        sem_post(&s);
        pthread_mutex_lock(&m);
        printf("\n == Acordar ==  |%d| ==\n", pthread_self());
    }
}

void notify() {
    
    for(;;){
        sem_wait(&x);
        if (aux > 0) {
            
            aux--;
           
            sem_post(&h);
            sem_wait(&s);
            
        }
         printf("\nThread [%d] foi liberada pelo notify!", pthread_self());
        //sleep(1);
        sem_post(&x);
    }
    
}

void notifyAll() {
    
    for(;;){
        sem_wait(&x);
        
        for (int i = 0; i < aux; i++)
            sem_post(&h);
        while (aux > 0) {
           
            aux--;
            sem_wait(&s);

        }
        printf("Thread [%d] foi liberada pelo notifyAll!\t", pthread_self());
         
        sem_post(&x);
    }
    
}



int main(){
    
    pthread_t  wa1[W1], not[N], notAll[NA], wa2[W2];

    sem_init(&x, 0, 1);
    sem_init(&s, 0, 0);
    sem_init(&h, 0, 0);
    

    //Criando as threads:

    
    
     for(int i = 0; i<W1; i++){
        pthread_create(&wa1[i], NULL, (void *)wait, NULL);
    }

    
    for(int i = 0; i<N; i++){
        pthread_create(&not[i], NULL, (void *)notify, NULL);
    }

    for(int i = 0; i<W2; i++){
        pthread_create(&wa2[i], NULL, (void *)wait, NULL);
    }
    
    
    for(int i = 0; i<NA; i++){
        pthread_create(&notAll[i], NULL, (void *)notifyAll, NULL);
    }

   
    

    

    // Join para esperar a finalizacao das threads:

    
    
    
    for(int i = 0; i < W1; i++) {
        
        if(pthread_join(wa1[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }

    for(int i = 0; i < N; i++) {
        if(pthread_join(not[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }

    for(int i = 0; i < W2; i++) {
        
        if(pthread_join(wa2[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }
    
    for(int i = 0; i < NA; i++) {
        if(pthread_join(notAll[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }
    
    
    
    
    

    //Libera os semaforos criados:
    sem_destroy(&x);
    sem_destroy(&s);
    sem_destroy(&h);
    pthread_mutex_destroy(&m);
    
    return 0;
}