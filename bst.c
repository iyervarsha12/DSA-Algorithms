/*
	Implementation of a binary search tree with functions for leftmost, rightmost, inserting element and sorting the tree values.
*/

#include <stdio.h>
#include<stdlib.h>

#define k 0 //atleast this much distance apart
#define ARRSIZE 10

struct Node
{
	int key;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

typedef struct Node node;
node *root=NULL;

node* leftmost(node *i) //find min
{
	if((i->left)==NULL)
		return i;
	else leftmost(i->left);
}

node* rightmost(node *i) //find max
{
	if((i->right)==NULL)
		return i;
	else rightmost(i->right);
}

int recursiveinsert(node *i,node *toinsert) //i is parent. 0 if left, 1 if right
{
	if((i!=NULL)&&(toinsert->key < i->key + k)&&(toinsert->key > i->key - k))
		return -1;
	else if((toinsert->key > i->key)&&(i->right==NULL))
	{
		i->right=toinsert;
		toinsert->parent = i;
		return 1;
	}
	else if((toinsert->key < i->key)&&(i->left==NULL))
	{
		i->left=toinsert;
		toinsert->parent = i;
		return 0;
	}
	else if(toinsert->key > i->key)
		recursiveinsert(i->right,toinsert);
	
	else //if(toinsert->key < i->key)
		recursiveinsert(i->left,toinsert);
}


int insertelement(int key)
{
	node *temp = malloc((size_t)sizeof(node));
	temp->key=key;
	temp->parent=NULL;
	temp->left=NULL;
	temp->right=NULL;
	
	if(root==NULL)
		root=temp;
	else
	{
		
		int side = recursiveinsert(root,temp);
		if(side==-1)
		{
			printf("\nElement %d could not be inserted.",key);
			free(temp);
		}
		//else 
			//printf("\nElement inserted with parent %d on the %s side",(temp->parent)->key,side? "right":"left");
	}
	return temp->key;
}

int i=0;

void storeSorted(node *root, int arr[]) 
{ 
    if (root != NULL) 
    { 
        storeSorted(root->left, arr); 
        arr[i++] = root->key; 
        storeSorted(root->right, arr); 
    } 
} 



int main(int argc, char *argv[])
{
	
	int arr[ARRSIZE]={16,4,10,14,7,9,3,2,8,1};
	for(int i=0;i<ARRSIZE;i++)
	{
		insertelement(arr[i]);
	}
	storeSorted(root,arr);
	
	for(int i=0;i<ARRSIZE;i++)
	{
		printf("%d ",arr[i]);
	}
	
	printf("\nMinimum node is %d",(leftmost(root))->key);
	printf("\nMaximum node is %d",(rightmost(root))->key);
	return 0;
}