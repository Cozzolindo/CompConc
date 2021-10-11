import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

import Classes.PC.Basic;
import Classes.PC.Consumer;
import Classes.PC.Producer;
import Classes.WR.Monitor;

public class Main{

    public static void main(String[] args) throws FileNotFoundException, InterruptedException{
        
        Scanner scan = new Scanner(System.in);
        System.out.println("Digite o numero de threads para os Consumidores/Escritores:");
        int nThreads = scan.nextInt();
        System.out.println("Digite o tamanho dos blocos do arquivo: ");
        int N = scan.nextInt();
        scan.close();
        String path = "Txt\\file.txt";
        File file = new File(path);
        List<Integer> index = new ArrayList<>();
        try{
            scan = new Scanner(file);
            String s = scan.nextLine();
            index.add(Integer.parseInt(s));
        }catch(IOException e){
            System.out.println(e.getMessage());
        }finally{
            if(!(scan == null)){
                scan.close();
            }
        }
        if(Math.ceil(index.get(0)/N) < nThreads){
            nThreads = (int)Math.ceil(index.get(0)/N);
            System.out.println("Muita thread pra pouco bloco, usando: " + nThreads);
        }
        Semaphore mutex = new Semaphore(1);
        Basic basicQ = new Basic(N, index);
        String sPath = "Txt\\perfection.txt";
        Producer[] producer = new Producer[1];
        List<String> vector = new ArrayList<>();
        Monitor monitor = new Monitor();

        long startTime = System.currentTimeMillis();
        for (int i = 0; i < 1; i++) {
            producer[i] = new Producer(basicQ, file);
            producer[i].start();
        }
        Consumer[] consumer = new Consumer[nThreads];
        for (int i = 0; i < nThreads; i++) {
            consumer[i] = new Consumer(i, nThreads, basicQ, vector, mutex, N, monitor, index, sPath);
            consumer[i].start();
        }
        for (int i = 0; i < nThreads; i++) {
            consumer[i].join();
        }
        long endTime = System.currentTimeMillis();

        System.out.println();
        System.out.println("Tempo de execucao foi: " + (endTime - startTime) + " milissegundos."); 
        System.out.println(50/3);
}

}