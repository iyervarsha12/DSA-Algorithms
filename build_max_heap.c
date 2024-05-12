/*
	Implementation of Heapsort using a max-heap.
*/

#include <stdio.h>
#define ARRSIZE 10

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void heapify(int arr[], int n, int i) //i is parent,  makes subtree with i as root into a max_heap recursively
{
	int largest = i;
	int left=2*i+1;
	int right=2*i+2;
	
	if((left<n)&&(arr[left]>arr[largest]))
		largest = left;
	if((right<n)&&(arr[right]>arr[largest]))
		largest = right;
	
	if(largest==i)
		return;
	else //largest is no longer root
	{
		swap(&arr[largest],&arr[i]);
		heapify(arr,n,largest); //since larger now contains the smaller part.
		
	}
}



void heapsort(int arr[])
{
	//building maxheap
	for(int i=(ARRSIZE/2) -1;i>=0;i--)
		heapify(arr,ARRSIZE,i);
	
	for(int i=ARRSIZE-1;i>0;i--)
	{
		swap(&arr[0],&arr[i]);
		heapify(arr,i,0); //root is the changed thing, remove last node and do it
		
	}
	
}

int main(int argc, char *argv[])
{

	int arr[ARRSIZE]={16,4,10,14,7,9,3,2,8,1};
	heapsort(arr);
	
	for(int i=0;i<ARRSIZE;i++)
		printf("%d ",arr[i]);
	return 0;
}