#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <unistd.h>

/* Variaveis globais */
int bloqueadas = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
int nthreads;
int *vetor;
/* Funcao barreira */
void barreira(int nthreads) {
    pthread_mutex_lock(&x_mutex);
    if (bloqueadas == (nthreads-1)) {
//ultima thread a chegar na barreira
        pthread_cond_broadcast(&x_cond);
        bloqueadas=0;
    } else {
        bloqueadas++;
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    pthread_mutex_unlock(&x_mutex);
}
/* Funcao das threads */
void *tarefa (void *arg) {
    int id = *(int*)arg;
    int salto;
    int aux;
    for(salto=1; salto<nthreads; salto*=2) {
        if(id >= salto) {
            aux = vetor[id-salto];
            //printf("|%d|[%d],",id, aux);
            barreira(nthreads-salto);
            vetor[id] = aux + vetor[id];
            
            barreira(nthreads-salto);
            
        } else {break;}
    }
        pthread_exit(NULL);
}
/* Funcao principal */
int main() {
    
    
/* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);
/* Recebe os parametros de entrada (tamanho do vetor == n´umero de threads) */
    puts("Digite o numero de threads:");
    scanf("%d", &nthreads);
    pthread_t threads[nthreads];
    int id[nthreads];
/* Inicia as variaveis globais e carrega o vetor de entrada */
    vetor = (int*)malloc(sizeof(int)*nthreads);
    
    for(int i = 0; i<nthreads; i++){
        if(i-1<0){
            vetor[i] = i;
        }else{
            vetor[i] = i + vetor[i-1];
        }
        
        printf("[%d] ", vetor[i]);
    }
    
    puts("\n===VETOR CRIADO CHEFIA===");
/* Cria as threads */
    for(int i=0;i<nthreads;i++) {
        id[i]=i;
        pthread_create(&threads[i], NULL, tarefa, (void *) &id[i]);
    }
    
/* Espera todas as threads completarem */
    for (int i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
    }
    puts(" ");
    for(int i = 0; i<nthreads; i++){
        
        printf("[%d] ", vetor[i]);
    }
/* Armazena o vetor de saida, libera vari´aveis e encerra */
    free(vetor);
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
    puts("\nEND!");
    return 0;
}