// Monitor que implementa a logica do padrao leitores/escritores
class LE {
    private int leit, escr;  
    private int fila = 0;
    // Construtor
    LE() { 
       this.leit = 0; //leitores lendo (0 ou mais)
       this.escr = 0; //escritor escrevendo (0 ou 1)
    } 
    
    // Entrada para leitores
    public synchronized void EntraLeitor (int id) {
      try { 
        
        while ((fila>0) || (this.escr > 0)) {
           System.out.println ("Leitor Bloqueado ["+id+"]");
           wait();  //bloqueia pela condicao logica da aplicacao 
        }
        this.leit++;  //registra que ha mais um leitor lendo
        System.out.println ("Leitor Lendo ["+id+"]");
      } catch (InterruptedException e) { }
    }
    
    // Saida para leitores
    public synchronized void SaiLeitor (int id) {
       this.leit--; //registra que um leitor saiu
        if (this.leit == 0) {
            this.notifyAll();
        } //libera escritor (caso exista escritor bloqueado)
       System.out.println ("Leitor Saindo ["+id+"]");
    }
    
    // Entrada para escritores
    public synchronized void EntraEscritor (int id) {
      try { 
        
        while ((this.escr > 0) || (this.leit>0)) {
            
            System.out.println ("Escritor Bloqueado |"+id+"|");
            fila++;
            wait();  //bloqueia pela condicao logica da aplicacao 
        }
        this.escr++;
        if(this.escr>0){
            fila--;
        }
         //registra que ha um escritor escrevendo
        System.out.println ("Escritor Escrevendo |"+id+"|");
      } catch (InterruptedException e) { }
    }
    
    // Saida para escritores
    public synchronized void SaiEscritor (int id) {
       this.escr--; //registra que o escritor saiu
       notify(); //libera leitores e escritores (caso existam leitores ou escritores bloqueados)
       System.out.println ("Escritor Saindo |"+id+"|");
    }
  }
  
  
  
  //Aplicacao de exemplo--------------------------------------------------------
  // Leitor
  class Leitor extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    LE monitor;//objeto monitor para coordenar a lógica de execução das threads
  
    // Construtor
    Leitor (int id, int delayTime, LE m) {
      this.id = id;
      this.delay = delayTime;
      this.monitor = m;
    }
  
    // Método executado pela thread
    public void run () {
    double j=777777777.7;
    double i;
      try {
        for (;;) {
            this.monitor.EntraLeitor(this.id);
            
            Thread.sleep(1000);
            
            this.monitor.SaiLeitor(this.id);
            sleep(this.delay); 
        }
      } catch (InterruptedException e) { return; }
    }
  }
  
  //--------------------------------------------------------
  // Escritor
  class Escritor extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo...
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads
  
    // Construtor
    Escritor (int id, int delayTime, LE m) {
      this.id = id;
      this.delay = delayTime;
      this.monitor = m;
    }
  
    // Método executado pela thread
    public void run () {
      double j=777777777.7, i;
      try {
        for (;;) {
            this.monitor.EntraEscritor(this.id); 
          
            Thread.sleep(1000);
            
          this.monitor.SaiEscritor(this.id); 
          sleep(this.delay); //atraso bobo...
        }
      } catch (InterruptedException e) { return; }
    }
  }
  
public class Minimize {
    static final int L = 3;
    static final int E = 4;

  public static void main (String[] args) {
    int i;
    LE monitor = new LE();            // Monitor (objeto compartilhado entre leitores e escritores)
    Leitor[] l = new Leitor[L];       // Threads leitores
    Escritor[] e = new Escritor[E];   // Threads escritores

    //inicia o log de saida
    System.out.println ("import verificaLE");
    System.out.println ("le = verificaLE.LE()");
    
    
    for (i=0; i<L; i++) {
       l[i] = new Leitor(i+1, (i+1)*500, monitor);
       l[i].start(); 
    }
    for (i=0; i<E; i++) {
        e[i] = new Escritor(i+1, (i+1)*500, monitor);
        e[i].start(); 
     }
    
  }
}
