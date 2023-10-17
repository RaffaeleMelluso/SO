#include <stdio.h>
#include <stdlib.h>
int range_of_even( int *nums, int length, int *min, int *max)
{
    int i,c=0;
    for(i=0;i<length;i++)
    {
        if(nums[i]%2==0)
        {
            c++;
            if(nums[i]>*max)
                *max=nums[i];
            if(nums[i]<*min)
                *min=nums[i];
        }
    }
    if(c>0)
        return 1;
    else
        return 0;
}
void main()
{
    int v[]={-1, 2, 7, 4};
    int min=99, max=0, len=4;
    printf("Risultato operazione %d\n", 
    range_of_even(&v,len,&min,&max));
    printf("Min %d, Max %d\n",min, max);
}