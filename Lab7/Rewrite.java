public class Rewrite extends Thread {
    private int id;
    private int delay;
    private WR monitor;
    private vector A;

    Rewrite(int id, int delayTime, WR m, vector A){
        this.id = id;
        this.monitor = m;
        this.delay = delayTime;
        this.A = A;
    }

    public void run(){
        int i;
        try{
            for(;;) //infinite loop 
            {
                this.monitor.passReader(this.id);
                for (i = 0; i<A.getSize(); i++) {
                    if(this.A.getInd(i) % 2 == 0){
                        System.out.println("\nO numero: [" + this.A.getInd(i) + "] e par!");
                    }else{
                        System.out.println("\nO numero: [" + this.A.getInd(i) + "] e impar!");
                    }
                }
                this.monitor.exitReader(this.id);
                sleep(this.delay); 
                this.monitor.passWriter(this.id);
                for (i=0; i<A.getSize(); i++) {
                    A.setInd(i, 2*A.getInd(i));
                    System.out.println("Resultado da multiplicacao: ["+A.getInd(i)+"] ");
                }
                this.monitor.exitWriter(this.id);
                sleep(this.delay);
            }
        }catch(InterruptedException e){return;}
    }
}
