package Classes.WR;

public class Monitor {
    
    private int write, read;

    public Monitor(){
        this.read = 0;
        this.write = 0;
    }

    public synchronized void passReader() {
        try {
          while (this.write > 0) {
            wait();
          }
          this.read++;
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
      }
    
    public synchronized void exitReader() {
        this.read--;
        if (this.read == 0) {
          this.notify();
        }
    }
    
    public synchronized void passWriter() {
        try {
          while ((this.write > 0) || (this.read > 0)) {
            wait();
          }
          this.write++;
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public synchronized void exitWriter() {
        this.write--;
        notifyAll();

    }
    
}
