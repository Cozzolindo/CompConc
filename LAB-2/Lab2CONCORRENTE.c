/*                  Laboratório 2 Carlos Cozzolino
                            DRE: 115086800
        Tema: Multiplicação de matrizes quadradas usando computação concorrente
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

int nthreads;
float* matA;
float* matB;
float* saida;

typedef struct{
    int id;
    int dimA;
} tArgs;

void* thread(void* arg){

    tArgs* args = (tArgs*) arg;

    for(int i = args->id; i < args->dimA; i += nthreads){
        for( int j = 0; j<args->dimA; j++){
            for(int k = 0; k<args->dimA; k++){
                saida[i*(args->dimA)+j] += matA[i*(args->dimA)+k] * matB[k*(args->dimA)+j];
            }
        }
    }

    pthread_exit(NULL);
}
int main(int argc){
    double inicio, fim, delta;
    int dimA,again;
    pthread_t* tid;
    tArgs* args;


    //Parametros de entrada:
    INICIO:
    GET_TIME(inicio);
    if(argc<2){
        printf("\nDigite a dimensao das matrizes:\n");
        scanf("%d",&dimA);
        printf("\nDigite o numero de threads:\n");
        scanf("%d",&nthreads);
    }
    if(nthreads>dimA){
        nthreads=dimA;
    }
    //Alocação de memória:

    matA = (float *)malloc(sizeof(float) * dimA * dimA);
    if(matA == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
    }

    matB = (float *)malloc(sizeof(float) * dimA * dimA);
    if(matB == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
    }

    saida = (float *)malloc(sizeof(float) * dimA * dimA);
    if(saida == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
    }

    tid = (pthread_t*)malloc(sizeof(pthread_t)*nthreads);
    if(tid == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
    }

    args = (tArgs*)malloc(sizeof(tArgs)*nthreads);
    if(args == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
    }

    //Adicionando valores pras matrizes:

    for (int i = 0; i < dimA; i++){
        for(int j = 0; j<dimA; j++){
            matA[i*dimA+j] = i+j;
            matB[i*dimA+j] = i-j;
            saida[i*dimA+j] = 0;
        }
    }

    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de inicializacao:%lf\n",delta);

    //Chamando as threads:

    GET_TIME(inicio);
    for(int i = 0; i<nthreads;i++){
        (args+i)->id = i;
        (args+i)->dimA = dimA;
        if(pthread_create(tid+i,NULL,thread,(void*)(args+i))){
            puts("ERROR === 'pthread_create'");
            return 3;
        }
    }

    //Um joinzin pra esperar as threads:

    for(int i = 0; i<nthreads; i++){
        pthread_join(*(tid+i),NULL);
    }
    
    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de multiplicacao:%lf\n",delta);


    //Vendo as matrizes criadas:
/*
    puts("Matriz de entrada");
    for(int i=0; i<dimA; i++){
        for(int j=0; j<dimA; j++){
            printf("%.1f ",matA[i*dimA+j]);
        }
        puts("");
    }
    puts("Vetor de entrada");
    for(int i=0; i<dimA; i++){
        for(int j=0; j<dimA; j++){
            printf("%.1f ",matB[i*dimA+j]);
        }
        puts("");
    }*/
    puts("Vetor de saida");
    for(int i=0; i<dimA; i++){
        for(int j=0; j<dimA; j++){
            printf("%.1f ",saida[i*dimA+j]);
        }
        puts("");
    }
    //Liberacao de memoria:

    GET_TIME(inicio);
    free(matA);
    free(matB);
    free(saida);
    free(tid);
    free(args);
    
    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de finalizacao:%lf\n",delta);
    
    //Vale a pena ver de novo:

    printf("\nDeseja repetir o processo?\n 0 para sair\n 1 para repetir.\n");
    scanf("%d",&again);
    if(again==0){
        puts("\nObrigado por me libertar.\n");
        goto EXIT;
    }else{
        goto INICIO;
    }

    EXIT:

    return printf("FIM");
    

}