package Classes.PC;

import java.util.LinkedList;
import java.util.Queue;


public class Basic {
    
    protected Queue<String> queue = new LinkedList<>(); //Lista do tipo fila para manipularmos os elementos mais tarde
    protected boolean isEmpty = true, isDone = false; //Booleans para controlarmos os acessos dos produtores/consumidores
    

    public Basic(){
    }

    //Função para adicionar um bloco na fila
    public synchronized void plus(String content){
        while(queue.size() == 10){ //Caso a fila esteja cheia, precisamos aguardar alguem sair
            try{
                wait();
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
        queue.add(content);
        isEmpty = false;
        notifyAll(); //NotifyAll para evitar deadlocks
    }

    //Função para remover um bloco da fila
    public synchronized String remove(){
        while(isEmpty && !(isDone)){ //Caso a fila esteja vazia mas a execução dos produtores nao terminou, precisamos esperar alguem produzir algo
            try{
                wait();
            }catch(InterruptedException e){
                System.out.println(e.getMessage());
            }
        }

        if(queue.size() == 0 && isDone){ //Caso a fila esteja vazia e os produtores já terminaram sua produção, terminamos de remover elementos da fila
            return null;
        }

        System.out.println("Removido por:" + Thread.currentThread().getId());
        String content = queue.remove();
        if(queue.size() == 0){ //Caso a fila esteja vazia, validamos o boolean isEmpty
            isEmpty = true;
        }else if(queue.size() == 9){
            notifyAll(); // Caso a fila chegue próximo de sua capacidade total, sinalizamos para todas as threads que alguém pode remover algo
        }

        return content;

    }

    public void setIsDone(boolean isDone) { 
        this.isDone = isDone;
    }

    public Queue<String> getQueue() {
        return this.queue;
    }

    public int getSize(){
        return queue.size();
    }

    @Override
    public String toString() {
        return "{" +
            " queue='" + getQueue() + "'" +
                "}";
    }


}
