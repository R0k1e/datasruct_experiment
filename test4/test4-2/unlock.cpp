#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//�����ļ���Ϊlock.txt
//����ļ���Ϊout.txt 
typedef struct Node{
	int weight,parent,lc,rc;
	char *code;
}Node;

typedef struct Htree_head{
	char flag[5];
	char last;
	char unused[10];
}Fhead;

void initHtree(Node *ht)//���ĳ�ʼ�� 
{
	for(int i=0;i<512;i++)
	{
		ht[i].weight=0;
		ht[i].lc=-1;
		ht[i].rc=-1;
		ht[i].parent=-1;
		ht[i].code = (char *) calloc(sizeof(char),256);
	}
	
}
int createHtree(Node *ht,int *Num)//���ɹ������� 
{
	for(int i=0;i<256;i++){
		ht[i].weight=Num[i];
	} //��Num���鴫�ص��ַ�Ƶ�ȸ������ĸ�Ԫ��weight 
	
	int i,j,k,m;
	for(i=256;i<511;i++)//�������ĸ�Ԫ�� 
	{
		j=-1,k=-1;
		for(int l=0;l<i;l++)
		{
			if(ht[l].parent==-1&&ht[l].weight!=0){
				if(j==-1){
					j=l;
				}
				else if(k==-1){
					k=l;
					if(ht[j].weight>ht[k].weight){
						m=j;
						j=k;
						k=m;
					}
				}
				else if(ht[l].weight<ht[j].weight){
					k=j;
					j=l;
				}
				else if(ht[l].weight<ht[k].weight)
				k=l;
			}
		}
		if(k==-1)//ֻʣ��һ��Ԫ��û��˫�ף������Ǹ�˭�� 
		break;
		/*��i��j��˫��*/
		ht[j].parent=i;
		ht[k].parent=i;
		ht[i].weight=ht[j].weight+ht[k].weight;
		ht[i].lc=j;
		ht[i].rc=k;
	}
	if(k!=-1)
	return i;
	else 
	return j;//���ظ��ڵ� 
}
void getHCode(Node *ht,int root,int index,char *code)//���ɹ������� 
{
	char Code[256];//���ڵ��ú�����ָ�code 
	strcpy(Code,code);
	if(ht[root].lc!=-1&&ht[root].rc!=-1)
	{
		code[index]='0';
		getHCode(ht,ht[root].lc,index+1,code);
		strcpy(code,Code);//code���ص���ǰ 
		
		code[index]='1';
		getHCode(ht,ht[root].rc,index+1,code);
		strcpy(code,Code);//ͬ�� 
	}
	else{
		strcpy(ht[root].code,code);//���������봫���� 
	}
}

void Hdecoding(Node *ht,int root,char last)//���뺯�� 
{
	FILE *fpIn=fopen("lock.txt","rb");
	FILE *fpOut=fopen("out.txt","wb");
	fseek(fpIn,0L,SEEK_END);//�����ļ�β 
	long fileSize = ftell(fpIn);//�ļ��ܳ��� 
	fseek(fpIn,16+sizeof(int)*256,SEEK_SET);//����Ԫ���� 
	long curLocation = ftell(fpIn);//���µ�ǰλ�� 
	
	unsigned char value,valueOut;
	int index=0,i=root,j;
	fread(&value,sizeof(unsigned char),1,fpIn);
	
	bool finished=false;
	while(!finished)
	{
		if(ht[i].lc==-1&&ht[i].rc==-1){
			valueOut=i;
			fwrite(&valueOut,sizeof(unsigned char),1,fpOut);
			i=root;
			if(curLocation>=fileSize&&index>=last)
			break;
		}
		
		j=(value & (1 << ((index) ^ 7)));
		if(j==0)
		i=ht[i].lc;
		else
		i=ht[i].rc;
		
		if(++index>=8){
			index=0;
			if(curLocation>=fileSize){
				break;//ǿ���˳���������bug��������ѭ�� ����ɱ�������˰����� 
			}
			fread(&value,sizeof(unsigned char),1,fpIn);
			curLocation=ftell(fpIn);
		}
	}
	printf("Coding success!\n");//����ɹ��������Լ� 
	fclose(fpIn);
	fclose(fpOut);
}

int main()
{
	FILE *fpIn=fopen("lock.txt","rb");//�򿪼����ļ� 
	/*ʶ��Ԫ����*/ 
	Fhead head;
	int Num[256];
	fread(&head,sizeof(Fhead),1,fpIn);//��ȡԪ���� 
	if(head.flag[0]!='b'||head.flag[1]!='u'||head.flag[2]!='p'||head.flag[3]!='t')//����Ԫ�����ж��Ƿ�Ϊ������ɽ���ļ����ļ� 
	{
		printf("Error:It is not file which I can understand.\n");//��������ļ����������ܽ�ģ��������� 
		return 0;
	}
	fread(Num,sizeof(int),256,fpIn);//��ȡ�����ļ��и��ַ�Ƶ�ȣ��������ɹ��������͹��������� 
	fclose(fpIn);//�д򿪵�Ȼ�йر� 
	/*������������������ĳ�ʼ��*/
	Node ht[511];
	int root,last=head.last;//�˴�Ϊbug���ֺ���޲�������ʼ����head���ݻ��������������� 
	initHtree(ht);//���ĳ�ʼ�� 
	root=createHtree(ht,Num);//���ɹ������������ظ��ڵ� 
	char code[256];//Ϊÿ���ַ����ٹ�������Ĵ洢�ռ� 
	getHCode(ht,root,0,code);//���ɹ������벢����Node
	
	Hdecoding(ht,root,last);//��������ļ� 
	
	return 0;
}
