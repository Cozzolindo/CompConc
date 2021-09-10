import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class vector {
    private List<Integer> vector;

    public vector(){
        this.vector = new ArrayList<Integer>();
    }

    public vector(int n){
        this.vector = Arrays.asList(new Integer[n]);
        for(int i = 0; i<n; i++){
            this.vector.set(i,i);
        }
    }

    public int getInd(int ind){
        return this.vector.get(ind);
    }

    public void setInd(int ind, int item){
        this.vector.set(ind, item);
    }
    public int getSize(){
        return this.vector.size();
        
    }
}
