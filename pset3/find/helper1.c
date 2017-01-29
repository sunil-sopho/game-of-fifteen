/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
   int start=0, mid = n/2, end = n-1;
   if(value==values[0]||value==values[n-1])
   {
       return true;
   }
   for(int i=0;;i++)
   {
       if(value==values[mid])
        {
           return true;
        }
       else if(value>values[mid])
        {
           start = mid+1;
           mid = (start + end)/2;
        }   
        else if(value < values[mid])
        {
            end = mid;
            mid = (start+end)/2;
        }    
        if(start>=end)
        break;
   }  
   return false;
}
    

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int temp,i,j,pos;
    for(i=0;i<n;i++)
    { 
        temp = *(values+i);
        pos=i;
        for(j = i + 1;j < n;j++)
        {
            if(values[pos] > values[j])
            {
                temp = *(values+j);
                pos = j;
            }
        }
        *(values +pos)=*(values+i);
        *(values + i) = temp;
    }
}
