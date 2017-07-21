package com.sort;

import java.util.Arrays;

public class Quicksort1 {
    public static int[] a=new int[]{6,15,-29,2,0,32,2,45,32,5};
    public static final int len=10;
    public static void swap(int i,int j){
        int k=a[j];
        a[j]=a[i];
        a[i]=k;
    }
    
    public static int partition(int []array,int left,int right){
        //�̶����зַ�ʽ
        int key=array[left];
        while(left<right){
            while(array[right]>=key && right>left){//�Ӻ�벿����ǰɨ��
                right--;
            }
            array[left]=array[right];
            while(array[left]<=key && right>left){//��ǰ�벿�����ɨ��
                left++;
            }
            array[right]=array[left];
        }
        array[right]=key;
        return right;
    }
    
    public static void quicksort(int[] array,int left ,int right){
        if(left>=right){
            return ;
        }
        int index=partition(array,left,right);
        quicksort(array,left,index-1);
        quicksort(array,index+1,right);
    }
    
    public static void main(String[] args) {
        
        quicksort(a,0,9);
        
        System.out.println(Arrays.toString(a));
    }
}
