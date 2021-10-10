package Classes.WR;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class Writer extends Thread {
    private Monitor monitor; // objeto monitor para coordenar a lógica de execução das threads
    private final List<Integer> index;
    private final List<String> vector;
    private String path;
    private final int N;


    // Construtor
    public Writer(Monitor monitor, List<Integer> index, List<String> vector, String path, int N) {
        this.monitor = monitor;
        this.index = index;
        this.vector = vector;
        this.path = path;
        this.N = N;
    }
    
    // Método executado pela thread
    public void run() {
        int count = 0;
        int i;   
        System.out.println("Starting thread #" + Thread.currentThread().getId());
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
