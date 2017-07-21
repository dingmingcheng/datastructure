package com.sort;

import java.util.Arrays;
//������
public class heapsort1 {
    public static int[] a=new int[]{6,15,29,17,0,32};
    public static final int len=6;
    public static void swap(int i,int j){
        int k=a[j];
        a[j]=a[i];
        a[i]=k;
    }
    
    public static void heapSort() {  
        for (int i = 0; i < len; i++) {  
            createMaxdHeap(len - 1 - i);  
            swap(0, len - 1 - i);            
        }  
    }  
  
    public static void createMaxdHeap(int xb) {  
        for(int i = (xb-1)/2;i >= 0; i--){
            int ls=i;
            while(ls*2+1 <= xb){//δ����xb��xb����Ѵ�С
                int big = ls*2+1;
                if(big < xb){//���Ҷ��Ӵ��ڣ������Ҷ������ҳ�����
                    if(a[big] < a[big+1]) big++;
                }
                if(a[ls] < a[big]){
                    swap(ls,big);
                    ls = big;// ���¼����޸�
                }
                else break;
            }
        }
    }  
    
    public static void main(String[] args) {
        
        heapSort();
        System.out.println(Arrays.toString(a));
    }
}
