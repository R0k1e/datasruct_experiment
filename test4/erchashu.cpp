#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    struct node* lc;
    struct node* rc;
    char data;
} tree;

char *num=(char*)malloc(sizeof(char)*10000);
int judge=1;

void createtree(tree *root);
void printree(tree *root,int level);

int main ()
{
    gets(num);
    tree *root=(tree*)malloc(sizeof(tree));
    createtree(root);
    if(judge==1)
        printree(root,0);
    system("pause");
    return 0;
}


void createtree(tree *root) //创建二叉树
{
    if(!root) return;
    root->data=*num;
    num++;
    if(*num!='*'&&*num!=0)
    {
        root->lc=(tree*)malloc(sizeof(tree));
        createtree(root->lc);
    }
    else if(*num==0)
    {
        printf("error input");
        exit(0);
    }
    else
    {
        root->lc=NULL;
        num++;
    }
    if(*num!='*'&&*num!=0)
    {
        root->rc=(tree*)malloc(sizeof(tree));
        createtree(root->rc);
    }
    else if(*num==0)
    {
        printf("error input");
        exit(0);
    }
    else
    {
        root->rc=NULL;
        num++;
    }
}



void printree(tree* root,int level) //横向打印二叉树
{
	int i;
	if(!root) 
    {
		for(i=0;i<level;i++) 
			printf("    ");
		printf("\n");
		return;
	}
	printree(root->rc,level+1);
	for(i=0;i<level;i++) 
		printf("    ");
	printf("%c\n",root->data);
	printree(root->lc,level+1);
}
