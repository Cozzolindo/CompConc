
class Writer extends Thread {
    private int id;
    private int delay;
    private WR monitor;
    private vector A;
    
    
    

    Writer (int id, int delayTime, WR m, vector A){
        this.id = id;
        this.monitor = m;
        this.delay = delayTime;
        this.A = A;
        
        
        

    }

    public void run(){
        int i;
        try {
            //for(j = 0; j<size; j++) 
            for(;;)
            {
                this.monitor.passWriter(this.id); 
                for (i=0; i<A.getSize(); i++) {
                    A.setInd(i, id);
                    System.out.println("Resultado da troca: ["+A.getInd(i)+"] ");
                } //...loop bobo para simbolizar o tempo de escrita
                this.monitor.exitWriter(this.id); 
                sleep(this.delay); //atraso bobo...
            }
        }catch(InterruptedException e){
            return;
        }
        
        
    }
    
}
