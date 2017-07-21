package com.sort;

import java.util.Arrays;

public class maopao {
    public static int[] a=new int[]{6,15,-29,2,0,32,2,45,32,5};
    public static final int len=10;
    public static void swap(int i,int j){
        int k=a[j];
        a[j]=a[i];
        a[i]=k;
    }
    
    public static void main(String[] args) {
        for(int i = 0; i < len-1; i++ ){
            for(int j = 0; j < len-1; j++ ){
                if(a[j]>a[i]) swap(i,j);
            }
        }
        System.out.println(Arrays.toString(a));
    }
}
