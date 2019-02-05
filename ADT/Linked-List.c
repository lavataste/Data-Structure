#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Node
{
	char data;
	struct Node* next;
	struct Node* prev;
};
typedef struct Node NODE;
void Blank(char*, int);
void InsertStart(NODE*, NODE**, NODE**);
void InsertFirst(NODE*, NODE**);
void InsertMiddle(NODE*, NODE*);
void InsertLast(NODE*, NODE**);
void DeleteFirst(NODE*, NODE**);
void DeleteMiddle(NODE*);
void DeleteLast(NODE*, NODE**);
void DeleteLastOne(NODE*, NODE**, NODE**);
int GetIndex(NODE*, NODE*);
int DistinctionRange(int, NODE*, NODE*);
void Clear(NODE**, NODE**);
int main()
{
	NODE* node[100];
	NODE* head=0, *tail=0, *traverse=0, *cursor=0;
	NODE** hp=&head;
	NODE** tp=&tail;
	NODE** cp=&cursor;
	char command[50]={};
	int length=0, i=0, index=0, j=0, inlist=0, sum=0, distinction=0; 
		printf(
	"+a : add a (If you write like +aa, it ignores second a.)\n"
	"=a : Replace the element of current cursor to a (If you write like =aa, it ignored second a.)\n"
	"- : delete the element of current cursor\n"
	"< : move cursor to first element\n"
	"> : move cursor to last element\n"
	"N : move cursor to next element\n"
	"P : move cursor to previous element\n"
	"G : display the element of current cursor\n"
	"# : display the length of the list.\n"
	"nG : displaty the element of n sequence\n"
	"n=a : the element of n sequence replaced to a\n"
	"L : list all elements\n"
	"E : distinction of empty list.\n"
	"C : empty the list\n"
	"Q : quit the program.\n"
	);
	while(1)
	{
		printf("Enter the command.\n");
		gets(command); 
		length=strlen(command);
		Blank(command, length);
		length=strlen(command);
		for(i=0;i<length;i++)
		{
			traverse=head;
			if(command[i]=='+')
			{
				node[index]=(NODE*)malloc(sizeof(NODE));
				node[index]->data=command[i+1];
				if(command[i+1]==0)
				{
				}
				else if(head==0 && tail==0)
				{
					InsertStart(node[index], hp, tp);
					cursor=head;
				}
				else if(cursor->next!=0)
				{
					InsertMiddle(node[index], cursor);
					cursor=cursor->next;
				}
				else if(cursor->next==0)
				{
					InsertLast(node[index], tp);
					cursor=tail;
				}
/*				else if(cursor->prev==0 && cursor->next!=0)
				{
					InsertFirst(node[index], hp);
					cursor=head;
				}*/ //There is no situation to insert first list so I didn't include the code.
				i++;
				index++;
			}
			else if(command[i]=='l' || command[i]=='L')
			{
				if(cursor==0)
				{
					printf("There is no element.\n");
				}
				else
				{
					for(j=0;j<GetIndex(tail, head)+1;j++)
					{
						printf("%c ", traverse->data);
						traverse=traverse->next;
					}
					printf("\n");
				}
			}
			else if(command[i]=='g' || command[i]=='G')
			{
				if(head==0)
				{
					printf("There is no element.\n");
				}
				else
				{
					printf("The cursor is on the %c. The index is %d\n", cursor->data, GetIndex(cursor, head));
				}
			}
			else if(command[i]=='<')
			{
				if(head==0)
				{
					printf("There is no element.\n");
				}
				else
				{
					cursor=head;
				}
			}
			else if(command[i]=='>')
			{
				if(head==0)
				{
					printf("There is no element.\n");
				}
				else
				{
					cursor=tail;
				}
			}
			else if(command[i]=='N' || command[i]=='n')
			{
				if(head==0)
				{
					printf("There is no element.\n");
				}
				else if(cursor==tail)
				{
					printf("You can't get out the range. The %c%c%c is on the last node.\n", 34, cursor->data, 34);
				}
				else
				{
				cursor=cursor->next;
				}
			}
			else if(command[i]=='P' || command[i]=='p')
			{
				if(head==0)
				{
					printf("There is no element.\n");
				}
				else if(cursor==head)
				{
					printf("You can't get out the range. The %c%c%c is on the first node.\n", 34, cursor->data, 34);
				}
				else
				{
					cursor=cursor->prev;
				}
			}
			else if(command[i]=='-')
			{
				if(cursor==0)
				{
					printf("There is no element.\n");
				}
				else if(cursor->prev==0 && cursor->next!=0)
				{
					cursor=cursor->next;
					DeleteFirst(cursor->prev, hp);
				}
				else if(cursor->prev!=0 && cursor->next!=0)
				{
					cursor=cursor->next;
					DeleteMiddle(cursor->prev);
				}
				else if(cursor->prev!=0 && cursor->next==0)
				{
					cursor=cursor->prev;
					DeleteLast(cursor->next, tp);
				}
				else if(cursor->prev==0 && cursor->next==0)
				{
					DeleteLastOne(cursor, hp, tp);
					cursor=0;
				}
			}
			else if(command[i]=='=')
			{
				if(cursor==0)
				{
					printf("There is no element.\n");
				}
				else
				{
					cursor->data=command[i+1];
				}
			}
			else if(command[i]=='#')
			{
				if(head==0)
				{
					printf("0\n");
				}
				else
				{
					printf("%d\n", GetIndex(tail, head)+1);
				}
			}
			else if(command[i]>=49 && command[i]<=57)
			{
				sum=command[i]-48;
				distinction=DistinctionRange(sum, head, tail);
				if((command[i+1]=='g' || command[i+1]=='G'))
				{
					if(distinction==0)
					{
						for(j=0;j<command[i]-48-1;j++)
						{
							traverse=traverse->next;
						}
						printf("%c\n", traverse->data);
					}
					i++;
				}
				else if(command[i+1]=='=')
				{
					if(distinction==0)
					{
						for(j=0;j<command[i]-48-1;j++)
						{
							traverse=traverse->next;
						}
						traverse->data=command[i+2];
						cursor=traverse;
					}
					i=i+2;
				}
				else if(command[i+1]>=48 && command[i+1]<=57)
				{
					sum=(command[i]-48)*10+command[i+1]-48;  //dujari number yong
					distinction=DistinctionRange(sum, head, tail);
					if(command[i+2]=='g' || command[i+2]=='G')
					{
						if(distinction==0)
						{
							for(j=0;j<sum-1;j++)
							{
								traverse=traverse->next;
							}
							printf("%c\n", traverse->data);
						}
						i=i+2;
					}
					else if(command[i+2]=='=')
					{
						if(distinction==0)
						{
							for(j=0;j<sum-1;j++)
							{
								traverse=traverse->next;
							}
							traverse->data=command[i+3];
							cursor=traverse;
						}
						i=i+3;
					}	
				}	
			}
			else if(command[i]=='?')
			{
				inlist=0;
				if(head!=0)
				{
					for(j=0;j<GetIndex(tail, head)+1;j++)
					{
						if(traverse->data==command[i+1])
						{
							inlist++;
							cursor=traverse;
							printf("%d\n", j+1);
						}
						if(traverse!=tail)
						{
							traverse=traverse->next;
						}	 
					}
					if(inlist==0)
					{
						printf("-1\n");
						cursor=tail;
					}
				}
				else
				{
					printf("There is no elements.\n");
				}
				i++;
			}
			else if(strcmp(command, "C")==0)
			{
				Clear(hp, tp);
				cursor=0;
			}
			else if(command[i]=='e' || command[i]=='E')
			{
				if(head==0)
				{
					printf("True\n");
				}
				else
				{
					printf("False\n");
				}
			}
			else if(strcmp(command, "Q")==0)
			{
				printf("The program shutdown.");
				return 0;
			}
		}
	}
	return 0;
}
void Blank(char* array, int size)
{
	int i, j, k=1;
	for(i=0;i<size;i++)
	{
		if(*(array+i)==' ')
		{
			for(j=0;j<size-i-1;j++)
			{
				*(array+i+j)=*(array+i+j+1);
			}
			i--;
			*(array+size-k)=0;
			k--;
		}
	}
}
void InsertStart(NODE* node, NODE** hp, NODE** tp)
{
	*hp=node;
	*tp=node;
	node->prev=0;
	node->next=0;
}
void InsertFirst(NODE* node, NODE** hp)
{
	node->prev=0;
	node->next=*hp;
	*hp=node;
}
void InsertMiddle(NODE* node, NODE* cursor)
{
	cursor->next->prev=node;
	node->next=cursor->next;
	cursor->next=node;
	node->prev=cursor;
}
void InsertLast(NODE* node, NODE** tp)
{
	node->next=0;
	node->prev=*tp;
	(*tp)->next=node;	
	*tp=node;
}
int GetIndex(NODE* node, NODE* head)
{
	int i=0;
	for(i=0;i<200;i++)
	{
		if(head==node)
		{
			break;
		}
		else
		{
			head=head->next;
		}
	}
	return i;
}
void DeleteFirst(NODE* node, NODE** hp)
{
	*hp=node->next;
	node->next->prev=0;
	free(node);	
}
void DeleteMiddle(NODE* node)
{
	node->next->prev=node->prev;
	node->prev->next=node->next;
	free(node);
}
void DeleteLast(NODE* node, NODE** tp)
{
	*tp=node->prev;
	node->prev->next=0;
	free(node);
}
void DeleteLastOne(NODE* node, NODE** hp, NODE** tp)
{
	*hp=0;
	*tp=0;
	free(node);
}
int DistinctionRange(int number, NODE* head, NODE* tail) 
{
	if(number>=GetIndex(tail, head)+1)
	{
		if(head==tail && head!=0)
		{
			printf("There is only one element.\n");	
			return 1;					
		}
		else if(tail==0)
		{
			printf("There is no element.\n");
			return 1;
		}
		else
		{
			printf("There are only %d elements.\n", GetIndex(tail, head)+1);
			return 1;
		} 
	}
	return 0;
}
void Clear(NODE** hp, NODE** tp)
{
	int i, n;
	n=GetIndex(*tp, *hp);
	for(i=0;i<n;i++)
	{
		*tp=(*tp)->prev;
		free((*tp)->next);
	}
	free(*tp);
	*hp=0;
	*tp=0;
}
