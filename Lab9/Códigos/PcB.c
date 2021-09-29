#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

#define tam 5 //Tamanho do buffer
#define P 1 //Quantidade de produtores dessa questao
#define C 5 //Quantidade de consumidores dessa questao

sem_t empty, full, mutex; //semaforos utilizados
int buffer[tam];// vetor para alocar o produto gerado pelas threads
//Variaveis de estado:
int in = 0;
int out = 0;
int ini = 0;
int count = 0;

// Funcao para imprimir o buffer atual:
void imprimeBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    printf("%d ", buffer[i]);
  printf("\n");
}

//Funcao para criar numeros randomicos
int randomize(int n){
    int random = rand()%5;
    int i = 0;
    int cond = rand()%10;
    if(cond>5){ 
        do{
            random*=(rand()%5);
            random--;
            i++;
        }while(i<n);
    }else{
        do{
            random-=rand()%5;
        }while(random > -1*rand()%1000);
    }
    return pow(random*n, rand()%5);
}

//Funcao produtora com semaforos
void *producer(int *args){
    int* id = (int*) args;
    
    
    for(;;){    

        sem_wait(&empty);//Espera um sinal de quantos espacos vazios temos
        sem_wait(&mutex);// Mutex usado para outra thread nao interferir enquanto uma esta trabalhando
        
        int item = randomize(*id);// Cria o item pro buffer
        buffer[in] = item; // Adiciona o item no buffer
        printf("Produtor [%d] adicionou %d em |%d|\n", pthread_self(), item, in);
        in = (in + 1)%tam; // Avanca para a proxima casa
            
        imprimeBuffer(tam);
        sleep(1);//Sleep utilizado para acompanhar o print do Produto gerado
        count++;// Variavel contador para controlarmos quando precisamos mandar um sinal para a funcao consumer
        sem_post(&mutex); //Sinaliza que a proxima thread pode comecar a atuar
            
        if(count == tam){//Caso o contador fique do mesmo tamanho do buffer, podemos libera-lo para a funcao consumidora
            ini = tam;//Variavel 'ini' utilizada para liberar o wait(full)
            
            sem_post(&full);
            sleep(1);//Sleep para evitar que as threads terminem o trabalho rápido demais
            
            

        }
    }
    pthread_exit(NULL);
    
}

//Funcao consumidora com semaforos
void *consumer(int *args){
    int* id = (int*) args;
    int item;// Variavel utilizado para imprimir o item que foi removido
    
    for(;;){   
        
        while(ini < tam){//Loop para aguardar o buffer ficar cheio
            sem_wait(&full);
            
            
        }    
        //Nesse escopo da funcao, a mesma logica da funcao anterior foi aplicada:
        sem_wait(&mutex);
        
        
        item = buffer[out];
        printf("Consumidor [%d] removeu %d de |%d|\n", pthread_self(), item, out);
        buffer[out] = 0;
            
        out = (out+1)%tam;
        count--;
        sleep(1);
        
        sem_post(&mutex);
        if(count == 0){ //Quando o contador chega a zero, significa que esvaziamos o buffer e a funcao produtora pode ser avisada
            ini = 0;//reseta a variavel ini e fecha o laco wait(full) novamente
            for ( int i = 0; i< tam; i++){//Loop utilizado para avisar quantos espacos vazios temos
                sem_post(&empty);
                sleep(1);
            }

        }    
    }
    pthread_exit(NULL);
        
}

//Funcao para iniciar o buffer
void iniciaBuffer(int n) {
    int i;
    for(i=0; i<n; i++){
        buffer[i] = 0;
    }
}

int main(){
    
    //Identificadores das threads:
    pthread_t prod[P], con[C];

    //Inicializadores dos semaforos:
    sem_init(&empty, 0, tam);//'empty' comeca com valor tam para sabermos que o buffer tem 'tam' espacos vazios
    sem_init(&full, 0, 0);//'full' comeca com valor zero pois o vetor inicia vazio
    sem_init(&mutex, 0, 1);//'mutex' comeca com valor 1 para a funcao produtora poder iniciar
    
    iniciaBuffer(tam);

    //Alocando espacos para os identificadores:
    int *id[P];
    int *di[C];
    for(int i =0; i<P; i++){
        id[i] = malloc(sizeof(int));
        if(id[i] == NULL){
            exit(-1);
        }
        *id[i] = i+1;
    }

    for(int i =0; i<C; i++){
        di[i] = malloc(sizeof(int));
        if(di[i] == NULL){
            exit(-1);
        }
        *di[i] = i+1;
    }

    //Criando as threads:
    for(int i = 0; i<P; i++){
        pthread_create(&prod[i], NULL, (void *)producer, (void *)id[i]);
    }

    for(int i = 0; i<C; i++){
        pthread_create(&con[i], NULL, (void *)consumer, (void *)di[i]);
    }

    // Join para esperar a finalizacao das threads:
    for(int i = 0; i < P; i++) {
        if(pthread_join(prod[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        free(id[i]);
    }
    for(int i = 0; i < C; i++) {
        
        if(pthread_join(con[i],NULL)){
            printf("ERROR -- pthread join;");
            exit(-1);
        }
        free(di[i]);
    }

    //Libera os semaforos criados:
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}