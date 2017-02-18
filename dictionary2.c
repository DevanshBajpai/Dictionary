#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int compare(char a[],char b[])
{
	int i=0;
	if(a[i]<=122&&a[i]>=97)//For making the first alphabet of word upper case
	a[i]-=32;
	if(b[i]<=122&&b[i]>=97)
	b[i]-=32;
	for(i=1;a[i]!='\0';i++)//For making all other alphabates lowercase
	{
		if((int)a[i]<=90&&(int)b[i]>=65)
		a[i]+=32;
	}
	for(i=1;b[i]!='\0';i++)
	{
		if((int)b[i]<=90&&(int)b[i]>=65)
		b[i]+=32;
	}
	return strcmp(a,b);//returns >0 if a>b; <0 if a<b; =0 if a==b;
}
struct node
{
	char word[100];
	struct node *next;
};
struct node *head=NULL;
void add(char b[])//adding an element at the top of list. 
{
	int i;
	struct node *link;
	link=(struct node*)malloc(sizeof(struct node));
	for(i=0;b[i]!='\0';i++)
	link->word[i]=b[i];
	link->word[i]=b[i];
	link->next=NULL;
	if(head==NULL)
	head=link;
	else
	{
		link->next=head;
		head=link;
	}
}
void deletelist()//deletion of list at the end of program
{
	struct node *link;
	link=head;
	while(link!=NULL)
	{
		head=head->next;
		free(link);
		link=head;
	}
}
int size()//function to calculate the size of list.
{
	int count=0;
	struct node *link;
	link=head;
	while(link!=NULL)
	{
		count++;
		link=link->next;
	}
	return count;
}
int main()
{
	FILE *fptr;
	struct node *link,*link1;
	int i=0,j,k;
	char filename[100],ch,temp[100];
	printf("Enter the name of file to be sorted\n");
	scanf("%s",filename);//Name of the file whose content is to be sorted.
	if((fptr=fopen(filename,"r"))==NULL)
	{
		printf("Cannot open file\n");
		exit(1);
	}
	do
	{
		fscanf(fptr,"%s",temp);
		add(temp);
		ch=fgetc(fptr);
	}while(ch!=EOF);
	fclose(fptr);
	printf("the words in the file are\n\n");
	link=head;
	while(link!=NULL)//Displaying the content of the file on stdout.
	{
		printf("%s\n",link->word);	
		link=link->next;
	}
	k=size();
	link=head;
	for(i=0;i<k-1;i++)//function for sorting :bubble sort
	{
		for(j=0;j<k-i-2;j++)
		{
			if(j==0)
			{
				if(compare(link->word,link->next->word)>0)
				{
					link=link->next;
					head->next=link->next;
					link->next=head;
					head=link;
				}
			}
				if(compare(link->next->word,link->next->next->word)>0)
				{				
					link1=link->next;
					link->next=link->next->next;
					link1->next=link->next->next;
					link->next->next=link1;
				}	
			link=link->next;
		}
		link=head;
	}
	link=head;
	while(link->next!=NULL)//Removing the duplicate words.
	{
		if(strcmp(link->word,link->next->word)==0)
		{
			link1=link->next;
			link->next=link1->next;
			free(link1);
		}
		else
		link=link->next;
	}
	link=head;
	printf("\n\n\n");
	while(link!=NULL)//Printing the sorted words on stdout
	{
		printf("%s\n",link->word);	
		link=link->next;
	}
	printf("Enter the name of the file to create as dictionary\n");
	scanf("%s",filename);//Name of file for dictionary.
	if((fptr=fopen(filename,"w"))==NULL)
	{
		printf("Cannot open file\n");
		exit(1);
	}
	fprintf(fptr,"\t\t\t\t\t\t\t\t\tDictionary\n");
	link=head;
	while(link!=NULL)//Saving the sorted words in file.
	{
		fprintf(fptr,"%s\n",link->word);
		link=link->next;
	}
	deletelist();//free memory
	return 0;
}
