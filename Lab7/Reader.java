
class Reader extends Thread {
    private int id;
    private int delay;
    private WR monitor;
    private vector A;
    
    

    static boolean isPrime(int n){
        if(n<=1){
            return false;
        }
        else if(n==2){
            return true;
        }
        else if(n%2==0){
            return false;
        }
        for(int i =3; i<=Math.sqrt(n); i+=2){
            if(n%i== 0){
                return false;
            }
        }
        return true;
    }

    Reader (int id, int delayTime, WR m, vector A){
        this.id = id;
        this.monitor = m;
        this.delay = delayTime;
        this.A = A;
        
        
        
    }

    public void run(){
        int i;
    try {
      //for(j = 0; j<size; j++) 
      for(;;)//infinite loop 
      {
        this.monitor.passReader(this.id);
        for (i = 0; i<A.getSize(); i++) {
            if(isPrime(this.A.getInd(i))){
                System.out.println("\nO numero: [" + this.A.getInd(i) + "] e primo!");
            }else{
                System.out.println("\nO numero: [" + this.A.getInd(i) + "] nao e primo!");
            }
        } //...loop bobo para simbolizar o tempo de leitura
        this.monitor.exitReader(this.id);
        sleep(this.delay); 
        
      }
        }catch(InterruptedException e){
            return;
        }   
    }


    
}
