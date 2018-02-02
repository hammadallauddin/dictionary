#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h> 
#define dict "dictionary.txt"

FILE *data;
int n=0;
int q=0;

struct lib {char word[20], mean[50], posp[15], sent[50];};
struct lib a[500];

void search(void);    //to search a word
void new1(void);       //to add a word
void list(void);        //to show list of all words
void deletew(void);      //to delete a word

int main()
{
	system("cls");
	system("color f9");
	int mode;
	
	while(1)
	{
		system("cls");
		printf("\n\n\n___________________________\n\n");
		printf("DICTIONARY");
		printf("\n___________________________\n\n");
		
		printf("\n1.SEARCH WORD.\n2.SHOW LIST OF WORDS.\n3.ADD WORDS.\n4.DELETE WORD.\n5.EXIT.");
		printf("\n___________________________\n\n");
			
		
		printf("\n\nENTER MODE: ");
		scanf("%d",&mode);
		
		switch(mode)
		{
			case 1:
				search();
				break;
			case 2:
				list();
				break;
			case 3:
				new1();
				break;
			case 4:
				deletew();
				break;
			case 5:
				exit(0);
			default:
				printf("\nChoose only from modes 1-5");
		}
	}

}

void new1(void)
{
	system("cls");
	char ch;
	
	data=fopen(dict,"a");
	
	if(data==NULL)
	printf("File does not exist.");
	
	else
	do
	{
		gets(a[n].word);  /*added this statement to avoid gets() bug. The compiler wasn't taking input for first gets() statement. 
		That's why added it as a very first statement of this function so that the compiler starts taking input from the second gets() statement i.e. for words.*/
		
		printf("\n\nEnter word: ");
		gets(a[n].word);
		
		printf("\nEnter meaning: ");
		gets(a[n].mean);
		
		printf("\nEnter part of speech: ");
		gets(a[n].posp);
		
		printf("\nEnter sentence: ");
		gets(a[n].sent);
		
		fprintf(data,"%s\t%s\t%s\t%s\n", a[n].word, a[n].mean, a[n].posp, a[n].sent);
		n++;

		printf("\nAdd more words? (y/n)");
		
	}
	while((ch=getche())=='y');
	
	fclose(data);
}

void list(void)
{
	data=fopen(dict,"r");
	
	if(data==NULL)
	printf("File does not exist.");
	
	else
	{
		printf("\n________________________________________________________________________________\n");
		printf("\n%-15s %-15s%-15s\t\t%-50s\n","WORDS","MEANING","PARTS OF SPEECH","SENTENCE");
		printf("________________________________________________________________________________\n");
		while(fscanf(data,"%d",a[q].word) != EOF)  /*since EOF returns an integer value therefore used %d instead of %s coz char to int conversion is invalid*/             
		{
			fscanf(data,"%s\t%[^\n]s\t%[^\n]s\t%[^\n]s\n", &a[q].word, &a[q].mean, &a[q].posp, &a[q].sent);  /* [^\n] allows scanf() to take multi-word input until enter isn't pressed.*/
			printf("\n%-10s\t%15s\t%15s\t\t\t%s\n ",a[q].word, a[q].mean, a[q].posp ,a[q].sent);
			q++;
		}
	}
	fclose(data);
	printf("\nPress any key for main menu.");
	getch();
}


void search(void)
{
	system("cls");
	int w=0;
	char search[20];
	do
	{
		gets(search); //because of gets bug.
		printf("\n\nEnter word to search:");
		gets(search);
		data=fopen(dict,"r");
		if(data==NULL)
		printf("File does not exist.");
		else
		{
			while(fscanf(data,"%d",a[w].word) != EOF) //used %d instead of %s coz of invalid conversion from char to int
			{
				fscanf(data,"%s\t%[^\n]s\t%[^\n]s\t%[^\n]s\n", &a[w].word, &a[w].mean, &a[w].posp, &a[w].sent);
				if(strcmp(a[w].word,search)==0)
				{
					printf("\n________________________________________________________________________________\n");
					printf("\n%-15s\t%-15s\t%-15s\t\t%-50s\n","WORDS","MEANING","PARTS OF SPEECH","SENTENCE");
					printf("________________________________________________________________________________\n");
					printf("\n%-10s\t%15s\t%15s\t\t\t%s\n ",a[w].word, a[w].mean, a[w].posp ,a[w].sent);
					w++;
				} 
			} 
		}	
		fclose(data);
		printf("\n\nSearch more words?(y/n):");
	}
	while(getche()=='y');
}

void deletew(void)
{
	system("cls");
	char worddel[20];
	int i=0;
	FILE *data2;
	do
	{	
		data=fopen(dict,"r");
	
		gets(worddel);
		printf("\nEnter word: ");
		gets(worddel);
	
		data2=fopen("replica.txt","a");
		rewind(data);
	
		while((fscanf(data,"%s\t%[^\n]s\t%[^\n]s\t%[^\n]s\n", &a[i].word, &a[i].mean, &a[i].posp, &a[i].sent))!=EOF)
		{
			if(strcmpi(a[i].word, worddel)!=0)  //all the words from dict except the one which is being entered by the user for deletion, are copied on replica.text
			fprintf(data2,"%s\t%s\t%s\t%s\n", a[i].word, a[i].mean, a[i].posp, a[i].sent);
			i++;
		}
	
		fclose(data);
		fclose(data2);
	
		remove(dict); //deletes dict
		rename("replica.txt",dict); //renames replica.txt as dict
		printf("\nDelete more words?(y/n)");
	}
	while(getche()== 'y');
}

