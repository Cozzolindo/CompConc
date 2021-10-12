import java.io.File;
import java.io.FileNotFoundException;
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

        //Declarando as variáveis que o usuário precisa informar
        Scanner scan = new Scanner(System.in);
        System.out.println("Digite o numero de threads para os Consumidores/Escritores:");
        int nThreads = scan.nextInt();
        System.out.println("Digite o tamanho dos blocos do arquivo: ");
        int N = scan.nextInt();
        System.out.println("Digite o caminho do arquivo de texto (exemplo Txt\\file.txt): ");
        scan.nextLine();
        String path = scan.nextLine();
        File file = new File(path);
        System.out.println("Digite o caminho de destino arquivo de texto que sera (exemplo Txt\\output.txt): ");
        String sPath = scan.nextLine();
        scan.close();

        //Declarando variáveis para os nossos contrutores:
        List<Integer> index = new ArrayList<>();
        index.add(N*10);
        Basic basicQ = new Basic();
        
        Producer[] producer = new Producer[1]; //Thread produtora de tamanho 1, valor fixo
        List<String> vector = new ArrayList<>(); //Vetor para adicionarmos nossos elementos
        Monitor monitor = new Monitor();
        Semaphore mutex = new Semaphore(1); //Semaforo iniciado em 1 para evitar condição de corrida
        
        long startTime = System.currentTimeMillis(); //Para para iniciar a medida do tempo

        //Iniciando as threads:
        for (int i = 0; i < 1; i++) {
            producer[i] = new Producer(basicQ, file);
            producer[i].start();
        }
        Consumer[] consumer = new Consumer[nThreads];
        for (int i = 0; i < nThreads; i++) {
            consumer[i] = new Consumer(basicQ, vector, mutex, N, monitor, index, sPath);
            consumer[i].start();
        }

        //Join para aguardar a finalização de todas as threads antes de continuarmos
        for (int i = 0; i < nThreads; i++) {
            consumer[i].join();
        }
        long endTime = System.currentTimeMillis();//Comando para finalizar a medida de tempo

        System.out.println();
        System.out.println("Tempo de execucao foi: " + (endTime - startTime) + " milissegundos."); //Print com a duração da execução do programa 
}

}