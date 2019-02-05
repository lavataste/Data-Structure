#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct content
{
	char word[20];
	char meaning[100];
	struct content* next;
	struct content* prev;
};
typedef struct content CONTENT;
int ABC(CONTENT*, CONTENT*);
void MakeList(CONTENT*, CONTENT*, CONTENT**);
void MakeLastList(CONTENT*, CONTENT*);
void Delete(CONTENT*, CONTENT**);
void Initialize(CONTENT**, int*);
void PrintCommand();
int GetLastNumber(CONTENT*);
void PrintNextPrev(CONTENT*);
void FindAlphabet(CONTENT*, char);
int main()
{
	char command[20];
	CONTENT* c[200];
	CONTENT* header=0, *traverse=0, *current=0;
	CONTENT** hp=&header;
	int i, j, k, l, n, index=0;
	int* ip=&i;
	printf("It is dictionary program.\nYou can save the words and the meanings.\n\n");
	PrintCommand();
	while(1)
	{
		n=GetLastNumber(header);	//To print the number of words
		traverse=header;	//To traverse list, it initialize with header
		fflush(stdin);	//Remove the enter in buffer
		printf("\nEnter the command.\n");
		gets(command);
		if(strcmp(command, "e")==0 || strcmp(command, "E")==0)
		{
			printf("\nWrite the word you want save.\n");
			c[i]=(CONTENT*)malloc(sizeof(CONTENT));     
			gets(c[i]->word);
			printf("\nWrite the meaning.\n");
			gets(c[i]->meaning);
			if(i!=0) //To find the place of the new word
			{
				for(j=0;j<i;j++)
				{	
					l=ABC(c[i], traverse);
					if(l==1)
					{ 
						MakeList(c[i], traverse, hp);
						break;
					}
					else if(l==2)
					{
						printf("\nThere is already %c%s%c\n", 34, c[i]->word, 34);
						break;
					}
					else if(l==0)
					{
						if(traverse->next==0)
						{
							MakeLastList(c[i], header);
							break;
						}
					}
					traverse=traverse->next;	
				}
			i++;
			}	
			else //When the first enter, prev and next pointer must be NULL
			{
				c[0]->prev=0;
				c[0]->next=0;
				header=c[0];
				traverse=c[0];
				current=c[0];
				i++;
			}
		}
		else if(strcmp(command, "L")==0 || strcmp(command, "l")==0)
		{
			if(header==0)
			{
				printf("\nThere are no words.\n");
			}
			else
			{
			traverse=header;
			while(1) // Traverse pointer traverse from head pointer to last pointer
				{
					printf("\n%s\n\n", traverse->word);
					if(traverse->next==0)
					{
						break;
					}
					traverse=traverse->next;	
					j++;	
		 		}
			} 
		}
		else if(strcmp(command, "d")==0 || strcmp(command, "D")==0)
		{
			printf("\nWrite the word you want delete.\n");
			gets(command);
			k=0;
			for(j=0;j<i;j++)
			{
				if(strcmp(traverse->word, command)==0) // Compare word with command
				{
					printf("\nThe word %c%s%c is deleted\n", 34, traverse->word, 34); 
					Delete(traverse, hp);
					k++;
					break;
				}
				else
				{
					traverse=traverse->next;
				}
				
			}
			if(k==0)
			{
				printf("\nThere is no %c%s%c.\n", 34, command, 34);
			}
		}
		else if(strcmp(command, "I")==0 || strcmp(command, "i")==0)
		{
			printf("\nDo you want to really initialize? (Y/N)\n");
			gets(command);
			if(strcmp(command, "y")==0 || strcmp(command, "Y")==0)
			{			
				Initialize(hp, ip);
				printf("\nInitialization is done.\n");
			}
			else
			{
				printf("\nInitialization is canceled.\n");
			}
		}
		else if(strcmp(command, "s")==0 || strcmp(command, "S")==0)
		{
			printf("\nWhat the word do you want to search?\n");
			gets(command);
			for(j=0;j<i;j++)
			{
				if(strcmp(traverse->word, command)==0)
				{
					printf("Meaning : %s\n\n", traverse->meaning);
					PrintNextPrev(traverse);
					break;
				}
				else if(traverse->next==0 || traverse==0)
				{
					printf("There is no %c%s%c.\n", 34, command, 34);
					break;
				}
				else
				{
					traverse=traverse->next;
				}

			}
		}
		else if(strcmp(command, "c")==0 || strcmp(command, "C")==0)
		{
			PrintCommand();
		}
		else if(strcmp(command, "m")==0 || strcmp(command, "M")==0)
		{
			if(GetLastNumber(header)==0)
			{
				printf("\nThere is no word.\n");
			}
			else if(GetLastNumber(header)==1)
			{
				printf("\nThere is only one word.\n");
				printf("%s\nMeaning : %s\n\n", header->word, header->meaning);
			}
			else
			{
				printf("\nEnter the index you want to move. There are %d words.\n", GetLastNumber(header));
				scanf("%d", &index);
				if(index>GetLastNumber(header) || index<1)
				{
					printf("\nThe index is invalid.\n");
				}
				else
				{
					for(j=1;j<index;j++)
					{
						traverse=traverse->next;
					}
					printf("%s\nMeaning : %s\n\n", traverse->word, traverse->meaning);
					PrintNextPrev(traverse);
				}
			}
		}
		else if(strcmp(command, "f")==0 || strcmp(command, "F")==0)
		{
			printf("\nEnter the Alphabet you want to find.\n");
			gets(command);
			FindAlphabet(header, command[0]);
		}

		else
		{
			printf("\nInvalid command.\n");
		}
		
			j=0;
			traverse=header;
	}
	for(j=0;j<i;j++)
	{
		free(c[j]);
	}
	return 0;
}










