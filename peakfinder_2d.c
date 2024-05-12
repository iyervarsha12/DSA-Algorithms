/*
	Implementation of the peakfinder (2D) algorithm, where a peak is defined as the value of that array index being greater than or equal to the values of the indexes next to it.
	It has code to find the maximum both recursively and in a more straightforward way.
*/

#include <stdio.h>

#define m 4 //column
#define n 3 //row

/*
int maxfinder(int arr[n][m],int size, int midcol)
{
	if(size==1)
		return arr[0][midcol];
	return maxfinder(arr[size-1][midcol],maxfinder(arr,size-1,midcol));
}
*/

int peakfinder(int arr[n][m],int startcol, int endcol)
{
	int midcol = (startcol+endcol)/2; //j
	int i=0; //for global maximum
	
	/*
	//finding global max recursively
	int max = maxfinder(arr,n);
	*/
	
	//finding global max straighforward
	int max=arr[i][midcol];
	for(int k=1;k<n;k++)
	{
		if(max<arr[k][midcol])
		{
			max = arr[k][midcol];
			i=k;
		}
	}
	
	
	//max is at pos i,midcol
	//boundary conditions
	if((midcol==0)&&(arr[i][midcol]>=arr[i][midcol+1]))
		return max;
	else if((midcol==m-1)&&(arr[i][midcol]>=arr[i][midcol-1]))
		return max;
	
	if(arr[i][midcol-1]>arr[i][midcol])
		peakfinder(arr,startcol,midcol-1);
	else if(arr[i][midcol+1]>arr[i][midcol])
		peakfinder(arr,midcol+1,endcol);
	else return max;
}


int main(int argc, char *argv[])
{

	int arr[n][m]={{1,0,0,1},{2,3,4,5},{6,9,10,0}};
	
	//2d recusrive algorithm
	printf("\nPeak is %d",peakfinder(arr,0,m-1));
	
	
	return 0;
}