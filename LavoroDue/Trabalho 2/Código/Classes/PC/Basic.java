package Classes.PC;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;


public class Basic {
    
    protected Queue<String> queue = new LinkedList<>();
    protected boolean isEmpty = true, isDone = false;
    //protected int size;
    protected int N;
    protected List<Integer> index;

    public Basic(int N, List<Integer> index){
        this.N = N;
        this.index = index;
    }

    public synchronized void plus(String content){
        while(queue.size() == (int) Math.ceil(index.get(0)/2*N)){
            try{
                wait();
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
        queue.add(content);
        isEmpty = false;
        notifyAll();
    }

    public synchronized String remove(){
        while(isEmpty && !(isDone)){
            try{
                wait();
            }catch(InterruptedException e){
                System.out.println(e.getMessage());
            }
        }

        if(queue.size() == 0 && isDone){
            return null;
        }

        System.out.println("Removido por:" + Thread.currentThread().getId());
        String content = queue.remove();
        if(queue.size() == 0){
            isEmpty = true;
        }else if(queue.size() == (int)Math.ceil(index.get(0)/2*N)-1){
            notifyAll();
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
