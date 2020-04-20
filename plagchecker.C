#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
char title_stack[500][140];
int top=-1;
struct node
{
	char c[140],title[100];
	struct node *rlink;
	struct node *llink;
};
struct node *first=NULL;
void push(char c[100])
{
	char ch[100];
	strcpy(ch,c);
	if(top!=499)
	{
		top++;
		strcpy(title_stack[top],ch);
	}
	else
		printf("the stack is full\n");
	
}
void addtofile(struct node* doc)
{
	FILE* fi;
	fi=fopen("C:\\Users\\abhay\\Desktop\\testfile.txt","a");
	if(fi!=NULL)
	{
		struct node *curr=doc,*prev=NULL,*next=NULL;
			fseek(fi,0,SEEK_END);
			fwrite(curr,sizeof(struct node),1,fi);
			//fprintf(fi,"%s\t%s\n",curr->title,curr->c);
			printf("writing %s to the file\n",curr->title);
			fclose(fi);
	}
	else
		printf("file open error\n");
	
}
void stckdisp()
{
	int i;
	printf("--------------------\nDISPLAYING THE TITLES REJECTED\n--------------------\n");
	if(top==-1)
		printf("there are no documents in this stack\n");
	else
	{
		for(i=0;i<=top;i++)
		printf("%s",title_stack[i]);
	}
}
void add(struct node* p)
{
	struct node* temp;
	if(first==NULL)
	{
		first=p;
		p->rlink=NULL;
		p->llink=NULL;
	}
	else
	{
		temp=first;
		while(temp->rlink!=NULL)
		{
			temp=temp->rlink;
		}
		temp->rlink=p;
		p->llink=temp;
		p->rlink=NULL;
	}
}
void compare(float per)
{
	struct node* p,* temp;
	p=(struct node*)malloc(sizeof(struct node));
	p->llink=NULL;
	p->rlink=NULL;
	char split1[140][140],split2[140][140],c,ti[100],rjti[100];
	int flag=0,i,j=0,m=0,len1,len2,ctr=0,ctr2=0,count=0,gcount,tic=0;
	float res,samenum,numwrds;
	printf("---------------------------------\nenter the title\n--------------------------------\n");
		fflush(stdin);
		fgets(ti,90,stdin);
		strcpy(p->title,ti);
		fflush(stdin);
		printf("--------------------------------\nenter the description(press tab when done typing)\n--------------------------------\n");
		scanf("%[^\t]s",p->c);
	if(first==NULL)
	{
		printf("\nthere is no existing linked list\n");
		printf("adding Document to database\n");
		add(p);
		addtofile(p);
	}
	else
	{
		temp=first;
		len2=strlen(p->c);
			for(i=0;i<=len2;i++)
			{
				if(p->c[i]==' '||p->c[i]=='\0')
				{
					split2[ctr2][m]='\0';
					ctr2++;
					m=0;
				}
				else
				{
					split2[ctr2][m]=p->c[i];
					m++;
				}
			}
		while(temp!=NULL)
		{
			len1=strlen(temp->c);
			for(i=0;i<=len1;i++)
			{
				if(temp->c[i]==' '||temp->c[i]=='\0')
				{
					split1[ctr][j]='\0';
					ctr++;
					j=0;
				}
				else
				{
					split1[ctr][j]=temp->c[i];
					j++;
				}
				
			}
			ctr=ctr+1;
			for(i=0;i<ctr;i++)
			{
				if(strcmp(split2[i],split1[i])==0)
					count++;
			}
					numwrds=ctr;
					samenum=count;
				res=(samenum/numwrds)*100;
				if(res>per)
				{
					flag=1;
					break;
				}
			temp=temp->rlink;
			ctr=0;
			count=0;
		}
				printf("the number of words that are same is: \n%f\n",samenum);
				printf("the percentage of plagiarism is :\n%f\n",res);
				printf("the number of words counted is : %f\n",numwrds);
		if(flag==1)
		{
			printf("\nthe document is plagiarised above the mentioned limit with the document titled: %s\nadding to reject stack\n",temp->title);
			strcpy(rjti,p->title);
			push(rjti);
		}
		else
		{
			printf("the document's plagiarism level is under the mentioned percentage\nadding document to database\n");
			add(p);
			addtofile(p);
		}
	}
	
}
void display()
{
		struct node* temp;
		if(first==NULL)
			printf("there is no data to display\n");
		else
		{
			temp=first;
			printf("--------------------\nDOCUMENTS STORED ARE\n--------------------\n");
			while(temp!=NULL)
			{
				printf("\n%s\n%s\n",temp->title,temp->c);
				temp=temp->rlink;
			}
		}
}
void delete_proj()
{
	char key[100];int flag=0;
	struct node* temp,*prev,*next;
	if(first==NULL)
		printf("the list is empty\n");
	else
	{
	printf("enter the Title of the document to be deleted\n");
	fflush(stdin);
	fgets(key,100,stdin);
	temp=first;
		if(strcmp(first->title,key)==0 && first->rlink==NULL && first->llink==NULL)
		{
			flag=1;
			printf("deleting the Document : %s\n",temp->title);
			first=NULL;
			free(temp);
		}
		else if(strcmp(first->title,key)==0 && first->rlink!=NULL)
		{
			flag=1;
			first=first->rlink;
			first->llink=NULL;
			printf("deleting the Document : %s\n",temp->title);
			free(temp);
		}
		else
		{
			while(temp!=NULL)
			{
				if(strcmp(temp->title,key)==0 && temp->rlink!=NULL)
				{
					flag=1;
					printf("deleting document : %s\n",temp->title);
					prev=temp->llink;
					next=temp->rlink;
					prev->rlink=next;
					next->llink=prev;
					free(temp);
					break;
				}
				else if(strcmp(temp->title,key)==0 && temp->rlink==NULL)
				{
					printf("deleting Document : %s\n",temp->title);
					prev=temp->llink;
					prev->rlink=NULL;
					free(temp);
					break;
				}
				temp=temp->rlink;
			}
		}
	}
	if(flag==0)
		printf("no document was found\n");
}
int main()
{   
    int i,a=1,b;
	float per;
	printf("enter the percentage of plagiarism acceptable\n");
	scanf("%f",&per);
	while(a)
	{
		printf("press\n1 to display reject stack\n2 to compare and add Document\n3 to display the Documents\n4 to delete a Document\n");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				system("cls");
				stckdisp();
				break;
			case 2:
				system("cls");
				compare(per);
				break;
			case 3:
				system("cls");
				display();
				break;
			case 4:
				system("cls");
				delete_proj();
				break;
			//case 5:
			//	system("cls");
			//	readfromfile();
			//	break;
			default:
				printf("wrong choice\n");
		}
		printf("enter 1 to continue and 0 exit\n");
		scanf("%d",&b);
		a=b;
		system("cls");
	}
	return 0;
}