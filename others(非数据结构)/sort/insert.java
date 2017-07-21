package com.sort;

import java.util.Arrays;

public class insert {
    public static int[] a=new int[]{6,15,-29,2,0,32,2,45,32,5};
    public static final int len=10;
    public static void swap(int i,int j){
        int k=a[j];
        a[j]=a[i];
        a[i]=k;
    }
    
    public static void main(String[] args) {
        int[] ans=new int[len];
        ans[0]=a[0];
        for(int i=1;i<len;i++){
            int flag=i;
            while(flag>=1 && a[i]<ans[flag-1]){                
                flag--;
                ans[flag+1]=ans[flag];
            }
            ans[flag]=a[i];
        }
        
        System.out.println(Arrays.toString(ans));
    }
}
