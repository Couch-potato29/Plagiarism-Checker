#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

int plag_level = 85;
int fileflag;
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
        printf("Stack is Full!!!\n");
    
}

void addtofile(struct node* doc)
{
    //char fipath[1000] = "C:\\Users\\HariK\\Desktop\\";
    char fipath[1000] = "/home/harikrishnan/Desktop/Database/";
    char temp[100];
    strcpy(temp,doc->title);
    strcat(fipath,temp);
    strcat(fipath,".txt");
    FILE *fi;
    fi = fopen(fipath,"w+");
    fprintf(fi,"%s",doc->c);
    fclose(fi);
}

void readdatabase()
{
    DIR *d;
    struct dirent *dir;
    d = opendir("/home/harikrishnan/Desktop/Database");
    if (d) 
    {
        while ((dir = readdir(d)) != NULL) 
        {
            struct node* p;
            p = (struct node*)malloc(sizeof(struct node));
            p ->llink=NULL;
            p ->rlink=NULL;
            if (dir->d_type == DT_REG)
            {
                char temp[100];
                char temp2[100];
                //printf("%s\n", dir->d_name);
                strcpy(temp,dir->d_name);
                for(int i = 0;i < strlen(temp);i ++)
                {
                    char c = temp[i];
                    if(c != '.')
                    {
                        temp2[i] = c;
                    }
                    if(c == '.')
                    {
                        //temp2[i] = "\0";
                        break;
                    }
                }
                FILE *fi;
                char doctemp[140];
                char fipath[500] = "/home/harikrishnan/Desktop/Database/";
                strcat(fipath,temp);
                //strcat(fipath,".txt");
                fi = fopen(fipath,"r");
                if(fi != NULL)
                {
                    int e;
                    char f;
                    int k = 0;
                    while ((e = getc(fi)) != EOF)
                    {
                        f = (char)(e);
                        doctemp[k] = f;
                        k++;
                    }
                    strcpy(p->title,temp2);
                    strcpy(p->c,doctemp);
                    //printf("%s\n",p->title);
                    //printf("%s\n",p->c);
                    add(p);
                    
                    k = 0;
                }
                fclose(fi);
                memset(temp, '\0', strlen(temp));
                memset(temp2, '\0', strlen(temp2));
                memset(doctemp, '\0', strlen(doctemp));
                //strcpy(temp,"");
                //strcpy(doctemp,"");
            }
        }
    }
    closedir(d);
}

void stckdisp()
{
    int i;
    printf("--------------------\nRejected Titles\n--------------------\n");
    if(top==-1)
        printf("No Docs found!!!\n");
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
    int flag=0,i,j=0,m=0,len1,len2,ctr=0,ctr2=0,count=0;
    float res,samenum,numwrds;
    printf("1.Open a existing a file\n2.Create a new file\n");
    scanf("%d",&fileflag);
    if(fileflag == 1)
    {
        char temp[140];
        char finame[100];
        char fipath[500] = "/home/harikrishnan/Desktop/Upload/";
        printf("Copy the file into the Upload folder and type the file name below(Without file extension):\n");
        FILE *fi;
        scanf("%s",finame);
        strcat(fipath,finame);
        strcat(fipath,".txt");
        fi = fopen(fipath,"r");
        if(fi == NULL)
        {
            printf("File doesnt Exist\n");
        }
        else
        {
            int c;
            char d;
            int i = 0;
            while ((c = getc(fi)) != EOF)
            {
                d = (char)(c);
                temp[i] = d;
                i++;
            }
            strcpy(p->title,finame);
            strcpy(p->c,temp);
            printf(p->c);
            i = 0;
        }
        fclose(fi);
    }
    else if (fileflag == 2)
    {
    system('clear');
    printf("---------------------------------\nEnter the Title\n--------------------------------\n");
        fflush(stdin);
        scanf("%s",&ti);
        strcpy(p->title,ti);
        printf("--------------------------------\nEnter the content of the Document(press tab when done typing)\n--------------------------------\n");
        scanf("%[^\t]s",p->c);
    }
    if(first==NULL)
    {
        printf("\nNo Existing Linked List...\n");
        printf("Adding Document to Database...\n");
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
                    numwrds=ctr-1;
                    samenum=count-1;
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
                printf("No of Words Copied: \n%f\n",samenum);
                printf("Plagiarism Precentage:\n%f\n",res);
                printf("Total No of Words: : %f\n",numwrds);
        if(flag==1)
        {
            printf("\nThe document is plagiarised above the mentioned limit with the document titled: %s\nAdding to Rejected Stack...\n",temp->title);
            strcpy(rjti,p->title);
            push(rjti);
        }
        else
        {
            printf("The document's plagiarism level is under the mentioned percentage\nAdding document to database...\n");
            add(p);
            addtofile(p);
        }
    }
    
 }

