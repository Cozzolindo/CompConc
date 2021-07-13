/*
    Carlos Cozzolino
    DRE: 115086800
    Laboratório 1 - Computação Concorrente
*/

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
// Definindo o tamanho máximo do array e o nº máx de threads
#define max 10000
#define mthread 2
int num[max]; //Variável global para a lista
int part = 0; //Auxiliar para dividir as threads

//Criando a thread:
void *threads(void *arg){
    // Cada thread precisa atuar em metade do array, logo, vamos dividi-las aqui
    int thread_part = part++;
    int pp;
    
    // Tarefa que a thread irá  realizar
    for(int i = (max/mthread)*thread_part; i < (thread_part+1)*(max/mthread); i++){
        pp = num[i]*num[i];
        printf("%d\t",pp);

    }

    pthread_exit(NULL);
}

int main(){
    for (int i = 0; i < max; i++)
    {
        num[i] = i;//atribuindo valores pra lista
    }

    pthread_t tid[mthread];

    for(int i = 0; i < mthread; i++){
        pthread_create(&tid[i],NULL,threads,(void*)NULL);
    }
    for(int i = 0; i < mthread; i++){
        pthread_join(tid[i],NULL);
    }
    return printf("\n FIM!");
    
}

