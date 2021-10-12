package Classes.PC;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Producer extends Thread {
    
    private final Basic basicQ;
    private final Scanner scan;

    public Producer(Basic basicQ, File file) throws FileNotFoundException{
        this.basicQ = basicQ;
        this.scan = new Scanner(file);
    } 

    @Override
    public void run(){
        
        scan.nextLine();//Remove a primeira linha que contem apenas o numero total de elementos
        while(scan.hasNext()){
            //System.out.println("Produced by: " + Thread.currentThread().getId());
            basicQ.plus(scan.nextLine());//Adiciona algo na fila, seguindo o padrão produtor/consumidor
            
        }
        
       basicQ.setIsDone(true);//Quando termina de ler o arquivo, torna esse boolean verdadeiro
    }
}
