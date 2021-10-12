package Classes.WR;

public class Monitor {
    
    private int write;

    public Monitor(){
        this.write = 0; //Variavel para controlarmos o acessos dos escritores
    }
    
    public synchronized void passWriter() {
        try {
          while ((this.write > 0)) {//Caso tenha alguem escrevendo, bloqueia a entrada de novos escritores
            wait();
          }
          this.write++;//Quando alguem entra, incrementa em um a variavel
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public synchronized void exitWriter() {
        this.write--;//Quando a variável termina de escrever, removemos 1 da variavel
        notifyAll();//NotifyAll apos a alteração da variável para as threads perceberem o novo estado

    }
    
}
