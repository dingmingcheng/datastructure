package com.sort;

import java.util.Arrays;

public class guibing {
    public static int[] a=new int[]{6,15,-29,2,0,32,2,45,32,5};
    public static final int len=10;
    public static void swap(int i,int j){
        int k=a[j];
        a[j]=a[i];
        a[i]=k;
    }
        
    public static void mergeSort(int[] a){
        int len = 1;
        while(len < a.length){
            
            for(int i = 0; i < a.length; i += 2*len){
                merge(a, i, len);
                //System.out.println(i+" "+len+" "+Arrays.toString(a));
            }
            len *= 2;
        }
    }
    
    public static void merge(int[] a, int i, int len){
        int start = i;
        int len_i = i + len;//归并的前半部分数组
        int j = i + len;
        int len_j = j +len;//归并的后半部分数组
        int[] temp = new int[2*len];
        int count = 0;
        while(i < len_i && j < len_j && j < a.length){
            if(a[i] <= a[j]){
                temp[count++] = a[i++];
            }
            else{
                temp[count++] = a[j++];
            }
        }
        while(i < len_i && i < a.length){//注意：这里i也有可能超过数组长度
            temp[count++] = a[i++];
        }
        while(j < len_j && j < a.length){
            temp[count++] = a[j++];
        }
        count = 0;
        while(start < j && start < a.length){
            a[start++] = temp[count++];
        }
    }
    
    public static void main(String[] args) {
        
        mergeSort(a); 
        System.out.println(Arrays.toString(a));
    }
}
