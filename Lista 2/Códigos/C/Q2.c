#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

#define nThreads 2 


long long int contador=0;
int c = 0;//Variavel global para delimitar o tempo de espera do condicional

// Variaveis para controlarmos as execucoes das threads
pthread_mutex_t mutex;
pthread_cond_t condt1;

//Função FazAlgo para ganhar um tempo de execução nas threads
int FazAlgo(long long int x){
    for(int i = 0; i< 1000000; i++){
        x+=i;
    }
    return 0;
}

//Funcao T1 apresentada no exercício
void *T1 (void *arg) {
    for(;;) { //Loop infinito que aprendi com a Silvana e agora vivo repetindo
        
        FazAlgo(contador);
        pthread_mutex_lock(&mutex);//Primeiro lock utilizado para evitar uma condicao de corrida
        contador++;
        //printf("%lld ", contador);

        //Condicional que  libera as threads para a funcao T2 
        if(contador%100==0){
            
            pthread_cond_broadcast(&condt1);
            c = 2;
            sleep(10); //Sleep utilizado para garantir que T2 tera tempo de ser executado
        }
        
        pthread_mutex_unlock(&mutex);
        //sleep(1);
           
    }
}

//Funcao T2 que imprime os numeros divisiveis por 100
void *T2 (void *arg){
    
    for(;;){
        pthread_mutex_lock(&mutex);
        while(c<1){ //Loop para garantir que a espera do sinal vindo de T1
            pthread_cond_wait(&condt1, &mutex);
        }
        printf("[%lld] eh divisivel por 100\n", contador);
        
        c = 0;   //retornar o valor de c para zero e torna o loop anterior verdadeiro
                //evitando prints desnecessários ou ate mesmo errados
        
        pthread_mutex_unlock(&mutex);
    }
}

//Funcao main para criar as threads, mutex e cond
int main(){
    pthread_t threads[nThreads];
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condt1, NULL);

    
    pthread_create(&threads[0], NULL, T1, NULL);
    pthread_create(&threads[1], NULL, T2, NULL);
    
     //Prints para te tirar do tedio de ter que esperar o contador chegar ate o 100
    //e para ver que o programa ainda ta executando firme e forte
    puts("Estamos preparando tudo para voce!");
    sleep(2);
    puts("Isso pode levar mais alguns segundos...");
    sleep(2);
    puts("Ainda pode demorar um pouco...");
    sleep(2);
    puts("Nao esqueca de se hidratar para continuar nos dando aulas!");
    sleep(2);
    puts("Quase la...");
    
    for (int i = 0; i < nThreads; i++) {
    pthread_join(threads[i], NULL);
    }


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condt1);
    return 0;
}