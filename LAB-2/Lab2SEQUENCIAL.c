/*                  Laboratório 2 Carlos Cozzolino
                            DRE: 115086800
        Tema: Multiplicação de matrizes quadradas usando computação concorrente
*/

#include<stdio.h>
#include<stdlib.h>

#include "timer.h"


float* matA;
float* matB;
float* saida;


int main(int argc){

    int dimA,again;
    double inicio, fim, delta;
    
    
    //Parametros de entrada:
    INICIO:
    GET_TIME(inicio);
    if(argc<2){
        printf("\nDigite a dimensao das matrizes:\n");
        scanf("%d",&dimA);
    }

    if(dimA==0){
        puts("Insira uma dim valida!\n");
        goto INICIO;
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
    printf("\nTempo de inicializacao:%lf",delta);

    //Multiplicação:
    GET_TIME(inicio);
    for(int i = 0; i < dimA; i++){
        for( int j = 0; j<dimA; j++){
            for(int k = 0; k<dimA; k++){
                saida[i*dimA+j] += matA[i*(dimA)+k] * matB[k*(dimA)+j];
            }
        }
    }
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo de multiplicacao:%lf",delta);

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
    puts("\n\nVetor de saida");
    for(int i=0; i<dimA; i++){
        for(int j=0; j<dimA; j++){
            printf("%.1f ",saida[i*dimA+j]);
        }
        puts("");
    }
   

    GET_TIME(inicio);
    free(matA);
    free(matB);
    free(saida);
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo de finalizacao:%lf\n",delta);

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