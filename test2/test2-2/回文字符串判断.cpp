#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;

//栈结构 
typedef struct StackNode{
	ElemType data;
	struct StackNode *next;
}StackNode,*LinkStackPrt; 

typedef struct LinkStack{
	LinkStackPrt top;
	int count;
}LinkStack;

//队列结构
typedef struct QueueNode{
	ElemType data;
	struct QueueNode *next;
}QueueNode,*LinkQueuePrt; 

typedef struct LinkQueue{
	LinkQueuePrt front,rear;
}LinkQueue; 

//栈操作函数 
bool pushStack(LinkStack *s,ElemType e);
bool popStack(LinkStack *s,ElemType *e);
void initStackLink(LinkStack *s);

//队列操作函数
void initQueueLink(LinkQueue *q); 
bool pushQueue(LinkQueue *q,ElemType e);
bool popQueue(LinkQueue *q,ElemType *e);

int main()
{
	LinkStack s;
	LinkQueue q;
	ElemType ch,a,b; 
	bool success=1,truth=1;
	scanf("%c",&ch);
	initStackLink(&s); 
	initQueueLink(&q);
	while(ch!='#')
	{
		success=pushStack(&s,ch);
		if(success==0)
		printf("进栈错误");
		success=pushQueue(&q,ch);
		if(success==0)
		printf("进队列错误");
		ch=getchar();
	}
	while(s.top!=NULL&&truth==1)
	{
		success=popStack(&s,&a);
		if(success==0)
		printf("出栈错误");
		success=popQueue(&q,&b);
		if(success==0)
		printf("出队列错误");
		if(a!=b)
		{
			truth=0;
			break;
		}
	}
	if(truth==1)
	printf("It is palindrome number.\n");
	else
	printf("It is not palindrome number.\n");
	return 0;
}

void initStackLink(LinkStack *s)
{
	(*s).top=NULL;
	(*s).count=0;
}

bool pushStack(LinkStack *s,ElemType e)
{
	LinkStackPrt p=(LinkStackPrt)malloc(sizeof(StackNode));
	p->data=e;
	p->next=s->top;
	s->top=p;
	s->count++;
	return 1;
}

bool popStack(LinkStack *s,ElemType *e)
{
	LinkStackPrt p;
	if(s->top==NULL)
	{
		return 0;
	}
	else
	{
		*e=s->top->data;
		p=s->top;
		s->top=s->top->next;
		free(p);
		s->count--;
		return 1;
	}
}

void initQueueLink(LinkQueue *q)
{
	q->front=(LinkQueuePrt)malloc(sizeof(QueueNode));
	q->rear=q->front;
	q->front->next=NULL;
}

bool pushQueue(LinkQueue *q,ElemType e)
{
	LinkQueuePrt p=(LinkQueuePrt)malloc(sizeof(QueueNode));
	p->data=e;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
	return 1;
}

bool popQueue(LinkQueue *q,ElemType *e)
{
	LinkQueuePrt p;
	if(q->front==q->rear)
	return 0;
	else
	{
		p=q->front->next;
		*e=p->data;
		q->front->next=p->next;
		
		if(q->rear==p)
		q->rear=q->front;
		
		free(p);
		return 1;
	}
}
