package Classes.PC;


import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.Semaphore;

import Classes.WR.Monitor;

public class Consumer extends Thread{
    
    private final Basic basicQ;
    private List<String> vector;
    private Semaphore mutex;
    private final int N;
    private final String path;
    private final List<Integer> index;
    private Monitor monitor;
    


    public Consumer(Basic basicQ, List<String> vector, Semaphore mutex, int N, Monitor monitor, List<Integer> index, String path){
        this.basicQ = basicQ;
        this.vector = vector;
        this.mutex = mutex;
        this.N = N;
        this.path = path;
        this.monitor = monitor;
        this.index = index;
    }

    @Override
    public void run(){
        int[] lista = new int[N];
        
        for(;;){
            String sort =  basicQ.remove();//Remove um elemento da fila com o padrão produtor/consumidor;
            if(sort == null){//Se não temos mais strings para remover significa que todas já foram ordenadas e adicionadas ao vetor
                //System.out.println("Todas as strings foram tratadas.");
                break;
            }
            
            try {
                mutex.acquire(); //Semáforo para evitar condição de corrida entre as threads que estão ordenando
            } catch (InterruptedException e) {
                e.printStackTrace();
            } 
            //Ordenação do vetor:
            String[] splite = (sort.split(" "));
            for(int i = 0; i< N; i++){
                lista[i] = Integer.parseInt(splite[i]);
            }
            Arrays.sort(lista);
            for(int k : lista){
                vector.add(Integer.toString(k));
            }
            mutex.release();
            

         
        }
        int count = 0;
        int i;   
        //Aqui começa a lógica dos escritores, logo após o término da ordenação
        //System.out.println("Quer escrever #" + Thread.currentThread().getId());
        try(BufferedWriter bw = new BufferedWriter(new FileWriter(path))){
            this.monitor.passWriter(); //Deixa apenas um escritor entrar
            for(i = 0; i<index.get(0); i++) {//escreve no arquivo de texto informado os valores que recebeu
                bw.write(vector.get(i));
                bw.write(" ");
                count++;
                if(count == N){//Quebra de linha quando atingimos o valor de N
                    bw.newLine();
                    count = 0;
                }
            }
            bw.close();
            this.monitor.exitWriter();//Deixa o escritor sair
            //System.out.println("A thread [" + Thread.currentThread().getId() + "] escreveu no arquivo.");
        }catch(IOException e){
            e.printStackTrace();
        }

        
    }
}
