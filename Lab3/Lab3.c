#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
/*  ===================================================================
          Programa que retorna o maior e menor número de um vetor
                            Carlos Cozzolino
                             DRE: 115086800
    ===================================================================
*/
long long int dim;
int nthreads;
float* vetor;
//float* retorno;

typedef struct{
    float min;
    float max;
} tArgs;


void* threads( void* arg ){

    tArgs* args = (tArgs*) arg;
    args = (tArgs*) malloc(sizeof(tArgs));
    long long int id = 0;
    long int tamBloco = dim/nthreads;
    long int start = id*tamBloco;
    long int end;
    args->min=vetor[0];
    args->max=vetor[0];
    
    if(id == nthreads-1){
        end=dim;
    }
    else{
        end= start + tamBloco;
        }
    
    for(long long int i = start+1; i<end; i ++){
        
        if( args->max < vetor[i]){
            args->max = vetor[i];
        }
        if(args->min > vetor[i]){
            args->min = vetor[i];
        }
        id++;
        
    }
    pthread_exit((void*)args);


}

int main(){

    double inicio, fim, delta;
    float* resultado;
    pthread_t *tid;
    float *resposta;
    tArgs *retorno;


    //Inicializando
    printf("Digite a dimensao do vetor:\n");
    scanf("%ld",&dim);
    printf("Digite o numeros de threads que deseja utilizar:\n");
    scanf("%d",&nthreads);

    //Alocando memoria:
    GET_TIME(inicio);
    retorno = (tArgs*) malloc(sizeof(tArgs));
    if(retorno == NULL){
        puts("ERROR === 'malloc'\n");
        return 1;
    }
    vetor = (float*)malloc(sizeof(float) * dim);
    if(vetor == NULL){
        fprintf(stderr,"ERROR === 'malloc'\n");
        return 1;
    }
    
    resultado = (float*)malloc(sizeof(float) * 2);
    if(resultado == NULL){
        fprintf(stderr,"ERROR === 'malloc'\n");
        return 1;
    }
    resposta = (float*)malloc(sizeof(float) * 2);
    if(resposta == NULL){
        fprintf(stderr,"ERROR === 'malloc'\n");
        return 1;
    }

    
    tid = (pthread_t*)malloc(sizeof(pthread_t) * nthreads);
    if(tid == NULL){
        fprintf(stderr,"ERROR === 'malloc'\n");
        return 1;
    }
    
    
    

    //Preenche o vetor de entrada:
    long double T = 3.0;
    long double C = 2.0;
    for(long int i = 0; i<dim; i++){
    
        vetor[i] = ((dim/T)-(dim/C))*(-1);
        T+=3;
        C+=7*(-1);
        //printf("%f ",vetor[i]);
    }
    
    resultado[0] = vetor[0];
    resultado[1] = vetor[0];
    
    
    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de inicializacao: %lf\n",delta);

    //Encontrando o maior e menor valor:
    GET_TIME(inicio);
    for(long int i = 0; i<dim; i++){
        if(resultado[0]<vetor[i]){
            resultado[0] = vetor[i];
        }
        if(vetor[i]<resultado[1]){
            resultado[1] = vetor[i];
        }
    }
    
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo sequencial: %lf",delta);

    //Cria as threads:
    GET_TIME(inicio);
    for(long long int i = 0; i<nthreads; i++){
        
        if(pthread_create(tid+i, NULL, threads, (void*) NULL)){
            fprintf(stderr, "ERROR === 'pthread_create'\n");
            return 2;
        }
    }

    //Aguarda o termino das threads
    for(long long int i = 0; i<nthreads; i++){
        pthread_join(*(tid+i), (void**)&retorno);
        if(i==0){
            resposta[0] = retorno->max;
            resposta[1] = retorno->min;
        }
        else{
            if(resposta[0]<retorno->max){
                resposta[0] = retorno->max;
            }
            if(resposta[1]>retorno->min){
                resposta[1] = retorno->min;
            }
        }
        free(retorno);
        
    }
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo concorrente: %lf\n",delta);
    
    printf("\nMaior valor Sequencial: %.4f\n",resultado[0]);
    printf("Menor valor Sequencial: %.4f\n",resultado[1]);
    printf("\nMaior valor Concorrente: %.4f\n",resposta[0]);
    printf("Menor valor Concorrente: %.4f\n",resposta[1]);
    
    //Liberação de memoria:
    free(vetor);
    free(resultado);
    free(tid);
    free(resposta);
    return printf("\nFIM!\n");
}
