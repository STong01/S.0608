//二叉排序树的存储结构采用二叉链表作为存储结构
#define _CRT_SECURE_NO_WARNINGS
#define MAXNODE 300
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int datatype; //二叉链表结点类型
typedef struct Node
{
	datatype data;    
	struct Node *lchild, *rchild;
}NodeType;
//代码如下:
int Binary_Search(int data[], int key, int n)
{
	int mid;    
	int low = 1, high = n;
	while (low <= high)
	{
		mid = (low + high) / 2;        
		if (key == data[mid]) 
			return mid;
		else if (key<data[mid]) 
			high = mid - 1;        
		else low = mid + 1;
	}
	return 0;
}
void zhebansearch()
{
	int data[MAX]; 
	int n, i, key, j;
	printf("请输入数组的长度：");  
	scanf("%d", &n); 
	printf("请输入一组数:");
	for (i = 1; i <= n; i++)  
		scanf("%d", &data[i]);
	printf("请输入你要找的的关键码:"); 
	scanf("%d", &key);
	j = Binary_Search(data, key, n);  
	if (j == 0)  
		printf("没有此关键码!\n");
	else 
		printf("此关键码:%d\n", data[j]);
}

int SearchData(NodeType *T, NodeType **p, NodeType **q, datatype kx)
{
	int flag = 0; 
	*q = T;
	while (*q)
	{
		if (kx>(*q)->data){
			*p = *q; 
			*q = (*q)->rchild; 
		}
		else
		{
			if (kx<(*q)->data)
			{
				*p = *q; 
				*q = (*q)->lchild;
			}
			else
			{
				flag = 1; 
				break;
			}
		}
	}    
	return flag;
}
int InsertNode(NodeType **T, datatype kx)
{
	int flag = 0;
	NodeType *p = *T, *q, *s;
	if (!SearchData(*T, &p, &q, kx))
	{
		s = (NodeType*)malloc(sizeof(NodeType));
		s->data = kx;
		s->lchild = NULL;
		s->rchild = NULL;
		if (p == NULL)
		{
			*T = s;
		}
		else
		{
			if (kx>p->data)
				p->rchild = s;
			else
				p->lchild = s;
		}
		flag = 1;
	}
	return flag;
}
int DeleteNode(NodeType **T, datatype kx)
{
	int flag = 0;    
	NodeType *p = *T, *q, *s, **f;
	if (SearchData(*T, &p, &q, kx))
	{
		if (p == q) /* 待删除结点为根结点 */
		{
			f = T;
		}
		else
		{
			f = &(p->lchild);
			if (kx>p->data)            
				f = &(p->rchild);
		}
		if (q->rchild == NULL){ 
			*f = q->lchild; 
		}
		else
		{
			if (q->lchild == NULL){ 
				*f = q->rchild; 
			}
			else
			{
				p = q->rchild;    
				s = p;    
				while (p->lchild)
				{
					s = p;    
					p = p->lchild;
				}
				*f = p;        
				p->lchild = q->lchild;
				if (s != p)
				{
					s->lchild = p->rchild; 
					p->rchild = q->rchild;
				}
			}
		}        
		free(q); 
		flag = 1;
	}
	return flag;
}
void InOrder(NodeType *bt)
{
	if (bt == NULL)        
		return;
	InOrder(bt->lchild);    
	printf("%5d", bt->data);
	InOrder(bt->rchild);
}
void menu()
{
	printf("1：折半查找\n"); 
	printf("2：随机建立二叉树\n");
	printf("3：删除二叉树上的结点\n"); 
	printf("4：退出！\n");
	printf("请选择你的操作：");
}
void main()
{
	int n, i;    
	NodeType *T = NULL;
	while (1)
	{
		menu();    
		scanf("%d", &i); 
		if (i == 4) 
			break;
		switch (i)
		{
		case 1:
			zhebansearch(); 
			break;
		case 2:
		{/*插入并建立二叉树*/
				  int flag, b, d[MAX], i = 1; 
				  datatype kx;
				  printf("请输入数组长度:"); 
				  scanf("%d", &n); 
				  b = n;
				  srand(time(0));          
				  kx = rand() % 100; 
				  d[0] = kx;
				  while (n != 0)
				   {
					   flag = InsertNode(&T, kx);
					   if (flag == 0)
					   {
						   printf("Insert Failed\n"); 
						   break;
					   }
					   kx = rand() % 100; 
					   d[i] = kx; 
					   n--; 
					   i++;
				   }    
				  printf("随机产生的数:");
				   for (i = 0; i<b; i++)
					   printf("%4d", d[i]); 
				   printf("\n"); 
				   printf("二叉树建立后的遍历:");
				   InOrder(T); 
				   printf("\n\n"); 
				   break; }
		case 3:
		{/*删除二叉树上的结点*/
				   int flag; datatype kx;
				   printf("请输入你要删出的节点数:");
				   scanf("%d", &kx); 
				   flag = DeleteNode(&T, kx);
				   if (flag == 0)
				   {
					   printf("Deleted Failed\n");
				   }
				   else
				   {
					   printf("Deleted successed\n"); 
					   printf("  删除后的遍历:"); 
					   InOrder(T); 
					   printf("\n\n");
				   }
				   break;
		}
		}
	}
}