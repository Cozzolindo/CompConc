#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>


sem_t prior, wrt, mutex; //Semaforos utilizados
int writers = 0, readers = 0; // Vriaveis para controlarmos leitores e escritores
unsigned int count = 1; // Variavel para efetuar a leitura e escrita

//Funcao dos leitores:
void *lettore(){
    
    printf("Leitor [%d] criado.\n", pthread_self());//Print dos leitores criados
    //sleep(1);

    //Loop feito para facilitar a corretude do programa
    for(;;)
    {
        
        sem_wait(&mutex);
        
        
        while(writers > 0){ //Loop criado para aguardar o numero de escritoras ser zero
            sem_post(&mutex); //Faz um sinal para o proximo mutex
            sem_wait(&prior); // Aguarda o sinal do proximo prior
            
            sem_post(&prior); // Faz um sinal para o proximo prior, que se encontra na Funcao Scrittore
            sem_wait(&mutex); // Aguardo o proximo sinal do mutex
        }
        // O loop acima aguarda um sinal de prior e mutex

        readers++; // Adiciona um leitor na fila
        if(readers == 1){ // Decrementa do semaforo de escrita
            sem_wait(&wrt);
        }

        sem_post(&mutex); //Fecha a parte crítica da funcao, para os leitores efetuarem a leitura
        printf("\nLeitor [%d] esta lendo.", pthread_self());
        //sleep(1);
        printf("\nLeitor [%d] leu: [%d].\n", pthread_self(), count);
        sem_wait(&mutex); // Libera a parte critica da funcao

        readers--; // Remove o leitor da fila de leitores criada
        
        if(readers == 0){ // Caso a fila de leitores seja zero, podemos avisar os escritores para começarem a escrever
            sem_post(&wrt);
            //sleep(1);
        }
        sem_post(&mutex);
        
    }
}

//Funcao dos escritores:
void *scrittore(){

    printf("Escritor |%d| criado.\n", pthread_self());
    //sleep(1);

    for(;;){
        
        sem_wait(&mutex);
        writers++; // Adiciona um escritor na fila
        if(writers == 1){
            
            sem_wait(&prior); // Caso tenha alguem na fila de escritores, os leitores devem encerrar sua leitura e colocar os escritores como prioridade
            
        }
        
        sem_post(&mutex); // Fecha a parte critica para os escritores iniciarem a escrita
        sem_wait(&wrt); // Restringe a quantidade de escritores que podem escrever por vez
        
        printf("Escritor |%d| esta escrevendo!\t", pthread_self());
        count = count*2;
        printf("Escritor |%d| escreveu: |%d|.\n", pthread_self(), count);
        
        writers--;
        sem_post(&wrt); // Libera o proximo escritor depois de terminar a escrita
        sem_wait(&mutex); // Libera a parte critica da funcao
        
        
        if(writers == 0){ // Caso a fila de escritores seja zero, podemos avisar os leitores para lerem os novos dados
            sem_post(&prior);
            //sleep(1);
        }
        sem_post(&mutex);
        
        
        
    }
}

int main(){
    int wr, rd;
    printf("Digite o numero de threads leitoras:\n");
    scanf("%d", &rd);
    printf("Digite o numero de threads escritoras:\n");
    scanf("%d", &wr);

    pthread_t writ[wr], read[rd];

    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);
    sem_init(&prior, 0, 1);

    //Criando as threads:
    for(int i = 0; i<rd; i++){
        pthread_create(&read[i], NULL, (void *)lettore, NULL);
    }

    for(int i = 0; i<wr; i++){
        pthread_create(&writ[i], NULL, (void *)scrittore, NULL);
    }

    

    // Join para esperar a finalizacao das threads:
    for(int i = 0; i < rd; i++) {
        
        if(pthread_join(read[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }
    
    for(int i = 0; i < wr; i++) {
        if(pthread_join(writ[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        
    }
    

    //Libera os semaforos criados:
    sem_destroy(&wrt);
    sem_destroy(&mutex);
    sem_destroy(&prior);
    
    return 0;
}
