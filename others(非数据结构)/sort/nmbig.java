import java.util.Arrays;
//n个数中最大的m个，根据最小堆求解
public class nmbig {
    public static int[] a=new int[]{59,6,15,29,17,0,32,12,-6,-18,29,123,456};
    public static int[] b=null;
    public static final int len=13;
    public static void swap(int i,int j){
        int k=b[j];
        b[j]=b[i];
        b[i]=k;
    }
    
    public static void heapSort() {  
        for (int i = 0; i < len; i++) { 
            createMindHeap(len - 1 - i);  
            swap(0, len - 1 - i);            
        }  
    }  
    
    public static void createMindHeap(int xb) {  
        for(int i = (xb-1)/2;i >= 0; i--){
            int ls=i;
            while(ls*2+1 <= xb){
                int big=ls*2+1;
                if(big<xb){
                    if(b[big] > b[big+1]) big++;
                }
                if(b[ls] > b[big]){
                    swap(ls,big);
                    ls=big;
                }
                else break;
            }
        }
    }  
    
    public static void find(int m){
        b = new int[m];
        for(int i = 0; i < m; i++){
            b[i] = a[i];
        }
        createMindHeap(m-1);
        for(int i = m; i < len; i++){
            if( a[i] > b[0]){
                b[0]=a[i];
                createMindHeap(m-1);
            }
        }
    }
    public static void main(String[] args) {
        
        find(4);
        System.out.println(Arrays.toString(b));
    }
}
