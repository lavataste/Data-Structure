#define Max_Size 50
#include<stdio.h>
#include<string.h>
typedef struct
{
	char my_stack[Max_Size];
	int top;
	int count;
} STACK;

void Push(STACK*, char);
char Pop(STACK*);
void PrintCommand();
int main()
{
	char command[20];
	char temp;
	int length, count, count_2=0, repeat, size, judgement;
	STACK s;
	STACK save;
	s.top=-1;
	s.count=0;
	save.top=-1;
	save.count=0;
	printf("Welcome. The program is Inlab Exercise #03, the ADTs of stack.\nThe maker is ¿°ÅÂ¹Î.\n");    
	PrintCommand();
	while(1)
	{
		repeat=0, judgement=0;
		printf("Enter the command.\n");
		fflush(stdin);
		gets(command); // Get the command 
		length=strlen(command);
		for(count=0;count<length;count++) // Repeat the number of command string length
		{
			if(command[count]=='+')   // Create
			{
				Push(&s, command[count+1]);
				count++;	
			}
			else if(command[count]=='L' || command[count]=='l')
			{
				if(s.top==-1)
				{
					printf("The stack is empty.\n");
				}
				else
				{
					repeat=s.count;
					for(count_2=0;count_2<repeat;count_2++)
					{
						Push(&save, Pop(&s));
					}
					for(count_2=0;count_2<repeat;count_2++)
					{
						temp=Pop(&save);
						printf("%c ", temp);
						Push(&s, temp);
					}
					printf("\n");
				}
			}
			else if(command[count]=='P' || command[count]=='p')
			{
				temp=Pop(&s);
				printf("%c\n", temp);
				Push(&s, temp);
			}
			else if(command[count]=='-')
			{
				if(s.top==-1)
				{
					printf("Error. The stack is empty.\n");
				}
				else
				{
					printf("'%c' is poped.\n", Pop(&s));
				}
			}
			else if(command[count]=='F' || command[count]=='f')
			{
				if(s.top==Max_Size-1)
				{
					printf("True\n");
				}
				else
				{
					printf("False\n");
				}
			}
			else if(command[count]=='#')
			{
				printf("%d\n", s.count);
			}
			else if(command[count]>=49 && command[count]<=57)
			{
				if(command[count+1]=='-')
				{
					for(count_2=0;count_2<command[count]-48;count_2++)
					{
						Pop(&s);	
					}
				}
				count++;
			}
			else if(command[count]=='E' || command[count]=='e')
			{
				if(s.top==-1)
				{
					printf("True\n");
				}
				else
				{
					printf("False\n");
				}
			}
			else if(command[count]=='?')
			{
				repeat=s.count;
				for(count_2=0;count_2<repeat;count_2++)
				{
					temp=Pop(&s);
					if(temp==command[count+1])
					{
						printf("%d ", repeat-count_2);
						judgement++;
					}
					Push(&save, temp);
				}
				for(count_2=0;count_2<repeat;count_2++)
				{
					Push(&s, Pop(&save));
				}
				if(judgement==0)
				{
					printf("-1\n");
				}
				else
				{
					printf("\n");
				}
				count++;
			}
			else if(command[count]=='=')
			{
				if(s.top==-1)
				{
					printf("Error. The stack is empty.\n");
				}
				else
				{
					Pop(&s);
					Push(&s, command[count+1]);
					count++;
				}
			}
			else if(command[count]=='C' || command[count]=='c')
			{
				printf("Do you want to really initialize the stack? (Y/N)\n");
				scanf("%c", &temp);
				if(temp=='Y')
				{
					repeat=s.count;
					for(count_2=0;count_2<repeat;count_2++)
					{
						Pop(&s);
					}
				}
			}
			else if(command[count]=='Q' || command[count]=='q')
			{
				printf("Do you want to really quit the program? (Y/N)\n");
				scanf("%c", &temp);
				if(temp=='Y')
				{
					return 0;
				}
			}
			
			
		}
	}
	return 0; 
}




void Push(STACK* sp, char data)
{
	if(sp->top>Max_Size-1)
	{
		printf("The stack is full\n");
	}
	else
	{
		sp->top++;
		sp->my_stack[sp->top]=data;
		sp->count++;
	}
}
char Pop(STACK* sp)
{
	if(sp->top==-1)
	{
		printf("The stack is empty.\n");
		return 0;
	}
	else
	{
		sp->count--;
		return sp->my_stack[sp->top--];
	}
}
void PrintCommand()
{
	printf(
	"==========================================================================\n"
	"+a : add 'a' (If you write like +aa, it ignores second a.)\n"
	"=a : Replace the element of top element to 'a' (If you write like =aa, it ignored second a.)\n"
	"- : delete the element of top\n"
	"# : display the number of the elements in the stack.\n"
	"F : check whether the stack is full.\n"
	"E : check whether the stack is empty.\n"
	"P : display the top element.\n"
	"?a : check the sequence of element 'a' (If there is no 'a', return -1.)\n"
	"L : list all elements of the stack.\n"
	"C : empty the stack.\n"
	"Q : quit the program.\n"
	"==========================================================================\n"
	);
}
