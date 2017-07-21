package com.sort;

import java.util.Arrays;

public class xuanze {
    public static int[] a=new int[]{6,15,-29,2,0,32,2,45,32,5};
    public static final int len=10;
    public static void swap(int i,int j){
        int k=a[j];
        a[j]=a[i];
        a[i]=k;
    }
    
    public static void main(String[] args) {
        for(int i=0;i<len-1;i++){
            int min=a[i],k=i;
            for(int j=i+1;j<len;j++){
                if(a[j]<min){
                    min=a[j];k=j;
                }
            }
            if(k!=i){
                swap(k,i);
            }
        }
        
        System.out.println(Arrays.toString(a));
    }
}