int ABC(CONTENT* a, CONTENT* b)
{
	int length=0, i=0, r=3;
	int length_a=strlen(a->word);
	int length_b=strlen(b->word);
	char* word1, *word2;
	word1=(char*)malloc(20*sizeof(char));
	word2=(char*)malloc(20*sizeof(char));
	strcpy(word1, a->word);
	strcpy(word2, b->word);
	for(i=0;i<strlen(word1);i++)
	{
		if(word1[i]>=65 && word1[i]<=90)
		{
			word1[i]=word1[i]+32;
		}
	}
	for(i=0;i<strlen(word2);i++)
	{
		if(word2[i]>=65 && word2[i]<=90)
		{
			word2[i]=word2[i]+32;
		}
	}
	if(length_a>=length_b)
	{
		length=length_b;
	}
	else
	{
		length=length_a;
	}
	for(i=0;i<length;i++)
	{
		if(word1[i]<word2[i])
		{
			r=1;
			break;
		}
		else if(word1[i]>word2[i])
		{
			r=0;
			break;
		}
		else if(strcmp(word1, word2)==0)
		{
			r=2;
			break;
		}
		else if(i==length-1 && word1[i+1]==0)
		{
			r=1;
			break;
		}
		else if(i==length-1 && word2[i+1]==0)
		{
			r=0;
			break;
		}
	}
	free(word1);
	free(word2);
	return r;
}
void MakeList(CONTENT* a, CONTENT* b, CONTENT** hp)
{	
	if(b->prev!=0)
	{
		a->prev=b->prev;
		b->prev->next=a;
	}
	else
	{
		a->prev=0;
		*hp=a; 
	}
	a->next=b;
	b->prev=a;	
}	
void MakeLastList(CONTENT* a, CONTENT* header)
{
	int i;
	for(i=0;i<100;i++)
	{ 
		if(header->next==0)
		{ 
			break;
		}
		else
		{
			header=header->next;
		}
	}
	a->prev=header;
	a->next=0;
	header->next=a;
}
void Delete(CONTENT* traverse, CONTENT** hp)
{
	if(traverse->prev!=0)
	{
		traverse->prev->next=traverse->next;
	}
	else
	{
		if(traverse->next==0)
		{
			free(traverse);
			return;
		}
		*hp=traverse->next;
	}
	traverse->next->prev=traverse->prev;
	free(traverse);
}
void Initialize(CONTENT** hp, int* ip)
{
	CONTENT* traverse, *temp;
	traverse=*hp;
	int j;
	for(j=0;j<*ip;j++)
	{
		temp=traverse;
		if(traverse->next!=0)
		{
			traverse=traverse->next;
			free(temp);
		}
		else
		{
			free(temp);
			*hp=0;
			break;
		}
	}
	*ip=0;
}
void PrintCommand()
{
	printf(	"================================================================================================================\n"
			" Commands List\n"
			" E : Enter the word.\n"
			" D : Delete the word.\n"
			" S : Search the word.\n"
			" F : Find the word with Alphabet. (It is only work English words.)\n"
		    " L : List the all words.\n"
		    " M : Move to the word with index.\n"
			" I : Initialize the words.\n"
			" C : Show the commands list.\n"
		    "=================================================================================================================\n");
}
int GetNumber(CONTENT* header, char* command)
{
	int i;
	for(i=0;i<100;i++)
		{
			if(strcmp(header->word, command)==0)
			{
				return i+1;
			}
			else if(header->next==0)
			{
				return 0;
			}
			else
			{
				header=header->next;
			}
		}
	return 0;
}
int GetLastNumber(CONTENT* header)
{
	int i;
	if(header==0)
	{
		return 0;
	}
	for(i=0;i<100;i++)
		{
			if(header->next==0)
			{
				break;
			}
			else
			{
				header=header->next;
			}	
		}
	return i+1;
}
void PrintNextPrev(CONTENT* traverse)
{
	if(traverse->prev!=0 && traverse->next!=0)
	{
		printf("The previous word is %c%s%c.\n", 34, traverse->prev->word, 34);
		printf("The next word is %c%s%c.\n", 34, traverse->next->word, 34);
	}
	else if(traverse->prev==0 && traverse->next==0)
	{
		return;
	}
	else if(traverse->prev!=0 && traverse->next==0)
	{
		printf("The previous word is %c%s%c.\n", 34, traverse->prev->word, 34);
		printf("%c%s%c is the last word.\n", 34, traverse->word, 34);
	}
	else if(traverse->prev==0 && traverse->next!=0)
	{
		printf("%c%s%c is the first word.\n", 34, traverse->word, 34);
		printf("The next word is %c%s%c.\n", 34, traverse->next->word, 34);
	}
}
void FindAlphabet(CONTENT* header, char alphabet)
{
	int i=GetLastNumber(header);
	int j;
	int k=0;
	for(j=1;j<i;j++)
	{
		if(header->word[0]==alphabet || header->word[0]==alphabet+32 || header->word[0]==alphabet-32)
		{
			printf("%s\n\n", header->word);
			k++;	
		}
		header=header->next;
	}
	if(k==0)
	{
		printf("There are no words.\n");
	}
}
