import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;


class vector{
    private List<Integer> vector;

    public vector(){
        this.vector = new ArrayList<Integer>();
    }

    public vector(int n){
        this.vector = Arrays.asList(new Integer[n]);
        for(int i = 0; i<n; i++){
            this.vector.set(i,i);
        }
    }

    public int getInd(int ind){
        return this.vector.get(ind);
    }

    public void setInd(int ind, int item){
        this.vector.set(ind, item);
    }
}

class Odds{
    private int elements;
    private int nThreads;
    private vector A;
    private int counter = 0;

    Odds(int elements, int nThreads, vector A){
        this.elements = elements;
        this.A = A;
        this.nThreads = nThreads;
    }

    public synchronized void Odd(int id){
        int start, end;
        int blockSize = this.elements/this.nThreads;
        start = id*blockSize;
        end = id ==nThreads-1? elements: start + blockSize;

        for(int i = start; i<end; i++){
            if(this.A.getInd(i) % 2 == 0){
                System.out.print("\nO numero: [" + this.A.getInd(i) + "] e par!");
                counter++;
            }
        }
    }

    public int getOdd(){
        return this.counter;
    }

    
}

class Th extends Thread{
    private int id;
    private Odds odd;

    public Th(int id, Odds odd){
        this.id = id;
        this.odd = odd;
    }

    public void run(){
        System.out.print("\nThread " + this.id + " iniciou!");
        this.odd.Odd(this.id);
    }
}
public class CountOdds {

    
    public static void main(String[] args){

        Scanner scan = new Scanner(System.in);
        System.out.println("Digite o numero de threads que deseja utilizar:\n");
        int nThreads = scan.nextInt();
        int elements = 3*nThreads;
        vector A = new vector(elements);
        
        System.out.print("Vetor gerado:\n");
        for(int i = 0; i<elements; i++){
            System.out.print("["+A.getInd(i)+"] ");
        }
        Thread[] threads = new Thread[nThreads];
        Odds odd = new Odds(elements, nThreads, A);

        for(int i = 0; i<threads.length; i++){
            threads[i] = new Th(i,odd);
        }

        for(int i = 0; i<threads.length; i++){
            threads[i].start();
        }

        for(int i = 0; i<threads.length; i++){
            try{
                threads[i].join();
            }catch(InterruptedException IE){
                return;
            }
        }
        
        System.out.println("\nNumero atual de pares: " + odd.getOdd());
    }
}
