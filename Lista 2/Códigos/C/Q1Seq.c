/*
    Exercício Sequencial
*/
#include <stdio.h>
#include <stdlib.h>

int nthreads;
int* vetor;
int main(){
    puts("Digite o numero de threads:");
    scanf("%d", &nthreads);
/* Inicia as variaveis globais e carrega o vetor de entrada */
    vetor = (int*)malloc(sizeof(int)*nthreads);
    
    for(int i = 0; i<nthreads; i++){
        if(i-1<0){
            vetor[i] = i;
        }else{
            vetor[i] = i + vetor[i-1];
        }
    }
    for (int i = 0; i<nthreads; i++){
        printf("[%d] ", vetor[i]);
    }
    puts("\n===VETOR CRIADO VEI===");
    for(int i = 1; i<nthreads; i++){
        vetor[i] = vetor[i]+vetor[i-1];
    }

    for (int i = 0; i<nthreads; i++){
        printf("[%d] ", vetor[i]);
    }

    free(vetor);
    return puts("\nEND!");
}