void display()
{
        struct node* temp;
        if(first==NULL)
            printf("No Data to Display!!!\n");
        else
        {
            temp=first;
            printf("--------------------\nDocuments:\n--------------------\n");
            while(temp!=NULL)
            {
                printf("\n%s\n%s\n",temp->title,temp->c);
                temp=temp->rlink;
            }
        }
}

void delete_proj()
{

    char finame[300] = "/home/harikrishnan/Desktop/Database/";
    char key[100];int flag=0;
    struct node* temp,*prev,*next;
    if(first==NULL)
        printf("It is empty...\n");
    else
    {
    printf("Document name to be deleted:\n");
    fflush(stdin);
    scanf("%s",&key);
    strcat(finame,key);
    strcat(finame,".txt");
    temp=first;
        if(strcmp(first->title,key)==0 && first->rlink==NULL && first->llink==NULL)
        {
            flag=1;
            printf("Deleting %s...\n",temp->title);
            first=NULL;
            free(temp);
            remove(finame);
        }
        else if(strcmp(first->title,key)==0 && first->rlink!=NULL)
        {
            flag=1;
            first=first->rlink;
            first->llink=NULL;
            printf("Deleting %s...\n",temp->title);
            free(temp);
            remove(finame);
        }
        else
        {
            while(temp!=NULL)
            {
                if(strcmp(temp->title,key)==0 && temp->rlink!=NULL)
                {
                    flag=1;
                    printf("Deleting %s...\n",temp->title);
                    prev=temp->llink;
                    next=temp->rlink;
                    prev->rlink=next;
                    next->llink=prev;
                    free(temp);
                    remove(finame);
                    break;
                }
                else if(strcmp(temp->title,key)==0 && temp->rlink==NULL)
                {
                    printf("Deleting %s...\n",temp->title);
                    prev=temp->llink;
                    prev->rlink=NULL;
                    free(temp);
                    remove(finame);
                    break;
                }
                temp=temp->rlink;
            }
        }
    }
    if(flag==0)
        printf("Document not Found!!!\n");
}

int main()
{   
    int i,a=1,b;
    float per;
    readdatabase();
    //printf("Enter Plagiarism Percentage acceptable:\n");
    //scanf("%f",&per);
    per = plag_level;
    while(a)
    {
        printf("Welcome!!!\n1.Display reject stack\n2.Compare and Add Document\n3.Display the Documents\n4.Delete a Document\n");
        scanf("%d",&i);
        switch(i)
        {
            case 1:
                //system("cls");
                system("clear");
                stckdisp();
                break;
            case 2:
                //system("cls");
                system("clear");
                compare(per);
                break;
            case 3:
                //system("cls");
                system("clear");
                display();
                break;
            case 4:
                //system("cls");
                system("clear");
                delete_proj();
                break;
            default:
                printf("wrong choice\n");
        }
        printf("enter 1 to continue and 0 exit\n");
        scanf("%d",&b);
        a=b;
        system("clear");
        //system("cls");
    }
    getchar();
    return 0;
