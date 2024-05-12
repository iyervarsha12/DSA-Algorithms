/*
	Implementation of the peakfinder (1D) algorithm, where a peak is defined as the value of that array index being greater than or equal to the values of the indexes next to it.
*/

#include <stdio.h>
#define ARRSIZE 7

int peakfinder(int arr[],int start, int end)
{
	int mid = (start+end)/2;
	
	//boundary conditions


	if((mid==0)&&(arr[mid]>=arr[mid+1]))
		return arr[mid];
	else if((mid==ARRSIZE-1)&&(arr[mid]>=arr[mid-1]))
		return arr[mid];
	
	if(arr[mid]<arr[mid-1])
		peakfinder(arr,start,mid-1);
	else if(arr[mid]<arr[mid+1])
		peakfinder(arr,mid+1,end);
	else 
		return arr[mid];
	
}


int main(int argc, char *argv[])
{
	//2,4,3,5,6,7,1
	int arr[ARRSIZE]={4,6,5,3,2,1,1};
	//Recursive approach:
	printf("\nPeakfinder returns %d",peakfinder(arr,0,ARRSIZE-1));
	
	
	/*
	//Straightforward approach:
	for(int i=0;i<ARRSIZE;i++)
	{
		if((i==0)&&(arr[i]>=arr[i+1]))
			printf("\nPeak is %d at position %d",arr[i],i);
		else if((i==ARRSIZE-1)&&(arr[i]>=arr[i-1]))
			printf("\nPeak is %d at position %d",arr[i],i);
		else if((arr[i]>=arr[i-1])&&(arr[i]>=arr[i+1]))
			printf("\nPeak is %d at position %d",arr[i],i);
	}
	*/
	
	return 0;
}