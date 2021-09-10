

public class countEvens {
    static final int W = 10;
    static final int R = 3;
    static final int RW = 3;

    public static void main(String[] args){

        vector A = new vector(1);
        int i;
        WR monitor = new WR();
        Writer[] w = new Writer[W];
        Reader[] r = new Reader[R];
        Rewrite[] rw = new Rewrite[RW];
        System.out.println("V A L E N D O");
        
        for(i = 0; i<R; i++){
            r[i] = new Reader(i, (i+1)*500, monitor, A);
            r[i].start();
                
        }
        for(i = 0; i<W; i++){
            w[i] = new Writer(i, (i+1)*500, monitor, A);
            w[i].start();
        }
        for(i = 0; i<RW; i++){
            rw[i] = new Rewrite(i, (i+1)*500, monitor, A);
            rw[i].start();
        }
    }
        
}
