package Classes.PC;


import java.util.Arrays;
import java.util.List;
import java.util.concurrent.Semaphore;

public class Consumer extends Thread{
    
    private final Basic basicQ;
    private List<String> vector;
    private Semaphore mutex;
    private final int N;

    public Consumer(Basic basicQ, List<String> vector, Semaphore mutex, int N){
        this.basicQ = basicQ;
        this.vector = vector;
        this.mutex = mutex;
        this.N = N;
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
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            } 
            String[] splite = (sort.split(" "));
            for(int i = 0; i< N; i++){
                lista[i] = Integer.parseInt(splite[i]);
            }
            Arrays.sort(lista);
            for(int k : lista){
                vector.add(Integer.toString(k));
            }
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            mutex.release();   
        }
    }
}
