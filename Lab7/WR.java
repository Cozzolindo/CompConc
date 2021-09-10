class WR{
        private int write, read;

        public WR(){
            this.read = 0;
            this.write = 0;
        }

        public synchronized void passReader (int id){
            try{
                while(this.write>0){
                    //System.out.println("Leitor "+id+" BLOQUEADO");
                    wait();
                }
                this.read++;
                //System.out.println("Leitor "+id+" LENDO");
            }catch(InterruptedException e){}
        }

        public synchronized void exitReader(int id){
            this.read--;
            if(this.read == 0){
                this.notify();
            }
            //System.out.println("Leitor "+id+" SAINDO");
        }

        public synchronized void passWriter(int id){
            try{
                while((this.write>0)||(this.read>0)){
                    //System.out.println("Escritor "+id+" BLOQUEADO");
                    wait();
                }
                this.write++;
                //System.out.println("Escritor "+id+" ESCREVENDO");
            }catch(InterruptedException e){}
        }

        public synchronized void exitWriter(int id){
            this.write--;
            notifyAll();
            //System.out.println("ESCRITOR "+id+" SAINDO");
        }
   
}