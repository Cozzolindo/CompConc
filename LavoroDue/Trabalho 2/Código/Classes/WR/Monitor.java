package Classes.WR;

public class Monitor {
    
    private int write;

    public Monitor(){
        this.write = 0;
    }
    
    public synchronized void passWriter(int id) {
      try {
        while ((this.write > 0)) {
          System.out.println("\nEscritor " + id + " bloqueado");
          wait();
        }
        this.write++;
        System.out.println("Escritor " + id + " escrevendo");
      } catch (InterruptedException e) {
      }
    }
  
    public synchronized void exitWriter(int id) {
      this.write--;
      notify();
      System.out.println("Escritor " + id + " saindo");
    }
    
}
