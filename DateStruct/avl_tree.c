#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
typedef char TElemType;
typedef struct AVLNode
{
	TElemType data;
	struct AVLNode *Left,*Right;
	int Height;
}AVLNode;

int Height(AVLNode *r)
{
	if(r == NULL)
	{
		return 0;
	}
	return r->Height;
}

AVLNode *SingleRotateWithRight(AVLNode *K2)
{
	AVLNode *K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	K2->Height = MAX(Height(K2->Left),Height(K2->Right)) + 1;
	K1->Height  = MAX(Height(K1->Left),Height(K1->Right)) + 1;

	return K1;
}

AVLNode *SingleRotateWithLeft(AVLNode *K2)
{
	AVLNode *K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K2->Height = MAX(Height(K2->Left),Height(K2->Right)) + 1;
	K1->Height = MAX(Height(K1->Left),Height(K1->Right)) + 1;

	return K1;
}

AVLNode *DoubleRotateLeftRight(AVLNode *K3)
{
	K3->Left = SingleRotateWithLeft(K3->Left);
	return SingleRotateWithRight(K3);
}

AVLNode *DoubleRotateRightLeft(AVLNode * K3)
{
	K3->Right = SingleRotateWithRight(K3->Right);
	return SingleRotateWithLeft(K3);
}


AVLNode *Insert(AVLNode *T,TElemType x)
{
	if(T == NULL)
	{
		T = malloc(sizeof(*T));
		T->data =x;
		T->Left = NULL;
		T->Right = NULL;
		T->Height = 1;
		return T;
	}
	if(x > T->data)
	{
		T->Right = Insert(T->Right,x);
		T->Height = MAX(Height(T->Right),Height(T->Left))+1;
		if(Height(T->Right) - Height(T->Left) > 1)
		{
			if(x > T->Right->data)
			{
				T = SingleRotateWithLeft(T);
			}
			else 
			{
				T = DoubleRotateRightLeft(T);
			}
		}		
	}    
	else if(x < T->data)
	{
		T->Left = Insert(T->Left,x);
		T->Height = MAX(Height(T->Right),Height(T->Left))+1;
		if(Height(T->Left) - Height(T->Right) > 1)
		{
			if(x > T->Left->data)
			{
				T = DoubleRotateLeftRight(T);
			}
			else 
			{
				T = SingleRotateWithRight(T);
			}
		}
	}
	return T;
}

void pre_order(AVLNode *r)
{
	if(r == NULL)
	{
		return ;
	}
	printf("%c ",r->data);
	pre_order(r->Left);
	pre_order(r->Right);
}

void mid_order(AVLNode *r)
{
	if(r == NULL)
	{
		return ;
	}
	
	mid_order(r->Left);


	printf("%c ",r->data);

	
	mid_order(r->Right);
}


void post_order(AVLNode *r)
{
	if(r == NULL)
	{
		return ;
	}
	post_order(r->Left);
	post_order(r->Right);
	printf("%c ",r->data);
}

int main()
{
	AVLNode *T = NULL;
	int i=0;
	char str[1024];
	gets(str);
	while(str[i])
	{
		T = Insert(T, str[i]);
		i++;
	}
	//pre_order(T);
	//putchar('\n');
	mid_order(T);
	putchar('\n');
	//post_order(T);
	//putchar('\n');
}
