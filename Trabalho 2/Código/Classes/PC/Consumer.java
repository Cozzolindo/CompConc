package Classes.PC;


import java.util.Arrays;
import java.util.List;

public class Consumer extends Thread{
    
    private final Basic basicQ;
    private List<String> vector;

    public Consumer(Basic basicQ, List<String> vector){
        this.basicQ = basicQ;
        this.vector = vector;
    }

    @Override
    public void run(){
        for(;;){
            String sort =  basicQ.remove();
            if(sort == null){
                System.out.println("Todas as strings foram tratadas.");
                break;
            }
            String[] splite = (sort.split(" "));
            Arrays.sort(splite);
            for(String s : splite){
                vector.add(s);
            }
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }   
        }
    }
}
