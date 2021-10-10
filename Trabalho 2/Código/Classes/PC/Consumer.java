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
            
            String sort =  basicQ.remove();
            if(sort == null){
                System.out.println("Todas as strings foram tratadas.");
                break;
            }
            
            try {
                mutex.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } 
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
        System.out.println("Quer escrever #" + Thread.currentThread().getId());
        try(BufferedWriter bw = new BufferedWriter(new FileWriter(path))){
            this.monitor.passWriter();
            for(i = 0; i<index.get(0); i++) {
                bw.write(vector.get(i));
                bw.write(" ");
                count++;
                if(count == N){
                    bw.newLine();
                    count = 0;
                }
            }
            this.monitor.exitWriter();
            System.out.println("A thread [" + Thread.currentThread().getId() + "] escreveu no arquivo.");
        }catch(IOException e){
            e.printStackTrace();
        }

        
    }
}
