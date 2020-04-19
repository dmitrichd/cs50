/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>

#include "helpers.h"
#define limit 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // binary search without recursion
    int start = 0;
    int end = n;

    while (start <= end)
    {
        int mid = start + (end-start)/2;

        if (value == values[mid])
        return true;

        if (value > values[mid])
        start = mid + 1;
        else
        end = mid - 1;

    }

return false;

    /*simplest linear search with
    for (int i = 0; i <= n; i++)
    {
        if (values[i] == value)
        return true;

    }

    return false;
    */
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
   //lets try counting sort

   int cArr[limit] = {0}; //createa counting array

   for (int i = 0; i <= n; i++) //initializing counter array with input array data
   ++cArr[values[i]];

    /*Copy sorted array to input arraywithout zeroes, and
    if there is no such a number, just skip zeroe in counting array*/
   for (int i = 0, v = 0; i < limit; i++)
   {
        if (cArr[i] > 0)
        {
            for (int m = 1; m <= cArr[i]; m++)
            {
            values[v] = i;
            ++v;
            }
        }

   }

return;

   /*simplest bubble sort that stops if array is sorted*/
   /*bool sorted = false;

    while (!sorted)
    {
        sorted = true;

        for(int i = 0; i < n-1; i++)
        {
            if (values[i]>values[i+1])
            {
                sorted = false;
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;

            }

        }
    }

    return; */
}
