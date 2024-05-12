/*
	Implementation of AVL trees.
	We can find leftmost node, rightmost node, height of the tree, insert element to the tree with automatic rebalancing. 
*/

#include <stdio.h>
#include<stdlib.h>

#define k 0 //atleast this much distance apart
#define ARRSIZE 9

struct Node
{
	int key;
	int height;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

typedef struct Node node;
node *root=NULL;

node* leftmost(node *i) //find min
{
	//printf("%d ",i->key);
	if((i->left)==NULL)
		return i;
	else leftmost(i->left);
}

node* rightmost(node *i) //find max
{
	//printf("%d ",i->key);
	if((i->right)==NULL)
		return i;
	else rightmost(i->right);
}

int height(node *i)
{
	if(i==NULL)
		return -1;
	else return i->height;
}

void updateheight(node *i)
{
	int v1=height(i->left);
	int v2=height(i->right);
	if(v1>v2)
		i->height = v1+1;
	else i->height = v2+1;
}

void rightrotate(node *b)
{
	if(b==NULL)
		return;
	node *finalparent = b->parent;
	int side=0; //left
	if(finalparent!=NULL && finalparent->right ==b)
		side=1;
	node *gamma = b->right;
	node *a = b->left;
	node *alpha = a->left;
	node *beta = a->right;
	
	
	if(a!=NULL)
		a->parent = finalparent;
	b->parent = a;
	if(beta!=NULL)
		beta->parent = b;
	if(gamma!=NULL)
		gamma->parent = b;
	if(alpha!=NULL)
		alpha ->parent = a;
	a->left = alpha;
	a->right = b;
	b->left = beta;
	b->right = gamma;
	if(finalparent!=NULL)
	{
		if(side==0)
			finalparent->left = a;
		else finalparent->right = a;
		
		//root=a;
	}
	else root = a;
	updateheight(b);
	updateheight(a);
}

void leftrotate(node *a)
{
	if(a==NULL)
		return;
	node *finalparent = a->parent;
	int side=0; //left
	if(finalparent!=NULL && finalparent->right ==a)
		side=1;
	node *b = a->right;
	node *alpha = a->left;
	node *beta = b->left;
	node *gamma = b->right;
	if(b!=NULL)
		b->parent = finalparent;
	a->parent = b;
	if(gamma!=NULL)
		gamma->parent = b;
	if(alpha!=NULL)
		alpha->parent = a;
	if(beta!=NULL)
		beta->parent = a;
	b->left = a;
	b->right = gamma;
	a->left = alpha;
	a->right = beta;
	if(finalparent!=NULL)
	{
		if(side==0)
		finalparent->left = b;
		else finalparent->right = b;
		
		//root=b;
	}
	else root = b;
	updateheight(b);
	updateheight(a);
	
}

void rebalance(node *i)
{
	if(i==NULL)
		return;
	updateheight(i);
	//printf("\nelement %d with height %d, left ht %d and right ht %d",i->key, height(i),height(i->left),height(i->right));
	if(height(i->left)>=height(i->right)+2)
	{
		if(height(i->left->left) >= height(i->left->right))
		{
			//printf("IF1");
			rightrotate(i);
		}
		else
		{
			//printf("ELSE1");
			leftrotate(i->left);
			rightrotate(i);
		}
		printf("\nElement %d readjusted with parent %d",i->key,(i->parent)->key);
	}
	else if(height(i->right)>=height(i->left)+2)
	{
		if(height(i->right->right) >= height(i->right->left))
		{
			//printf("IF2");
			leftrotate(i);
		}
		else
		{
			//printf("ELSE2");
			rightrotate(i->right);
			leftrotate(i);
		}
		printf("\nElement %d readjusted with parent %d",i->key,(i->parent)->key);
	}
	i = i->parent;	
	rebalance(i);
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
	temp->height=0;
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
		//printf("\nRebalancing after entering elt %d: ",key);
		rebalance(temp);
		//printf("am back");
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
	//41,20,65,11,29,50,26,23,55
	int arr[ARRSIZE]={41,20,65,11,29,50,26,23,55};
	for(int i=0;i<ARRSIZE;i++)
	{
		insertelement(arr[i]);
	}
	printf("\nSorting: ");
	storeSorted(root,arr);
	
	for(int i=0;i<ARRSIZE;i++)
	{
		printf("%d ",arr[i]);
	}
	
	//printf("\nPATHS");
	printf("\nMinimum node is %d",(leftmost(root))->key);
	printf("\nMaximum node is %d",(rightmost(root))->key);
	return 0;
}