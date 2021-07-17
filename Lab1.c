/*
    Carlos Cozzolino
    DRE: 115086800
    Laboratório 1 - Computação Concorrente
*/

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <math.h>

// Definindo o tamanho máximo do array e o nº máx de threads
#define max 10000
#define mthread 2
int* num; //Variável global para a lista


typedef struct{
    int first;
    int last;
} t_Args;
//Criando a thread:
void *threads(void *arg){
    t_Args *args = (t_Args *)arg; //Declarando a estrutura na thread
    
    // Tarefa que a thread irá  realizar
    for(int i = args->first; i< args->last; i++){
        num[i] = num[i]*num[i];
    }
    free(arg);
    pthread_exit(NULL);
}

int main(){

    pthread_t tid[mthread];

    
    //Criando o ponteiro de tamanho max:
    num = (int *)malloc(sizeof(int) * max);

    //Criando um vetor de com números de 0-10000:
    for(int i = 0;i<max;i++){
		num[i] = i; 
	}
    

    t_Args *arg;//Struct com argumentos da thread
    

    for(int i = 0; i < mthread; i++){
        arg = malloc(sizeof(t_Args));
        if(arg == NULL){
            printf("ERROR\t====\t'malloc'\t");exit(-1);
        }
        arg->first = floor((double)max/mthread * i);
        arg->last = floor((double)max/mthread * (i+1));
        if (pthread_create(&tid[i],NULL,threads,(void*)arg)){
            printf("ERROR\t====\t'pthread_create'\t");exit(-1);
        };
    }
    for(int i = 0; i < mthread; i++){
        pthread_join(tid[i],NULL);
    }

    for(int i = 0; i<max;i++){
        printf("%d --> ",num[i]);
    }

    return printf("\n FIM!");
    
}

/*
     Reposta das outras atividades :
     
    1- Existe sim mudança na ordem de execução das threads, já que quando criamos um fluxo
    de execução, cada thread terá uma ordem de execução aleatória e independente da função
    principal.

    2- Não teve nenhuma mudança na forma de execução do fluxo das threads, porém, agora as
    threads recebem um argumento para trabalharem, no caso do programa as threads receberam
    um identificador de criação.

    3- Sim, com uma struct em C (que foi declarada e usada na thread) podemos ver as threads 
    recebendo mais de um argumento e trabalhando com eles.

    4- Com o comando join podemos ver que a função main só termina quando todas as operações
    envolvendo as threads se encerram.
*/
