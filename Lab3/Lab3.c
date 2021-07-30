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
float* retorno;



void* threads( void* arg ){

    long long int id = 0;
    id = id+1;
    long long int tamBloco = dim/nthreads;
    long long int start = id*tamBloco;
    long long int end;
    float *big;
    float *smol;
    float *resultadoC;
   

    //big = (float *)malloc(sizeof(float));
    //smol = (float *)malloc(sizeof(float));
    

    resultadoC = (float *)malloc(sizeof(float)*2);
    if(resultadoC == NULL){
        fprintf(stderr, "ERROR === 'malloc'\n");
        exit(1);
    }

    resultadoC[0] = vetor[0];
    resultadoC[1] = vetor[0];
   
    if(id == nthreads-1){
        end = dim;
    }else{
        end = start + tamBloco;
    }
    
    for(long long int i = id; i<dim; i += nthreads){
        
        if( resultadoC[0] < vetor[i]){
            resultadoC[0] = vetor[i];
        }
        if(resultadoC[1] > vetor[i]){
            resultadoC[1] = vetor[i];
        }
        
    }
    
    
    //resultadoC[0] = *big;
    //resultadoC[1] = *smol;
    
    pthread_exit((void*)resultadoC);


}

int main(){

    double inicio, fim, delta;
    float* resultado;
    pthread_t *tid;
    float* resultadoT;


    //Inicializando
    printf("Digite a dimensao do vetor:\n");
    scanf("%ld",&dim);
    printf("Digite o numeros de threads que deseja utilizar:\n");
    scanf("%d",&nthreads);

    //Alocando memoria:
    GET_TIME(inicio);
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
    /*
    resultadoT = (float*)malloc(sizeof(float) * 2);
    if(resultadoT == NULL){
        fprintf(stderr,"ERROR === 'malloc'\n");
        return 1;
    }*/

    
    tid = (pthread_t*)malloc(sizeof(pthread_t) * nthreads);
    if(tid == NULL){
        fprintf(stderr,"ERROR === 'malloc'\n");
        return 1;
    }
    
    
    

    //Preenche o vetor de entrada:
    long double T = 3.0;
    long double C = dim/7.0;
    for(long int i = 0; i<dim; i++){
    
        vetor[i] = ((dim/T)-(C/T));
        T = (T+0.3);
        C = (C+0.1);
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
    printf("\nTempo sequencial:%lf",delta);
    /*
    puts("\nVetor:\n");
    for (int i = 0; i<dim; i++){
        printf("%.15f ",vetor[i]);
    }*/
/*
    for(long int i = 0; i<dim; i++){
        if(vetor[0]<vetor[i]){
            vetor[0] = vetor[i];
        }
        if(vetor[i]<vetor[1]){
            vetor[1] = vetor[i];
        }
    }

    puts("\nVetor:\n");
    for (int i = 0; i<dim; i++){
        printf("%.15f ",vetor[i]);
    }*/

    //Cria as threads:
    GET_TIME(inicio);
    for(long long int i = 0; i<nthreads; i++){
        
        if(pthread_create(tid+i, NULL, threads, (void*) NULL)){
            fprintf(stderr, "ERROR === 'pthread_create'\n");
            return 2;
        }
    }

    //Aguarda o termina das threads
    for(long long int i = 0; i<nthreads; i++){
        pthread_join(*(tid+i), (void**)&retorno);
        
    }
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo concorrente: %lf\n",delta);
    
    printf("\nMaior valor: %.4f\n",resultado[0]);
    printf("Menor valor: %.4f\n",resultado[1]);
    printf("\nMaior valorC: %.4f\n",retorno[0]);
    printf("Menor valorC: %.4f\n",retorno[1]);
    
    //Liberação de memoria:
    free(vetor);
    free(resultado);
    free(tid);
    free(retorno);
    return printf("\nFIM!\n");
}